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
	, EastArea(ColMapImage_, 0, 0, 0, 0)
	, WestArea(ColMapImage_, 0, 0, 0, 0)
	, NorthArea(ColMapImage_, 0, 0, 0, 0)
	, SouthArea(ColMapImage_, 0, 0, 0, 0)
	, NorthWestArea(ColMapImage_, 0, 0, 0, 0)
	, EastSouthArea(ColMapImage_, 0, 0, 0, 0)
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
	TakeDamage();
	Die();
}

void Monster::UpdateDirection()
{
	int PrevIndex_ = Index_; // ���� �ε��� ����
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

	if (IsAreaChanged == true)
	{
		if (Dir_.x == 1) // ���������� ���� �ְ�
		{
			int EastIndex = Index_ + AreaHeight_;
			int NorthIndex = Index_ - 1;
			if (Index_ < 182)
			{
				EastArea = Areas_[EastIndex];
				if (true == EastArea.HasWall()) // ������ ��ġ�� ���� �������� �ƴϰ�, �����ʿ� ��ֹ��� ������ ��������
				{
					Dir_ = float4::DOWN;
					Direction_ = "Down";
				}

				if (Index_ % 13 != 0) // ���� ���� �ƴϰ�
				{
					NorthArea = Areas_[NorthIndex];
					if (false == NorthArea.HasWall())
					{
						Dir_ = float4::UP;
						Direction_ = "Up";
					}
				}

			}
			else // ������ ��ġ�� ���� ���� �������̸� ��������
			{
				Dir_ = float4::DOWN;
				Direction_ = "Down";
			}
		}

		else if (Dir_.x == -1) // �������� ���� �ְ�
		{
			int WestIndex = Index_ - AreaHeight_;
			int SouthIndex = Index_ + 1;
			if (Index_ >= 13)
			{
				WestArea = Areas_[WestIndex];
				if (true == WestArea.HasWall()) // ������ ��ġ�� ���� ������ �ƴϰ�, ���ʿ� ��ֹ��� ������ �ö󰡶�
				{
					Dir_ = float4::UP;
					Direction_ = "Up";
				}

				if (Index_ % 13 != 12)
				{
					SouthArea = Areas_[SouthIndex];
					if (false == SouthArea.HasWall())
					{
						Dir_ = float4::DOWN;
						Direction_ = "Down";
					}
				}
			}

			else // ������ ��ġ�� ���� �����̸� �ö󰡶�
			{
				Dir_ = float4::UP;
				Direction_ = "Up";
			}
		}

		else if (Dir_.y == 1) // �Ʒ��� �������� �ְ�
		{
			int SouthIndex = Index_ + 1;
			int EastIndex = Index_ + AreaHeight_;
			if (Index_ % 13 != 12) // ������ ��ġ�� �� �Ʒ��� �ƴϰ�, �Ʒ��� ��ֹ��� ������ �������� ����
			{
				SouthArea = Areas_[SouthIndex];
				if (true == SouthArea.HasWall())
				{
					Dir_ = float4::LEFT;
					Direction_ = "Left";
				}

				if (Index_ < 182) // ���� �������� �ƴϰ�
				{
					EastArea = Areas_[EastIndex];
					if (false == EastArea.HasWall()) // ������ ��ġ�� ���� �������� �ƴϰ�, �����ʿ� ��ֹ��� ������ ���������� ����
					{
						Dir_ = float4::RIGHT;
						Direction_ = "Right";
					}
				}
			}
			else // ������ ��ġ�� �� �Ʒ��� �������� ����
			{
				Dir_ = float4::LEFT;
				Direction_ = "Left";
			}
		}

		else if (Dir_.y == -1) // ���� ���� �ְ�
		{
			int NorthIndex = Index_ - 1;
			int WestIndex = Index_ - AreaHeight_;
			if (Index_ % 13 != 0) // ������ ��ġ�� �� ���� �ƴϰ�, ���� ��ֹ��� ������ ���������� ����
			{
				NorthArea = Areas_[NorthIndex];
				if (true == NorthArea.HasWall())
				{
					Dir_ = float4::RIGHT;
					Direction_ = "Right";
				}

				if (Index_ >= 13) // ������ ��ġ�� �� ���� �� ������ �ƴϰ�, ���ʿ� ��ֹ��� ������
				{
					WestArea = Areas_[WestIndex];
					if (false == WestArea.HasWall())
					{
						Dir_ = float4::LEFT;
						Direction_ = "Left";
					}
				}
			}
			else // ������ ��ġ�� �� ���� ���������� ����
			{
				Dir_ = float4::RIGHT;
				Direction_ = "Right";
			}
		}
	}
} 

void Monster::UpdateMove()
{
	Renderer_->ChangeAnimation("Move" + Direction_);
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
}

void Monster::TakeDamage()
{
	if (GetAttTime_ > 2.0) // 2�� �ȿ� �ٽ� ������ DMG�� ���� �ʴ´�. (Need to chk : TIME)
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
		TTL_MONSTER_COUNT--; // total ���� ���� �پ���.
		if (TTL_MONSTER_COUNT == 1) // ���� ���Ͱ� �Ѹ��� ������
		{
			SetSpeed(Speed_ + 20); // �ӵ��� ��������
		}
	}

	if (true == IsDie()) // HP�� 0�̰ų� 0���� ������
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
			if (/*Ÿ���� �´���*/ColActor->GetActor())
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
			if (/*Ÿ���� �´���*/ColActor->GetActor())
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
			if (/*Ÿ���� �´���*/ColActor->GetActor())
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
			if (/*Ÿ���� �´���*/ColActor->GetActor())
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