#include "Monster.h"
#include <vector>
#include <GameEngineContents/Area.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineContents/MapGameObject.h>
#include <GameEngine/GameEngineImageManager.h>


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
	
	if (GetLevel()->GetNameCopy() == "CampLevel")
	{
		SetColMapImage("Camp_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "VillageLevel")
	{
		SetColMapImage("Village_Col.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "CemetoryLevel")
	{
		SetColMapImage("Cemetory_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "Monster1Level")
	{
		SetColMapImage("MonsterStage1_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "Monster2Level")
	{
		SetColMapImage("MonsterStage2_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "BossLevel")
	{
		SetColMapImage("Boss_ColMap.bmp");
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
	TakeDamage();
	Die();
}

void Monster::UpdateDirection()
{
	int PrevIndex_ = Index_; // 이전 인덱스 저장
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
	}

	
	int EastIndex = Index_ + AreaHeight_;
	Area EastArea = Areas_[EastIndex];
	
	int WestIndex = Index_ - AreaHeight_;
	Area WestArea = Areas_[WestIndex];
	
	int NorthIndex = Index_ - 1;
	Area NorthArea = Areas_[NorthIndex];

	int SouthIndex = Index_ + 1;
	Area SouthArea = Areas_[SouthIndex];
	
	int NorthWestIndex = Index_ - (AreaHeight_ + 1);
	Area NorthWestArea = Areas_[NorthWestIndex];
	
	int EastSouthIndex = Index_ + (AreaHeight_ + 1);
	Area EastSouthArea = Areas_[EastSouthIndex];

	if (true == IsAreaChanged)
	{

		if (Dir_.y == 1) // 아래로 가고 있고
		{
			if (false == EastArea.HasWall()) // 오른쪽이 검은색이면
			{
				Dir_ = float4::RIGHT; // 오른쪽으로 이동해라
				Direction_ = "Right";
			}

			if (true == SouthArea.HasWall())
			{
				Dir_ = float4::LEFT;
				Direction_ = "Left";
			}
		}

		else if (Dir_.y == -1) // 위로 가고 있고
		{
			if(false == WestArea.HasWall()) // 왼쪽이 검은색이면
			{
				Dir_ = float4::LEFT; // 왼쪽으로 이동해라
				Direction_ = "Left";
			}

			if (true == NorthArea.HasWall()) // 위쪽이 검은색이면
			{
				Dir_ = float4::RIGHT; // 오른쪽으로 가라
				Direction_ = "Right";
			}
		}

		else if (Dir_.x == 1) // 오른쪽으로 가고 있고
		{
			if (true == NorthArea.HasWall())
			{
				Dir_ = float4::RIGHT;
				Direction_ = "Right";
			}

			else if (false == NorthArea.HasWall() && // 위쪽이 검정이 아니고
				true == NorthWestArea.HasWall()) // 왼쪽 위가 검정일 때 위로 가라
			{
				Dir_ = float4::UP;
				Direction_ = "Up";
			}
			
			else if (true == EastArea.HasWall())
			{
				Dir_ = float4::DOWN;
				Direction_ = "Down";
			}
		}

		else if (Dir_.x == -1) // 왼쪽으로 가고 있고
		{
			if (true == WestArea.HasWall())
			{
				Dir_ = float4::UP;
				Direction_ = "Up";
			}

			else if (false == SouthArea.HasWall() && // 아래쪽이 검정이 아니고
				true == EastSouthArea.HasWall()) // 오른쪽 아래가 검정일 때 아래로 이동해라
			{
				Dir_ = float4::DOWN;
				Direction_ = "Down";
			}
		}

		if (true == EastArea.HasWall() && // 오른쪽이 검정이고
			false == WestArea.HasWall()) 	// 왼쪽이 검정이 아닐때
		{
			if (true == SouthArea.HasWall()) // 만약 아래쪽이 검정이면 왼쪽으로 가라
			{
				Dir_ = float4::LEFT;
				Direction_ = "Left";
			}

			else // 아니면 내려가라
			{
				Dir_ = float4::DOWN;
				Direction_ = "Down";
			}
		}

		if (false == EastArea.HasWall() && // 오른쪽이 검정이 아니고
			true == WestArea.HasWall()) // 왼쪽이 검정일 때
		{
			if (true == NorthArea.HasWall())
			{
				Dir_ = float4::RIGHT;
				Direction_ = "Right";
			}

			else
			{
				Dir_ = float4::UP;
				Direction_ = "Up";
			}
		}
	}
}

void Monster::UpdateMove()
{
	if (Direction_ == "")
	{
		Direction_ = "Right";
		Dir_ = float4::RIGHT;
	}
	Renderer_->ChangeAnimation("Move" + Direction_);
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
}

void Monster::TakeDamage()
{
	if (GetAttTime_ > 2.0) // 2초 안에 다시 맞으면 DMG를 입지 않는다. (Need to chk : TIME)
	{
		std::vector<GameEngineCollision*> BubbleCol;
		if (CenterCol_->CollisionResult("WaveCol", BubbleCol, CollisionType::Rect, CollisionType::Rect))
		{
			for (GameEngineCollision* Collision : BubbleCol)
			{
				GameEngineActor* ColActor = Collision->GetActor();
				MapGameObject* Bubble = dynamic_cast<MapGameObject*>(ColActor);

				if (Bubble != nullptr)
				{
					SetHP(GetHp() - 1);
					GetAttTime_ = 0.0f;
				}
			}
		}
	}
}

void Monster::Render()
{
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


bool Monster::HasEastTile()
{
	std::vector<GameEngineCollision*> Collision;
	if (RightCol_->CollisionResult("", Collision, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* ColActor : Collision)
		{
			if (/*타일이 맞는지*/ColActor->GetActor())
			{
				return true;
			}
		}
	}
	return false;
}

bool Monster::HasWestTile()
{
	std::vector<GameEngineCollision*> Collision;
	if (LeftCol_->CollisionResult("", Collision, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* ColActor : Collision)
		{
			if (/*타일이 맞는지*/ColActor->GetActor())
			{
				return true;
			}
		}
	}
	return false;
}

bool Monster::HasNorthTile()
{
	std::vector<GameEngineCollision*> Collision;
	if (TopCol_->CollisionResult("", Collision, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* ColActor : Collision)
		{
			if (/*타일이 맞는지*/ColActor->GetActor())
			{
				return true;
			}
		}
	}
	return false;
}

bool Monster::HasSouthTile()
{
	std::vector<GameEngineCollision*> Collision;
	if (BottomCol_->CollisionResult("", Collision, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* ColActor : Collision)
		{
			if (/*타일이 맞는지*/ColActor->GetActor())
			{
				return true;
			}
		}
	}
	return false;
}


void Monster::SetColMapImage(std::string _Name)
{
	ColMapImage_ = GameEngineImageManager::GetInst()->Find(_Name);
}

GameEngineImage* Monster::GetColMapImage()
{
	return ColMapImage_;
}