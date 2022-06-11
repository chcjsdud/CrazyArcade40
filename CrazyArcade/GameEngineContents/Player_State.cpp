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

	AnimationName_ = "Idle_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::MoveStart()
{
	IsMove = true;

	AnimationName_ = "Move_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}


void Player::JumpStart()
{
	AnimationName_ = "Jump";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::AttackStart()
{
	AttMoveTime_ += GameEngineTime::GetDeltaTime();

	GameEngineSound::SoundPlayOneShot("Attack.mp3");
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
}

void Player::OnTurtleStart()
{
}

void Player::OnUFOStart()
{
}

void Player::OffOwlStart()
{
}

void Player::OffTurtleStart()
{
}

void Player::OffUFOStart()
{
}

void Player::IdleOwlStart()
{
	AnimationName_ = "IdleOwl_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_+ ChangeDirText_);
}

void Player::IdleTurtleStart()
{
	AnimationName_ = "IdleTurtle_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::RidingOwlStart()
{
	CurSpeed_ = 5.f;

	AnimationName_ = "RidingOwl_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::RidingTurtleStart()
{
	CurSpeed_ = 1.f;

	AnimationName_ = "RidingTurtle_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::RidingUFOStart()
{
	CurSpeed_ = 10.f;

	AnimationName_ = "IdleUFO_";
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


	//if (true == IsMoveKey())
	//{
	//	ChangeState(PlayerState::Move);
	//	return;
	//}

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
		Death();
	}
}

void Player::OnOwlUpdate()
{
}

void Player::OnTurtleUpdate()
{
}

void Player::OnUFOUpdate()
{
}

void Player::OffOwlUpdate()
{
}

void Player::OffTurtleUpdate()
{
}

void Player::OffUFOUpdate()
{
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

	Move(CurSpeed_);

	StagePixelCheck(CurSpeed_);
}

void Player::RidingTurtleUpdate()
{
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

	Move(CurSpeed_);

	StagePixelCheck(CurSpeed_);
}

void Player::RidingUFOUpdate()
{
	DirAnimationCheck();

	if (true == IsAttackKey())
	{
		Attack();
	}


	Move(CurSpeed_);
	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * CurSpeed_);

	IsMove = true;
}
