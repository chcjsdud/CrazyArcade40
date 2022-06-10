#include "Ghost.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include "Area.h"
#include "GameEngine/GameEngineCollision.h"

Ghost::Ghost()
	: Monster()
	, AttTime_(0.0f)
{
}

Ghost::~Ghost()
{
}

void Ghost::Start()
{
	Monster::Start();
	//Renderer_ = CreateRenderer("Monster.bmp");
	//GameEngineImage* Image = Renderer_->GetImage();
	//Image->CutCount(10, 8);
	//Renderer_->CreateAnimation("Monster.bmp", "MoveRight", 6, 7, 0.3f, true);
	//Renderer_->CreateAnimation("Monster.bmp", "MoveLeft", 4, 5, 0.3f, true);
	//Renderer_->CreateAnimation("Monster.bmp", "MoveUp", 0, 1, 0.3f, true);
	//Renderer_->CreateAnimation("Monster.bmp", "MoveDown", 2, 3, 0.3f, true);
	//Renderer_->CreateAnimation("Monster.bmp", "Die", 8, 10, 0.2f, true);
	//Renderer_->CreateAnimation("Monster.bmp", "Start", 11, 14, 0.1f, true);
	//Renderer_->ChangeAnimation("Start");
	//SetSpeed(70);
	//Dir_ = float4::ZERO;
	SetHP(10000);
	CenterCol_->SetPivot(float4(0.0f, -18.0f));
}

void Ghost::Render()
{
}

void Ghost::Update()
{
	AttTime_ += GameEngineTime::GetInst()->GetDeltaTime();
	UpdateDirection();
	UpdateMove();
}

void Ghost::UpdateDirection()
{

	PrevIndex_ = Index_; // ���� �ε��� ����
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
				SetPosition(NewArea.GetCenter());
			}
		}
		NewArea.SetMapTile(MapTile_);
	}

	if (Dir_.x == 0 && Dir_.y == 0)
	{
		IsAreaChanged = true;
	}

	if (IsAreaChanged == true)
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
			if (East != MovableAreas.end())
			{
				Dir_ = float4::RIGHT;
				Direction_ = "Right";
			}

			else
			{
				//if (MovableAreas.size() == 0)
				//{
				//	Dir_ = float4::ZERO;
				//	//Direction_ = "Zero";
				//}
				//else
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
		}

		else if (Dir_.x == -1)

		{
			//if (West != MovableAreas.end())
			//{
			//	Dir_ = float4::LEFT;
			//	Direction_ = "Left";
			//}

			//else
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
		}

		else if (Dir_.y == -1)
		{
			if (North != MovableAreas.end())
			{
				Dir_ = float4::UP;
				Direction_ = "Up";
			}

			else
			{
				//if (MovableAreas.size() == 0)
				//{
				//	Dir_ = float4::ZERO;
				//	//Direction_ = "Zero";
				//}
				//else
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
		}

		else if (Dir_.y == 1)
		{
			if (South != MovableAreas.end())
			{
				Dir_ = float4::DOWN;
				Direction_ = "Down";
			}

			else
			{
				//if (MovableAreas.size() == 0)
				//{
				//	Dir_ = float4::ZERO;
				//	//Direction_ = "Zero";
				//}
				//else
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
		}
	}
}

void Ghost::UpdateMove()
{
	if (true == Renderer_->IsAnimationName(""))
	{
		if (false == Renderer_->IsEndAnimation())
		{
			SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_ * 10);
		}
		else
		{
			AttTime_ = 0.0f;
			SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_ * 10);
		}
	}

	if (AttTime_ > 15.0f)
	{
		//Renderer_->ChangeAnimation("Move" + Direction_);
	}

	else
	{
		//Renderer_->ChangeAnimation("Move" + Direction_);
		SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}

}
