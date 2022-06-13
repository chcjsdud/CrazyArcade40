#include "BossBoom.h"
#include "Area.h"

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
			SetMove(float4::DOWN);
			if (CanAttackAreas_[8].GetCenter().y < GetPosition().y)
			{
				if (CanAttackAreas_.size() != 0)
				{
					for (auto it = CanAttackAreas_.begin(); it != CanAttackAreas_.end(); it++)
					{
						Area& _Area = it->second;
						float4 _Center = _Area.GetCenter() - float4(20.0f, 40.0f);
						// 블락을 체크해서 블락이 있으면 
						//if (0 == _Area.ChooseWaterAttackAni()) // 블럭 있음
						//{
 					//		TileIndex _TileIndex = _Area.GetMapTile()->GetTileIndex(_Center);
						//	_Area.GetMapTile()->DeleteTile(_TileIndex.X, _TileIndex.Y);
						//}

						//else if (1 == _Area.ChooseWaterAttackAni()) // 블럭 없음
						//{
							BossBubblePop(_Center, 0);
						//}
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
