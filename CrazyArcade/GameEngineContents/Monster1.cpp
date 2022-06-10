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
	Renderer_ = CreateRenderer("BasicMonster.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 6);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveRight", 25, 26, 0.3f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveLeft", 23, 24, 0.3f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveUp", 19, 20, 0.3f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveDown", 21, 22, 0.3f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "Die", 27, 29, 0.2f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "Start", 30, 33, 0.1f, true);
	Renderer_->ChangeAnimation("Start");
	SetSpeed(70);
	Dir_ = float4::ZERO;
	SetHP(1);

	CenterCol_->SetPivot(float4(0.0f, -18.0f));
}

void Monster1::Render()
{
	Monster::Render();
}

void Monster1::Update()
{
	if (true == Renderer_->IsAnimationName("Start") &&
		true == Renderer_->IsEndAnimation())
	{
		Renderer_->ChangeAnimation("MoveRight");
		Direction_ = "Right";
		Dir_ = float4::RIGHT;
	}
	else
	{
		Monster::Update();
	}
}