#include "Monster.h"
#include <vector>
#include <map>
#include <GameEngineContents/Area.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineContents/MapGameObject.h>
#include <GameEngine/GameEngineImageManager.h>
#include "GameEngine/GameEngine.h"
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GameEngineBase/GameEngineInput.h>

int Monster::LV1_MON_COUNT = 8;
int Monster::LV2_MON_COUNT = 6;
int Monster::BOSS_COUNT = 1;

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
	, CurArea(ColMapImage_, 0, 0, 0, 0)
	, NorthEastArea(ColMapImage_, 0, 0, 0, 0)
	, NorthWestArea(ColMapImage_, 0, 0, 0, 0)
	, SouthEastArea(ColMapImage_, 0, 0, 0, 0)
	, SouthWestArea(ColMapImage_, 0, 0, 0, 0)
	, IndexCheck_(false)
	, PrevIndex_(0)
	, MapTile_(nullptr)
	, CurBlockType_(BlockType::Max)
	, IsStageClear_(false)
	, SpeechBubble_(nullptr)
{
}

Monster::~Monster()
{
}


void Monster::Start()
{
	CenterCol_ = CreateCollision("Monster", float4(25.0f, 35.0f), float4(0.0f, 0.0f));

	if (GetLevel()->GetNameCopy() == "Monster1Level")
	{
		SetColMapImage("MonsterStage1_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "Monster2Level")
	{
		SetColMapImage("MonsterStage2_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "PlayerTeamTest")
	{
		SetColMapImage("Camp_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "BossLevel")
	{
		SetColMapImage("Boss_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "CemetoryLevel")
	{
		SetColMapImage("Cemetory_ColMap.bmp");
	}

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

	srand(time(NULL));
}

void Monster::Update()
{
	if (false == Renderer_->IsAnimationName("Start"))
	{
		GetAttTime_ += GameEngineTime::GetDeltaTime();
		UpdateDirection();
		UpdateMove();
		AllMonsterDeathModeSwitch();
		Die();
	}
}

void Monster::UpdateDirection()
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
		NewArea.SetMapTile(MapTile_);
	}

	CheckWaveTile(GetPosition());

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
				!(true == EastArea.HasBlock() && false == EastArea.HasWaveTile()))
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
				!(true == WestArea.HasBlock() && false == WestArea.HasWaveTile()))
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
				!(true == SouthArea.HasBlock() && false == SouthArea.HasWaveTile()))
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
				!(true == NorthArea.HasBlock() && false == NorthArea.HasWaveTile()))
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

void Monster::UpdateMove()
{
	if (true != IsDie())
	{
		Renderer_->ChangeAnimation("Move" + Direction_);
		SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
}

void Monster::TakeDamage()
{
	if (GetAttTime_ > 2.0) // 2초 안에 다시 맞으면 DMG를 입지 않는다. (Need to chk : TIME)
	{
		SetHP(GetHp() - 1);
		GetAttTime_ = 0.0f;
	}
}


void Monster::AllMonsterDeathModeSwitch()
{
	if (true == GameEngineInput::GetInst()->IsDown("AllMonsterDeath") && IsStageClear_ == false)
	{
		if (GetLevel()->GetNameCopy() == "Monster1Level" && GetHP() > 0)
		{
			Renderer_->ChangeAnimation("Die");
			SetHP(0);
			LV1_MON_COUNT = 0;
		}

		IsStageClear_ = true;
	}
}

void Monster::Render()
{
	std::string IndexX = "";
	std::string IndexY = "";


	TileIndex TileIndex_ = MapTile_->GetTileIndex(GetPosition() - float4(20.0f, 40.0f));
	IndexX = "Index X : " + std::to_string(TileIndex_.X);
	IndexY = "Index Y : " + std::to_string(TileIndex_.Y);

		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 30, IndexX.c_str(), static_cast<int>(IndexX.length()));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix() + 40, GetCameraEffectPosition().iy() - 10, IndexY.c_str(), static_cast<int>(IndexY.length()));

}

void Monster::Die()
{
	if (true == IsDie()) // HP가 0이거나 0보다 작으면
	{

		if (true == Renderer_->IsAnimationName("Die") && true == Renderer_->IsEndAnimation())
		{
			CenterCol_->Off();
			Death();
			if (GetLevel()->GetNameCopy() == "Monster1Level")
			{
				LV1_MON_COUNT--; // total 몬스터 수가 줄어든다.
			}

			else if (GetLevel()->GetNameCopy() == "Monster2Level") // 만약 몬스터가 한마리 남으면
			{
				LV2_MON_COUNT--; // total 몬스터 수가 줄어든다.
			}

			else if (GetLevel()->GetNameCopy() == "BossLevel")
			{
				BOSS_COUNT--;
			}

			if (LV1_MON_COUNT == 1 || LV2_MON_COUNT == 1)
			{
				SetSpeed(Speed_ + 20); // 속도가 빨라져라
			}
		}

		if (true != Renderer_->IsAnimationName("Die"))
		{
			Dir_ = float4::ZERO;
			Renderer_->ChangeAnimation("Die");
		}
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

void Monster::SetColMapImage(std::string _Name)
{
	ColMapImage_ = GameEngineImageManager::GetInst()->Find(_Name);
}

GameEngineImage* Monster::GetColMapImage()
{
	return ColMapImage_;
}

void Monster::CheckWaveTile(float4 _Pos)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos - float4(20.0f, 40.0f));
	if (TileIndex_.Y >= 13 || TileIndex_.X >= 15)
	{
		return;
	}

	BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	if (Tiles_ == nullptr)
	{
		return;
	}

	else if (Tiles_->BlockType_ == BlockType::WaveBlock)
	{
		TakeDamage();
	}
}