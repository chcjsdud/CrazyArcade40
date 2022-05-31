#include "Monster1.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include "Area.h"
#include "GameEngine/GameEngineCollision.h"

Monster1::Monster1()
	:Monster()
{
}

Monster1::~Monster1()
{
}

void Monster1::Start()
{
	//°¨±ÖÀÌ
	Monster::Start();
	Renderer_ = CreateRenderer("Monster.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 7);
	Renderer_->CreateAnimation("Monster.bmp", "MoveRight", 6, 7, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveLeft", 4, 5, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveUp", 0, 1, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveDown", 2, 3, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Die", 8, 10, 0.2f, true);
	Renderer_->ChangeAnimation("MoveRight");
	SetSpeed(100);
	Direction_ = "Right";
	Dir_ = float4::RIGHT;
	SetHP(1);
}

void Monster1::Render()
{
	Monster::Render();
}

void Monster1::Update()
{
	Monster::Update();
}