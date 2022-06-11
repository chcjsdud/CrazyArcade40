#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>
#include "MapGameObject.h"
#include "MapBackGround.h"
#include "GameEngine/GameEngine.h"
#include "GameItemObject.h"

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
	, MaridRenderer_(nullptr)
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
	, CheckDir_(PlayerDir::None)
	, IsBoomblock(false)
	, Time_(0.0f)
	, CurBlockType1_(BlockType::NoBlock)
	, CurBlockType2_(BlockType::NoBlock)
	, LeftBlock(BlockType::Max)
	, RightBlock(BlockType::Max)
	, UpBlock(BlockType::Max)
	, DownBlock(BlockType::Max)
	, Boom_(nullptr)
	, IsReady(true)
	, AttMoveTime_(0.0f)
	, MapTile_(nullptr)
	, IsLive(true)
{
	BazziAttCount_ = 1;
	MaridAttCount_ = 2;
	DaoAttCount_ = 1;

	BazziAttPower_ = 1.f;
	MaridAttPower_ = 1.f;
	DaoAttPower_ = 1.f;

	BazziSpeed_ = 5.f;
	MaridSpeed_ = 5.f;
	DaoSpeed_ = 5.f;

	BazziMaxAttCount_ = 6;
	MaridMaxAttCount_ = 9;
	DaoMaxAttCount_ = 10;

	BazziMaxAttPower_ = 7.f;
	MaridMaxAttPower_ = 6.f;
	DaoMaxAttPower_ = 7.f;

	BazziMaxSpeed_ = 9.f;
	MaridMaxSpeed_ = 9.f;
	DaoMaxSpeed_ = 7.f;

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

void Player::Move(float _CurSpeed)
{

	MoveDir = float4::ZERO;

	if (Type == PlayerType::Player1)
	{
		_CurSpeed = MainPlayer_1->CurSpeed_;
		MovePos_ = _CurSpeed * 7.f;

		if (CurState_ != PlayerState::Ready)
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

			if ((true == GameEngineInput::GetInst()->IsUp("1PRight") && CheckDir_ == PlayerDir::Right)
				|| (true == GameEngineInput::GetInst()->IsUp("1PLeft") && CheckDir_ == PlayerDir::Left)
				|| (true == GameEngineInput::GetInst()->IsUp("1PUp") && CheckDir_ == PlayerDir::Up)
				|| (true == GameEngineInput::GetInst()->IsUp("1PDown") && CheckDir_ == PlayerDir::Down))
			{
				CheckDir_ = PlayerDir::None;
			}
		}

		///////////////////////////////////////////////////////////

		if (CheckDir_ == PlayerDir::Left)
		{
			if (true == IsLeftMove)
			{
				MoveDir.x = -MovePos_;
			}

		}
		else if (CheckDir_ == PlayerDir::Right)
		{
			if (true == IsRightMove)
			{
				MoveDir.x = MovePos_;
			}

		}
		else if (CheckDir_ == PlayerDir::Up)
		{
			if (true == IsUpMove)
			{
				MoveDir.y = -MovePos_;
			}

		}
		else if (CheckDir_ == PlayerDir::Down)
		{
			if (true == IsDownMove)
			{
				MoveDir.y = MovePos_;
			}
		}
	}

	else if (Type == PlayerType::Player2)
	{
		_CurSpeed = MainPlayer_2->CurSpeed_;
		MovePos_ = _CurSpeed * 7.f;

		if (CurState_ != PlayerState::Ready)
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


			if ((true == GameEngineInput::GetInst()->IsUp("2PRight") && CheckDir_ == PlayerDir::Right)
				|| (true == GameEngineInput::GetInst()->IsUp("2PLeft") && CheckDir_ == PlayerDir::Left)
				|| (true == GameEngineInput::GetInst()->IsUp("2PUp") && CheckDir_ == PlayerDir::Up)
				|| (true == GameEngineInput::GetInst()->IsUp("2PDown") && CheckDir_ == PlayerDir::Down))
			{
				CheckDir_ = PlayerDir::None;
			}
			

			///////////////////////////////////////////////////////////

			if (CheckDir_ == PlayerDir::Left)
			{
				if (true == IsLeftMove)
				{
					MoveDir.x = -MovePos_;
				}

			}
			else if (CheckDir_ == PlayerDir::Right)
			{
				if (true == IsRightMove)
				{
					MoveDir.x = MovePos_;
				}

			}
			else if (CheckDir_ == PlayerDir::Up)
			{
				if (true == IsUpMove)
				{
					MoveDir.y = -MovePos_;
				}

			}
			else if (CheckDir_ == PlayerDir::Down)
			{
				if (true == IsDownMove)
				{
					MoveDir.y = MovePos_;
				}
			}
		}

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
	if (Type == PlayerType::Player1)
	{
		float4 Pos = MainPlayer_1->GetPosition();
		//CurItemType1_ = CheckItem(Pos + float4{ -20.0f,-20.0f });
		GameItemObject* Item = GetLevel()->CreateActor<GameItemObject>(static_cast<int>(ORDER::MAPOBJECT));
		Item->SetMapTile(MapTile_);
		CurItemType1_ = Item->CheckItem(Pos + float4{ -20.0f,-20.0f });

		ItemCheck(MainPlayer_1, CurItemType1_);
		if (true == IsItemKey())
		{
			ItemCheck(MainPlayer_1, CurItemType1_);
		}
	}

	if (nullptr != MainPlayer_2)
	{
		if (Type == PlayerType::Player2)
		{
			float4 Pos = MainPlayer_2->GetPosition();
			//CurItemType2_ = CheckItem(Pos + float4{ -20.0f, -20.0f });
			GameItemObject* Item = GetLevel()->CreateActor<GameItemObject>(static_cast<int>(ORDER::MAPOBJECT));
			Item->SetMapTile(MapTile_);
			CurItemType2_ = Item->CheckItem(Pos + float4{ -20.0f,-20.0f });

			if (true == IsItemKey())
			{
				ItemCheck(MainPlayer_2, CurItemType2_);
			}
		}
	}
}

void Player::ItemCheck(Player* _Player, ItemType _ItemType)
{
	CurCharacter = GetCharacter();

	switch (_ItemType)
	{
	case ItemType::Roller:
	{
		if (_Player->CurSpeed_ >= _Player->MaxSpeed_)
		{
			return;
		}

		_Player->CurSpeed_ += 1;
	/*	switch (CurCharacter)
		{
		case Character::BAZZI:
		{
			if (CurSpeed_ >= BazziMaxSpeed_)
			{
				return;
			}
		}
		break;
		case Character::LUXMARID:
		{
			if (CurSpeed_ >= MaridMaxSpeed_)
			{
				return;
			}
		}
		break;
		case Character::DAO:
		{
			if (CurSpeed_ >= DaoMaxSpeed_)
			{
				return;
			}
		}
		break;
		default:
			break;

		}

		_Player->CurSpeed_ += 1;*/
	}
	break;
	case ItemType::Bubble:
	{
		if (_Player->CurAttCount_ >= _Player->MaxAttCount_)
		{
			return;
		}

		_Player->CurAttCount_ += 1;

		/*switch (CurCharacter)
		{
		case Character::BAZZI:
		{
			if (CurAttCount_ >= BazziMaxAttCount_)
			{
				return;
			}
		}
		break;
		case Character::LUXMARID:
		{
			if (CurAttCount_ >= MaridMaxAttCount_)
			{
				return;
			}
		}
		break;
		case Character::DAO:
		{
			if (CurAttCount_ >= DaoMaxAttCount_)
			{
				return;
			}
		}
		break;
		default:
			break;
		}

		_Player->CurAttCount_ += 1;*/
	}
	break;
	case ItemType::Fluid:
	{
		if (_Player->CurAttPower_ >= _Player->MaxAttPower_)
		{
			return;
		}

		_Player->CurAttPower_ += 1;

		/*switch (CurCharacter)
		{
		case Character::BAZZI:
		{
			if (CurAttPower_ >= BazziMaxAttPower_)
			{
				return;
			}
		}
		break;
		case Character::LUXMARID:
		{
			if (CurAttPower_ >= MaridMaxAttPower_)
			{
				return;
			}
		}
		break;
		case Character::DAO:
		{
			if (CurAttPower_ >= DaoMaxAttPower_)
			{
				return;
			}
		}
		break;
		default:
			break;
		}

		_Player->CurAttCount_ += 1;*/
	}
	break;
	case ItemType::RedDevil:
	{
		if (_Player->CurSpeed_ == _Player->MaxSpeed_)
		{
			return;
		}

		_Player->CurSpeed_ = _Player->MaxSpeed_;
		/*switch (CurCharacter)
		{
		case Character::BAZZI:
		{
			if (CurSpeed_ == MaxSpeed_)
			{
				return;
			}
			CurSpeed_ = MaxSpeed_;
		}
		break;
		case Character::LUXMARID:
		{
			if (CurSpeed_ == MaxSpeed_)
			{
				return;
			}
			CurSpeed_ = MaxSpeed_;
		}
		break;
		case Character::DAO:
		{
			if (CurSpeed_ == MaxSpeed_)
			{
				return;
			}
			CurSpeed_ = MaxSpeed_;
		}
		break;
		default:
			break;
		}*/

	}
	break;
	case ItemType::UltraBubble:
	{
		if (_Player->CurAttPower_ == _Player->MaxAttPower_)
		{
			return;
		}

		_Player->CurAttPower_ = _Player->MaxAttPower_;
	}
	break;
	case ItemType::Niddle:
	{
		ChangeState(PlayerState::Revival);
		return;
	}
	break;
	case ItemType::Devil:
	{
		if (CurDir_ == PlayerDir::Left)
		{
			CheckDir_ = PlayerDir::Right;
			ChangeDirText_ = "Right";
		}
		else if (CurDir_ == PlayerDir::Right)
		{
			CheckDir_ = PlayerDir::Left;
			ChangeDirText_ = "Left";
		}
		else if (CurDir_ == PlayerDir::Up)
		{
			CheckDir_ = PlayerDir::Down;
			ChangeDirText_ = "Down";
		}
		else if (CurDir_ == PlayerDir::Down)
		{
			CheckDir_ = PlayerDir::Up;
			ChangeDirText_ = "Up";
		}
	}
	break;
	case ItemType::Shoes:
	{
		// 물방울 던지기 
	}
	break;
	case ItemType::Shield:
	{
		AddAccTime(Time_);

		// 3초가 지나기 전은 무적
		if (3.f > GetAccTime())
		{
			IsInvincible = true;
		}
		else // 3초가 지나면 무적 해제 및 ResetTime
		{
			IsInvincible = false;
			ReSetAccTime();
		}
	}
	break;
	case ItemType::SuperJump:
	{

	}
	break;
	case ItemType::Owl:
	{
		ChangeState(PlayerState::OnOwl);
		return;
	}
	break;
	case ItemType::Turtle:
	{
		ChangeState(PlayerState::OnTurtle);
		return;
	}
	break;
	case ItemType::SpaceShip:
	{
		ChangeState(PlayerState::OnUFO);
		return;
	}
	break;
	case ItemType::Bubble_Dark:
	{
		// 물풍선 이미지 변경
	}
	break;
	default:
		break;
	}

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

void Player::Attack()
{
	float4 ModifyPos = float4{ -20.f, -20.f };

	if (Type == PlayerType::Player1)
	{
		Boom_ = GetLevel()->CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
		Boom_->SetMapTile(MapTile_);
		Boom_->CreateBoom(MainPlayer_1->GetPosition() + ModifyPos, Player::MainPlayer_1->CurAttPower_);
	}

	if (Type == PlayerType::Player2)
	{
		Boom_ = GetLevel()->CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
		Boom_->SetMapTile(MapTile_);
		Boom_->CreateBoom(MainPlayer_2->GetPosition() + ModifyPos, Player::MainPlayer_2->CurAttPower_);
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

		//SetAttCount(BazziAttCount_);
		//SetAttPower(BazziAttPower_);
		//SetSpeed(BazziSpeed_);

		//SetMaxAttCount(BazziMaxAttCount_);
		//SetMaxAttPower(BazziMaxAttPower_);
		//SetMaxSpeed(BazziMaxSpeed_);
	}
	break;
	case Character::LUXMARID:
	{
		MaridRenderer_->On();
		PlayerAnimationRender_ = MaridRenderer_;
		PlayerAnimationRender_->On();

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
		DaoRenderer_->On();
		PlayerAnimationRender_ = DaoRenderer_;
		PlayerAnimationRender_->On();

		SetAttCount(DaoAttCount_);
		SetAttPower(DaoAttPower_);
		SetSpeed(DaoSpeed_);

		SetMaxAttCount(DaoMaxAttCount_);
		SetMaxAttPower(DaoMaxAttPower_);
		SetMaxSpeed(DaoMaxSpeed_);
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

// 플레이어의 현재 타일 체크 
void Player::TileCheckResultUpdate(BlockType _CurBlockType)
{
	switch (_CurBlockType)
	{
	case BlockType::WaveBlock:
	{
		// 무적이 아닐 때만
		if (false == IsInvincible)
		{
			// 탈 것을 타고 있는 상태에서는 -> Idle
			if (CurState_ == PlayerState::IdleOwl
				|| CurState_ == PlayerState::IdleTurtle
				|| CurState_ == PlayerState::RidingOwl
				|| CurState_ == PlayerState::RidingTurtle
				|| CurState_ == PlayerState::RidingUFO)
			{
				ChangeState(PlayerState::Idle);
				return;
			}

			if (CurState_ != PlayerState::Die
				&& CurState_ != PlayerState::DamageStart
				&& CurState_ != PlayerState::Damaged
				&& CurState_ != PlayerState::Fade)
			{
				ChangeState(PlayerState::DamageStart);
				return;
			}
		}
		else
		{
			return;

		}
	}
		break;
	case BlockType::BubbleBlock:
	{
		// 무적이 아닐 때만
		if (false == IsInvincible)
		{
			// 탈 것을 타고 있는 상태에서는 -> Idle
			if (CurState_ == PlayerState::IdleOwl
				|| CurState_ == PlayerState::IdleTurtle
				|| CurState_ == PlayerState::RidingOwl
				|| CurState_ == PlayerState::RidingTurtle
				|| CurState_ == PlayerState::RidingUFO)
			{
				ChangeState(PlayerState::Idle);
				return;
			}

			if (CurState_ != PlayerState::Die
				&& CurState_ != PlayerState::DamageStart
				&& CurState_ != PlayerState::Damaged
				&& CurState_ != PlayerState::Fade)
			{
				ChangeState(PlayerState::DamageStart);
				return;
			}
		}
		else
		{
			return;
		}
	}
		break;
	case BlockType::BushBlock:
	{
		PlayerAnimationRender_->SetAlpha(0);
			
	}
	break;
	case BlockType::ItemBlock:		// 아이템 체크하는 부분 
	{
		GameEngineSound::SoundPlayOneShot("eat_item.mp3");
		//int a = 0;
		PlayerInfoUpdate();
	}
	break;
	case BlockType::BoomBlock:
	{
		IsBoomblock = true;
		break;
	}
	break;
	default:
	{
		IsBoomblock = false;
		PlayerAnimationRender_->SetAlpha(255);
	}
	break;
	}

	// UFO를 탄 상태가 아닐 때만 아이템 체크 
	//if (CurState_ != PlayerState::RidingUFO)
	//{
	//	PlayerInfoUpdate();
	//}
	//
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

// 앞 뒤 양옆 블럭을 체크한 뒤 할 일
void Player::FrontBlockCheckUpdate()
{
	float4 Pos = {};
	if (Type == PlayerType::Player1)
	{
		Pos = MainPlayer_1->GetPosition();
	}
	else if (Type == PlayerType::Player2)
	{
		Pos = MainPlayer_2->GetPosition();
	}

	// 왼쪽 블럭
	switch (LeftBlock)
	{
	case BlockType::BoomBlock:
	{
		if (IsBoomblock == false) {
			IsLeftMove = false;
		}
	}
	break;
	case BlockType::FixBlock:
	{
		IsLeftMove = false;
	}
	break;
	case BlockType::PullBlock:
	{
		IsLeftMove = false;	

		Box_ = GetLevel()->CreateActor<MapGameObject>();
		Box_->SetMapTile(MapTile_);
		if (PlayerDir::Left == CurDir_)
		{
			Box_->PushBlock(Pos + float4{-40.0f, -20.0f}, BlockDir::LEFT);

		}
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
		if (IsBoomblock == false) {
			IsRightMove = false;
		}
	}
	break;
	case BlockType::FixBlock:
	{
		IsRightMove = false;
	}
	break;
	case BlockType::PullBlock:
	{
		IsRightMove = false;

		Box_ = GetLevel()->CreateActor<MapGameObject>();
		Box_->SetMapTile(MapTile_);
		if (PlayerDir::Right == CurDir_)
		{
			Box_->PushBlock(Pos + float4{ 0.0f, -20.0f }, BlockDir::RIGHT);

		}
		
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
		if (IsBoomblock == false) {
			IsUpMove = false;
		}
	}
	break;
	case BlockType::FixBlock:
	{
		IsUpMove = false;
	}
	break;
	case BlockType::PullBlock:
	{
		IsUpMove = false;

		Box_ = GetLevel()->CreateActor<MapGameObject>();
		Box_->SetMapTile(MapTile_);
		if (PlayerDir::Up == CurDir_)
		{
			Box_->PushBlock(Pos + float4{ -20.0f, -40.0f }, BlockDir::UP);

		}
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
		if (IsBoomblock == false) {
			IsDownMove = false;
		}
	}
	break;
	case BlockType::FixBlock:
	{
		IsDownMove = false;
	}
	break;
	case BlockType::PullBlock:
	{
		IsDownMove = false;

		Box_ = GetLevel()->CreateActor<MapGameObject>();
		Box_->SetMapTile(MapTile_);
		if (PlayerDir::Down == CurDir_)
		{
			Box_->PushBlock(Pos + float4{ -20.0f, 0.0f }, BlockDir::DOWN);

		}
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
	}

	if (nullptr != MainPlayer_2)
	{
		if (Type == PlayerType::Player2)
		{
			float4 Pos = MainPlayer_2->GetPosition();

			
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
				for (size_t i = 0; i < ColList.size(); i++)
				{
					ChangeState(PlayerState::Die);
					return;
				}
			}
		}


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

	if (nullptr != MainPlayer_2)
	{
		if (Type == PlayerType::Player2)
		{
			// 무적이 아닐 때만
			if (false == IsInvincible)
			{
				std::vector<GameEngineCollision*> ColList;

				if (true == Collision2P_->CollisionResult("Monster", ColList, CollisionType::Rect, CollisionType::Rect))
				{
					for (size_t i = 0; i < ColList.size(); i++)
					{
						ChangeState(PlayerState::Die);
						return;
					}
				}
			}
			

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

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	PlayerInit();
}

void Player::Start()
{
	Collision1P_ = CreateCollision("1PColl", { 40.f, 40.f }, { 0.f, 0.f });
	Collision1P_->Off();

	Collision2P_ = CreateCollision("2PColl", { 40.f, 40.f }, { 0.f, 0.f });
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

		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingOwl_Left", 0, 1, 0.15f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingOwl_Right", 2, 3, 0.15f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingOwl_Up", 4, 5, 0.15f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingOwl_Down", 6, 7, 0.15f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingTurtle_Left", 8, 9, 0.02f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingTurtle_Right", 10, 11, 0.2f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingTurtle_Up", 12, 13, 0.2f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingTurtle_Down", 14, 15, 0.2f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingUFO_Left", 16, 16, 0.09f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingUFO_Right", 17, 17, 0.09f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingUFO_Up", 18, 18, 0.09f, true);
		MaridRenderer_->CreateAnimation("luxMarid_3.bmp", "RidingUFO_Down", 19, 19, 0.09f, true);


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

		// Idle
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

		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingOwl_Left", 0, 1, 0.15f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingOwl_Right", 2, 3, 0.15f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingOwl_Up", 4, 5, 0.15f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingOwl_Down", 6, 7, 0.15f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingTurtle_Left", 8, 9, 0.02f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingTurtle_Right", 10, 11, 0.2f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingTurtle_Up", 12, 13, 0.2f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingTurtle_Down", 14, 15, 0.2f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingUFO_Left", 16, 16, 0.09f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingUFO_Right", 17, 17, 0.09f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingUFO_Up", 18, 18, 0.09f, true);
		DaoRenderer_->CreateAnimation("Dao_3.bmp", "RidingUFO_Down", 19, 19, 0.09f, true);



		DaoRenderer_->ChangeAnimation("Ready_");
		CurState_ = PlayerState::Ready;
		AnimationName_ = "Ready_";
		ChangeDirText_ = "Down";

		//DaoRenderer_->ChangeAnimation("Damaged_");
		//CurState_ = PlayerState::Damaged;
		//AnimationName_ = "Damaged_";
		//ChangeDirText_ = "Down";

		DaoRenderer_->Off();
	}


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

	TileCheckResult();
	FrontBlockCheck();

	CollisionCheck();


	DebugModeSwitch();
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

	std::string Posx = "";
	std::string Posy = "";
	std::string State = "";


	Posx = "Pos x : " + std::to_string(GetPosition().ix());
	Posy = "Pos y : " + std::to_string(GetPosition().iy());

	if (CurState_ == PlayerState::Wait)
	{
		State = "STATE : Wait";
	}
	else if (CurState_ == PlayerState::Ready)
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
	else if (CurState_ == PlayerState::IdleOwl)
	{
		State = "STATE : IdleOwl";
	}
	else if (CurState_ == PlayerState::IdleTurtle)
	{
		State = "STATE : IdleTurtle";
	}
	else if (CurState_ == PlayerState::RidingOwl)
	{
		State = "STATE : RidingOwl";
	}
	else if (CurState_ == PlayerState::RidingTurtle)
	{
		State = "STATE : RidingTurtle";
	}
	else if (CurState_ == PlayerState::RidingUFO)
	{
		State = "STATE : RidingUFO";
	}


	/*TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 30, Posx.c_str(), static_cast<int>(Posx.length()));
	TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 10, Posy.c_str(), static_cast<int>(Posy.length()));*/
	TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() + 10, State.c_str(), static_cast<int>(State.length()));
}

bool Player::IsMoveKey()
{
	if (true == IsMove)
	{
		if (Type == PlayerType::Player1)
		{
			if (CheckDir_ == PlayerDir::None)
			{
				return false;
			}
		}
		else if(Type == PlayerType::Player2)
		{
			if (CheckDir_ == PlayerDir::None)
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
		case PlayerState::OnOwl:
			OnOwlStart();
			break;
		case PlayerState::OnTurtle:
			OnTurtleStart();
			break;
		case PlayerState::OnUFO:
			OnUFOStart();
			break;
		case PlayerState::OffOwl:
			OffOwlStart();
			break;
		case PlayerState::OffTurtle:
			OffTurtleStart();
			break;
		case PlayerState::OffUFO:
			OffUFOStart();
			break;
		case PlayerState::IdleOwl:
			IdleOwlStart();
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
	case PlayerState::OnOwl:
		OnOwlUpdate();
		break;
	case PlayerState::OnTurtle:
		OnTurtleUpdate();
		break;
	case PlayerState::OnUFO:
		OnUFOUpdate();
		break;
	case PlayerState::OffOwl:
		OffOwlUpdate();
		break;
	case PlayerState::OffTurtle:
		OffTurtleUpdate();
		break;
	case PlayerState::OffUFO:
		OffUFOUpdate();
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
	if (CheckDir_ != CurDir_)
	{
		PlayerAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
		CurDir_ = CheckDir_;
	}
}

// 플레이어가 서있는 위치의 타일이 어떤 타입의 블럭인지 알려주는 함수 return 값이 Max이면 - 아무것도 없는 타일입니다.
BlockType Player::CheckBlockTile(float4 _Pos)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	ItemBlockTile* ItemTiles_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y);

	if (Tiles_ == nullptr)
	{
		return BlockType::Max;
	}


	if (Tiles_->BlockType_ == BlockType::WaveBlock)
	{
		return  BlockType::WaveBlock;
	}

	if (ItemTiles_ !=nullptr&& ItemTiles_->ItemType_!=ItemType::Max)
	{
		return ItemTiles_->BlockType_;

	}


	return Tiles_->BlockType_;



}

ItemType Player::CheckItem(float4 _Pos)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	ItemBlockTile* Tiles_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y);
	if (Tiles_ == nullptr)
	{
		return ItemType::Max;
	}
	else
	{
		return Tiles_->ItemType_;
	}

	return ItemType();
}
