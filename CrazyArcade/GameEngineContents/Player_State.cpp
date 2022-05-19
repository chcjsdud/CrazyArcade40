#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서

void Player::ReadyStart()
{
	AnimationName_ = "Ready_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::IdleStart()
{
	AnimationName_ = "Idle_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::MoveStart()
{
	AnimationName_ = "Move_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}


void Player::JumpStart()
{
}

void Player::DamagedStart()
{
}

void Player::LiveStart()
{
}

void Player::DieStart()
{
}

void Player::ReadyUpdate()
{
	if (PrevState_ != PlayerState::Ready)
	{
		if (true == PlayerAnimationRender_->IsEndAnimation())
		{
			//ChangeDirText_ = "Down";
			ChangeState(PlayerState::Idle);
			return;
		}
	}

}

void Player::IdleUpdate()
{
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
		return;
	}
}

void Player::MoveUpdate()
{
	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::Idle);
		return;
	}


	Move();

	StagePixelCheck(CurSpeed_);

}

void Player::JumpUpdate()
{
}

void Player::DamagedUpdate()
{
}

void Player::LiveUpdate()
{
}

void Player::DieUpdate()
{
}
