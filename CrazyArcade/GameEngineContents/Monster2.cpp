#include "Monster2.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineContents/MapGameObject.h>

Monster2::Monster2()
	: Monster()
	, MiniRenderer_(nullptr)
	, MiniRendererOn_(false)
	, GetBackTime_(0.0f)
{
}

Monster2::~Monster2()
{
}

void Monster2::Start()
{
	Monster::Start();

	//악어
	// 미니 악어
	MiniRenderer_ = CreateRenderer("Monster.bmp");
	GameEngineImage* MiniImage = MiniRenderer_->GetImage();
	MiniImage->CutCount(10, 8);
	MiniRenderer_->CreateAnimation("Monster.bmp", "MoveRight", 25, 26, 0.2f, true);
	MiniRenderer_->CreateAnimation("Monster.bmp", "MoveLeft", 29, 30, 0.2f, true);
	MiniRenderer_->CreateAnimation("Monster.bmp", "MoveUp", 23, 24, 0.2f, true);
	MiniRenderer_->CreateAnimation("Monster.bmp", "MoveDown", 27, 28, 0.2f, true);
	MiniRenderer_->CreateAnimation("Monster.bmp", "Die", 31, 33, 0.2f, true);
	MiniRenderer_->ChangeAnimation("MoveLeft");

	Renderer_ = CreateRenderer("Monster.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 8);
	Renderer_->CreateAnimation("Monster.bmp", "MoveRight", 19, 20, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveLeft", 21, 22, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveUp", 15, 16, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveDown", 17, 18, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Start", 33, 36, 0.1f, false);
	Renderer_->ChangeAnimation("Start");
	Dir_ = float4::ZERO;
	CenterCol_->SetScale(float4(40.0f, 40.0f));
	CenterCol_->SetPivot(float4(0.0f, -40.0f));
	SetHP(2);
	SetSpeed(100);
	MiniRenderer_->SetAlpha(0);
	MiniRenderer_->Off();
	MiniRendererOn_ = false;
}


void Monster2::Update()
{
	GetBackTime_ += GameEngineTime::GetDeltaTime();
	GetAttTime_ += GameEngineTime::GetDeltaTime();
	UpdateDirection();
	UpdateMove();
	UpdateGetBack();
	Die();
}

void Monster2::TakeDamage()
{
	if (GetAttTime_ > 2.0) // 1초 안에 다시 맞으면 DMG를 입지 않는다. (Need to chk : TIME)
	{
		SetHP(GetHp() - 1);
		if (GetHP() >= 1)
		{
			MiniRendererOn_ = true;
			MiniRenderer_->On();
			Renderer_->Off();
			SetSpeed(70); // Need to chk : Speed_
			GetBackTime_ = 0.0f;
			GetAttTime_ = 0.0f;
		}
	}

}

void Monster2::UpdateMove()
{
	if (true == Renderer_->IsAnimationName("Start"))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			Renderer_->ChangeAnimation("MoveRight");
			Direction_ = "Right";
			Dir_ = float4::RIGHT;
		}
	}
	else
	{
		if (MiniRendererOn_ == true)
		{
			MiniRenderer_->ChangeAnimation("Move" + Direction_);
		}
		else
		{
			Renderer_->ChangeAnimation("Move" + Direction_);
		}

		SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
}

void Monster2::UpdateGetBack()
{
	if (GetBackTime_ > 5.0f)
	{
		MiniRendererOn_ = false;
		MiniRenderer_->Off();
		Renderer_->On();
		SetSpeed(100);
		SetHP(2);
		//Renderer_->ChangeAnimation("");
	}
}


void Monster2::Die()
{
	if (true == IsDie() && true != MiniRenderer_->IsAnimationName("Die")) // HP가 0이거나 0보다 작으면
	{
		Dir_ = float4::ZERO;
		MiniRenderer_->ChangeAnimation("Die");
	}

	if (true == MiniRenderer_->IsAnimationName("Die") && true == MiniRenderer_->IsEndAnimation())
	{
		CenterCol_->Off();
		Renderer_->Death();
		MiniRenderer_->Death();
		TTL_MONSTER_COUNT--; // total 몬스터 수가 줄어든다.
		if (TTL_MONSTER_COUNT == 1) // 만약 몬스터가 한마리 남으면
		{
			SetSpeed(Speed_ + 20); // 속도가 빨라져라
		}
	}
}

void Monster2::UpdateDirection()
{
	Monster::UpdateDirection();
}

bool Monster2::IsDie()
{
	if (GetHP() <= 0)
	{
		return true;
	}
	else return false;
}


void Monster2::Render()
{
	Monster::Render();
}