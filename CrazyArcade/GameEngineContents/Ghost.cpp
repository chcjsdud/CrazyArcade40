#include "Ghost.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include "Area.h"
#include "GameEngine/GameEngineCollision.h"
#include "Player.h"

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
	Renderer_ = CreateRenderer("BasicMonster.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 6);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveRight", 8, 9, 0.5f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveLeft", 17, 18, 0.5f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveUp", 4, 5, 0.5f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveDown", 0, 1, 0.5f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "AttackStartDown", 2, 2, 1.0f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "AttackStartUp", 6, 6, 1.0f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "AttackStartRight", 10, 10, 1.0f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "AttackStartLeft", 16, 16, 1.0f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "AttackEndDown", 3, 3, 0.7f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "AttackEndUp", 7, 7, 0.7f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "AttackEndRight", 11, 11, 0.7f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "AttackEndLeft", 15, 15, 0.7f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "Die", 12, 14, 0.2f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "Start", 13, 14, 0.1f, true); // need to chk : image 
	Renderer_->ChangeAnimation("Start");
	SetSpeed(20);
	Dir_ = float4::ZERO;
	SetHP(10000);
	CenterCol_->SetPivot(float4(0.0f, -18.0f));
	SetPosition(Areas_[100].GetCenter());
}

void Ghost::Render()
{
}

void Ghost::Update()
{
	AttTime_ += GameEngineTime::GetInst()->GetDeltaTime();

	if (true == Renderer_->IsAnimationName("Start") &&
		true == Renderer_->IsEndAnimation())
	{
		Renderer_->ChangeAnimation("MoveRight");
		Direction_ = "Right";
		Dir_ = float4::RIGHT;
	}
	else if (true != Renderer_->IsAnimationName("Die"))
	{
		UpdateAttack();
		UpdateMove();
		UpdateDirection();
		Die();
	}

	if (Renderer_->IsAnimationName("Die") &&
		Renderer_->IsEndAnimation())
	{
		GameEngineSound::SoundPlayOneShot("Ghost.wav");
		Death();
	}
}

void Ghost::UpdateDirection()
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
				SetPosition(NewArea.GetCenter());
			}
		}
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
			// 동쪽이 벽이 아니고, 물풍선이 아니면
			EastArea = Areas_[EastIndex];
			if (false == EastArea.HasWall() &&
				!(true == EastArea.HasBlock() && false == EastArea.GhostCanMoveTile()))
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
			if (false == WestArea.HasWall() &&
				!(true == WestArea.HasBlock() && false == WestArea.GhostCanMoveTile()))
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
			if (false == SouthArea.HasWall() &&
				!(true == SouthArea.HasBlock() && false == SouthArea.GhostCanMoveTile()))
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
			if (false == NorthArea.HasWall() &&
				!(true == NorthArea.HasBlock() && false == NorthArea.GhostCanMoveTile()))
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
	if (true == Renderer_->IsAnimationName("AttackStart" + Direction_))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			GameEngineSound::SoundPlayOneShot("Ghost_Attack.wav");
			Renderer_->ChangeAnimation("AttackEnd" + Direction_);
		}
	}

	else if (true == Renderer_->IsAnimationName("AttackEnd" + Direction_))
	{
		if (false == Renderer_->IsEndAnimation())
		{
			if (Direction_ == "Right")
			{
				Dir_ = float4::RIGHT;
			}
			else if ((Direction_ == "Left"))
			{
				Dir_ = float4::LEFT;
			}
			else if ((Direction_ == "Up"))
			{
				Dir_ = float4::UP;
			}
			else if ((Direction_ == "Down"))
			{
				Dir_ = float4::DOWN;
			}
			SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_ * 10);
		}
		else
		{
			Renderer_->ChangeAnimation("Move" + Direction_);
			SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}

	else if (true != Renderer_->IsAnimationName("AttackStart" + Direction_) &&
		true != Renderer_->IsAnimationName("Start"))
	{
		Renderer_->ChangeAnimation("Move" + Direction_);
		SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
}

void Ghost::Die()
{
	std::vector<GameEngineCollision*> Collision;

	if (true == CenterCol_->CollisionResult("1PColl", Collision, CollisionType::Rect, CollisionType::Rect) ||
		true == CenterCol_->CollisionResult("2PColl", Collision, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* ColActor : Collision)
		{
			GameEngineActor* ColPlayer = ColActor->GetActor();
			if (dynamic_cast<Player*>(ColPlayer))
			{
				Renderer_->ChangeAnimation("Die");
			}

		}
	}
}

void Ghost::UpdateAttack()
{
	if (AttTime_ > 10.0f)
	{
		Renderer_->ChangeAnimation("AttackStart" + Direction_);
		Dir_ = float4::ZERO;
		AttTime_ = 0.0f;
	}
}
