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
#include "MapGameObject.h"

Boss::Boss()
	: Monster()
	, PlayerIndex_(4)
	, WaterTime_(0.0f)
	, RollTime_(0.0f)
	, AreaChangeCount_(0)
	, BossHP_(nullptr)
	, Boss_(nullptr)
	, BossBoom_(nullptr)
	, CheckIndex_()
	, WaterAttackStartTime_(0.0f)
	, WaterAttacOn_(false)
{
}

Boss::~Boss()
{
}

void Boss::SetBoom(MapGameObject* _BossBoom)
{
	BossBoom_ = _BossBoom;
}

void Boss::Start()
{
	Monster::Start();
	// 이미지
	Renderer_ = CreateRenderer("Boss.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 5);
	Renderer_->CreateAnimation("Boss.bmp", "Idle", 0, 1, 0.2f, true);
	Renderer_->CreateAnimation("Boss.bmp", "MoveRight", 2, 3, 0.2f, true);
	Renderer_->CreateAnimation("Boss.bmp", "MoveLeft", 4, 5, 0.2f, true);
	Renderer_->CreateAnimation("Boss.bmp", "MoveUp", 6, 7, 0.2f, true);
	Renderer_->CreateAnimation("Boss.bmp", "MoveDown", 0, 1, 0.2f, true);
	Renderer_->CreateAnimation("Boss.bmp", "Die", 36, 38, 0.3f, true);
	Renderer_->CreateAnimation("Boss.bmp", "DieBubble", 39, 42, 0.3f, true);
	Renderer_->CreateAnimation("Boss.bmp", "DieEnd", 43, 45, 0.3f, false); // 이미지 높이
	Renderer_->CreateAnimation("Boss.bmp", "TakeDamageDown", 13, 14, 0.2f, true);
	Renderer_->CreateAnimation("Boss.bmp", "TakeDamageRight", 15, 16, 0.2f, true);
	Renderer_->CreateAnimation("Boss.bmp", "TakeDamageLeft", 17, 18, 0.2f, true);
	// Need to chk : TakeDamageUp 필요
	Renderer_->CreateAnimation("Boss.bmp", "WaterAttack", 24, 35, 0.2f, false);
	Renderer_->CreateAnimation("Boss.bmp", "RollAttackRight", 8, 12, 0.2f, true);
	Renderer_->CreateAnimation("Boss.bmp", "RollAttackLeft", 19, 23, 0.2f, true);
	Renderer_->ChangeAnimation("MoveRight");
	Dir_ = float4::RIGHT;
	Direction_ = "Right";
	CenterCol_ = CreateCollision("Monster", float4(50.0f, 50.0f), float4(0.0f, 0.0f));
	CenterCol_->SetScale(float4(130.0, 150.0f));
	CenterCol_->SetPivot(float4(0.0f, -50.0f));

	{
		//Boss UI
		HPUI_ = CreateRenderer("HPUI.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0.0f, -180.0f));
		GameEngineImage* HPImage14 = GameEngineImageManager::GetInst()->Find("HP14.bmp");
		HPImage14->CutCount(1, 1);
		GameEngineImage* HPImage13 = GameEngineImageManager::GetInst()->Find("HP13.bmp");
		HPImage13->CutCount(1, 1);
		GameEngineImage* HPImage12 = GameEngineImageManager::GetInst()->Find("HP12.bmp");
		HPImage12->CutCount(1, 1);
		GameEngineImage* HPImage11 = GameEngineImageManager::GetInst()->Find("HP11.bmp");
		HPImage11->CutCount(1, 1);
		GameEngineImage* HPImage10 = GameEngineImageManager::GetInst()->Find("HP10.bmp");
		HPImage10->CutCount(1, 1);
		GameEngineImage* HPImage9 = GameEngineImageManager::GetInst()->Find("HP9.bmp");
		HPImage9->CutCount(1, 1);
		GameEngineImage* HPImage8 = GameEngineImageManager::GetInst()->Find("HP8.bmp");
		HPImage8->CutCount(1, 1);
		GameEngineImage* HPImage7 = GameEngineImageManager::GetInst()->Find("HP7.bmp");
		HPImage7->CutCount(1, 1);
		GameEngineImage* HPImage6 = GameEngineImageManager::GetInst()->Find("HP6.bmp");
		HPImage6->CutCount(1, 1);
		GameEngineImage* HPImage5 = GameEngineImageManager::GetInst()->Find("HP5.bmp");
		HPImage5->CutCount(1, 1);
		GameEngineImage* HPImage4 = GameEngineImageManager::GetInst()->Find("HP4.bmp");
		HPImage4->CutCount(1, 1);
		GameEngineImage* HPImage3 = GameEngineImageManager::GetInst()->Find("HP3.bmp");
		HPImage3->CutCount(1, 1);
		GameEngineImage* HPImage2 = GameEngineImageManager::GetInst()->Find("HP2.bmp");
		HPImage2->CutCount(1, 1);
		GameEngineImage* HPImage1 = GameEngineImageManager::GetInst()->Find("HP1.bmp");
		HPImage1->CutCount(1, 1);

		BossHP_ = CreateRenderer((int)ORDER::BOSS, RenderPivot::CENTER, float4{ 0.0f, 0.0f });
		BossHP_->CreateAnimation("HP14.bmp", "HP14", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP13.bmp", "HP13", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP12.bmp", "HP12", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP11.bmp", "HP11", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP10.bmp", "HP10", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP9.bmp", "HP9", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP8.bmp", "HP8", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP7.bmp", "HP7", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP6.bmp", "HP6", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP5.bmp", "HP5", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP4.bmp", "HP4", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP3.bmp", "HP3", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP2.bmp", "HP2", 0, 0, 1.0f, false);
		BossHP_->CreateAnimation("HP1.bmp", "HP1", 0, 0, 1.0f, false);
		BossHP_->ChangeAnimation("HP14");
	}

	{

		// 상태
		SetMonsterClass(MonsterClass::BOSS);
		SetHP(14);
		SetSpeed(50); // Need to chk : Speed

		// Index 설정
		Index_ = 97; // 시작 Index를
		SetPosition(Areas_[97].GetCenter());
	}
}

void Boss::Render()
{
}

void Boss::Update()
{
	WaterAttackStartTime_ += GameEngineTime::GetInst()->GetDeltaTime();
	WaterTime_ += GameEngineTime::GetInst()->GetDeltaTime();
	RollTime_ += GameEngineTime::GetInst()->GetDeltaTime();
	UpdateDirection();
	UpdateMove();
	UpdateHP();
	Die();

}

void Boss::Die()
{
	if (true == IsDie()) // HP가 0이거나 0보다 작으면
	{

		if (true == Renderer_->IsAnimationName("Die") && true == Renderer_->IsEndAnimation())
		{
			CenterCol_->Off();
			Death();
		}

		if (true != Renderer_->IsAnimationName("Die"))
		{
			Dir_ = float4::ZERO;
			Renderer_->ChangeAnimation("Die");
		}
	}

}

void Boss::UpdateHP()
{
	switch (GetHP())
	{
	case 0:
		BossHP_->SetAlpha(0);
		HPUI_->SetAlpha(0);
		break;
	case 1:
		BossHP_->ChangeAnimation("HP1");
		BossHP_->SetPivot(float4(-50.5f, -176.0f));
		break;
	case 2:
		BossHP_->ChangeAnimation("HP2");
		BossHP_->SetPivot(float4(-46.0f, -176.0f));
		break;
	case 3:
		BossHP_->ChangeAnimation("HP3");
		BossHP_->SetPivot(float4(-42.5f, -176.0f));
		break;
	case 4:
		BossHP_->ChangeAnimation("HP4");
		BossHP_->SetPivot(float4(-38.5f, -176.0f));
		break;
	case 5:
		BossHP_->ChangeAnimation("HP5");
		BossHP_->SetPivot(float4(-35.0f, -176.0f));
		break;
	case 6:
		BossHP_->ChangeAnimation("HP6");
		BossHP_->SetPivot(float4(-31.0f, -176.0f));
		break;
	case 7:
		BossHP_->ChangeAnimation("HP7");
		BossHP_->SetPivot(float4(-27.0f, -176.0f));
		break;
	case 8:
		BossHP_->ChangeAnimation("HP8");
		BossHP_->SetPivot(float4(-23.5f, -176.0f));
		break;
	case 9:
		BossHP_->ChangeAnimation("HP9");
		BossHP_->SetPivot(float4(-20.0f, -176.0f));
		break;
	case 10:
		BossHP_->ChangeAnimation("HP10");
		BossHP_->SetPivot(float4(-16.0f, -176.0f));
		break;
	case 11:
		BossHP_->ChangeAnimation("HP11");
		BossHP_->SetPivot(float4(-12.5f, -176.0f));
		break;
	case 12:
		BossHP_->ChangeAnimation("HP12");
		BossHP_->SetPivot(float4(-8.5f, -176.0f));
		break;
	case 13:
		BossHP_->ChangeAnimation("HP13");
		BossHP_->SetPivot(float4(-5.0f, -176.0f));
		break;
	case 14:
		BossHP_->ChangeAnimation("HP14");
		BossHP_->SetPivot(float4(0.0f, -176.0f));
		break;
	}
}

void Boss::UpdateMove()
{

	if (RandomAction_ < 3)
	{
		if (true != IsDie())
		{
			Renderer_->ChangeAnimation("Move" + Direction_);
			SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}

	else if (RandomAction_ == 3)
	{
		if (Renderer_->IsAnimationName("WaterAttack") &&
			Renderer_->IsEndAnimation())
		{
			if (WaterTime_ > 3.0f)
			{
				Dir_ = float4::ZERO;
				EndAttack_ = true;
				CanAttackAreas.clear();
			}
		}
	}

	else if (RandomAction_ == 4)
	{
		if (Renderer_->IsAnimationName("RollAttackRight"))
		{
			if (RollTime_ < 8.0f)
			{
				SetMove(float4::RIGHT * GameEngineTime::GetInst()->GetDeltaTime() * Speed_);
			}
			else
			{
				Dir_ = float4::ZERO;
				EndAttack_ = true;
			}
		}
		else if (Renderer_->IsAnimationName("RollAttackLeft"))
		{
			if (RollTime_ < 8.0f)
			{
				SetMove(float4::LEFT * GameEngineTime::GetInst()->GetDeltaTime() * Speed_);
			}
			else
			{
				Dir_ = float4::ZERO;
				EndAttack_ = true;
			}
		}

	}


}

void Boss::UpdateDirection()
{
	PrevIndex_ = Index_; // 이전 인덱스 저장
	bool IsAreaChanged = false;

	if (false == Renderer_->IsAnimationName("WaterAttack") &&
		false == Renderer_->IsAnimationName("RollAttack" + Direction_))
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
					if (AreaChangeCount_ == 1 ||
						Index_ < AreaHeight_ ||
						Index_ % AreaHeight_ == 0 ||
						Index_ % AreaHeight_ == AreaHeight_ - 1 ||
						Index_ >= (AreaWidth_ - 1) * AreaHeight_)
					{
						if ((Index_ < AreaHeight_ ||
							Index_ >= (AreaWidth_ - 1) * AreaHeight_) &&
							RandomAction_ != 0)
						{
							if (Index_ == 0 ||
								Index_ == 8 ||
								Index_ == 4 ||
								Index_ == 94 ||
								Index_ == 90 ||
								Index_ == 98)
							{
								RandomAction_ = 4;
								IsAreaChanged = true;
								AreaChangeCount_ = 0;
							}
							else
							{
								RandomAction_ = 0;
								IsAreaChanged = true;
								AreaChangeCount_ = 0;
							}
						}
						else
						{
							RandomAction_ = (rand() % 4);
							IsAreaChanged = true;
							AreaChangeCount_ = 0;
						}
						SetPosition(NewArea.GetCenter());
					}
				}
			}
		}
	}
	CheckWaveTile(GetPosition());

	if (Dir_.x == 0 && Dir_.y == 0)
	{
		if ((Renderer_->IsAnimationName("WaterAttack") && EndAttack_ == true) ||
			(Renderer_->IsAnimationName("RollAttack" + Direction_) && EndAttack_ == true))
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

void Boss::TakeDamage()
{
	if (GetAttTime_ > 2.0) // 2초 안에 다시 맞으면 DMG를 입지 않는다. (Need to chk : TIME)
	{
		SetHP(GetHp() - 1);
		GetAttTime_ = 0.0f;
		Renderer_->ChangeAnimation("TakeDamage" + Direction_);
		Dir_ = float4::ZERO;
	}
}

void Boss::UpdateAttack()
{
	if (false == Renderer_->IsAnimationName("WaterAttack") &&
		false == Renderer_->IsAnimationName("RollAttack" + Direction_))
	{
		WaterTime_ = 0.0f;
		RollTime_ = 0.0f;
		EndAttack_ = false;
	}

}


void Boss::RollAttack()
{
	UpdateAttack();
	if (Index_ < AreaHeight_ &&
		false == Renderer_->IsAnimationName("RollAttackRight") &&
		false == Renderer_->IsAnimationName("RollAttackLeft"))
	{
		Direction_ = "Right";
		Renderer_->ChangeAnimation("RollAttackRight");
	}
	else if (Index_ >= (AreaWidth_ - 1) * AreaHeight_ &&
		false == Renderer_->IsAnimationName("RollAttackLeft") &&
		false == Renderer_->IsAnimationName("RollAttackRight"))
	{
		Direction_ = "Left";
		Renderer_->ChangeAnimation("RollAttackLeft");
	}

}

void Boss::WaterAttack()
{
	UpdateAttack();
	Renderer_->ChangeAnimation("WaterAttack");
	CheckCanAttackTile();
	Dir_ = float4::ZERO;
}

void Boss::CheckCanAttackTile()
{
	if (MapTile_ == nullptr)
	{
		return;
	}

	int EastIndex = Index_ + AreaHeight_;
	int WestIndex = Index_ - AreaHeight_;
	int NorthIndex = Index_ - 1;
	int SouthIndex = Index_ + 1;
	int NorthEastIndex = EastIndex - 1;
	int	NorthWestIndex = WestIndex - 1;
	int	SouthEastIndex = EastIndex + 1;
	int	SouthWestIndex = WestIndex + 1;

	// 동서남북이 벽이 아니면
	if (EastIndex >= 0 &&
		EastIndex < Areas_.size() &&
		Index_ < Areas_.size() - AreaHeight_)
	{
		EastArea = Areas_[EastIndex];
		if (false == EastArea.HasWall())
		{
			Area& EastArea = Areas_[EastIndex];
			CanAttackAreas.insert(std::make_pair(0, EastArea));
		}
	}

	if (WestIndex >= 0 &&
		WestIndex < Areas_.size() &&
		Index_ >= AreaHeight_)
	{
		WestArea = Areas_[WestIndex];
		if (false == WestArea.HasWall())
		{
			Area& WestArea = Areas_[WestIndex];
			CanAttackAreas.insert(std::make_pair(1, WestArea));
		}
	}

	if (SouthIndex >= 0 &&
		SouthIndex < Areas_.size() &&
		Index_ % AreaHeight_ != AreaHeight_ - 1)
	{
		Area& SouthArea = Areas_[SouthIndex];
		if (false == SouthArea.HasWall() &&
			!(true == SouthArea.HasBlock() &&
				false == SouthArea.HasWaveTile()))
		{
			Area& SouthArea = Areas_[SouthIndex];
			CanAttackAreas.insert(std::make_pair(2, SouthArea));
		}
	}

	if (NorthIndex >= 0 &&
		NorthIndex < Areas_.size() &&
		Index_ % AreaHeight_ != 0)
	{
		Area& NorthArea = Areas_[NorthIndex];
		if (false == NorthArea.HasWall())
		{
			Area& NorthArea = Areas_[NorthIndex];
			CanAttackAreas.insert(std::make_pair(3, NorthArea));
		}
	}

	if (NorthEastIndex >= 0 &&
		NorthEastIndex < Areas_.size() &&
		Index_ % AreaHeight_ != 0 &&
		Index_ < Areas_.size() - AreaHeight_)
	{
		Area& NorthEastArea = Areas_[NorthEastIndex];
		CanAttackAreas.insert(std::make_pair(4, NorthEastArea));
	}

	if (NorthWestIndex >= 0 &&
		NorthWestIndex < Areas_.size() &&
		Index_ % AreaHeight_ != 0 &&
		Index_ >= AreaHeight_)
	{
		Area& NorthWestArea = Areas_[NorthWestIndex];
		CanAttackAreas.insert(std::make_pair(5, NorthWestArea));
	}

	if (SouthEastIndex >= 0 &&
		SouthEastIndex < Areas_.size() &&
		Index_ % AreaHeight_ != AreaHeight_ - 1 &&
		Index_ < Areas_.size() - AreaHeight_)
	{
		Area& SouthEastArea = Areas_[SouthEastIndex];
		CanAttackAreas.insert(std::make_pair(6, SouthEastArea));
	}

	if (SouthWestIndex >= 0 &&
		SouthWestIndex < Areas_.size() &&
		Index_ % AreaHeight_ != AreaHeight_ - 1 &&
		Index_ >= AreaHeight_)
	{
		Area& SouthWestArea = Areas_[SouthWestIndex];
		CanAttackAreas.insert(std::make_pair(7, SouthWestArea));
	}

	if (Index_ >= 0 &&
		Index_ < Areas_.size())
	{
		Area& CenterArea = Areas_[Index_];
		CanAttackAreas.insert(std::make_pair(8, CenterArea));
	}

	if (CanAttackAreas.size() != 0)
	{
		for (auto it = CanAttackAreas.begin(); it != CanAttackAreas.end(); it++)
		{
			// 블락을 체크해서 블락이 있으면 
			if (0 == it->second.ChooseWaterAttackAni()) // 블럭 있음
			{
				//WaterAttack_->ChangeAnimation("boom"); // 먼지
				//WaterAttack_->SetAlpha(255);
				//WaterAttacOn_ = true;
				auto a = it->second.GetMapTile()->GetTileIndex(it->second.GetCenter() - float4(20.0f, 40.0f));
				it->second.GetMapTile()->DeleteTile(a.X, a.Y);
			}

			//else if (1 == it->second.ChooseWaterAttackAni()) // 블럭 없음
			{
				BossBoom_->BubblePop(GetPosition() - float4(20.0f, 40.0f), 3);
				break;
			}
		}
	}
}

//Todo chowon: BOSS_COUNT--; -> boss 죽었을 때 