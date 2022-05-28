#include "Monster2.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineContents/MapGameObject.h>

Monster2::Monster2()
	:Monster()
{
}

Monster2::~Monster2()
{
}

void Monster2::Start()
{
	Monster::Start();

	//악어
	Renderer_ = CreateRenderer("Monster.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 7);
	Renderer_->CreateAnimation("Monster.bmp", "MoveRight", 16, 17, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveLeft", 22, 23, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveUp", 12, 13, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveDown", 14, 15, 0.2f, true);
	Renderer_->ChangeAnimation("MoveLeft");
	
	// 미니 악어
	MiniRenderer_ = CreateRenderer("Monster.bmp");
	GameEngineImage* MiniImage = Renderer_->GetImage();
	MiniImage->CutCount(10, 7);
	MiniRenderer_->CreateAnimation("Monster.bmp", "MoveRight", 16, 17, 0.2f, true);
	MiniRenderer_->CreateAnimation("Monster.bmp", "MoveLeft", 22, 23, 0.2f, true);
	MiniRenderer_->CreateAnimation("Monster.bmp", "MoveUp", 12, 13, 0.2f, true);
	MiniRenderer_->CreateAnimation("Monster.bmp", "MoveDown", 14, 15, 0.2f, true);
	MiniRenderer_->CreateAnimation("Monster.bmp", "Die", 18, 20, 0.2f, true);

	Index_ = 100;
	CenterCol_->SetScale(float4(50.0f, 80.0f));
	CenterCol_->SetPivot(float4(0.0f, -40.0f));
	SetHP(2);
	SetSpeed(100);
	Dir_ = float4::LEFT;
	Direction_ = "Right";
	Dir_ = float4::RIGHT;
	MiniRenderer_->SetAlpha(0);
	MiniRenderer_->Off();
}

void Monster2::Render()
{
}

void Monster2::Update()
{
	UpdateDirection();
	UpdateMove();
	Die();
}

void Monster2::TakeDamage()
{
	if (GetAttTime_ > 2.0) // 2초 안에 다시 맞으면 DMG를 입지 않는다. (Need to chk : TIME)
	{

		SetHP(GetHp() - 1);
		if (GetHP() < 2)
		{
			MiniRenderer_->ChangeAnimation("MiniMove" + Direction_);
			SetSpeed(70); // Need to chk : Speed_
		}
		GetAttTime_ = 0.0f;

	}
}

void Monster2::UpdateDirection()
{
	if (GetHP() > 1)
	{
		Monster::UpdateDirection();
	}

	else
	{
		MiniRenderer_->On();
		Renderer_->SetAlpha(0);
		Renderer_->Off();

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
			MiniRenderer_->ChangeAnimation("Move" + Direction_);
		}

	}
}
