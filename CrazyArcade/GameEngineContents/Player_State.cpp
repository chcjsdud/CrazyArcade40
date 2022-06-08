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
}

void Player::AttackStart()
{
	AttMoveTime_ += GameEngineTime::GetDeltaTime();
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
	//if (true == IsMove)
	//{
	//	
	//}


	StagePixelCheck(CurSpeed_);
}

void Player::JumpUpdate()
{
}

void Player::AttackUpdate()
{
	float4 ModifyPos = float4{ -20.f, -20.f };

	if (Type == PlayerType::Player1)
	{
		Boom_ = GetLevel()->CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
		Boom_->SetMapTile(MapTile_);

		Boom_->CreateBoom(MainPlayer_1->GetPosition() + ModifyPos, Player::MainPlayer_1->CurAttPower_);

		//BlockType block = Boom->CheckTile(MainPlayer_1->GetPosition());
		//체크타일이 웨이브면 -> Damaged

		ChangeState(PlayerState::Move);
		return;

	}

	if (Type == PlayerType::Player2)
	{
		Boom_ = GetLevel()->CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
		Boom_->SetMapTile(MapTile_);
		Boom_->CreateBoom(MainPlayer_2->GetPosition() + ModifyPos, Player::MainPlayer_2->CurAttPower_);

		ChangeState(PlayerState::Move);
		return;
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

	Move(CurSpeed_);
	StagePixelCheck(0.2f);

	if (5.f < GetAccTime())
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

	// 1.5초 후 -> Die
	//if (2.f < GetAccTime())
	//{
	//	ChangeState(PlayerState::Die);
	//	return;
	//}


	
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
