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
	, Collision1P_(nullptr)
	, Collision2P_(nullptr)
	, Type(PlayerType::Max)
	, BazziRenderer_(nullptr)
	, DaoRenderer_(nullptr)
	, MapColImage_(nullptr)
	, CurCharacter(Character::MAX)
	, IsDebug(false)
	, CurrentLevel_("")
{

}
Player::~Player()
{

}

void Player::DebugModeSwitch()
{
	if (true == GameEngineInput::GetInst()->IsDown("DebugMode") && true == IsDebug)
	{
		GetLevel()->IsDebugModeOff();
		IsDebug = false;
	}
	else if(true == GameEngineInput::GetInst()->IsDown("DebugMode") && false == IsDebug)
	{
		GetLevel()->IsDebugModeOn();
		IsDebug = true;
	}

}

void Player::Move()
{
	MoveDir = float4::ZERO;

	float MovePos = 280.f;

	if (Type == PlayerType::Player1)
	{
		if (true == GameEngineInput::GetInst()->IsPress("1PLeft"))
		{
			MoveDir.x = -MovePos;
		}
		else if (true == GameEngineInput::GetInst()->IsPress("1PRight"))
		{
			MoveDir.x = MovePos;
		}
		else if (true == GameEngineInput::GetInst()->IsPress("1PUp"))
		{
			MoveDir.y = -MovePos;
		}
		else if (true == GameEngineInput::GetInst()->IsPress("1PDown"))
		{
			MoveDir.y = MovePos;
		}
	}
	else
	{
		if (true == GameEngineInput::GetInst()->IsPress("2PLeft"))
		{
			MoveDir.x = -MovePos;
		}
		else if (true == GameEngineInput::GetInst()->IsPress("2PRight"))
		{
			MoveDir.x = MovePos;
		}
		else if (true == GameEngineInput::GetInst()->IsPress("2PUp"))
		{
			MoveDir.y = -MovePos;
		}
		else if (true == GameEngineInput::GetInst()->IsPress("2PDown"))
		{
			MoveDir.y = MovePos;
		}
	}



	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * CurSpeed_);

}

void Player::PlayerInfoUpdate()
{
	//SpeedUpdate();
	//AttackCountUpdate();
	//AttackLengthUpdate();
}

void Player::SpeedUpdate()
{
}

void Player::AttackCountUpdate()
{
}

void Player::AttackLengthUpdate()
{
}

void Player::CharTypeUpdate()
{
	switch (CurCharacter)
	{
	case Character::BAZZI:
	{
		BazziRenderer_->On();
		PlayerAnimationRender_ = BazziRenderer_;
		PlayerAnimationRender_->On();

		SetSpeed(1.f);
		SetAttCount(1);
		SetAttLength(10.f);			// 일단 10배

		SetMaxSpeed(90.f);
		SetMaxAttCount(6);
		SetMaxAttLength(70.f);

	}
		break;
	case Character::DAO:
	{
		DaoRenderer_->On();
		PlayerAnimationRender_ = DaoRenderer_;
		PlayerAnimationRender_->On();

		SetSpeed(1.f);
		SetAttCount(1);
		SetAttLength(10.f);			// 일단 10배

		SetMaxSpeed(90.f);
		SetMaxAttCount(6);
		SetMaxAttLength(70.f);
	}
		break;
	}

}

void Player::ColMapUpdate()
{
	CurrentLevel_ = GetCurrentLevel();

	//if (nullptr == MapColImage_)
	//{
	//	return;
	//}
	//	

	// ====================================== 테스트 레벨
	if (CurrentLevel_ == "PlayerTeamTest")
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Camp_ColMap.bmp");
	}


	if (CurrentLevel_ == "CampLevel")
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Camp_ColMap.bmp");
	}
	else if (CurrentLevel_ == "VillageLevel")
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Village_Col.bmp");
	}
	else if (CurrentLevel_ == "CemetoryLevel")
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Cemetory_ColMap.bmp");
	}
	else if (CurrentLevel_ == "Monster1Level")
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("MonsterStage1_ColMap.bmp");
	}
	else if (CurrentLevel_ == "Monster2Level")
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("MonsterStage2_ColMap.bmp");
	}
	else if (CurrentLevel_ == "BossLevel")
	{
		// ****** 보스레벨 ColMap 수정 필요 
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Camp_ColMap.bmp");
	}
	else
		return;
}

void Player::StagePixelCheck(float _Speed)
{
	//float4 LeftPos = GetPosition() + float4{ -5.f, 0.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;
	//float4 RightPos = GetPosition() + float4{ 15.f, 0.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;
	//float4 UpPos = GetPosition() + float4{ 0.0f, -15.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;
	//float4 DownPos = GetPosition() + float4{ 0.0f, 15.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;

	int LeftCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ -20.f, 0.f });
	int RightCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ 20.f, 0.f });
	int UpCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ 0.f, -20.f });
	int DownCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ 0.f, 20.f });
	
	//int LeftColor = MapColImage_->GetImagePixel(LeftPos);
	//int RightColor = MapColImage_->GetImagePixel(RightPos);
	//int UpColor = MapColImage_->GetImagePixel(UpPos);
	//int DownColor = MapColImage_->GetImagePixel(DownPos);

	//if (RGB(0, 0, 0) != LeftColor
	//	&& RGB(0, 0, 0) != RightColor
	//	&& RGB(0, 0, 0) != UpColor
	//	&& RGB(0, 0, 0) != DownColor)
	//{
	//	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * _Speed);
	//}
	if (RGB(0, 0, 0) == LeftCheck)
	{
		MoveDir.x = 1.f;
	}
	else if (RGB(0, 0, 0) != RightCheck)
	{
		MoveDir.x = -1.f;
	}
	else if (RGB(0, 0, 0) != UpCheck)
	{
		MoveDir.y = -1.f;
	}
	else if (RGB(0, 0, 0) != DownCheck)
	{
		MoveDir.y = 1.f;
	}
}

void Player::CollisionResultUpdate()
{

}

void Player::PlayerCollisionUpdate()
{
	if (Type == PlayerType::Player1)
	{
		Collision1P_->On();
	}
	else
	{
		Collision2P_->On();
	}
}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Player::Start()
{
	Collision1P_ = CreateCollision("1PColl", { 80, 80 });
	Collision1P_->Off();

	Collision2P_ = CreateCollision("2PColl", { 80, 80 });
	Collision2P_->Off();



	PlayerAnimationRender_ = CreateRenderer();
	PlayerAnimationRender_->SetPivotType(RenderPivot::BOT);
	PlayerAnimationRender_->SetPivot({ 0.f, 30.f });
	PlayerAnimationRender_->Off();

	// BAZZI
	{
		GameEngineImage* Left = GameEngineImageManager::GetInst()->Find("Left.bmp");
		Left->CutCount(6, 1);
		GameEngineImage* Right = GameEngineImageManager::GetInst()->Find("Right.bmp");
		Right->CutCount(6, 1);
		GameEngineImage* Down = GameEngineImageManager::GetInst()->Find("Down.bmp");
		Down->CutCount(8, 1);
		GameEngineImage* Up = GameEngineImageManager::GetInst()->Find("Up.bmp");
		Up->CutCount(8, 1);

		// 애니메이션
		
		BazziRenderer_ = CreateRenderer();
		BazziRenderer_->SetPivotType(RenderPivot::BOT);
		BazziRenderer_->SetPivot({ 0.f, 30.f });

		// Idle
		BazziRenderer_->CreateAnimation("Left.bmp", "Idle_Left", 0, 0, 1.f, false);
		BazziRenderer_->CreateAnimation("Right.bmp", "Idle_Right", 0, 0, 1.f, false);
		BazziRenderer_->CreateAnimation("Down.bmp", "Idle_Down", 0, 0, 1.f, false);
		BazziRenderer_->CreateAnimation("Up.bmp", "Idle_Up", 0, 0, 1.f, false);

		// Move
		BazziRenderer_->CreateAnimation("Left.bmp", "Move_Left", 0, 5, 0.09f, true);
		BazziRenderer_->CreateAnimation("Right.bmp", "Move_Right", 0, 5, 0.09f, true);
		BazziRenderer_->CreateAnimation("Down.bmp", "Move_Down", 0, 7, 0.09f, true);
		BazziRenderer_->CreateAnimation("Up.bmp", "Move_Up", 0, 7, 0.09f, true);

		AnimationName_ = "Idle_";
		BazziRenderer_->ChangeAnimation("Idle_Down");
		BazziRenderer_->Off();
		
	}

	

	///////////// 테스트
	{
		DaoRenderer_ = CreateRenderer();
		DaoRenderer_->SetPivotType(RenderPivot::BOT);
		DaoRenderer_->SetPivot({ 0.f, 30.f });

		GameEngineImage* Left = GameEngineImageManager::GetInst()->Find("Monster.bmp");
		Left->CutCount(10, 7);
		DaoRenderer_->CreateAnimation("Monster.bmp", "Move_Left", 0, 1, 0.2f, true);
		DaoRenderer_->CreateAnimation("Monster.bmp", "Move_Right", 2, 3, 0.2f, true);
		DaoRenderer_->CreateAnimation("Monster.bmp", "Move_Up", 4, 5, 0.2f, true);
		DaoRenderer_->CreateAnimation("Monster.bmp", "Move_Down", 16, 17, 0.2f, true);

		// Idle
		DaoRenderer_->CreateAnimation("Monster.bmp", "Idle_Left", 0, 0, 1.f, false);
		DaoRenderer_->CreateAnimation("Monster.bmp", "Idle_Right", 0, 0, 1.f, false);
		DaoRenderer_->CreateAnimation("Monster.bmp", "Idle_Down", 0, 0, 1.f, false);
		DaoRenderer_->CreateAnimation("Monster.bmp", "Idle_Up", 0, 0, 1.f, false);



		AnimationName_ = "Move_";
		DaoRenderer_->ChangeAnimation("Move_Down");

		DaoRenderer_->Off();
	}
	



	if(false == GameEngineInput::GetInst()->IsKey("1PLeft"))
	{
		// =============== 1P 이동 ===============
		GameEngineInput::GetInst()->CreateKey("1PLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("1PRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("1PUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("1PDown", VK_DOWN);

		// =============== 1P 공격 ===============
		GameEngineInput::GetInst()->CreateKey("1PAttack", VK_SPACE);

		// =============== 2P 이동 ===============
		GameEngineInput::GetInst()->CreateKey("2PLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("2PRight", 'D');
		GameEngineInput::GetInst()->CreateKey("2PUp", 'W');
		GameEngineInput::GetInst()->CreateKey("2PDown", 'S');

		// =============== 2P 공격 ===============
		GameEngineInput::GetInst()->CreateKey("2PAttack", VK_LSHIFT);

		// ============== 디버그 모드 =============
		GameEngineInput::GetInst()->CreateKey("DebugMode", 'O');
	}

	
}

void Player::Update()
{
	ColMapUpdate();

	CharTypeUpdate();

	DirAnimationCheck();
	PlayerStateUpdate();
	PlayerCollisionUpdate();

	//PlayerInfoUpdate();

	DebugModeSwitch();
}

void Player::Render()
{
}

bool Player::IsMoveKey()
{
	if (Type == PlayerType::Player1)
	{
		if (false == GameEngineInput::GetInst()->IsPress("1PLeft")
			&& false == GameEngineInput::GetInst()->IsPress("1PRight")
			&& false == GameEngineInput::GetInst()->IsPress("1PUp")
			&& false == GameEngineInput::GetInst()->IsPress("1PDown")
			)
		{
			return false;
		}
	}
	else
	{
		if (false == GameEngineInput::GetInst()->IsPress("2PLeft")
			&& false == GameEngineInput::GetInst()->IsPress("2PRight")
			&& false == GameEngineInput::GetInst()->IsPress("2PUp")
			&& false == GameEngineInput::GetInst()->IsPress("2PDown")
			)
		{
			return false;
		}
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

	if (Type == PlayerType::Player1)
	{
		if (true == GameEngineInput::GetInst()->IsPress("1PRight"))
		{
			CheckDir_ = PlayerDir::Right;
			ChangeDirText_ = "Right";
		}

		if (true == GameEngineInput::GetInst()->IsPress("1PLeft"))
		{
			CheckDir_ = PlayerDir::Left;
			ChangeDirText_ = "Left";
		}

		if (true == GameEngineInput::GetInst()->IsPress("1PUp"))
		{
			CheckDir_ = PlayerDir::Up;
			ChangeDirText_ = "Up";
		}

		if (true == GameEngineInput::GetInst()->IsPress("1PDown"))
		{
			CheckDir_ = PlayerDir::Down;
			ChangeDirText_ = "Down";
		}

	}
	else if (Type == PlayerType::Player2)
	{
		if (true == GameEngineInput::GetInst()->IsPress("2PRight"))
		{
			CheckDir_ = PlayerDir::Right;
			ChangeDirText_ = "Right";
		}

		if (true == GameEngineInput::GetInst()->IsPress("2PLeft"))
		{
			CheckDir_ = PlayerDir::Left;
			ChangeDirText_ = "Left";
		}

		if (true == GameEngineInput::GetInst()->IsPress("2PUp"))
		{
			CheckDir_ = PlayerDir::Up;
			ChangeDirText_ = "Up";
		}

		if (true == GameEngineInput::GetInst()->IsPress("2PDown"))
		{
			CheckDir_ = PlayerDir::Down;
			ChangeDirText_ = "Down";
		}
	}


	if (CheckDir_ != CurDir_)
	{
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
		CurDir_ = CheckDir_;
	}
}

