#include "Boss.h"
#include "Monster.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>
#include <vector>

Boss::Boss()
	: Monster()
	, PlayerIndex_(4)
	, RollTime_(0.0f)
	, WaterTime_(0.0f)
	, AttTime_(0.0f)
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
	Image->CutCount(10, 7);
	Renderer_->CreateAnimation("Monster.bmp", "Idle", 24, 25, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveRight", 26, 27, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveLeft", 40, 41, 0.2f, true);
	// Need to chk : MoveUp 이미지
	Renderer_->CreateAnimation("Monster.bmp", "MoveUp", 0, 1, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveDown", 24, 25, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Die1", 35, 36, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Die2", 37, 38, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "TakeDamage", 28, 28, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "WaterAttack", 29, 30, 0.2f, true); // 물주기
	Renderer_->CreateAnimation("Monster.bmp", "RollAttack", 31, 34, 0.2f, true); // 구르기
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
	AreaHeight_ = 3;
	AreaWidth_ = 3;

	for (int x = 0; x < AreaWidth_; ++x)
	{
		for (int y = 0; y < AreaHeight_; ++y)
		{
			float StartX = static_cast<float>((MapSizeX_ / AreaWidth_ * x) + 20);
			float StartY = static_cast<float>((MapSizeY_ / AreaHeight_ * y) + 40);
			float EndX = static_cast<float>((MapSizeX_ / AreaWidth_ * (x + 1)) + 20);
			float EndY = static_cast<float>((MapSizeY_ / AreaHeight_ * (y + 1)) + 40);

			Area area(ColMapImage_, StartX, StartY, EndX, EndY);
			Areas_.push_back(area);
		}
	}

	Index_ = 3; // 시작 Index를
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
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
}

void Boss::UpdateDirection()
{
	Monster::UpdateDirection();
}

void Boss::UpdateAttack()
{
	if ((Renderer_->IsAnimationName("RollAttack") && RollTime_ > 8) ||
		(Renderer_->IsAnimationName("WaterAttack") && WaterTime_ > 3))
	{
		AttTime_ = 0.0f;
		if (Index_ == 0 || Index_ == 3)
		{
			Dir_ = float4::RIGHT;
			Direction_ = "Right";
			Renderer_->ChangeAnimation("MoveRight");
		}

		else if (Index_ == 6 || Index_ == 7)
		{
			Dir_ = float4::DOWN;
			Direction_ = "Down";
			Renderer_->ChangeAnimation("MoveDown");
		}

		else if (Index_ == 8 || Index_ == 5)
		{
			Dir_ = float4::LEFT;
			Direction_ = "Left";
			Renderer_->ChangeAnimation("MoveLeft");
		}

		else if (Index_ == 1 || Index_ == 2 || Index_ == 4)
		{
			Dir_ = float4::UP;
			Direction_ = "Up";
			Renderer_->ChangeAnimation("MoveUp");
		}
	}

	if (AttTime_ > 4.0f && true == Renderer_->IsAnimationName("Move" + Direction_))
	{
		StayIdleTime_ = 0.0f;
		Dir_ = float4::ZERO;
		Renderer_->ChangeAnimation("Idle");
	}

	if (StayIdleTime_ > 1.0f && Renderer_->IsAnimationName("Idle"))
	{
		for (int i = 0; i < Areas_.size(); ++i)
		{
			Area& NewArea = Areas_[i]; // 플레이어의 Index와 내 Index 비교
			if (true == NewArea.Contains(Player_->GetPosition()))
			{
				PlayerIndex_ = i;
			}
			if (true == NewArea.Contains(GetPosition()))
			{
				Index_ = i;
			}
		}

		CheckIndex_ = PlayerIndex_ - Index_;

		if (true == SameYLine()) // 같은 세로줄에 있으면
		{
			if (CheckIndex_ > 0)
			{
				Dir_ = float4::DOWN;
				Direction_ = "Down";
				Renderer_->ChangeAnimation("MoveDown");
			}
			else // 플레이어가 나보다 위에 있으면
			{
				Dir_ = float4::UP;
				Direction_ = "Up";
				Renderer_->ChangeAnimation("MoveUp");
			}
		}
		else if (true == SameXLine())
		{
			if (Index_ == 3 || Index_ == 4 || Index_ == 5)
			{
				if (CheckIndex_ < 0)
				{
					Dir_ = float4::RIGHT;
					Direction_ = "Right";
					Renderer_->ChangeAnimation("MoveRight");
				}
				else // 플레이어가 나보다 왼쪽에 있으면
				{
					Dir_ = float4::LEFT;
					Direction_ = "Left";
					Renderer_->ChangeAnimation("MoveLeft");
				}
			}

			else if (Index_ != 3 || Index_ != 4 || Index_ != 5)
			{
				if (CheckIndex_ > 0)
				{
					Dir_ = float4::RIGHT;
					Direction_ = "Right";
					Renderer_->ChangeAnimation("RollAttack");
				}
				else // 플레이어가 나보다 왼쪽에 있으면
				{
					Dir_ = float4::LEFT;
					Direction_ = "Left";
					Renderer_->ChangeAnimation("RollAttack");
				}
				RollTime_ = 0.0f;
			}
		}

		else // 같은 세로줄도 가로줄도 아니면 물풍선 공격
		{
			WaterTime_ = 0.0f;
			Renderer_->ChangeAnimation("WaterAttack");
		}
	}

}

bool Boss::SameYLine() // 세로줄
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
}

void Boss::WaterAttack()
{
}


bool Boss::SameXLine() // 가로줄
{
	int Offset = PlayerIndex_ - Index_;
	if (Offset < 0)
	{
		Offset = Offset * -1;
	}

	return Offset % 3 == 0;
}