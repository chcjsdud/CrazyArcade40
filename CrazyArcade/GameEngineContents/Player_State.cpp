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

void Player::AttackStart()
{
}

void Player::DamagedStart()
{
	AnimationName_ = "Damaged_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);
}

void Player::RevivalStart()
{
	AnimationName_ = "Revival_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);
}

void Player::FadeStart()
{
	AnimationName_ = "Fade_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);
}

void Player::DieStart()
{
	AnimationName_ = "Die_";
	PlayerAnimationRender_->ChangeAnimation(AnimationName_);
}

void Player::IdeOwlStart()
{
}

void Player::IdleTurtleStart()
{
}

void Player::RidingOwlStart()
{
}

void Player::RidingTurtleStart()
{
}

void Player::RidingUFOStart()
{
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
}

void Player::MoveUpdate()
{
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


	Move();

	StagePixelCheck(CurSpeed_);
}

void Player::JumpUpdate()
{
}

void Player::AttackUpdate()
{
	
	if (Type == PlayerType::Player1)
	{
		Boom_ = GetLevel()->CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
		Boom_->SetMapTile(MapTile_);
		Boom_->CreateBoom(MainPlayer_1->GetPosition() - float4({25,30}), 3);

		//BlockType block = Boom->CheckTile(MainPlayer_1->GetPosition());
		//체크타일이 웨이브면 -> Damaged

		ChangeState(PlayerState::Idle);
		return;
	
	}
	
	if (Type == PlayerType::Player2)
	{
		Boom_ = GetLevel()->CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
		Boom_->SetMapTile(MapTile_);
		Boom_->CreateBoom(MainPlayer_2->GetPosition(), 3);
	}

	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
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

	if (4.f < GetAccTime())
	{
		ChangeState(PlayerState::Die);
		return;
	}
}

void Player::RevivalUpdate() 
{
	if (PlayerAnimationRender_->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
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

	// 1.5초 후 -> Die
	if (1.5f < GetAccTime())
	{
		ChangeState(PlayerState::Die);
		return;
	}

}

void Player::DieUpdate()
{
}

void Player::IdleOwlUpdate()
{
}

void Player::IdleTurtleUpdate()
{
}

void Player::RidingOwlUpdate()
{
}

void Player::RidingTurtleUpdate()
{
}

void Player::RidingUFOUpdate()
{
}
