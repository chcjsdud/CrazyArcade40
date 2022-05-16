#include "Monster2.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

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
	Renderer_->ChangeAnimation("MoveRight");
}

void Monster2::Render()
{
}

void Monster2::Update()
{
	UpdateMove();
	Die();
}
