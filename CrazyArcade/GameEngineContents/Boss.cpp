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
	//����
	Monster::Start();
	SetMonsterClass(MonsterClass::BOSS);
	SetHP(15);
	SetSpeed(50);
	Renderer_ = CreateRenderer("Boss.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 7);
	Renderer_->CreateAnimation("Monster.bmp", "MoveRight", 26, 27, 0.1f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveLeft", 40, 41, 0.1f, true);
	// Need to chk : MoveUp �̹���
	//Renderer_->CreateAnimation("Monster.bmp", "MoveUp", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveDown", 24, 25, 0.1f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Die1", 35, 36, 0.1f, true); // ���ֱ�
	Renderer_->CreateAnimation("Monster.bmp", "Die2", 37, 38, 0.1f, true); // �ɹ������
	Renderer_->CreateAnimation("Monster.bmp", "TakeDamage", 28, 28, 0.1f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Attack1", 29, 30, 0.1f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Attack2", 31, 34, 0.1f, true);
	Renderer_->ChangeAnimation("MoveRight");
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
	// ������ �� ���� �̵� ����
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
