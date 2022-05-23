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
	Renderer_->CreateAnimation("Monster.bmp", "MiniMoveRight", 16, 17, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MiniMoveLeft", 22, 23, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MiniMoveUp", 12, 13, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MiniMoveDown", 14, 15, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MiniDie", 18, 20, 0.2f, true);

	Index_ = 100;
	CenterCol_->SetScale(float4(50.0f, 80.0f));
	CenterCol_->SetPivot(float4(0.0f, -40.0f));
	SetHP(2);
	SetSpeed(100);
	Dir_ = float4::LEFT;
	Direction_ = "Right";
	Dir_ = float4::RIGHT;
}

void Monster2::Render()
{
}

void Monster2::Update()
{
	UpdateDirection();
	UpdateMove();
	TakeDamage();
	Die();
}

void Monster2::TakeDamage()
{
	if (GetAttTime_ > 2.0) // 2초 안에 다시 맞으면 DMG를 입지 않는다. (Need to chk : TIME)
	{
		std::vector<GameEngineCollision*> BubbleCol;
		if (CenterCol_->CollisionResult("WaveCol", BubbleCol, CollisionType::Rect, CollisionType::Rect))
		{
			for (GameEngineCollision* Collision : BubbleCol)
			{
				GameEngineActor* ColActor = Collision->GetActor();
				MapGameObject* Bubble = dynamic_cast<MapGameObject*>(ColActor);

				if (Bubble != nullptr)
				{
					SetHP(GetHp() - 1);
					if (GetHP() == 1)
					{
						Renderer_->ChangeAnimation("MiniMove" + Direction_);
						SetSpeed(70); // Need to chk : Speed_
					}
					GetAttTime_ = 0.0f;
					
				}
			}
		}
	}
}
