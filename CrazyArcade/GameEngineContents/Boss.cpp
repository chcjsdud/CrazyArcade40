#include "Boss.h"
#include "Monster.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>

Boss::Boss()
	: Monster()
	, PlayerIndex_(4)
	, WaterTime_(0.0f)
	, AreaChangeCount_(0)
{
}

Boss::~Boss()
{
}

void Boss::Start()
{
	// 이미지
	Renderer_ = CreateRenderer("Monster.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 8);
	Renderer_->CreateAnimation("Monster.bmp", "Idle", 37, 38, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveRight", 39, 40, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveLeft", 41, 42, 0.2f, true);
	// Need to chk : MoveUp 이미지
	Renderer_->CreateAnimation("Monster.bmp", "MoveUp", 43, 44, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveDown", 37, 38, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Die", 64, 73, 0.3f, true); // Need to chk : 속도
	Renderer_->CreateAnimation("Monster.bmp", "TakeDamage", 50, 51, 0.2f, true); // 아래
	//Renderer_->CreateAnimation("Monster.bmp", "TakeDamage", 52, 53, 0.2f, true); // 오른쪽
	//Renderer_->CreateAnimation("Monster.bmp", "TakeDamage", 54, 55, 0.2f, true); // 왼쪽
	Renderer_->CreateAnimation("Monster.bmp", "WaterAttack", 61, 63, 0.2f, false); // 물주기
	Renderer_->CreateAnimation("Monster.bmp", "RollAttackRight", 45, 49, 0.2f, true); // 구르기
	Renderer_->CreateAnimation("Monster.bmp", "RollAttackLeft", 56, 60, 0.2f, true); // 구르기
	Renderer_->ChangeAnimation("MoveRight");
	Dir_ = float4::RIGHT;
	Direction_ = "Right";
	CenterCol_ = CreateCollision("Monster", float4(50.0f, 50.0f), float4(0.0f, 0.0f));
	CenterCol_->SetScale(float4(130.0, 150.0f));
	CenterCol_->SetPivot(float4(0.0f, -50.0f));

	// ColMap
	if (GetLevel()->GetNameCopy() == "BossLevel")
	{
		SetColMapImage("Boss_ColMap.bmp");
	}
	else
	{
		return;
	}

	// 상태
	SetMonsterClass(MonsterClass::BOSS);
	SetHP(150);
	SetSpeed(50); // Need to chk : Speed

	// Index 설정
	SetMapSizeX(440);
	SetMapSizeY(360);
	AreaHeight_ = 9;
	AreaWidth_ = 11;

	for (int x = 0; x < AreaWidth_; ++x)
	{
		for (int y = 0; y < AreaHeight_; ++y)
		{
			float StartX = static_cast<float>((MapSizeX_ / AreaWidth_ * x) + 100);
			float StartY = static_cast<float>((MapSizeY_ / AreaHeight_ * y) + 120);
			float EndX = static_cast<float>((MapSizeX_ / AreaWidth_ * (x + 1)) + 100);
			float EndY = static_cast<float>((MapSizeY_ / AreaHeight_ * (y + 1)) + 120);

			Area area(ColMapImage_, StartX, StartY, EndX, EndY);
			Areas_.push_back(area);
		}
	}

	Index_ = 49; // 시작 Index를
	SetPosition(Areas_[49].GetCenter());
	srand(time(NULL));
}

void Boss::Render()
{
}

void Boss::Update()
{
	WaterTime_ += GameEngineTime::GetInst()->GetDeltaTime();
	UpdateDirection();
	UpdateAttack();
	UpdateMove();
}

void Boss::UpdateMove()
{
	if (RandomAction_ < 3)
	{
		Monster::UpdateMove();
	}
	else if (RandomAction_ == 3)
	{
		if (Renderer_->IsAnimationName("WaterAttack") &&
			Renderer_->IsEndAnimation())
		{
			if (WaterTime_ > 2.0f)
			{
				EndAttack_ = true;
			}
		}
	}
	else if (RandomAction_ == 4)
	{
		if (Renderer_->IsAnimationName("RollAttackRight"))
		{
			if (Index_ < (AreaWidth_ - 1) * AreaHeight_)
			{
				SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
			}
			else
			{
				EndAttack_ = true;
				Dir_ = float4::ZERO;
			}
		}
		else if (Renderer_->IsAnimationName("RollAttackLeft"))
		{
			if (Index_ > AreaHeight_)
			{
				SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
			}
			else
			{
				EndAttack_ = true;
				Dir_ = float4::ZERO;
			}
		}
	}
}

void Boss::UpdateDirection()
{
	PrevIndex_ = Index_; // 이전 인덱스 저장
	bool IsAreaChanged = false;

	if (false == Renderer_->IsAnimationName("WaterAttack") &&
		false == Renderer_->IsAnimationName("RollAttack"))
	{
		for (int i = 0; i < Areas_.size(); ++i)
		{
			Area& NewArea = Areas_[i];
			if (true == NewArea.InCenter(GetPosition()))
			{
				if (PrevIndex_ != i)
				{
					Index_ = i;
					AreaChangeCount_++;
					if (AreaChangeCount_ == 3 ||
						Index_ < AreaHeight_ ||
						Index_ % AreaHeight_ == 0 ||
						Index_ % AreaHeight_ == AreaHeight_ - 1 ||
						Index_ >= (AreaWidth_ - 1) * AreaHeight_)
					{
						if (Index_ < AreaHeight_ ||
							Index_ >= (AreaWidth_ - 1) * AreaHeight_)
						{
							RandomAction_ = 4;
							IsAreaChanged = true;
							AreaChangeCount_ = 0;
						}
						else
						{
							RandomAction_ = (rand() % 4);
							IsAreaChanged = true;
							AreaChangeCount_ = 0;
						}
					}
					SetPosition(NewArea.GetCenter());
				}
			}
			NewArea.SetMapTile(MapTile_);
		}
	}
	CheckWaveTile(GetPosition());

	if (Dir_.x == 0 && Dir_.y == 0)
	{
		if ((Renderer_->IsAnimationName("WaterAttack") && EndAttack_ == true) ||
			(Renderer_->IsAnimationName("RollAttack") && EndAttack_ == true))
		{
			RandomAction_ = 0;
			IsAreaChanged = true;

		}
	}

	if (true == IsAreaChanged && RandomAction_ < 3)
	{
		MovableAreas.clear();
		int EastIndex = Index_ + AreaHeight_;
		int WestIndex = Index_ - AreaHeight_;
		int NorthIndex = Index_ - 1;
		int SouthIndex = Index_ + 1;

		if (EastIndex >= 0 &&
			EastIndex < Areas_.size() &&
			Index_ < Areas_.size() - AreaHeight_)
		{
			// 동쪽이 벽이 아니고, 물풍선이 아니면
			EastArea = Areas_[EastIndex];
			if (false == EastArea.HasWall())
			{
				Area& EastArea = Areas_[EastIndex];
				MovableAreas.insert(std::make_pair(0, EastArea));
			}
		}

		if (WestIndex >= 0 &&
			WestIndex < Areas_.size() &&
			Index_ >= AreaHeight_)
		{
			// 서쪽이 벽이 아니고, Wave 타일이 아니면
			WestArea = Areas_[WestIndex];
			if (false == WestArea.HasWall())
			{
				Area& WestArea = Areas_[WestIndex];
				MovableAreas.insert(std::make_pair(1, WestArea));

			}
		}

		if (SouthIndex >= 0 &&
			SouthIndex < Areas_.size() &&
			Index_ % AreaHeight_ != AreaHeight_ - 1)
		{
			// 남쪽이 벽이 아니고, Wave 타일이 아니면
			Area& SouthArea = Areas_[SouthIndex];
			if (false == SouthArea.HasWall())
			{
				Area& SouthArea = Areas_[SouthIndex];
				MovableAreas.insert(std::make_pair(2, SouthArea));
			}
		}

		if (NorthIndex >= 0 &&
			NorthIndex < Areas_.size() && // 맵 크기 안에 들어와야하고,
			Index_ % AreaHeight_ != 0) // 맵의 제일 위쪽이 아닐 때
		{
			Area& NorthArea = Areas_[NorthIndex];
			if (false == NorthArea.HasWall())
			{
				Area& NorthArea = Areas_[NorthIndex];
				MovableAreas.insert(std::make_pair(3, NorthArea));
			}
		}

		std::map<int, Area>::const_iterator East = MovableAreas.find(0);
		std::map<int, Area>::const_iterator West = MovableAreas.find(1);
		std::map<int, Area>::const_iterator South = MovableAreas.find(2);
		std::map<int, Area>::const_iterator North = MovableAreas.find(3);
		Area PrevArea = Areas_[PrevIndex_];

		if (Dir_.x == 1) // 오른쪽으로 갈때
		{
			if (MovableAreas.size() == 0)
			{
				Dir_ = float4::ZERO;
				//Direction_ = "Zero";
			}
			else
			{
				int RandomDir = (rand() % 4);
				std::map<int, Area>::const_iterator FoundArea = MovableAreas.find(RandomDir);
				if (MovableAreas.size() > 1)
				{
					while (FoundArea == MovableAreas.end() ||
						(FoundArea->second.GetCenter().x == PrevArea.GetCenter().x &&
							FoundArea->second.GetCenter().y == PrevArea.GetCenter().y)
						/* || RandomDir == 0*/)
					{
						RandomDir = (rand() % 4);
						FoundArea = MovableAreas.find(RandomDir);
					}
				}
				else
				{
					FoundArea = MovableAreas.begin();
				}

				if (FoundArea == West)
				{
					Dir_ = float4::LEFT;
					Direction_ = "Left";
				}

				else if (FoundArea == South)
				{
					Dir_ = float4::DOWN;
					Direction_ = "Down";
				}

				else if (FoundArea == North)
				{
					Dir_ = float4::UP;
					Direction_ = "Up";
				}
			}
		}

		else if (Dir_.x == -1)

		{
			if (MovableAreas.size() == 0)
			{
				Dir_ = float4::ZERO;
				//Direction_ = "Zero";
			}
			else
			{
				int RandomDir = (rand() % 4);
				std::map<int, Area>::const_iterator FoundArea = MovableAreas.find(RandomDir);

				if (MovableAreas.size() > 1)
				{
					while (FoundArea == MovableAreas.end() ||
						(FoundArea->second.GetCenter().x == PrevArea.GetCenter().x &&
							FoundArea->second.GetCenter().y == PrevArea.GetCenter().y)
						/* || RandomDir == 1*/)
					{
						RandomDir = (rand() % 4);
						FoundArea = MovableAreas.find(RandomDir);
					}
				}
				else
				{
					FoundArea = MovableAreas.begin();
				}

				if (FoundArea == East)
				{
					Dir_ = float4::RIGHT;
					Direction_ = "Right";
				}

				else if (FoundArea == South)
				{
					Dir_ = float4::DOWN;
					Direction_ = "Down";
				}

				else if (FoundArea == North)
				{
					Dir_ = float4::UP;
					Direction_ = "Up";
				}
			}
		}

		else if (Dir_.y == -1)
		{
			if (MovableAreas.size() == 0)
			{
				Dir_ = float4::ZERO;
				//Direction_ = "Zero";
			}
			else
			{
				int RandomDir = (rand() % 4);
				std::map<int, Area>::const_iterator FoundArea = MovableAreas.find(RandomDir);
				if (MovableAreas.size() > 1)
				{
					while (FoundArea == MovableAreas.end() ||
						(FoundArea->second.GetCenter().x == PrevArea.GetCenter().x &&
							FoundArea->second.GetCenter().y == PrevArea.GetCenter().y)
						/* || RandomDir == 3*/)
					{
						RandomDir = (rand() % 4);
						FoundArea = MovableAreas.find(RandomDir);
					}
				}

				else
				{
					FoundArea = MovableAreas.begin();
				}

				if (FoundArea == East)
				{
					Dir_ = float4::RIGHT;
					Direction_ = "Right";
				}

				else if (FoundArea == South)
				{
					Dir_ = float4::DOWN;
					Direction_ = "Down";
				}

				else if (FoundArea == West)
				{
					Dir_ = float4::LEFT;
					Direction_ = "Left";
				}
			}
		}

		else if (Dir_.y == 1)
		{
			if (MovableAreas.size() == 0)
			{
				Dir_ = float4::ZERO;
				//Direction_ = "Zero";
			}
			else
			{
				int RandomDir = (rand() % 4);
				std::map<int, Area>::const_iterator FoundArea = MovableAreas.find(RandomDir);
				if (MovableAreas.size() > 1)
				{
					while (FoundArea == MovableAreas.end() ||
						(FoundArea->second.GetCenter().x == PrevArea.GetCenter().x &&
							FoundArea->second.GetCenter().y == PrevArea.GetCenter().y)
						/* || RandomDir == 2*/)
					{
						RandomDir = (rand() % 4);
						FoundArea = MovableAreas.find(RandomDir);
					}
				}
				else
				{
					FoundArea = MovableAreas.begin();
				}

				if (FoundArea == East)
				{
					Dir_ = float4::RIGHT;
					Direction_ = "Right";
				}

				else if (FoundArea == North)
				{
					Dir_ = float4::UP;
					Direction_ = "Up";
				}

				else if (FoundArea == West)
				{
					Dir_ = float4::LEFT;
					Direction_ = "Left";
				}
			}
		}

		else
		{
			int RandomDir = (rand() % 4);
			std::map<int, Area>::const_iterator FoundArea = MovableAreas.find(RandomDir);
			if (MovableAreas.size() > 1)
			{
				while (FoundArea == MovableAreas.end() ||
					(FoundArea->second.GetCenter().x == PrevArea.GetCenter().x &&
						FoundArea->second.GetCenter().y == PrevArea.GetCenter().y))
				{
					RandomDir = (rand() % 4);
					FoundArea = MovableAreas.find(RandomDir);
				}
			}
			else
			{
				FoundArea = MovableAreas.begin();
			}

			if (FoundArea == East)
			{
				Dir_ = float4::RIGHT;
				Direction_ = "Right";
			}

			else if (FoundArea == North)
			{
				Dir_ = float4::UP;
				Direction_ = "Up";
			}

			else if (FoundArea == West)
			{
				Dir_ = float4::LEFT;
				Direction_ = "Left";
			}

			else if (FoundArea == South)
			{
				Dir_ = float4::DOWN;
				Direction_ = "Down";
			}
		}
	}

	else if (RandomAction_ == 3)
	{
		WaterAttack();
	}
	else if (RandomAction_ == 4)
	{
		RollAttack();
	}
}

void Boss::UpdateAttack()
{
	if (WaterTime_ > 3)
	{
		WaterTime_ = 0.0f;
	}
}


void Boss::RollAttack()
{
	EndAttack_ = false;
	if (Index_ < AreaHeight_) 
	{
		Renderer_->ChangeAnimation("RollAttackRight");

	} 
	else if (Index_ >= (AreaWidth_ - 1) * AreaHeight_)
	{
		Renderer_->ChangeAnimation("RollAttackLeft");
	}

}

void Boss::WaterAttack()
{
	UpdateAttack();
	EndAttack_ = false;
	Renderer_->ChangeAnimation("WaterAttack");
	Dir_ = float4::ZERO;
}

//
//bool Boss::SameXLine() // 가로줄
//{
//	int Offset = PlayerIndex_ - Index_;
//	if (Offset < 0)
//	{
//		Offset = Offset * -1;
//	}
//
//	return Offset % 3 == 0;
//}

//bool Boss::SameYLine() // 세로줄
//{
//	if (PlayerIndex_ < 3 && Index_ < 3)
//	{
//		return true;
//	}
//
//	else if (PlayerIndex_ >= 3 && Index_ >= 3 &&
//		PlayerIndex_ < 6 && Index_ < 6)
//	{
//		return true;
//	}
//
//	else if (PlayerIndex_ >= 6 && Index_ >= 6 &&
//		PlayerIndex_ < 9 && Index_ < 9)
//	{
//		return true;
//	}
//
//	else
//	{
//		return false;
//	}
//}