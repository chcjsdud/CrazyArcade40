#include "Monster2.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>


Monster2::Monster2()
	:Monster()
{
}

Monster2::~Monster2()
{
}

void Monster2::Start()
{
	//¾Ç¾î
	Monster::Start();
	SetSpeed(10);
	Renderer_ = CreateRenderer("Monster.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 7);
	Renderer_->CreateAnimation("Monster.bmp", "MoveRight", 16, 17, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveLeft", 22, 23, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveUp", 12, 13, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveDown", 14, 15, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Die", 18, 20, 0.2f, true);
	Renderer_->ChangeAnimation("MoveLeft");
	Collision_->SetScale(float4(50.0f, 80.0f));
	Collision_->SetPivot(float4(0.0f, -40.0f));

	SetSpeed(100);
	Dir_ = float4::LEFT;
}

void Monster2::Render()
{
}

void Monster2::Update()
{
	UpdateMove();
	Die();
}
