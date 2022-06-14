#include "BossBoom.h"
#include "Area.h"
#include "GameItemObject.h"
#include <GameEngine/GameEngineImageManager.h>

BossBoom::BossBoom()
{
}

BossBoom::~BossBoom()
{
}

void BossBoom::Start()
{
	Bubble_ = CreateRenderer("BossBoom.bmp");
	GameEngineImage* Image = Bubble_->GetImage();
	Image->CutCount(8, 3);
	Bubble_->CreateAnimation("BossBoom.bmp", "BubbleBubble", 0, 3, 0.1f, true);
	Bubble_->CreateAnimation("BossBoom.bmp", "Dust", 19, 20, 0.1f, true);
	Bubble_->CreateAnimation("BossBoom.bmp", "None", 21, 21, 0.1f, false);
	Bubble_->ChangeAnimation("None");
}

void BossBoom::Update()
{
	if (Bubble_->IsAnimationName("BubbleBubble"))
	{
		if (CanAttackAreas_.find(8) != CanAttackAreas_.end())
		{
			SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() *  300);
			if (CanAttackAreas_[8].GetCenter().y < GetPosition().y)
			{
				if (CanAttackAreas_.size() != 0)
				{
					for (auto it = CanAttackAreas_.begin(); it != CanAttackAreas_.end(); it++)
					{
						Area& _Area = it->second;
						float4 _Center = _Area.GetCenter() - float4(20.0f, 40.0f);
						// 블락을 체크해서 블락이 있으면 
						if (0 == _Area.ChooseWaterAttackAni()) // 블럭 있음
						{
							GameEngineSound::SoundPlayOneShot("Boss_Hit.mp3");
							TileIndex _TileIndex = _Area.GetMapTile()->GetTileIndex(_Center);
							BlockTile* _check = _Area.GetMapTile()->GetTile<BlockTile>(_TileIndex.X, _TileIndex.Y);
							_check->TilePos_ = _Center;
							if (_check->BlockType_ == BlockType::BubbleBlock || _check->BlockType_ == BlockType::WaveBlock)
							{
								BossBubblePop(_Center);
								return;
							}
							
							else
							{
								_check->Renderer->ChangeAnimation("Death");
								_check->TileIndex_ = _TileIndex;
								DeleteTileList_.push_back(_check);
							}
						}


						else if (1 == _Area.ChooseWaterAttackAni()) // 블럭 없음
						{
							GameEngineSound::SoundPlayOneShot("Boss_Hit.mp3");
							TileIndex _TileIndex = _Area.GetMapTile()->GetTileIndex(_Center);
							ItemBlockTile* _checkItem = _Area.GetMapTile()->GetTile<ItemBlockTile>(_TileIndex.X, _TileIndex.Y);
							if (_checkItem != nullptr)
							{
								_Area.GetMapTile()->DeleteTile(_TileIndex.X, _TileIndex.Y);

							}
							BossBubblePop(_Center);
						}

						else if (3 == _Area.ChooseWaterAttackAni()) // 블럭 있음
						{
							GameEngineSound::SoundPlayOneShot("Boss_Hit.mp3");
							TileIndex _TileIndex = _Area.GetMapTile()->GetTileIndex(_Center);
							ItemBlockTile* _checkItem = _Area.GetMapTile()->GetTile<ItemBlockTile>(_TileIndex.X, _TileIndex.Y);
							_Area.GetMapTile()->DeleteTile(_TileIndex.X, _TileIndex.Y);
							BossBubblePop(_Center);
						}
					}
				}
				SetPosition(float4::ZERO);
				Bubble_->ChangeAnimation("None");
			}
		}
		else
		{
			SetPosition(float4::ZERO);
			Bubble_->ChangeAnimation("None");
		}
	}
	else
	{
		SetPosition(float4::ZERO);
		Bubble_->ChangeAnimation("None");
	}
	BossWaveDeath();
	
	for (size_t i = 0; i < DeleteTileList_.size(); i++)
	{
		if (DeleteTileList_[i]->Renderer->IsEndAnimation() == true)
		{
			BlockTile* Tiles_ = CanAttackAreas_.begin()->second.GetMapTile()->GetTile<BlockTile>(DeleteTileList_[i]->TileIndex_.X, DeleteTileList_[i]->TileIndex_.Y);//현재 검사중인 타일 정보
			ItemType ItemValue = Tiles_->ItemType_;
			float4 CreatePos = DeleteTileList_[i]->TilePos_;
			CanAttackAreas_.begin()->second.GetMapTile()->DeleteTile(DeleteTileList_[i]->TileIndex_.X, DeleteTileList_[i]->TileIndex_.Y);
			DeleteTileList_.erase(DeleteTileList_.begin() + i);
			if (ItemValue != ItemType::Max)
			{
				GameItemObject* Item = GetLevel()->CreateActor<GameItemObject>(static_cast<int>(ORDER::MAPOBJECT));
				Item->SetMapTile(CanAttackAreas_.begin()->second.GetMapTile());
 				Item->CreateItem(CreatePos , ItemValue);

			}

		}
	}

}


void BossBoom::BubbleBubblePop(std::map<int, Area>& _CanAttackAreas)
{
	CanAttackAreas_ = _CanAttackAreas;
	Bubble_->ChangeAnimation("BubbleBubble");

	if (CanAttackAreas_.find(8) != CanAttackAreas_.end())
	{
		float4 _Position = float4(CanAttackAreas_[8].GetCenter().x, CanAttackAreas_[8].GetCenter().y - 100);
		SetPosition(_Position);
	}
}
