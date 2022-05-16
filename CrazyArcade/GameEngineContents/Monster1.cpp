#include "Monster1.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

Monster1::Monster1()
	:Monster()
{
}

Monster1::~Monster1()
{
}

void Monster1::Start()
{
	Monster::Start();
	SetSpeed(10);
	Renderer_ = CreateRenderer("Monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	//Image->CutCount(, );
	Renderer_->CreateAnimation("Monster1.bmp", "WalkRight", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkLeft", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Attack", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Die", 0, 1, 0.1f, true);
	Renderer_->ChangeAnimation("WalkRight");
}

void Monster1::Render()
{
}

void Monster1::Update()
{
	UpdateMove();
	Die();
}
