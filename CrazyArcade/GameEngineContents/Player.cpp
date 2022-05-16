#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Player::Player()
    : Speed_(100.f)
    , AttackLength_(20.f)   
    , AttackCount_(1.f)
    , MoveDir(float4::ZERO)
    , PlayerAnimationRender_(nullptr)
    , CurState_(PlayerState::Idle)
    , CurDir_(PlayerDir::Down)
	, PlayerCollision_(nullptr)
{

}
Player::~Player()
{

}

void Player::Move()
{
	MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir = float4::UP;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir = float4::DOWN;
	}
}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Player::Start()
{
	PlayerCollision_ = CreateCollision("PlayerHitBox", { 80, 80 });

	PlayerAnimationRender_ = CreateRenderer();
	PlayerAnimationRender_->SetPivotType(RenderPivot::BOT);
	PlayerAnimationRender_->SetPivot({ 0.f, 30.f });



	AnimationName_ = "Move_";
	PlayerAnimationRender_->ChangeAnimation("Move_Down");


	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		// =============== 1P 이동 ===============
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MoveDown", VK_DOWN);

		// =============== 1P 공격 ===============
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_SPACE);
	}
}

void Player::Update()
{
	DirAnimationCheck();
	PlayerStateUpdate();
}

void Player::Render()
{
}

bool Player::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveRight") &&
		false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
		false == GameEngineInput::GetInst()->IsPress("MoveDown")
		)
	{
		return false;
	}

	return true;
}

void Player::ChangeState(PlayerState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Move:
			MoveStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Damaged:
			DamagedStart();
			break;
		case PlayerState::Live:
			LiveStart();
			break;
		case PlayerState::Die:
			DieStart();
			break;
		}
	}

	CurState_ = _State;
}

void Player::PlayerStateUpdate()
{
	switch (CurState_)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Move:
		MoveUpdate();
		break;
	case PlayerState::Jump:
		JumpUpdate();
		break;
	case PlayerState::Damaged:
		DamagedUpdate();
		break;
	case PlayerState::Live:
		LiveUpdate();
		break;
	case PlayerState::Die:
		DieUpdate();
		break;
	}
}

void Player::DirAnimationCheck()
{
}

