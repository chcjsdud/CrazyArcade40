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
}

void Player::LiveStart()
{
}

void Player::DieStart()
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

	if (true == GameEngineInput::GetInst()->IsDown("1PAttack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("2PAttack"))
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
		Boom_->SetMapTile(MapTile_);
		Boom_ = GetLevel()->CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
		Boom_->CreateBoom(MainPlayer_1->GetPosition(), 3);
	}
	
	if (Type == PlayerType::Player2)
	{
		Boom_->SetMapTile(MapTile_);
		Boom_ = GetLevel()->CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
		Boom_->CreateBoom(MainPlayer_2->GetPosition(), 3);
	}

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
