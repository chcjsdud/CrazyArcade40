#include "Monster.h"
#include <vector>
#include <GameEngineContents/Area.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineContents/MapGameObject.h>
#include <GameEngine/GameEngineImageManager.h>
#include "GameEngine/GameEngine.h"


int Monster::TTL_MONSTER_COUNT = 0;

Monster::Monster()
	: Renderer_(nullptr)
	, LeftCol_(nullptr)
	, RightCol_(nullptr)
	, TopCol_(nullptr)
	, BottomCol_(nullptr)
	, CenterCol_(nullptr)
	, ColMapImage_(nullptr)
	, MonsterClass_(MonsterClass::DEFAULT)
	, MonsterState_(MonsterState::IDLE)
	, HP_(1)
	, Speed_(100)
	, Tile_()
	, GetAttTime_(0.0f)
	, AreaWidth_(15)
	, AreaHeight_(13)
	, MapSizeX_(600)
	, MapSizeY_(520)
	, Index_(0)
	, EastArea(ColMapImage_, 0, 0, 0, 0)
	, WestArea(ColMapImage_, 0, 0, 0, 0)
	, NorthArea(ColMapImage_, 0, 0, 0, 0)
	, SouthArea(ColMapImage_, 0, 0, 0, 0)
	, CurArea(ColMapImage_,0,0,0,0)
	, IndexCheck_(false)
{
	TTL_MONSTER_COUNT++;
}

Monster::~Monster()
{
}


void Monster::Start()
{
	CenterCol_ = CreateCollision("Monster", float4(50.0f, 50.0f), float4(0.0f, 0.0f));
	
	{	// Tile Chk Col
		LeftCol_ = CreateCollision("LeftCol", float4(10.0f, 10.0f), float4(-50.0f, 0.0f));
		TopCol_ = CreateCollision("TopCol", float4(10.0f, 10.0f), float4(0.0f, -50.0f));
		RightCol_ = CreateCollision("RightCol", float4(10.0f, 10.0f), float4(50.0f, 0.0f));
		BottomCol_ = CreateCollision("BottomCol", float4(10.0f, 10.0f), float4(0.0f, 50.0f));
	}
	
	if (GetLevel()->GetNameCopy() == "Monster1Level")
	{
		SetColMapImage("MonsterStage1_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "Monster2Level")
	{
		SetColMapImage("MonsterStage2_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "PlayerTeamTest")
	{
		SetColMapImage("Camp_ColMap.bmp");
	}
	else
	{
		return;
	}
	

	for (int x = 0; x < AreaWidth_; ++x)
	{
		for (int y = 0; y < AreaHeight_; ++y)
		{
			float StartX = (MapSizeX_ / AreaWidth_ * x) + 20;
			float StartY = (MapSizeY_ / AreaHeight_ * y) + 40;
			float EndX = (MapSizeX_ / AreaWidth_ * (x + 1)) + 20;
			float EndY = (MapSizeY_ / AreaHeight_ * (y + 1)) + 40;

			Area area(ColMapImage_, StartX, StartY, EndX, EndY);
			Areas_.push_back(area);
		}
	}
}

void Monster::Update()
{
	GetAttTime_ += GameEngineTime::GetDeltaTime();
	UpdateDirection();
	UpdateMove();
	Die();
}

void Monster::UpdateDirection()
{
	PrevIndex_ = Index_; // 이전 인덱스 저장
	bool IsAreaChanged = false;

	for (int i = 0; i < Areas_.size(); ++i)
	{
		Area& NewArea = Areas_[i];
		if (true == NewArea.InCenter(GetPosition()))
		{
			if (PrevIndex_ != i)
			{
				Index_ = i;
				IsAreaChanged = true;
			}
		}
		NewArea.SetMapTile(MapTile_);
	}
	
	CheckWaveTile(GetPosition());

	if (IsAreaChanged == true)
	{
		if (Dir_.x == 1) // 오른쪽으로 가고 있고
		{
			int EastIndex = Index_ + AreaHeight_;
			int NorthIndex = Index_ - 1;
			if (Index_ < 182) // 몬스터의 위치가 제일 오른쪽이 아니고
			{
				EastArea = Areas_[EastIndex];
				if (true == EastArea.HasBubble(GetPosition())) // 아래에 물풍선이 있으면
				{
					Dir_ = float4::LEFT;
					Direction_ = "Left";
				}
				else if (true == EastArea.HasWall() || // 오른쪽에 벽이 있거나
					(true == EastArea.HasBlock(GetPosition()) && (false == EastArea.HasWaveTile(GetPosition())) && false == EastArea.HasBubble(GetPosition()))) // 오른쪽에 블럭이 있고, 그 블럭이 물폭탄이 아니면 내려가라
				{
					Dir_ = float4::DOWN;
					Direction_ = "Down";
				}

				else if (Index_ % 13 != 0) // 제일 위가 아니고
				{
					NorthArea = Areas_[NorthIndex];
					if (false == NorthArea.HasWall() && false == NorthArea.HasBlock(GetPosition())) // 위쪽이 벽이 아니거나, 블럭이 없으면 올라가라
					{
						Dir_ = float4::UP;
						Direction_ = "Up";
					}
				}

			}
			else // 몬스터의 위치가 맵의 제일 오른쪽이면 내려가라
			{
				Dir_ = float4::DOWN;
				Direction_ = "Down";
			}
		}

		else if (Dir_.x == -1) // 왼쪽으로 가고 있고
		{
			int WestIndex = Index_ - AreaHeight_;
			int SouthIndex = Index_ + 1;
			if (Index_ >= 13)
			{
				WestArea = Areas_[WestIndex];
				if (true == WestArea.HasBubble(GetPosition())) // 아래에 물풍선이 있으면
				{
					Dir_ = float4::RIGHT;
					Direction_ = "Right";
				}

				else if (true == WestArea.HasWall() ||
					(true == WestArea.HasBlock(GetPosition()) && (false == WestArea.HasWaveTile(GetPosition())) && false == WestArea.HasBubble(GetPosition()))) // 몬스터의 위치가 제일 왼쪽이 아니고, 왼쪽에 장애물이 있으면 올라가라
				{
					Dir_ = float4::UP;
						Direction_ = "Up";
				}

				else if (Index_ % 13 != 12)
				{
					SouthArea = Areas_[SouthIndex];
						if (false == SouthArea.HasWall() && false == SouthArea.HasBlock(GetPosition())) // 몬스터의 위치가 제일 왼쪽이 아니고, 제일 아래가 아니고, 아래에 장애물이 없으면 내려가라
						{
							Dir_ = float4::DOWN;
							Direction_ = "Down";
						}
				}
			}

			else // 몬스터의 위치가 제일 왼쪽이면 올라가라
			{
				Dir_ = float4::UP;
				Direction_ = "Up";
			}
		}

		else if (Dir_.y == 1) // 아래로 내려가고 있고
		{
			int SouthIndex = Index_ + 1;
			int EastIndex = Index_ + AreaHeight_;
			if (Index_ % 13 != 12) // 몬스터의 위치가 맨 아래가 아니고, 아래에 장애물이 있으면 왼쪽으로 가라
			{
				SouthArea = Areas_[SouthIndex];

				if (true == SouthArea.HasBubble(GetPosition())) // 아래에 물풍선이 있으면
				{
					Dir_ = float4::UP;
					Direction_ = "Up";
				}

				else if (true == SouthArea.HasWall() || (true == SouthArea.HasBlock(GetPosition()) && false == SouthArea.HasWaveTile(GetPosition())) && false == SouthArea.HasBubble(GetPosition()))
				{
					Dir_ = float4::LEFT;
					Direction_ = "Left";
				}

				else if (Index_ < 182) // 제일 오른쪽이 아니고
				{
					EastArea = Areas_[EastIndex];
					if (false == EastArea.HasWall() && false == EastArea.HasBlock(GetPosition())) // 몬스터의 위치가 제일 오른쪽이 아니고, 오른쪽에 장애물이 없으면 오른쪽으로 가라
					{
						Dir_ = float4::RIGHT;
						Direction_ = "Right";
					}
				}
			}
			else // 몬스터의 위치가 맨 아래면 왼쪽으로 가라
			{
				Dir_ = float4::LEFT;
				Direction_ = "Left";
			}
		}

		else if (Dir_.y == -1) // 위로 가고 있고
		{
			int NorthIndex = Index_ - 1;
			int WestIndex = Index_ - AreaHeight_;
			if (Index_ % 13 != 0) // 몬스터의 위치가 맨 위가 아니고, 위에 장애물이 있으면 오른쪽으로 가라
			{
				NorthArea = Areas_[NorthIndex];
				if (true == NorthArea.HasBubble(GetPosition())) // 왼쪽에 물풍선이 있으면
				{
					Dir_ = float4::DOWN;
					Direction_ = "Down";
				}

				else if (true == NorthArea.HasWall() || (true == NorthArea.HasBlock(GetPosition()) && false == NorthArea.HasWaveTile(GetPosition())) && false == NorthArea.HasBubble(GetPosition()))
				{
					Dir_ = float4::RIGHT;
					Direction_ = "Right";
				}

				else if (Index_ >= 13) // 몬스터의 위치가 맨 위와 맨 왼쪽이 아니고, 왼쪽에 장애물이 없으면
				{
					WestArea = Areas_[WestIndex];
					if (false == WestArea.HasWall() && false == WestArea.HasBlock(GetPosition()))
					{
						Dir_ = float4::LEFT;
						Direction_ = "Left";
					}
				}
			}
			else // 몬스터의 위치가 맨 위면 오른쪽으로 가라
			{
				Dir_ = float4::RIGHT;
				Direction_ = "Right";

			}
		}
		Renderer_->ChangeAnimation("Move" + Direction_);
	}
}

void Monster::UpdateMove()
{
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
}

void Monster::TakeDamage()
{
	if (GetAttTime_ > 2.0) // 2초 안에 다시 맞으면 DMG를 입지 않는다. (Need to chk : TIME)
	{

		SetHP(GetHp() - 1);
		GetAttTime_ = 0.0f;
	}
}

void Monster::Render()
{

	std::string IndexX = "";
	std::string IndexY = "";


	TileIndex TileIndex_ = MapTile_->GetTileIndex(GetPosition() - float4(20.0f, 40.0f));
	IndexX = "Index X : " + std::to_string(TileIndex_.X);
	IndexY = "Index Y : " + std::to_string(TileIndex_.Y);


	TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 30, IndexX.c_str(), static_cast<int>(IndexX.length()));
	TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 10, IndexY.c_str(), static_cast<int>(IndexY.length()));
}

void Monster::Die()
{
	if (true == Renderer_->IsAnimationName("Die") && true == Renderer_->IsEndAnimation())
	{
		CenterCol_->Off();
		Death();
		TTL_MONSTER_COUNT--; // total 몬스터 수가 줄어든다.
		if (TTL_MONSTER_COUNT == 1) // 만약 몬스터가 한마리 남으면
		{
			SetSpeed(Speed_ + 20); // 속도가 빨라져라
		}
	}

	if (true == IsDie()) // HP가 0이거나 0보다 작으면
	{
		Dir_ = float4::ZERO;
		Renderer_->ChangeAnimation("Die");
	}
}

bool Monster::IsDie()
{
	if (GetHP() <= 0)
	{
		return true;
	}
	else return false;
}

void Monster::SetColMapImage(std::string _Name)
{
	ColMapImage_ = GameEngineImageManager::GetInst()->Find(_Name);
}

GameEngineImage* Monster::GetColMapImage()
{
	return ColMapImage_;
}

void Monster::CheckWaveTile(float4 _Pos)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	if (TileIndex_.Y >= 13)
	{
		return;

	}

	BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	if (Tiles_ == nullptr)
	{
		return;
	}

	else if (Tiles_->BlockType_ == BlockType::WaveBlock)
	{
		TakeDamage();
	}
}