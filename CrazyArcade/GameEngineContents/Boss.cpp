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
	AreaHeight_ = 3;
	AreaWidth_ = 3;

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

	Index_ = 3; // ���� Index��
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
			if (Index_ < 6)
			{
				EastArea = Areas_[EastIndex];
				if (true == EastArea.HasWall()) // ������ ��ġ�� ���� �������� �ƴϰ�, �����ʿ� ��ֹ��� ������ ��������
				{
					Dir_ = float4::DOWN;
					Direction_ = "Down";
					Renderer_->ChangeAnimation("MoveDown");
				}

			}
			else // ������ ��ġ�� ���� ���� �������̸� ��������
			{
				Dir_ = float4::DOWN;
				Direction_ = "Down";
				Renderer_->ChangeAnimation("MoveDown");
			}
		}

		else if (Dir_.x == -1) // �������� ���� �ְ�
		{
			int WestIndex = Index_ - AreaHeight_;
			int SouthIndex = Index_ + 1;
			if (Index_ >= 3)
			{
				WestArea = Areas_[WestIndex];
				if (true == WestArea.HasWall()) // ������ ��ġ�� ���� ������ �ƴϰ�, ���ʿ� ��ֹ��� ������ �ö󰡶�
				{
					Dir_ = float4::UP;
					Direction_ = "Up";
					Renderer_->ChangeAnimation("MoveUp");
				}
			}

			else // ������ ��ġ�� ���� �����̸� �ö󰡶�
			{
				Dir_ = float4::UP;				
				Direction_ = "Up";
				Renderer_->ChangeAnimation("MoveUp");
			}
		}

		else if (Dir_.y == 1) // �Ʒ��� �������� �ְ�
		{
			int SouthIndex = Index_ + 1;
			int EastIndex = Index_ + AreaHeight_;
			if (Index_ % 3 != 2) // ������ ��ġ�� �� �Ʒ��� �ƴϰ�, �Ʒ��� ��ֹ��� ������ �������� ����
			{
				SouthArea = Areas_[SouthIndex];
				if (true == SouthArea.HasWall())
				{
					Dir_ = float4::LEFT;
					Direction_ = "Left";
					Renderer_->ChangeAnimation("MoveLeft");
				}
			}
			else // ������ ��ġ�� �� �Ʒ��� �������� ����
			{
				Dir_ = float4::LEFT;
				Direction_ = "Left";
				Renderer_->ChangeAnimation("MoveLeft");
			}
		}

		else if (Dir_.y == -1) // ���� ���� �ְ�
		{
			int NorthIndex = Index_ - 1;
			int WestIndex = Index_ - AreaHeight_;
			if (Index_ % 3 != 0) // ������ ��ġ�� �� ���� �ƴϰ�, ���� ��ֹ��� ������ ���������� ����
			{
				NorthArea = Areas_[NorthIndex];
				if (true == NorthArea.HasWall())
				{
					Dir_ = float4::RIGHT;
					Direction_ = "Right";
					Renderer_->ChangeAnimation("MoveRight");
				}
			}
			else // ������ ��ġ�� �� ���� ���������� ����
			{
				Dir_ = float4::RIGHT;
				Direction_ = "Right";
				Renderer_->ChangeAnimation("MoveRight");
			}
		}
	}
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
			Area& NewArea = Areas_[i]; // �÷��̾��� Index�� �� Index ��
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

		if (true == SameYLine()) // ���� �����ٿ� ������
		{
			if (CheckIndex_ > 0)
			{
				Dir_ = float4::DOWN;
				Direction_ = "Down";
				Renderer_->ChangeAnimation("MoveDown");
			}
			else // �÷��̾ ������ ���� ������
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
				else // �÷��̾ ������ ���ʿ� ������
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
				else // �÷��̾ ������ ���ʿ� ������
				{
					Dir_ = float4::LEFT;
					Direction_ = "Left";
					Renderer_->ChangeAnimation("RollAttack");
				}
				RollTime_ = 0.0f;
			}
		}

		else // ���� �����ٵ� �����ٵ� �ƴϸ� ��ǳ�� ����
		{
			WaterTime_ = 0.0f;
			Renderer_->ChangeAnimation("WaterAttack");
		}
	}

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
}

void Boss::WaterAttack()
{
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