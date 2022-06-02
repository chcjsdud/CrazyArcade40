#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>
#include "MapGameObject.h"
#include "MapBackGround.h"
#include "GameEngine/GameEngine.h"

Player* Player::MainPlayer_1 = nullptr;
Player* Player::MainPlayer_2 = nullptr;

Player::Player()
	: CurSpeed_(0.f)
	, MaxSpeed_(0.f)
	, CurAttPower_(0.f)
	, CurAttCount_(0)
	, MaxAttPower_(0.f)
	, MaxAttCount_(0)
	, MoveDir(float4::ZERO)
	, PlayerAnimationRender_(nullptr)
	, CurState_(PlayerState::Idle)
	, PrevState_(CurState_)
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
	, IsMove(false)
	, MapBackGround_(nullptr)
	, MapColRenderer_(nullptr)
	, IsLeftMove(true)
	, IsRightMove(true)
	, IsUpMove(true)
	, IsDownMove(true)
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
	else if (true == GameEngineInput::GetInst()->IsDown("DebugMode") && false == IsDebug)
	{
		GetLevel()->IsDebugModeOn();
		IsDebug = true;
	}

}

void Player::Move()
{
	MoveDir = float4::ZERO;

	float MovePos = 250.f;

	if (Type == PlayerType::Player1)
	{
		if (true == GameEngineInput::GetInst()->IsPress("1PLeft"))
		{
			if (true == IsLeftMove)
			{
				MoveDir.x = -MovePos;
				//if (true == GameEngineInput::GetInst()->IsPress("1PUp"))			// 1. Left + UP 동시에 눌렸을 경우 => UP
				//{
				//	MoveDir.y = -MovePos;
				//}
				//else if (true == GameEngineInput::GetInst()->IsPress("1PDown"))		// 2. Left + Down 동시에 눌렸을 경우 => Down
				//{
				//	MoveDir.y = MovePos;
				//}
				//else
				//{
				//	MoveDir.x = -MovePos;
				//}
			}

		}
		else if (true == GameEngineInput::GetInst()->IsPress("1PRight"))
		{
			if (true == IsRightMove)
			{
				MoveDir.x = MovePos;
				//if (true == GameEngineInput::GetInst()->IsPress("1PUp"))		// 1. Right + UP 동시에 눌렸을 경우 => UP
				//{
				//	MoveDir.y = -MovePos;
				//}
				//else if (true == GameEngineInput::GetInst()->IsPress("1PDown"))		// 2. Right + Down 동시에 눌렸을 경우 => Down
				//{
				//	MoveDir.y = MovePos;
				//}
				//else
				//{
				//	MoveDir.x = MovePos;
				//}
			}
		
		}
		else if (true == GameEngineInput::GetInst()->IsPress("1PUp"))
		{
			if (true == IsUpMove)
			{
				MoveDir.y = -MovePos;
			}
		
		}
		else if (true == GameEngineInput::GetInst()->IsPress("1PDown"))
		{
			if (true == IsDownMove)
			{
				MoveDir.y = MovePos;
			}
		}
	}
	else
	{
		if (true == GameEngineInput::GetInst()->IsPress("2PLeft"))
		{
			if (true == IsLeftMove)
			{
				if (true == GameEngineInput::GetInst()->IsPress("2PUp"))			// 1. Left + UP 동시에 눌렸을 경우 => UP
				{
					MoveDir.y = -MovePos;
				}
				else if (true == GameEngineInput::GetInst()->IsPress("2PDown"))		// 2. Left + Down 동시에 눌렸을 경우 => Down
				{
					MoveDir.y = MovePos;
				}
				else
				{
					MoveDir.x = -MovePos;
				}
			}
			
		}
		else if (true == GameEngineInput::GetInst()->IsPress("2PRight"))
		{
			if (true == IsRightMove)
			{
				if (true == GameEngineInput::GetInst()->IsPress("2PUp"))		// 1. Right + UP 동시에 눌렸을 경우 => UP
				{
					MoveDir.y = -MovePos;
				}
				else if (true == GameEngineInput::GetInst()->IsPress("2PDown"))		// 2. Right + Down 동시에 눌렸을 경우 => Down
				{
					MoveDir.y = MovePos;
				}
				else
				{
					MoveDir.x = MovePos;
				}
			}
	
		}
		else if (true == GameEngineInput::GetInst()->IsPress("2PUp"))
		{
			if (true == IsUpMove)
			{
				MoveDir.y = -MovePos;
			}
			
		}
		else if (true == GameEngineInput::GetInst()->IsPress("2PDown"))
		{
			if (true == IsDownMove)
			{
				MoveDir.y = MovePos;
			}
		}
	}



	//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * CurSpeed_);

}

void Player::PlayerInfoUpdate()
{
	//SpeedUpdate();
	//AttackCountUpdate();
	//AttackPowerUpdate();
}

void Player::SpeedUpdate()
{
}

void Player::AttackCountUpdate()
{
}

void Player::AttackPowerUpdate()
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
		SetAttPower(10.f);			// 일단 10배

		SetMaxSpeed(90.f);
		SetMaxAttCount(6);
		SetMaxAttPower(70.f);
	}
	break;
	case Character::DAO:
	{
		DaoRenderer_->On();
		PlayerAnimationRender_ = DaoRenderer_;
		PlayerAnimationRender_->On();

		SetSpeed(1.f);
		SetAttCount(1);
		SetAttPower(10.f);			// 일단 10배

		SetMaxSpeed(90.f);
		SetMaxAttCount(6);
		SetMaxAttPower(70.f);
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
		//MapColImage_ = GameEngineImageManager::GetInst()->Find("Boss_ColMap.bmp");
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
		// ****** 보스레벨 ColMap 수정 필요 // 몬스터 테스트 위해서 기존 CampColMap->BossColMap으로 바꿔놨어용
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Boss_ColMap.bmp");
	}
	else
		return;
}

void Player::StagePixelCheck(float _Speed)
{
	float4 LeftTopPos = GetPosition() + float4{ -19.f, -5.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;
	float4 RightTopPos = GetPosition() + float4{ 19.f, -5.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;
	float4 LeftBotPos = GetPosition() + float4{ -19.f, 30.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;
	float4 RightBotPos = GetPosition() + float4{ 19.f, 30.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;

	int LeftTopColor = MapColImage_->GetImagePixel(LeftTopPos);
	int RightTopColor = MapColImage_->GetImagePixel(RightTopPos);
	int LeftBotColor = MapColImage_->GetImagePixel(LeftBotPos);
	int RightBotColor = MapColImage_->GetImagePixel(RightBotPos);


	if (RGB(0, 0, 0) != LeftTopColor
		&& RGB(0, 0, 0) != RightTopColor
		&& RGB(0, 0, 0) != LeftBotColor
		&& RGB(0, 0, 0) != RightBotColor)
	{
		IsMove = true;
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * _Speed);

	/*	if (true == IsMove)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * _Speed);
		}*/
	}
}

//BlockType blockType_ = {};

void Player::TileCheckResultUpdate(BlockType _CurBlockType)
{
	switch (_CurBlockType)
	{
	case BlockType::WaveBlock:
	{
		ChangeState(PlayerState::Damaged);
		return;
	}
	case BlockType::BubbleBlock:
	{
		ChangeState(PlayerState::Damaged);
		return;
	}
	break;
	case BlockType::BushBlock:
	{

	}
	break;
	case BlockType::ItemBlock:
	{

	}
	break;

	}

}

void Player::TileCheckResult()
{
	if (Type == PlayerType::Player1)
	{
		float4 Pos = MainPlayer_1->GetPosition();
		CurBlockType1_ = CheckBlockTile(Pos + float4{ -20.0f,-20.0f });

		TileCheckResultUpdate(CurBlockType1_);
	}

	if (nullptr != MainPlayer_2)
	{
		if (Type == PlayerType::Player2)
		{
			float4 Pos = MainPlayer_2->GetPosition();
			CurBlockType2_ = CheckBlockTile(Pos + float4{ -20.0f, -20.0f });

			TileCheckResultUpdate(CurBlockType2_);
		}

	}

}

void Player::FrontBlockCheckUpdate()
{
	// 왼쪽 블럭
	switch (LeftBlock)
	{
	case BlockType::BoomBlock:
	{
		IsLeftMove = false;
	}
	break;
	case BlockType::FixBlock:
	{
		IsLeftMove = false;
	}
	break;
	default:
	{
		IsLeftMove = true;
	}
	break;
	}

	// 오른쪽 블럭
	switch (RightBlock)
	{
	case BlockType::BoomBlock:
	{
		IsRightMove = false;
	}
	break;
	case BlockType::FixBlock:
	{
		IsRightMove = false;
	}
	break;
	default:
	{
		IsRightMove = true;
	}
	break;
	}

	// 위쪽 블럭
	switch (UpBlock)
	{
	case BlockType::BoomBlock:
	{
		IsUpMove = false;
	}
	break;
	case BlockType::FixBlock:
	{
		IsUpMove = false;
	}
	break;
	default:
	{
		IsUpMove = true;
	}
	break;
	}


	// 아래쪽 블럭
	switch (DownBlock)
	{
	case BlockType::BoomBlock:
	{
		IsDownMove = false;
	}
	break;
	case BlockType::FixBlock:
	{
		IsDownMove = false;
	}
	break;
	default:
	{
		IsDownMove = true;
	}
	break;
	}
}

void Player::FrontBlockCheck()
{
	if (Type == PlayerType::Player1)
	{
		float4 Pos = MainPlayer_1->GetPosition();

		TileIndex RightIndex = MapTile_->GetTileIndex(Pos + float4{ 10.f, 0.f });
		TileIndex DownIndex = MapTile_->GetTileIndex(Pos + float4{ 0.f, 10.f });

		LeftBlock = CheckBlockTile(Pos + float4{ -40.0f, -20.0f });
		UpBlock = CheckBlockTile(Pos + float4{ -20.0f, -40.0f });

		if (RightIndex.X != 15)
		{
			RightBlock = CheckBlockTile(Pos + float4{ 0.0f, -20.0f });
		}
		if (DownIndex.Y != 13)
		{
			DownBlock = CheckBlockTile(Pos + float4{ -20.0f, 0.0f });
		}
	

		FrontBlockCheckUpdate();
	/*
		if (LeftBlock == BlockType::BoomBlock)
		{
			IsLeftMove = false;
		}
		else
		{
			IsLeftMove = true;
		}

		if (RightBlock == BlockType::BoomBlock)
		{
			IsRightMove = false;
		}
		else
		{
			IsRightMove = true;
		}

		if (UpBlock == BlockType::BoomBlock)
		{
			IsUpMove = false;
		}
		else
		{
			IsUpMove = true;
		}

		if (DownBlock == BlockType::BoomBlock)
		{
			IsDownMove = false;
		}
		else
		{
			IsDownMove = true;
		}*/
	}

	if (nullptr != MainPlayer_2)
	{
		if (Type == PlayerType::Player2)
		{
			float4 Pos = MainPlayer_2->GetPosition();

			TileIndex RightIndex = MapTile_->GetTileIndex(Pos + float4{ 10.f, 0.f });
			TileIndex DownIndex = MapTile_->GetTileIndex(Pos + float4{ 0.f, 20.f });

			LeftBlock = CheckBlockTile(Pos + float4{ -40.0f, -20.0f });
			UpBlock = CheckBlockTile(Pos + float4{ -20.0f, -40.0f });

			if (RightIndex.X != 15)
			{
				RightBlock = CheckBlockTile(Pos + float4{ 0.0f, -20.0f });
			}
			if (DownIndex.Y != 13)
			{
				DownBlock = CheckBlockTile(Pos + float4{ -20.0f, 0.0f });
			}

			FrontBlockCheckUpdate();
		}
	}
	
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

void Player::MonsterCollisionCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (Type == PlayerType::Player1)
	{
		if (true == Collision1P_->CollisionResult("Monster", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			for (size_t i = 0; i < ColList.size(); i++)
			{
				ChangeState(PlayerState::Die);
				return;
			}
		}
	}

	if (nullptr != MainPlayer_2)
	{
		if (Type == PlayerType::Player2)
		{
			if (true == Collision1P_->CollisionResult("Monster", ColList, CollisionType::Rect, CollisionType::Rect))
			{
				for (size_t i = 0; i < ColList.size(); i++)
				{
					ChangeState(PlayerState::Die);
					return;
				}
			}
		}
	}

}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Player::Start()
{
	Collision1P_ = CreateCollision("1PColl", { 50.f, 50.f }, { 0.f, 0.f });
	Collision1P_->Off();

	Collision2P_ = CreateCollision("2PColl", { 50.f, 50.f }, { 0.f, 0.f });
	Collision2P_->Off();



	PlayerAnimationRender_ = CreateRenderer();
	PlayerAnimationRender_->SetPivotType(RenderPivot::CENTER);
	PlayerAnimationRender_->SetPivot({ 0.f, 0.f });

	PlayerAnimationRender_->Off();

	// BAZZI
	{
		GameEngineImage* Bazzi1 = GameEngineImageManager::GetInst()->Find("Bazzi_1.bmp");
		Bazzi1->CutCount(5, 18);
		GameEngineImage* Bazzi2 = GameEngineImageManager::GetInst()->Find("Bazzi_2.bmp");
		Bazzi2->CutCount(5, 2);
		GameEngineImage* Bazzi3 = GameEngineImageManager::GetInst()->Find("Bazzi_3.bmp");
		Bazzi3->CutCount(5, 4);
		GameEngineImage* Bazzi = GameEngineImageManager::GetInst()->Find("Bazzi_1a.bmp");
		Bazzi->CutCount(5, 18);

		// 애니메이션

		BazziRenderer_ = CreateRenderer((int)ORDER::PLAYER, RenderPivot::CENTER, float4{ 0.f, 0.f });

		// Idle
		BazziRenderer_->CreateAnimation("Bazzi_1.bmp", "Ready_", 37, 53, 0.06f, false);
		BazziRenderer_->CreateAnimation("Bazzi_1.bmp", "Idle_Left", 0, 0, 1.f, false);
		BazziRenderer_->CreateAnimation("Bazzi_1.bmp", "Idle_Right", 6, 6, 1.f, false);
		BazziRenderer_->CreateAnimation("Bazzi_1.bmp", "Idle_Up", 12, 12, 1.f, false);
		BazziRenderer_->CreateAnimation("Bazzi_1.bmp", "Idle_Down", 20, 20, 1.f, false);

		// Move
		BazziRenderer_->CreateAnimation("Bazzi_1.bmp", "Move_Left", 1, 5, 0.1f, true);
		BazziRenderer_->CreateAnimation("Bazzi_1.bmp", "Move_Right", 7, 11, 0.1f, true);
		BazziRenderer_->CreateAnimation("Bazzi_1.bmp", "Move_Up", 13, 19, 0.1f, true);
		BazziRenderer_->CreateAnimation("Bazzi_1.bmp", "Move_Down", 21, 28, 0.1f, true);

		BazziRenderer_->CreateAnimation("Bazzi_1.bmp", "Win_", 29, 36, 0.1f, true);
		BazziRenderer_->CreateAnimation("Bazzi_1a.bmp", "Damaged_", 60, 71, 0.2f, true);
		BazziRenderer_->CreateAnimation("Bazzi_1a.bmp", "Fade_", 72, 79, 0.2f, true);
		BazziRenderer_->CreateAnimation("Bazzi_2.bmp", "Die_", 0, 5, 0.15f, false);
		BazziRenderer_->CreateAnimation("Bazzi_2.bmp", "Revival_", 6, 9, 0.15f, false);

		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingOwl_Left", 0, 1, 0.15f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingOwl_Right", 2, 3, 0.15f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingOwl_Up", 4, 5, 0.15f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingOwl_Down", 6, 7, 0.15f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingTurtle_Left", 8, 9, 0.02f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingTurtle_Right", 10, 11, 0.2f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingTurtle_Up", 12, 13, 0.2f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingTurtle_Down", 14, 15, 0.2f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingUFO_Left", 16, 16, 0.09f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingUFO_Right", 17, 17, 0.09f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingUFO_Up", 18, 18, 0.09f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingUFO_Down", 19, 19, 0.09f, true);


		BazziRenderer_->ChangeAnimation("Ready_");
		CurState_ = PlayerState::Ready;
		AnimationName_ = "Ready_";
		ChangeDirText_ = "Down";

		//BazziRenderer_->ChangeAnimation("Idle_Down");
		//AnimationName_ = "Idle_";
		//ChangeDirText_ = "Down";
		//ChangeState(PlayerState::Idle);


		BazziRenderer_->Off();
	}

	// Lux Marid
	{
		GameEngineImage* Marid1 = GameEngineImageManager::GetInst()->Find("luxMarid_1.bmp");
		Marid1->CutCount(5, 12);
		GameEngineImage* Marid2 = GameEngineImageManager::GetInst()->Find("luxMarid_2.bmp");
		Marid2->CutCount(5, 2);

		// 애니메이션
		MaridRenderer_ = CreateRenderer((int)ORDER::PLAYER, RenderPivot::CENTER, float4{ 0.f, 0.f });

		// Idle
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Ready_", 37, 53, 0.06f, false);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Idle_Left", 0, 0, 1.f, false);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Idle_Right", 6, 6, 1.f, false);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Idle_Up", 12, 12, 1.f, false);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Idle_Down", 20, 20, 1.f, false);

		// Move
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Move_Left", 1, 5, 0.1f, true);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Move_Right", 7, 11, 0.1f, true);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Move_Up", 13, 19, 0.1f, true);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Move_Down", 21, 28, 0.1f, true);

		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Win_", 29, 36, 0.1f, true);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Damaged_", 60, 71, 0.2f, true);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Fade_", 72, 79, 0.15f, false);
		MaridRenderer_->CreateAnimation("luxMarid_2.bmp", "Die_", 0, 5, 0.15f, false);
		MaridRenderer_->CreateAnimation("luxMarid_2.bmp", "Revival_", 6, 9, 0.15f, false);

		//MaridRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingOwl_Left", 0, 1, 0.15f, true);
		//MaridRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingOwl_Right", 2, 3, 0.15f, true);
		//MaridRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingOwl_Up", 4, 5, 0.15f, true);
		//MaridRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingOwl_Down", 6, 7, 0.15f, true);
		//MaridRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingTurtle_Left", 8, 9, 0.02f, true);
		//MaridRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingTurtle_Right", 10, 11, 0.2f, true);
		//MaridRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingTurtle_Up", 12, 13, 0.2f, true);
		//MaridRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingTurtle_Down", 14, 15, 0.2f, true);
		//MaridRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingUFO_Left", 16, 16, 0.09f, true);
		//MaridRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingUFO_Right", 17, 17, 0.09f, true);
		//MaridRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingUFO_Up", 18, 18, 0.09f, true);
		//MaridRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingUFO_Down", 19, 19, 0.09f, true);


		MaridRenderer_->ChangeAnimation("Ready_");
		CurState_ = PlayerState::Ready;
		AnimationName_ = "Ready_";
		ChangeDirText_ = "Down";

		//BazziRenderer_->ChangeAnimation("Idle_Down");
		//AnimationName_ = "Idle_";
		//ChangeDirText_ = "Down";
		//ChangeState(PlayerState::Idle);


		MaridRenderer_->Off();
	}



	/////////////// 테스트
	//{
	//	DaoRenderer_ = CreateRenderer();
	//	DaoRenderer_->SetPivotType(RenderPivot::BOT);
	//	DaoRenderer_->SetPivot({ 0.f, 30.f });

	//	GameEngineImage* Left = GameEngineImageManager::GetInst()->Find("Monster.bmp");
	//	Left->CutCount(10, 7);
	//	DaoRenderer_->CreateAnimation("Monster.bmp", "Move_Left", 0, 1, 0.2f, true);
	//	DaoRenderer_->CreateAnimation("Monster.bmp", "Move_Right", 2, 3, 0.2f, true);
	//	DaoRenderer_->CreateAnimation("Monster.bmp", "Move_Up", 4, 5, 0.2f, true);
	//	DaoRenderer_->CreateAnimation("Monster.bmp", "Move_Down", 16, 17, 0.2f, true);

	//	// Idle
	//	DaoRenderer_->CreateAnimation("Monster.bmp", "Idle_Left", 0, 0, 1.f, false);
	//	DaoRenderer_->CreateAnimation("Monster.bmp", "Idle_Right", 0, 0, 1.f, false);
	//	DaoRenderer_->CreateAnimation("Monster.bmp", "Idle_Down", 0, 0, 1.f, false);
	//	DaoRenderer_->CreateAnimation("Monster.bmp", "Idle_Up", 0, 0, 1.f, false);

	//	//DaoRenderer_->ChangeAnimation("Ready_Down");

	//	//AnimationName_ = "Idle_";
	//	DaoRenderer_->ChangeAnimation("Idle_Down");

	//	DaoRenderer_->Off();
	//}




	if (false == GameEngineInput::GetInst()->IsKey("1PLeft"))
	{
		// =============== 1P 이동 ===============
		GameEngineInput::GetInst()->CreateKey("1PLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("1PRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("1PUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("1PDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("1PAttack", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("1PItem", VK_HANGUL);

		// =============== 2P 이동 ===============
		GameEngineInput::GetInst()->CreateKey("2PLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("2PRight", 'D');
		GameEngineInput::GetInst()->CreateKey("2PUp", 'W');
		GameEngineInput::GetInst()->CreateKey("2PDown", 'S');
		GameEngineInput::GetInst()->CreateKey("2PAttack", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("2PItem", VK_LCONTROL);

		// ============== 디버그 모드 =============
		GameEngineInput::GetInst()->CreateKey("DebugMode", 'O');

		GameEngineInput::GetInst()->CreateKey("2POn", 'X');
	}

	IsReady = true;
}

void Player::Update()
{
	ColMapUpdate();

	CharTypeUpdate();

	PlayerStateUpdate();
	PlayerCollisionUpdate();

	TileCheckResult();
	FrontBlockCheck();

	MonsterCollisionCheck();

	//PlayerInfoUpdate();

	

	DebugModeSwitch();
}

void Player::Render()
{

	std::string IndexX = "";
	std::string IndexY = "";


	TileIndex TileIndex_ = MapTile_->GetTileIndex(GetPosition() - float4{20,40});
	IndexX = "Index X : " + std::to_string(TileIndex_.X);
	IndexY = "Index Y : " + std::to_string(TileIndex_.Y);


	TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 30, IndexX.c_str(), static_cast<int>(IndexX.length()));
	TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 10, IndexY.c_str(), static_cast<int>(IndexY.length()));

	//std::string Posx = "";
	//std::string Posy = "";
	//std::string State = "";


	//Posx = "Pos x : " + std::to_string(GetPosition().ix());
	//Posy = "Pos y : " + std::to_string(GetPosition().iy());

	//if (CurState_ == PlayerState::Wait)
	//{
	//	State = "STATE : Wait";
	//}
	//else if (CurState_ == PlayerState::Ready)
	//{
	//	State = "STATE : Ready";
	//}
	//else if (CurState_ == PlayerState::Idle)
	//{
	//	State = "STATE : Idle";
	//}
	//else if (CurState_ == PlayerState::Move)
	//{
	//	State = "STATE : Move";
	//}
	//else if (CurState_ == PlayerState::Jump)
	//{
	//	State = "STATE : Jump";
	//}
	//else if (CurState_ == PlayerState::Attack)
	//{
	//	State = "STATE : Attack";
	//}
	//else if (CurState_ == PlayerState::Damaged)
	//{
	//	State = "STATE : Damaged";
	//}
	//else if (CurState_ == PlayerState::Revival)
	//{
	//	State = "STATE : Revival";
	//}
	//else if (CurState_ == PlayerState::Fade)
	////{
	////	State = "STATE : Fade";
	//}
	//else if (CurState_ == PlayerState::Die)
	//{
	//	State = "STATE : Die";
	//}
	//else if (CurState_ == PlayerState::IdleOwl)
	//{
	//	State = "STATE : IdleOwl";
	//}
	//else if (CurState_ == PlayerState::IdleTurtle)
	//{
	//	State = "STATE : IdleTurtle";
	//}
	//else if (CurState_ == PlayerState::RidingOwl)
	//{
	//	State = "STATE : RidingOwl";
	//}
	//else if (CurState_ == PlayerState::RidingTurtle)
	//{
	//	State = "STATE : RidingTurtle";
	//}
	//else if (CurState_ == PlayerState::RidingUFO)
	//{
	//	State = "STATE : RidingUFO";
	//}
	//

	//TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() -30, Posx.c_str(), static_cast<int>(Posx.length()));
	//TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() -10, Posy.c_str(), static_cast<int>(Posy.length()));
	//TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() +10, State.c_str(), static_cast<int>(State.length()));
}

bool Player::IsMoveKey()
{
	if (true == IsMove)
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

	return false;
}

bool Player::IsAttackKey()
{
	if (Type == PlayerType::Player1)
	{
		if (true == GameEngineInput::GetInst()->IsDown("1PAttack"))
		{
			return true;
		}
	}
	else
	{
		if (true == GameEngineInput::GetInst()->IsDown("2PAttack"))
		{
			return true;
		}
	}

	return false;
}

bool Player::IsItemKey()
{
	if (Type == PlayerType::Player1)
	{
		if (true == GameEngineInput::GetInst()->IsDown("1PItem"))
		{
			return true;
		}
	}
	else
	{
		if (true == GameEngineInput::GetInst()->IsDown("2PItem"))
		{
			return true;
		}
	}

	return false;
}

void Player::ChangeState(PlayerState _State)
{
	if (true == IsReady)
	{
		ReadyStart();
		IsReady = false;

	}

	if (CurState_ != _State)
	{
		switch (_State)
		{
		case PlayerState::Wait:
			WaitStart();
			break;
		case PlayerState::Ready:
			ReadyStart();
			break;
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Move:
			MoveStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Attack:
			AttackStart();
			break;
		case PlayerState::Damaged:
			DamagedStart();
			break;
		case PlayerState::Revival:
			RevivalStart();
			break;
		case PlayerState::Fade:
			FadeStart();
			break;
		case PlayerState::Die:
			DieStart();
			break;
		case PlayerState::IdleOwl:
			IdeOwlStart();
			break;
		case PlayerState::IdleTurtle:
			IdleTurtleStart();
			break;
		case PlayerState::RidingOwl:
			RidingOwlStart();
			break;
		case PlayerState::RidingTurtle:
			RidingTurtleStart();
			break;
		case PlayerState::RidingUFO:
			RidingUFOStart();
			break;
		}

	}

	CurState_ = _State;
}

void Player::PlayerStateUpdate()
{
	switch (CurState_)
	{
	case PlayerState::Wait:
		WaitUpdate();
		break;
	case PlayerState::Ready:
		ReadyUpdate();
		break;
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Move:
		MoveUpdate();
		break;
	case PlayerState::Jump:
		JumpUpdate();
		break;
	case PlayerState::Attack:
		AttackUpdate();
		break;
	case PlayerState::Damaged:
		DamagedUpdate();
		break;
	case PlayerState::Revival:
		RevivalUpdate();
		break;
	case PlayerState::Fade:
		FadeUpdate();
		break;
	case PlayerState::Die:
		DieUpdate();
		break;
	case PlayerState::IdleOwl:
		IdleOwlUpdate();
		break;
	case PlayerState::IdleTurtle:
		IdleTurtleUpdate();
		break;
	case PlayerState::RidingOwl:
		RidingOwlUpdate();
		break;
	case PlayerState::RidingTurtle:
		RidingTurtleUpdate();
		break;
	case PlayerState::RidingUFO:
		RidingUFOUpdate();
		break;
	}
}

void Player::DirAnimationCheck()
{

	std::string ChangeName;

	PlayerDir CheckDir_ = CurDir_;

	if (CurState_ != PlayerState::Ready)
	{
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

}

// 플레이어가 서있는 위치의 타일이 어떤 타입의 블럭인지 알려주는 함수 return 값이 Max이면 - 아무것도 없는 타일입니다.
BlockType Player::CheckBlockTile(float4 _Pos)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);

	if (Tiles_ == nullptr)
	{
		return BlockType::Max;
	}
	else
	{
		return Tiles_->BlockType_;
	}
}