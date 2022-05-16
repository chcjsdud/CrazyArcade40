#include "Monster2.h"
#include <GameEngine/GameEngineRenderer.h>

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
	SetSpeed(10);
	Renderer_ = CreateRenderer("Monster2.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	//Image->CutCount(, );
	Renderer_->CreateAnimation("Monster2.bmp", "WalkRight", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("Monster2.bmp", "WalkLeft", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("Monster2.bmp", "Attack", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("Monster2.bmp", "Die", 0, 1, 0.1f, true);
	Renderer_->ChangeAnimation("WalkRight");
}

void Monster2::Render()
{
}

void Monster2::Update()
{
	UpdateMove();
	Die();
}
