#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>
#include "MapGameObject.h"
#include "MapBackGround.h"
#include "GameEngine/GameEngine.h"
#include "GameItemObject.h"
#include <GameEngineContents/Monster.h>

Player* Player::MainPlayer_1 = nullptr;
Player* Player::MainPlayer_2 = nullptr;
MapGameObject* Player::Boom_=nullptr;
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
	, MaridRenderer_(nullptr)
	, MapColImage_(nullptr)
	, CurCharacter(Character::MAX)
	, IsDebug(false)		// false에서 잠시 바꿔둠
	, CurrentLevel_("")
	, IsMove(false)
	, MapBackGround_(nullptr)
	, MapColRenderer_(nullptr)
	, IsLeftMove(true)
	, IsRightMove(true)
	, IsUpMove(true)
	, IsDownMove(true)
	, CheckDir_(PlayerDir::None)
	, IsBoomblock(false)
	, Time_(0.0f)
	, CurBlockType1_(BlockType::NoBlock)
	, CurBlockType2_(BlockType::NoBlock)
	, LeftBlock(BlockType::Max)
	, RightBlock(BlockType::Max)
	, UpBlock(BlockType::Max)
	, DownBlock(BlockType::Max)
	, IsReady(true)
	, AttMoveTime_(0.0f)
	, MapTile_(nullptr)
	, IsLive(true)
	, IsShield(false)
	, IsDevil(false)
	, IsInvincible(false)
	, IsShoes(false)
	, InputDir_(CurDir_)
	, PlayerRideState_(PlayerRideState::Max)
	, CurItem_(ItemType::Max)
	, IsNiddle(false)
	, IsJump(false)
	, MoveSpeed_(CurSpeed_)
	, IsUFO(false)
	, UseShield(false)
	, CurItemType1_(ItemType::Max)
	, CurItemType2_(ItemType::Max)
	, EffectRenderer_(nullptr)
	, Player1BoomCount_(CurAttCount_)
	, Player2BoomCount_(CurAttCount_)
	, TestTime_(0.0f)
	, ShieldTime_(0.0f)
	, DevilTime_(0.0f)

{
	BazziAttCount_ = 1;
	MaridAttCount_ = 2;
	DaoAttCount_ = 1;

	BazziAttPower_ = 2.f;
	MaridAttPower_ = 2.f;
	DaoAttPower_ = 2.f;

	BazziSpeed_ = 5.f;
	MaridSpeed_ = 5.f;
	DaoSpeed_ = 4.5f;

	BazziMaxAttCount_ = 6;
	MaridMaxAttCount_ = 9;
	DaoMaxAttCount_ = 10;

	BazziMaxAttPower_ = 7.f;
	MaridMaxAttPower_ = 6.f;
	DaoMaxAttPower_ = 7.f;

	BazziMaxSpeed_ = 7.f;
	MaridMaxSpeed_ = 7.f;
	DaoMaxSpeed_ = 6.5f;
}
Player::~Player()
{

}

void Player::DebugModeSwitch()
{
	if (true == GameEngineInput::GetInst()->IsDown("Invincible"))
	{
		if (false == IsInvincible)
		{
			IsInvincible = true;

			EffectRenderer_->On();
		}
		else
		{
			IsInvincible = false;

			EffectRenderer_->Off();
		}
		
	}

	if (true == GameEngineInput::GetInst()->IsDown("Debug_Col") && true == IsDebug)
	{
		GetLevel()->IsDebugModeOff();
		IsDebug = false;
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Debug_Col") && false == IsDebug)
	{
		GetLevel()->IsDebugModeOn();
		IsDebug = true;
	}

}

void Player::PositionUpdate()
{
	if (nullptr != MainPlayer_1)
	{
		Player1Pos_ = MainPlayer_1->GetPosition() + float4{ -20.0f, -20.0f };
		Player2Pos_ = MainPlayer_2->GetPosition() + float4{ -20.0f, -20.0f };
	}
}

void Player::SetCollision(GameEngineCollision* _Collision)
{
	_Collision->GetActor();
}

void Player::PlayerInit()
{
	switch (CurCharacter)
	{
	case Character::BAZZI:
	{
		SetAttCount(BazziAttCount_);
		SetAttPower(BazziAttPower_);
		SetSpeed(BazziSpeed_);

		SetMaxAttCount(BazziMaxAttCount_);
		SetMaxAttPower(BazziMaxAttPower_);
		SetMaxSpeed(BazziMaxSpeed_);
	}
	break;
	case Character::LUXMARID:
	{
		SetAttCount(MaridAttCount_);
		SetAttPower(MaridAttPower_);
		SetSpeed(MaridSpeed_);

		SetMaxAttCount(MaridMaxAttCount_);
		SetMaxAttPower(MaridMaxAttPower_);
		SetMaxSpeed(MaridMaxSpeed_);
	}
	break;
	case Character::DAO:
	{
		SetAttCount(DaoAttCount_);
		SetAttPower(DaoAttPower_);
		SetSpeed(DaoSpeed_);

		SetMaxAttCount(DaoMaxAttCount_);
		SetMaxAttPower(DaoMaxAttPower_);
		SetMaxSpeed(DaoMaxSpeed_);
	}
	break;
	default:
		break;
	}
}

void Player::PlayerInfoUpdate()
{
	if (true == IsDevil && PlayerRideState::Max != PlayerRideState_)
	{
		IsDevil = false;
	}

	if (Type == PlayerType::Player1)
	{
		float4 Pos = MainPlayer_1->GetPosition() + float4{ -20.0f,-20.0f };
		GameItemObject* Item = GetLevel()->CreateActor<GameItemObject>(static_cast<int>(ORDER::MAPOBJECT));
		Item->SetMapTile(MapTile_);
		CurItemType1_ = Item->CheckItem(Pos);

		ItemCheck(MainPlayer_1, CurItemType1_);

		ArrowRenderer_1P->On();
	}

	if (nullptr != MainPlayer_2)
	{
		if (Type == PlayerType::Player2)
		{
			float4 Pos = MainPlayer_2->GetPosition() + float4{ -20.0f,-20.0f };
			GameItemObject* Item = GetLevel()->CreateActor<GameItemObject>(static_cast<int>(ORDER::MAPOBJECT));
			Item->SetMapTile(MapTile_);
			CurItemType2_ = Item->CheckItem(Pos);

			ItemCheck(MainPlayer_2, CurItemType2_);

			ArrowRenderer_1P->On();
		}
	}
}



void Player::CharTypeUpdate()
{
	switch (CurCharacter)
	{
	case Character::BAZZI:
	{
		BazziRenderer_->On();
		PlayerAnimationRender_ = BazziRenderer_;
		PlayerAnimationRender_->On();;
	}
	break;
	case Character::LUXMARID:
	{
		MaridRenderer_->On();
		PlayerAnimationRender_ = MaridRenderer_;
		PlayerAnimationRender_->On();
	}
	break;
	case Character::DAO:
	{
		DaoRenderer_->On();
		PlayerAnimationRender_ = DaoRenderer_;
		PlayerAnimationRender_->On();
	}
	break;
	}
}

void Player::ColMapUpdate()
{
	CurrentLevel_ = GetCurrentLevel();

	// ====================================== 테스트 레벨
	if (CurrentLevel_ == "PlayerTeamTest")
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Boss_ColMap.bmp");
		//MapColImage_ = GameEngineImageManager::GetInst()->Find("Camp_ColMap.bmp");
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
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Boss_ColMap.bmp");
	}
	else
		return;
}

void Player::StagePixelCheck(float _Speed)
{
	float4 LeftTopPos = GetPosition() + float4{ -12.f, 5.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;
	float4 RightTopPos = GetPosition() + float4{ 12.f, 5.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;
	float4 LeftBotPos = GetPosition() + float4{ -12.f, 30.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;
	float4 RightBotPos = GetPosition() + float4{ 12.f, 30.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;

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
	}
}

void Player::PlayerCollisionUpdate()
{
	if (Type == PlayerType::Player1)
	{
		Collision1P_->On();
		ArrowRenderer_1P->On();

	}
	else
	{
		Collision2P_->On();
		ArrowRenderer_2P->On();
		ArrowRenderer_1P->Off();
	}
}

void Player::CollisionCheck()
{
	// 무적이 아닐 때만
	if (Type == PlayerType::Player1)
	{
		if (false == IsInvincible)
		{
			std::vector<GameEngineCollision*> ColList;

			if (true == Collision1P_->CollisionResult("Monster", ColList, CollisionType::Rect, CollisionType::Rect))
			{
				for (GameEngineCollision* ColActor : ColList)
				{
					Monster* ColMonster = dynamic_cast<Monster*>(ColActor->GetActor());
					if (ColMonster != nullptr)
					{
						if (ColMonster->GetHP() <= 0)
						{
							return;
						}

						else
						{
							ChangeState(PlayerState::Die);
						}
					}
				}
			}
		}

		if (GetLevel()->GetNameCopy() == "Monster1Level"
			|| GetLevel()->GetNameCopy() == "Monster2Level"
			|| GetLevel()->GetNameCopy() == "BossLevel")
		{
			std::vector<GameEngineCollision*> ColList;

			if (MainPlayer_1->CurState_ == PlayerState::Damaged
				|| MainPlayer_1->CurState_ == PlayerState::Fade)
			{
				if (true == Collision1P_->CollisionResult("2PColl", ColList, CollisionType::Rect, CollisionType::Rect))
				{
					if (MainPlayer_2->CurState_ == PlayerState::Damaged
						|| MainPlayer_2->CurState_ == PlayerState::Fade)
					{
						return;
					}

					for (size_t i = 0; i < ColList.size(); i++)
					{
						ChangeState(PlayerState::Revival);
						return;
					}
				}
			}
		}
		else
		{
				// 물방울에 갇힌 상태힐 때 다른 플레이어가 터뜨릴 수 있다
			{
				std::vector<GameEngineCollision*> ColList;

				if (MainPlayer_1->CurState_ == PlayerState::Damaged
					|| MainPlayer_1->CurState_ == PlayerState::Fade)
				{
					if (true == Collision1P_->CollisionResult("2PColl", ColList, CollisionType::Rect, CollisionType::Rect))
					{
						if (MainPlayer_2->CurState_ == PlayerState::Damaged
							|| MainPlayer_2->CurState_ == PlayerState::Fade)
						{
							return;
						}

						for (size_t i = 0; i < ColList.size(); i++)
						{
							ChangeState(PlayerState::Die);
							return;
						}
					}
				}
			}
		}
	}

	if (nullptr != MainPlayer_2)
	{
		if (Type == PlayerType::Player2)
		{
			// 무적이 아닐 때만
			if (/*false == IsShield
				&&*/ false == IsInvincible)
			{
				std::vector<GameEngineCollision*> ColList;

				if (true == Collision2P_->CollisionResult("Monster", ColList, CollisionType::Rect, CollisionType::Rect))
				{
					for (GameEngineCollision* ColActor : ColList)
					{
						Monster* ColMonster = dynamic_cast<Monster*>(ColActor->GetActor());
						if (ColMonster != nullptr)
						{
							if (ColMonster->GetHP() <= 0)
							{
								return;
							}

							else
							{
								ChangeState(PlayerState::Die);
							}
						}
					}
					//for (size_t i = 0; i < ColList.size(); i++)
					//{
					//	ChangeState(PlayerState::Die);
					//	return;
					//}
				}
			}

			if (GetLevel()->GetNameCopy() == "Monster1Level"
				|| GetLevel()->GetNameCopy() == "Monster2Level"
				|| GetLevel()->GetNameCopy() == "BossLevel")
			{
				std::vector<GameEngineCollision*> ColList;


				if (MainPlayer_2->CurState_ == PlayerState::Damaged
					|| MainPlayer_2->CurState_ == PlayerState::Fade)
				{
					if (true == Collision2P_->CollisionResult("1PColl", ColList, CollisionType::Rect, CollisionType::Rect))
					{
						if (MainPlayer_1->CurState_ == PlayerState::Damaged
							|| MainPlayer_1->CurState_ == PlayerState::Fade)
						{
							return;
						}

						for (size_t i = 0; i < ColList.size(); i++)
						{
							ChangeState(PlayerState::Revival);
							return;
						}
					}
				}
			}
			else {

					// 물방울에 갇힌 상태힐 때 다른 플레이어가 터뜨릴 수 있다
				{
					std::vector<GameEngineCollision*> ColList;


					if (MainPlayer_2->CurState_ == PlayerState::Damaged
						|| MainPlayer_2->CurState_ == PlayerState::Fade)
					{
						if (true == Collision2P_->CollisionResult("1PColl", ColList, CollisionType::Rect, CollisionType::Rect))
						{
							if (MainPlayer_1->CurState_ == PlayerState::Damaged
								|| MainPlayer_1->CurState_ == PlayerState::Fade)
							{
								return;
							}

							for (size_t i = 0; i < ColList.size(); i++)
							{
								ChangeState(PlayerState::Die);
								return;
							}
						}
					}
				}
			}
		}
	}

}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	PlayerInit();

}

void Player::Start()
{
	Collision1P_ = CreateCollision("1PColl", { 35.f, 35.f }, { 0.f, 10.f });
	Collision1P_->Off();

	Collision2P_ = CreateCollision("2PColl", { 35.f, 35.f }, { 0.f, 10.f });
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
		GameEngineImage* Bazzi4 = GameEngineImageManager::GetInst()->Find("Bazzi_4.bmp");
		Bazzi4->CutCount(5, 7);

		GameEngineImage* Devil = GameEngineImageManager::GetInst()->Find("Player_Devil.bmp");
		Devil->CutCount(5, 18);
		GameEngineImage* Effect = GameEngineImageManager::GetInst()->Find("Effect_Shield.bmp");
		Effect->CutCount(5, 2);

		// 쉴드 이펙트
		EffectRenderer_ = CreateRenderer((int)ORDER::UI);
		EffectRenderer_->SetPivotType(RenderPivot::CENTER);
		EffectRenderer_->SetPivot({ 0.f, 0.f });
		EffectRenderer_->CreateAnimation("Effect_Shield.bmp", "Effect_Shield", 0, 5, 0.03f, true);
		EffectRenderer_->ChangeAnimation("Effect_Shield");
		EffectRenderer_->Off();

		
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
		BazziRenderer_->CreateAnimation("Bazzi_4.bmp", "DamagedStart_", 6, 10, 0.07f, false);
		BazziRenderer_->CreateAnimation("Bazzi_4.bmp", "Damaged_", 11, 23, 0.2f, true);
		BazziRenderer_->CreateAnimation("Bazzi_4.bmp", "Fade_", 24, 31, 0.25f, true);
		BazziRenderer_->CreateAnimation("Bazzi_2.bmp", "Die_", 0, 5, 0.15f, false);
		BazziRenderer_->CreateAnimation("Bazzi_2.bmp", "Revival_", 6, 9, 0.15f, false);

		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "IdleOwl_Left", 0, 0, 0.15f, false);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "IdleOwl_Right", 2, 2, 0.15f, false);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "IdleOwl_Up", 4, 4, 0.15f, false);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "IdleOwl_Down", 6, 6, 0.15f, false);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "IdleTurtle_Left", 8, 8, 0.15f, false);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "IdleTurtle_Right", 10, 10, 0.15f, false);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "IdleTurtle_Up", 12, 12, 0.15f, false);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "IdleTurtle_Down", 14, 14, 0.15f, false);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingOwl_Left", 0, 1, 0.15f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingOwl_Right", 2, 3, 0.15f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingOwl_Up", 4, 5, 0.15f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingOwl_Down", 6, 7, 0.15f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingTurtle_Left", 8, 9, 0.2f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingTurtle_Right", 10, 11, 0.2f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingTurtle_Up", 12, 13, 0.2f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingTurtle_Down", 14, 15, 0.2f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingUFO_Left", 16, 16, 0.09f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingUFO_Right", 17, 17, 0.09f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingUFO_Up", 18, 18, 0.09f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "RidingUFO_Down", 19, 19, 0.09f, true);

		BazziRenderer_->CreateAnimation("Player_Devil.bmp", "Idle_Left_Devil", 0, 1, 0.15f, true);
		BazziRenderer_->CreateAnimation("Player_Devil.bmp", "Idle_Right_Devil", 2, 3, 0.15f, true);
		BazziRenderer_->CreateAnimation("Player_Devil.bmp", "Idle_Up_Devil", 4, 5, 0.15f, true);
		BazziRenderer_->CreateAnimation("Player_Devil.bmp", "Idle_Down_Devil", 6, 7, 0.15f, true);
		BazziRenderer_->CreateAnimation("Player_Devil.bmp", "Move_Left_Devil", 8, 12, 0.1f, true);
		BazziRenderer_->CreateAnimation("Player_Devil.bmp", "Move_Right_Devil", 13, 17, 0.1f, true);
		BazziRenderer_->CreateAnimation("Player_Devil.bmp", "Move_Up_Devil", 18, 24, 0.1f, true);
		BazziRenderer_->CreateAnimation("Player_Devil.bmp", "Move_Down_Devil", 25, 31, 0.1f, true);

		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "OnOwl_", 0, 7, 0.035f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "OnTurtle_", 8, 15, 0.035f, true);
		BazziRenderer_->CreateAnimation("Bazzi_3.bmp", "OnUFO_", 16, 19, 0.05f, true);

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
		GameEngineImage* Marid3 = GameEngineImageManager::GetInst()->Find("luxMarid_3.bmp");
		Marid3->CutCount(5, 4);
		GameEngineImage* Marid4 = GameEngineImageManager::GetInst()->Find("luxMarid_4.bmp");
		Marid4->CutCount(5, 4);
		GameEngineImage* Marid5 = GameEngineImageManager::GetInst()->Find("luxMarid_5.bmp");
		Marid5->CutCount(5, 6);

		// 애니메이션
		MaridRenderer_ = CreateRenderer((int)ORDER::PLAYER, RenderPivot::CENTER, float4{ 0.f, 0.f });

		// Idle
		MaridRenderer_->CreateAnimation("luxMarid_4.bmp", "Ready_", 0, 17, 0.06f, false);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Idle_Right", 0, 0, 1.f, false);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Idle_Left", 6, 6, 1.f, false);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Idle_Up", 12, 12, 1.f, false);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Idle_Down", 18, 18, 1.f, false);

		// Move
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Move_Right", 1, 5, 0.1f, true);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Move_Left", 7, 11, 0.1f, true);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Move_Up", 13, 17, 0.09f, true);
		MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Move_Down", 19, 23, 0.09f, true);

		//MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Win_", 29, 36, 0.1f, true);
		MaridRenderer_->CreateAnimation("luxMarid_5.bmp", "DamagedStart_", 0, 4, 0.07f, false); // 0.2   0.25
		MaridRenderer_->CreateAnimation("luxMarid_5.bmp", "Damaged_", 5, 18, 0.2f, true); // 0.2   0.25
		MaridRenderer_->CreateAnimation("luxMarid_5.bmp", "Fade_", 19, 25, 0.25f, false);
		MaridRenderer_->CreateAnimation("luxMarid_2.bmp", "Die_", 0, 5, 0.15f, false);
		MaridRenderer_->CreateAnimation("luxMarid_2.bmp", "Revival_", 6, 9, 0.15f, false);

		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "IdleOwl_Left", 0, 0, 0.15f, false);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "IdleOwl_Right", 2, 2, 0.15f, false);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "IdleOwl_Up", 4, 4, 0.15f, false);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "IdleOwl_Down", 6, 6, 0.15f, false);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "IdleTurtle_Left", 8, 8, 0.15f, false);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "IdleTurtle_Right", 10, 10, 0.15f, false);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "IdleTurtle_Down", 12, 12, 0.15f, false);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "IdleTurtle_Up", 14, 14, 0.15f, false);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingOwl_Left", 0, 1, 0.15f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingOwl_Right", 2, 3, 0.15f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingOwl_Up", 4, 5, 0.15f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingOwl_Down", 6, 7, 0.15f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingTurtle_Left", 8, 9, 0.2f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingTurtle_Right", 10, 11, 0.2f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingTurtle_Up", 14, 15, 0.2f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingTurtle_Down", 12, 13, 0.2f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingUFO_Left", 16, 16, 0.09f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingUFO_Right", 17, 17, 0.09f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingUFO_Up", 18, 18, 0.09f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingUFO_Down", 19, 19, 0.09f, true);

		MaridRenderer_->CreateAnimation("Player_Devil.bmp", "Idle_Right_Devil", 60, 61, 0.15f, true);
		MaridRenderer_->CreateAnimation("Player_Devil.bmp", "Idle_Left_Devil", 62, 63, 0.15f, true);
		MaridRenderer_->CreateAnimation("Player_Devil.bmp", "Idle_Up_Devil", 64, 65, 0.15f, true);
		MaridRenderer_->CreateAnimation("Player_Devil.bmp", "Idle_Down_Devil", 66, 67, 0.15f, true);
		MaridRenderer_->CreateAnimation("Player_Devil.bmp", "Move_Right_Devil", 68, 72, 0.1f, true);
		MaridRenderer_->CreateAnimation("Player_Devil.bmp", "Move_Left_Devil", 73, 77, 0.1f, true);
		MaridRenderer_->CreateAnimation("Player_Devil.bmp", "Move_Up_Devil", 78, 82, 0.1f, true);
		MaridRenderer_->CreateAnimation("Player_Devil.bmp", "Move_Down_Devil", 83, 87, 0.1f, true);

		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "OnOwl_", 0, 7, 0.035f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "OnTurtle_", 8, 15, 0.035f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "OnUFO_", 16, 19, 0.05f, true);


		MaridRenderer_->ChangeAnimation("Ready_");
		CurState_ = PlayerState::Ready;
		AnimationName_ = "Ready_";
		ChangeDirText_ = "Down";


		//MaridRenderer_->ChangeAnimation("Damaged_");
		//CurState_ = PlayerState::Damaged;
		//AnimationName_ = "Damaged_";
		//ChangeDirText_ = "Down";

		//BazziRenderer_->ChangeAnimation("Idle_Down");
		//AnimationName_ = "Idle_";
		//ChangeDirText_ = "Down";
		//ChangeState(PlayerState::Idle);


		MaridRenderer_->Off();
	}


	// Dao
	{
		GameEngineImage* Dao1 = GameEngineImageManager::GetInst()->Find("Dao_1.bmp");
		Dao1->CutCount(5, 12);
		GameEngineImage* Dao2 = GameEngineImageManager::GetInst()->Find("Dao_2.bmp");
		Dao2->CutCount(5, 2);
		GameEngineImage* Dao3 = GameEngineImageManager::GetInst()->Find("Dao_3.bmp");
		Dao3->CutCount(5, 4);
		GameEngineImage* Dao4 = GameEngineImageManager::GetInst()->Find("Dao_4.bmp");
		Dao4->CutCount(5, 4);
		GameEngineImage* Dao5 = GameEngineImageManager::GetInst()->Find("Dao_5.bmp");
		Dao5->CutCount(5, 6);

		// 애니메이션
		DaoRenderer_ = CreateRenderer((int)ORDER::PLAYER, RenderPivot::CENTER, float4{ 0.f, 0.f });

		// Idle4
		DaoRenderer_->CreateAnimation("Dao_4.bmp", "Ready_", 0, 17, 0.06f, false);
		DaoRenderer_->CreateAnimation("Dao_1.bmp", "Idle_Right", 0, 0, 1.f, false);
		DaoRenderer_->CreateAnimation("Dao_1.bmp", "Idle_Left", 6, 6, 1.f, false);
		DaoRenderer_->CreateAnimation("Dao_1.bmp", "Idle_Up", 12, 12, 1.f, false);
		DaoRenderer_->CreateAnimation("Dao_1.bmp", "Idle_Down", 18, 18, 1.f, false);

		// Move
		DaoRenderer_->CreateAnimation("Dao_1.bmp", "Move_Right", 1, 5, 0.1f, true);
		DaoRenderer_->CreateAnimation("Dao_1.bmp", "Move_Left", 7, 11, 0.1f, true);
		DaoRenderer_->CreateAnimation("Dao_1.bmp", "Move_Up", 13, 17, 0.09f, true);
		DaoRenderer_->CreateAnimation("Dao_1.bmp", "Move_Down", 19, 23, 0.09f, true);

		//MaridRenderer_->CreateAnimation("luxMarid_1.bmp", "Win_", 29, 36, 0.1f, true);
		DaoRenderer_->CreateAnimation("Dao_5.bmp", "DamagedStart_", 0, 4, 0.07f, false); // 0.2   0.25
		DaoRenderer_->CreateAnimation("Dao_5.bmp", "Damaged_", 5, 18, 0.2f, true); // 0.2   0.25
		DaoRenderer_->CreateAnimation("Dao_5.bmp", "Fade_", 19, 25, 0.25f, false);
		DaoRenderer_->CreateAnimation("Dao_2.bmp", "Die_", 0, 5, 0.15f, false);
		DaoRenderer_->CreateAnimation("Dao_2.bmp", "Revival_", 6, 9, 0.15f, false);

		DaoRenderer_->CreateAnimation("Dao_3.bmp", "IdleOwl_Left", 0, 0, 0.15f, false);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "IdleOwl_Right", 2, 2, 0.15f, false);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "IdleOwl_Up", 4, 4, 0.15f, false);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "IdleOwl_Down", 6, 6, 0.15f, false);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "IdleTurtle_Left", 8, 8, 0.15f, false);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "IdleTurtle_Right", 10, 10, 0.15f, false);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "IdleTurtle_Up", 12, 12, 0.15f, false);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "IdleTurtle_Down", 14, 14, 0.15f, false);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingOwl_Left", 0, 1, 0.15f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingOwl_Right", 2, 3, 0.15f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingOwl_Up", 4, 5, 0.15f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingOwl_Down", 6, 7, 0.15f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingTurtle_Left", 8, 9, 0.2f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingTurtle_Right", 10, 11, 0.2f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingTurtle_Up", 12, 13, 0.2f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingTurtle_Down", 14, 15, 0.2f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingUFO_Up", 16, 16, 0.09f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingUFO_Down", 17, 17, 0.09f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingUFO_Left", 18, 18, 0.09f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingUFO_Right", 19, 19, 0.09f, true);

		DaoRenderer_->CreateAnimation("Player_Devil.bmp", "Idle_Left_Devil", 32, 33, 0.15f, true);
		DaoRenderer_->CreateAnimation("Player_Devil.bmp", "Idle_Right_Devil", 34, 35, 0.15f, true);
		DaoRenderer_->CreateAnimation("Player_Devil.bmp", "Idle_Up_Devil",36, 37, 0.15f, true);
		DaoRenderer_->CreateAnimation("Player_Devil.bmp", "Idle_Down_Devil", 38, 39, 0.15f, true);
		DaoRenderer_->CreateAnimation("Player_Devil.bmp", "Move_Left_Devil", 40, 44, 0.1f, true);
		DaoRenderer_->CreateAnimation("Player_Devil.bmp", "Move_Right_Devil", 45, 49, 0.1f, true);
		DaoRenderer_->CreateAnimation("Player_Devil.bmp", "Move_Up_Devil", 50, 54, 0.1f, true);
		DaoRenderer_->CreateAnimation("Player_Devil.bmp", "Move_Down_Devil", 55, 59, 0.1f, true);

		DaoRenderer_->CreateAnimation("Dao_3.bmp", "OnOwl_", 0, 7, 0.035f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "OnTurtle_", 8, 15, 0.035f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "OnUFO_", 16, 19, 0.05f, true);


		DaoRenderer_->ChangeAnimation("Ready_");
		CurState_ = PlayerState::Ready;
		AnimationName_ = "Ready_";
		ChangeDirText_ = "Down";

		//DaoRenderer_->ChangeAnimation("Damaged_");
		//CurState_ = PlayerState::Damaged;
		//AnimationName_ = "Damaged_";
		//ChangeDirText_ = "Down";

		DaoRenderer_->Off();


		
		ArrowRenderer_1P = CreateRenderer((int)ORDER::UI, RenderPivot::CENTER, float4{ 0.f, -53.f });
		ArrowRenderer_1P->CreateAnimation("1P_Arrow.bmp", "1P_Arrow", 0, 16, 0.06f, true);
		ArrowRenderer_1P->ChangeAnimation("1P_Arrow");
		ArrowRenderer_1P->Off();
		
		ArrowRenderer_2P = CreateRenderer((int)ORDER::UI, RenderPivot::CENTER, float4{ 25.f, -57.f });
		ArrowRenderer_2P->CreateAnimation("2P_Arrow.bmp", "2P_Arrow", 0, 10, 0.1f, true);
		ArrowRenderer_2P->ChangeAnimation("2P_Arrow");
		ArrowRenderer_2P->Off();
		
	}


	if (false == GameEngineInput::GetInst()->IsKey("1PLeft"))
	{
		// =============== 1P 이동 ===============
		GameEngineInput::GetInst()->CreateKey("1PLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("1PRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("1PUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("1PDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("1PAttack", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("1PItem", VK_HANJA);

		// =============== 2P 이동 ===============
		GameEngineInput::GetInst()->CreateKey("2PLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("2PRight", 'D');
		GameEngineInput::GetInst()->CreateKey("2PUp", 'W');
		GameEngineInput::GetInst()->CreateKey("2PDown", 'S');
		GameEngineInput::GetInst()->CreateKey("2PAttack", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("2PItem", VK_LCONTROL);

		// ============== 디버그 모드 =============
		GameEngineInput::GetInst()->CreateKey("Invincible", 'O');
		GameEngineInput::GetInst()->CreateKey("Revival", 'I');
		GameEngineInput::GetInst()->CreateKey("Jump", 'J');

		//GameEngineInput::GetInst()->CreateKey("2POn", 'X');
	}

	IsReady = true;
	//PlayerInit();

}

void Player::Update()
{
	ColMapUpdate();

	CharTypeUpdate();

	PlayerStateUpdate();
	PlayerCollisionUpdate();

	ItemTime();
	TileCheckResult();
	FrontBlockCheck();
	CollisionCheck();

	DebugModeSwitch();

	// ======= 테스트 중 
	/*if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}*/
}

void Player::Render()
{

	//std::string IndexX = "";
	//std::string IndexY = "";


	//TileIndex TileIndex_ = MapTile_->GetTileIndex(GetPosition() - float4{ 20,20 });
	//IndexX = "Index X : " + std::to_string(TileIndex_.X);
	//IndexY = "Index Y : " + std::to_string(TileIndex_.Y);


	//TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 30, IndexX.c_str(), static_cast<int>(IndexX.length()));
	//TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 10, IndexY.c_str(), static_cast<int>(IndexY.length()));

	//std::string Posx = "";
	//std::string Posy = "";
	
	//Posx = "Pos x : " + std::to_string(GetPosition().ix());
	//Posy = "Pos y : " + std::to_string(GetPosition().iy());

	/*TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 30, Posx.c_str(), static_cast<int>(Posx.length()));
	TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 10, Posy.c_str(), static_cast<int>(Posy.length()));*/
	if (true == GetLevel()->GetIsDebug())
	{
		std::string State = "";
		std::string RideState = "";

		std::string CurSpeed = "";
		std::string CurAttCount = "";
		std::string CurAttPower = "";
		std::string MaxSpeed = "";
		std::string MaxAttCount = "";
		std::string MaxAttPower = "";

		if (CurState_ == PlayerState::Ready)
		{
			State = "STATE : Ready";
		}
		else if (CurState_ == PlayerState::Idle)
		{
			State = "STATE : Idle";
		}
		else if (CurState_ == PlayerState::Move)
		{
			State = "STATE : Move";
		}
		else if (CurState_ == PlayerState::Jump)
		{
			State = "STATE : Jump";
		}
		else if (CurState_ == PlayerState::Attack)
		{
			State = "STATE : Attack";
		}
		else if (CurState_ == PlayerState::Damaged)
		{
			State = "STATE : Damaged";
		}
		else if (CurState_ == PlayerState::Revival)
		{
			State = "STATE : Revival";
		}
		else if (CurState_ == PlayerState::Fade)
		{
			State = "STATE : Fade";
		}
		else if (CurState_ == PlayerState::Die)
		{
			State = "STATE : Die";
		}
		else if (CurState_ == PlayerState::IdleRide && PlayerRideState_ == PlayerRideState::Owl)
		{
			State = "STATE : IdleOwl";
		}
		else if (CurState_ == PlayerState::IdleRide && PlayerRideState_ == PlayerRideState::Turtle)
		{
			State = "STATE : IdleTurtle";
		}
		else if (CurState_ == PlayerState::RidingRide && PlayerRideState_ == PlayerRideState::Owl)
		{
			State = "STATE : RidingOwl";
		}
		else if (CurState_ == PlayerState::RidingRide && PlayerRideState_ == PlayerRideState::Turtle)
		{
			State = "STATE : RidingTurtle";
		}
		else if (CurState_ == PlayerState::RidingRide && PlayerRideState_ == PlayerRideState::UFO)
		{
			State = "STATE : RidingUFO";
		}

		if (PlayerRideState_ == PlayerRideState::UFO)
		{
			RideState = "RIDE : UFO";
		}
		else if (PlayerRideState_ == PlayerRideState::Max)
		{
			RideState = "RIDE : MAX";
		}

		CurSpeed = "SPEED : " + std::to_string(CurSpeed_);
		CurAttCount = "COUNT : " + std::to_string(CurAttCount_);;
		CurAttPower = "POWER : " + std::to_string(CurAttPower_);;
		MaxSpeed = "MAXSPEED : " + std::to_string(MaxSpeed_);;
		MaxAttCount = "MAXCOUNT : " + std::to_string(MaxAttCount_);;
		MaxAttPower = "MAXPOWER : " + std::to_string(MaxAttPower_);;

		SetBkMode(GameEngine::BackBufferDC(), OPAQUE);
		SetTextColor(GameEngine::BackBufferDC(), RGB(0, 0, 0));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 50, State.c_str(), static_cast<int>(State.length()));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 30, CurSpeed.c_str(), static_cast<int>(CurSpeed.length()));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 10, CurAttCount.c_str(), static_cast<int>(CurAttCount.length()));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() + 10, CurAttPower.c_str(), static_cast<int>(CurAttPower.length()));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() + 30, MaxSpeed.c_str(), static_cast<int>(MaxSpeed.length()));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() + 50, MaxAttCount.c_str(), static_cast<int>(MaxAttCount.length()));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() + 70, MaxAttPower.c_str(), static_cast<int>(MaxAttPower.length()));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() + 100, RideState.c_str(), static_cast<int>(RideState.length()));

	}


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
		case PlayerState::DamageStart:
			DamagedStartStart();
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
		case PlayerState::OnRide:
			OnRideStart();
			break;
		case PlayerState::OffRide:
			OffRideStart();
			break;
		case PlayerState::IdleRide:
			IdleRideStart();
			break;
		case PlayerState::RidingRide:
			RidingRideStart();
			break;

		}

	}

	CurState_ = _State;
}

void Player::PlayerStateUpdate()
{
	switch (CurState_)
	{
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
	case PlayerState::DamageStart:
		DamagedStartUpdate();
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
	case PlayerState::OnRide:
		OnRideUpdate();
		break;
	case PlayerState::OffRide:
		OffRideUpdate();
		break;
	case PlayerState::IdleRide:
		IdleRideUpdate();
		break;
	case PlayerState::RidingRide:
		RidingRideUpdate();
		break;

	}
}

void Player::DirAnimationCheck()
{
	if (CheckDir_ != CurDir_)
	{
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
		CurDir_ = CheckDir_;
	}
}


