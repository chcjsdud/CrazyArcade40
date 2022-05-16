#include "Boss.h"
#include "Monster.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

Boss::Boss()
	:Monster()
{
}

Boss::~Boss()
{
}

void Boss::Start()
{
	Monster::Start();
	SetMonsterClass(MonsterClass::BOSS);
	SetHP(15);
	SetSpeed(50);
	Renderer_ = CreateRenderer("Boss.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	//Image->CutCount(, );
	Renderer_->CreateAnimation("Boss.bmp", "WalkRight", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("Boss.bmp", "WalkLeft", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("Boss.bmp", "Attack", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("Boss.bmp", "Die", 0, 1, 0.1f, true);
	Renderer_->ChangeAnimation("WalkRight");
}

void Boss::Render()
{
}

void Boss::Update()
{
	UpdateMove();
	Die();
}

void Boss::UpdateMove()
{
	// 보스는 블럭 위로 이동 가능
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
}
