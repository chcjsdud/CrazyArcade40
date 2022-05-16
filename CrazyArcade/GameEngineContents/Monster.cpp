#include "Monster.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineTime.h>

Monster::Monster()
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, ColMapImage_(nullptr)
	, MonsterClass_(MonsterClass::DEFAULT)
	, MonsterState_(MonsterState::WALK)
	, HP_(1)
	, Speed_(1)
{
}

Monster::~Monster()
{
}


void Monster::Start()
{
	//GameEngineLevel* Level = GetLevel();
	//ColMapImage_ = Level->GetColMapImage();
	Collision_ = CreateCollision("Monster", float4(50.0f, 50.0f), float4(0.0f, 0.0f));

}

void Monster::Update()
{
	UpdateMove();
}

void Monster::UpdateMove()
{
	// Move
	// Need to chk : 블럭 충돌 시 이동방향
	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(20.0f, 0.0f)))
	{
		Dir_ = float4::LEFT;
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(-20.0f, 0.0f)))
	{
		Dir_ = float4::RIGHT;
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(0.0f, -20.0f)))
	{
		Dir_ = float4::DOWN;
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(0.0f, 20.0f)))
	{
		Dir_ = float4::UP;
	}

	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
	
	// 1. 블럭충돌 
	// 2. 물풍선충돌
}
void Monster::Render()
{
}


void Monster::Die()
{
	if (true == IsDie())
	{
		if (true == Renderer_->IsAnimationName("Die"))
		{
			if (true == Renderer_->IsEndAnimation())
			{
				Collision_->Off();
				Death();
			}
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
