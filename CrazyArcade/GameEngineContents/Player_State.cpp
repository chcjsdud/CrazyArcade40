#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineLevel.h>
#include "MapGameObject.h"
#include "MapBackGround.h"


void Player::WaitStart()
{
}

void Player::ReadyStart()
{
	IsMove = false;

	AnimationName_ = "Ready_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ /*+ ChangeDirText_*/);
}

void Player::IdleStart()
{
	IsMove = true;
	ReSetAccTime();

	if (true == IsDevil)
	{
		AnimationName_ = "Idle_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Devil");
	}
	else
	{
		AnimationName_ = "Idle_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	}

}

void Player::MoveStart()
{
	IsMove = true;

	if (true == IsDevil)
	{
		AnimationName_ = "Move_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Devil");
	}
	else
	{
		AnimationName_ = "Move_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	}

}


void Player::JumpStart()
{
	AnimationName_ = "Jump";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::AttackStart()
{
	AttMoveTime_ += GameEngineTime::GetDeltaTime();

	if (Type == PlayerType::Player1)
	{
		if (Player::MainPlayer_1->CurAttCount_ > Boom_->ReturnPlayer1BoomCount())
		{
			GameEngineSound::SoundPlayOneShot("Attack.mp3");
		}
	}
	else if (Type == PlayerType::Player2)
	{
		if (Player::MainPlayer_2->CurAttCount_ > Boom_->ReturnPlayer2BoomCount())
		{
			GameEngineSound::SoundPlayOneShot("Attack.mp3");
		}
	}
}

void Player::DamagedStartStart()
{
	AnimationName_ = "DamagedStart_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);

	GameEngineSound::SoundPlayOneShot("Damaged.wav");
}

void Player::DamagedStart()
{
	IsMove = false;
	MoveDir = float4::ZERO;

	AddAccTime(Time_);

	AnimationName_ = "Damaged_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);
}

void Player::RevivalStart()
{
	IsMove = false;
	MoveDir = float4::ZERO;

	AnimationName_ = "Revival_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);

	CheckDir_ = PlayerDir::None;

	GameEngineSound::SoundPlayOneShot("Revival.mp3");
}

void Player::FadeStart()
{
	IsMove = false;
	MoveDir = float4::ZERO;

	ReSetAccTime();
	AddAccTime(Time_);

	AnimationName_ = "Fade_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);
}


void Player::DieStart()
{
	IsMove = false;
	MoveDir = float4::ZERO;
	IsLive = false;

	ReSetAccTime();
	AddAccTime(Time_);

	AnimationName_ = "Die_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);

	GameEngineSound::SoundPlayOneShot("Die.mp3");
}

void Player::OnOwlStart()
{
	IsMove = false;
	AddAccTime(Time_);

	AnimationName_ = "OnOwl_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);
}

void Player::OnTurtleStart()
{
	IsMove = false;
	AddAccTime(Time_);

	AnimationName_ = "OnTurtle_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);
}

void Player::OnUFOStart()
{
	IsMove = false;
	AddAccTime(Time_);

	AnimationName_ = "OnUFO_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);
}

void Player::OffOwlStart()
{
	IsMove = false;
	AddAccTime(Time_);

	AnimationName_ = "OnOwl_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);
}

void Player::OffTurtleStart()
{
	IsMove = false;
	AddAccTime(Time_);

	AnimationName_ = "OnTurtle_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);
}

void Player::OffUFOStart()
{
	IsMove = false;
	AddAccTime(Time_);

	AnimationName_ = "OnUFO_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);
}

void Player::IdleOwlStart()
{
	IsMove = true;
	ReSetAccTime();

	AnimationName_ = "IdleOwl_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_+ ChangeDirText_);
}

void Player::IdleTurtleStart()
{
	IsMove = true;
	ReSetAccTime();

	AnimationName_ = "IdleTurtle_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::RidingOwlStart()
{
	IsMove = true;
	CurSpeed_ = 5.5f;

	AnimationName_ = "RidingOwl_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::RidingTurtleStart()
{
	IsMove = true;
	CurSpeed_ = 2.f;

	AnimationName_ = "RidingTurtle_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::RidingUFOStart()
{
	IsMove = true;
	ReSetAccTime();
	CurSpeed_ = 8.5f;

	AnimationName_ = "RidingUFO_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::WaitUpdate()
{
}

void Player::ReadyUpdate()
{
	if (true == PlayerAnimationRender_->IsEndAnimation())
	{

		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::IdleUpdate()
{
	DirAnimationCheck();

	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == IsAttackKey())
	{
		ChangeState(PlayerState::Attack);
		return;
	}
	
	Move(CurSpeed_);
}

void Player::MoveUpdate()
{
	DirAnimationCheck();

	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	if (true == IsAttackKey())
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	Move(CurSpeed_);

	StagePixelCheck(CurSpeed_);
}

void Player::JumpUpdate()
{
}

void Player::AttackUpdate()
{
	Attack();

	ChangeState(PlayerState::Move);
	return;
}

void Player::DamagedStartUpdate()
{
	if (PlayerAnimationRender_->IsEndAnimation())
	{
		ChangeState(PlayerState::Damaged);
		return;
	}
}

void Player::DamagedUpdate()
{
	if (true == IsItemKey())
	{
		ChangeState(PlayerState::Revival);
		return;
	}

	Move(CurSpeed_);
	StagePixelCheck(0.2f);

	if (6.f < GetAccTime())
	{
		ChangeState(PlayerState::Fade);
		return;
	}

	//if (PlayerAnimationRender_->IsEndAnimation())
	//{
	//	ChangeState(PlayerState::Fade);
	//	return;
	//}

}


void Player::RevivalUpdate()
{
	if (PlayerAnimationRender_->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
		ChangeDirText_ = "Down";
		return;
	}
}

void Player::FadeUpdate()
{
	if (true == IsItemKey())
	{
		ChangeState(PlayerState::Revival);
		return;
	}

	// 1.5ÃÊ ÈÄ -> Die
	if (2.f < GetAccTime())
	{
		ChangeState(PlayerState::Die);
		return;
	}

	StagePixelCheck(0.2f);
}

void Player::DieUpdate()
{
	if (PlayerAnimationRender_->IsEndAnimation()
		&& 4.f < GetAccTime())
	{
		Off();
		//Death();
	}
}

void Player::OnOwlUpdate()
{
	if (2.f < GetAccTime())
	{
		ChangeState(PlayerState::IdleOwl);
		return;
	}
}

void Player::OnTurtleUpdate()
{
	if (2.f < GetAccTime())
	{
		ChangeState(PlayerState::IdleTurtle);
		return;
	}
}

void Player::OnUFOUpdate()
{
	if (2.f < GetAccTime())
	{
		ChangeState(PlayerState::RidingUFO);
		return;
	}
}

void Player::OffOwlUpdate()
{
	if (2.f < GetAccTime())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::OffTurtleUpdate()
{
	if (2.f < GetAccTime())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::OffUFOUpdate()
{
	if (2.f < GetAccTime())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::IdleOwlUpdate()
{
	DirAnimationCheck();

	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::RidingOwl);
		return;
	}

	if (true == IsAttackKey())
	{
		Attack();
	}
}

void Player::IdleTurtleUpdate()
{
	DirAnimationCheck();

	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::RidingTurtle);
		return;
	}

	if (true == IsAttackKey())
	{
		Attack();
	}
}

void Player::RidingOwlUpdate()
{
	Move(CurSpeed_);
	DirAnimationCheck();

	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::IdleOwl);
		return;
	}

	if (true == IsAttackKey())
	{
		Attack();
	}

	StagePixelCheck(CurSpeed_);
}

void Player::RidingTurtleUpdate()
{
	Move(CurSpeed_);
	DirAnimationCheck();

	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::IdleTurtle);
		return;
	}

	if (true == IsAttackKey())
	{
		Attack();
	}


	StagePixelCheck(CurSpeed_);
}

void Player::RidingUFOUpdate()
{
	Move(CurSpeed_);
	DirAnimationCheck();

	if (true == IsAttackKey())
	{
		Attack();
	}

	StagePixelCheck(CurSpeed_);

	IsMove = true;
}

void Player::Attack()
{
	float4 ModifyPos = float4{ -20.f, -20.f };

	if (Type == PlayerType::Player1)
	{ 
		Boom_->SetMapTile(MapTile_);
		if (Player::MainPlayer_1->CurAttCount_ <= Boom_->ReturnPlayer1BoomCount())
		{
			return;
		}

		GameEngineSound::SoundPlayOneShot("Attack.mp3");
		Boom_->CreateBoom(MainPlayer_1->GetPosition() + ModifyPos, Player::MainPlayer_1->CurAttPower_,1);
	}
	

	if (Type == PlayerType::Player2)
	{
		Boom_->SetMapTile(MapTile_);
		if (Player::MainPlayer_2->CurAttCount_ <= Boom_->ReturnPlayer2BoomCount())
		{
			return;
		}

		GameEngineSound::SoundPlayOneShot("Attack.mp3");
		Boom_->CreateBoom(MainPlayer_2->GetPosition() + ModifyPos, Player::MainPlayer_2->CurAttPower_,2);
	}
}
