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
	PlayerRideState_ = PlayerRideState::Max;

	MoveSpeed_ = CurSpeed_;
	CurSpeed_ = CurSpeed_;


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
	//GameEngineSound::SoundPlayOneShot("Jump.wav");
	AddAccTime(Time_);

	MoveDir = float4::ZERO;
	//2CheckDir_ = PlayerDir::None;

	AnimationName_ = "Idle_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::AttackStart()
{

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
	IsNiddle = false;
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
//---------------------------------------------------
void Player::OnRideStart()
{
	CheckDir_ = PlayerDir::None;

	if (PlayerRideState_ == PlayerRideState::Owl)
	{
		IsMove = false;
		AddAccTime(Time_);

		AnimationName_ = "OnOwl_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_);
	}	
	else if (PlayerRideState_ == PlayerRideState::Turtle)
	{
		IsMove = false;
		AddAccTime(Time_);

		AnimationName_ = "OnTurtle_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_);
	}
	else if (PlayerRideState_ == PlayerRideState::UFO)
	{
		IsMove = false;
		AddAccTime(Time_);

		AnimationName_ = "OnUFO_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_);
	}

}
void Player::OffRideStart()
{
	CheckDir_ = PlayerDir::None;
	TestTime_ = 1.6f;
	if (PlayerRideState_ == PlayerRideState::Owl)
	{
		IsMove = false;
		AddAccTime(Time_);

		AnimationName_ = "OnOwl_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_);
	}
	else if (PlayerRideState_ == PlayerRideState::Turtle)
	{
		IsMove = false;
		AddAccTime(Time_);

		AnimationName_ = "OnTurtle_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_);
	}
	else if (PlayerRideState_ == PlayerRideState::UFO)
	{
		IsMove = false;
		IsUFO = false;
		AddAccTime(Time_);

		AnimationName_ = "OnUFO_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_);
	}

}
void Player::IdleRideStart()
{
	if (PlayerRideState_ == PlayerRideState::Owl)
	{
		IsMove = true;
		ReSetAccTime();

		AnimationName_ = "IdleOwl_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	}
	else if (PlayerRideState_ == PlayerRideState::Turtle)
	{

		IsMove = true;
		ReSetAccTime();

		AnimationName_ = "IdleTurtle_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	}
	
}

void Player::RidingRideStart()
{
	if (PlayerRideState_ == PlayerRideState::Owl)
	{
		IsMove = true;
		CurSpeed_ = 5.5f;

		AnimationName_ = "RidingOwl_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	}
	else if (PlayerRideState_ == PlayerRideState::Turtle)
	{

		IsMove = true;
		CurSpeed_ = 2.f;

		AnimationName_ = "RidingTurtle_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	}
	else if (PlayerRideState_ == PlayerRideState::UFO)
	{
		IsMove = true;
		ReSetAccTime();
		CurSpeed_ = 8.5f;

		AnimationName_ = "RidingUFO_";
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	}
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
	DirAnimationCheck();
	StagePixelCheck(CurSpeed_);

	if (CurDir_ == PlayerDir::None)
	{
		CheckDir_ = PlayerDir::None;
		ChangeState(PlayerState::Idle);
		return;
	}

	MoveDir.y = -170.f * GameEngineTime::GetDeltaTime();

	if (CurDir_ == PlayerDir::Left)
	{
		MoveDir.x = -1.f;
	}
	else if (CurDir_ == PlayerDir::Right)
	{
		MoveDir.x = 1.f;
	}

	SetMove(MoveDir);

	if (0.6f < GetAccTime())
	{
		MoveDir.y += 10.f * GameEngineTime::GetDeltaTime();

		if (CurDir_ == PlayerDir::Left)
		{
			MoveDir.x = -0.7f;
		}
		else if (CurDir_ == PlayerDir::Right)
		{
			MoveDir.x = 0.7f;
		}

		SetMove(MoveDir);

		CheckDir_ = PlayerDir::None;
		ChangeState(PlayerState::Idle);
		return;
	}

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
	if (true == GameEngineInput::GetInst()->IsDown("Revival"))
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
	if (true == GameEngineInput::GetInst()->IsDown("Revival"))
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

void Player::OnRideUpdate()
{
	if (2.f < GetAccTime()
		&& PlayerAnimationRender_->IsEndAnimation())
	{
		if (PlayerRideState_ == PlayerRideState::UFO)
		{
			PlayerRideState_ = PlayerRideState::UFO;
			ChangeState(PlayerState::RidingRide);
			return;
		}
		else
		{
			ChangeState(PlayerState::IdleRide);
			return;
		} 
	}
}

void Player::OffRideUpdate()
{
	CurSpeed_ = MoveSpeed_;
	
	TestTime_ -= 1.0f * GameEngineTime::GetDeltaTime();
	IsInvincible = true;

	if (0.0f >= TestTime_)
	{
		IsInvincible = false;
		ChangeState(PlayerState::Idle);
		CurState_ = PlayerState::Idle;
		return;
	}
}


void Player::IdleRideUpdate()
{
	DirAnimationCheck();

	Move(CurSpeed_);
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::RidingRide);
		return;
	}


	if (true == IsAttackKey())
	{
		Attack();
	}
}

void Player::RidingRideUpdate()
{
	Move(CurSpeed_);
	DirAnimationCheck();

	if (false == IsMoveKey()&& PlayerRideState_ != PlayerRideState::UFO)
	{
		ChangeState(PlayerState::IdleRide);
		return;
	}


	if (true == IsAttackKey())
	{
		Attack();
	}

	StagePixelCheck(CurSpeed_);
}

void Player::Attack()
{
	float4 ModifyPos = float4{ -20.f, -20.f };

	if (Type == PlayerType::Player1)
	{ 
		
		if (Player::MainPlayer_1->CurAttCount_ <= Boom_->ReturnPlayer1BoomCount())
		{
			return;
		}

		if (BlockType::Max == CheckBlockTile(MainPlayer_1->GetPosition() + ModifyPos))
		{
			GameEngineSound::SoundPlayOneShot("Attack.mp3");

			Boom_->CreateBoom(MainPlayer_1->GetPosition() + ModifyPos, Player::MainPlayer_1->CurAttPower_, 1);
		}
		else if (BlockType::BushBlock == CheckBlockTile(MainPlayer_1->GetPosition() + ModifyPos))
		{
			GameEngineSound::SoundPlayOneShot("Attack.mp3");

			Boom_->CreateBoom(MainPlayer_1->GetPosition() + ModifyPos, Player::MainPlayer_1->CurAttPower_, 1);
		}
		else
			return;
	}
	

	if (Type == PlayerType::Player2)
	{
		Boom_->SetMapTile(MapTile_);
		if (Player::MainPlayer_2->CurAttCount_ <= Boom_->ReturnPlayer2BoomCount())
		{
			return;
		}

		if (BlockType::Max == CheckBlockTile(MainPlayer_2->GetPosition() + ModifyPos))
		{
			GameEngineSound::SoundPlayOneShot("Attack.mp3");
			Boom_->CreateBoom(MainPlayer_2->GetPosition() + ModifyPos, Player::MainPlayer_2->CurAttPower_, 2);
		}
		else if (BlockType::BushBlock == CheckBlockTile(MainPlayer_2->GetPosition() + ModifyPos))
		{
			GameEngineSound::SoundPlayOneShot("Attack.mp3");

			Boom_->CreateBoom(MainPlayer_2->GetPosition() + ModifyPos, Player::MainPlayer_2->CurAttPower_, 2);
		}
		else
			return;
	}
}
