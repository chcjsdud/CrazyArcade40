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
	, RollTime_(0.0f)
	, WaterTime_(0.0f)
	, AttTime_(0.0f)
	, AreaChangeCount_(0)
{
}

Boss::~Boss()
{
}

void Boss::Start()
{
	// �̹���
	Renderer_ = CreateRenderer("Monster.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 7);
	Renderer_->CreateAnimation("Monster.bmp", "Idle", 24, 25, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveRight", 26, 27, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveLeft", 40, 41, 0.2f, true);
	// Need to chk : MoveUp �̹���
	Renderer_->CreateAnimation("Monster.bmp", "MoveUp", 0, 1, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveDown", 24, 25, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Die1", 35, 36, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Die2", 37, 38, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "TakeDamage", 28, 28, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "WaterAttack", 29, 30, 0.2f, true); // ���ֱ�
	Renderer_->CreateAnimation("Monster.bmp", "RollAttack", 31, 34, 0.2f, true); // ������
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

	// ����
	SetMonsterClass(MonsterClass::BOSS);
	SetHP(150);
	SetSpeed(50); // Need to chk : Speed

	// Index ����
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

	Index_ = 49; // ���� Index��
	SetPosition(Areas_[49].GetCenter());
	srand(time(NULL));
}

void Boss::Render()
{
}

void Boss::Update()
{
	AttTime_ += GameEngineTime::GetDeltaTime();
	WaterTime_ += GameEngineTime::GetDeltaTime();
	RollTime_ += GameEngineTime::GetDeltaTime();
	StayIdleTime_ += GameEngineTime::GetDeltaTime();
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
			EndAttack_ = true;
		}
	}
	else if (RandomAction_ == 4)
	{
		if (Renderer_->IsAnimationName("RollAttack")/*("RollAttackRight")*/)
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
		else if (Renderer_->IsAnimationName("RollAttack")/*("RollAttackLeft")*/)
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
	PrevIndex_ = Index_; // ���� �ε��� ����
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
			// ������ ���� �ƴϰ�, ��ǳ���� �ƴϸ�
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
			// ������ ���� �ƴϰ�, Wave Ÿ���� �ƴϸ�
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
			// ������ ���� �ƴϰ�, Wave Ÿ���� �ƴϸ�
			Area& SouthArea = Areas_[SouthIndex];
			if (false == SouthArea.HasWall())
			{
				Area& SouthArea = Areas_[SouthIndex];
				MovableAreas.insert(std::make_pair(2, SouthArea));
			}
		}

		if (NorthIndex >= 0 &&
			NorthIndex < Areas_.size() && // �� ũ�� �ȿ� ���;��ϰ�,
			Index_ % AreaHeight_ != 0) // ���� ���� ������ �ƴ� ��
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

		if (Dir_.x == 1) // ���������� ����
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
}

bool Boss::SameYLine() // ������
{
	if (PlayerIndex_ < 3 && Index_ < 3)
	{
		return true;
	}

	else if (PlayerIndex_ >= 3 && Index_ >= 3 &&
		PlayerIndex_ < 6 && Index_ < 6)
	{
		return true;
	}

	else if (PlayerIndex_ >= 6 && Index_ >= 6 &&
		PlayerIndex_ < 9 && Index_ < 9)
	{
		return true;
	}

	else
	{
		return false;
	}
}

void Boss::RollAttack()
{
	EndAttack_ = false;
	if (Index_ < AreaHeight_)
	{
		Renderer_->ChangeAnimation("RollAttack")/*("RollAttackRight")*/;

	} 
	else if (Index_ >= (AreaWidth_ - 1) * AreaHeight_)
	{
		Renderer_->ChangeAnimation("RollAttack")/*("RollAttackLeft")*/;
	}

}

void Boss::WaterAttack()
{
	EndAttack_ = false;
	Renderer_->ChangeAnimation("WaterAttack");
	Dir_ = float4::ZERO;
}


bool Boss::SameXLine() // ������
{
	int Offset = PlayerIndex_ - Index_;
	if (Offset < 0)
	{
		Offset = Offset * -1;
	}

	return Offset % 3 == 0;
}