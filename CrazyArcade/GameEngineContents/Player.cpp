#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>

Player::Player()
    : CurSpeed_(0.f)
	, MaxSpeed_(0.f)
    , CurAttLength_(0.f)   
    , CurAttCount_(0)
	, MaxAttLength_(0.f)
	, MaxAttCount_(0)
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

	float MovePos = 280.f;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir.x = -MovePos;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir.x = MovePos;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir.y = -MovePos;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir.y = MovePos;
	}

	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * CurSpeed_);

}

void Player::ColMapUpdate()
{

}

void Player::StagePixelCheck(float _Speed)
{
	float4 CheckPos = GetPosition() + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;

	int Color = MapColImage_->GetImagePixel(CheckPos);
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * _Speed);
	}

	float4 DownPos = GetPosition() + float4{ 0.0f, 15.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;
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

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		// =============== 1P 이동 ===============
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MoveDown", VK_DOWN);

		// =============== 1P 공격 ===============
		GameEngineInput::GetInst()->CreateKey("Attack1P", VK_SPACE);
	}
}

void Player::Update()
{
	/*DirAnimationCheck();
	PlayerStateUpdate();*/
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
	std::string ChangeName;

	PlayerDir CheckDir_ = CurDir_;

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		CheckDir_ = PlayerDir::Right;
		ChangeDirText_ = "Right";
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		CheckDir_ = PlayerDir::Left;
		ChangeDirText_ = "Left";
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		CheckDir_ = PlayerDir::Up;
		ChangeDirText_ = "Up";
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		CheckDir_ = PlayerDir::Down;
		ChangeDirText_ = "Down";
	}

	if (CheckDir_ != CurDir_)
	{
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
		CurDir_ = CheckDir_;
	}
}

