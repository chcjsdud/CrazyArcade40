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
	Monster::Start();

	//�Ǿ�
	Renderer_ = CreateRenderer("Monster.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 7);
	Renderer_->CreateAnimation("Monster.bmp", "MoveRight", 16, 17, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveLeft", 22, 23, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveUp", 12, 13, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveDown", 14, 15, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Die", 18, 20, 0.2f, true);
	Renderer_->ChangeAnimation("MoveLeft");
	
	// �̴� �Ǿ�
	MiniRenderer_ = CreateRenderer("Monster.bmp");
	GameEngineImage* MiniImage = MiniRenderer_->GetImage();
	MiniImage->CutCount(10, 7);
	MiniRenderer_->CreateAnimation("Monster.bmp", "MoveRight", 16, 17, 0.2f, true);
	MiniRenderer_->CreateAnimation("Monster.bmp", "MoveLeft", 22, 23, 0.2f, true);
	MiniRenderer_->CreateAnimation("Monster.bmp", "MoveUp", 12, 13, 0.2f, true);
	MiniRenderer_->CreateAnimation("Monster.bmp", "MoveDown", 14, 15, 0.2f, true);
	MiniRenderer_->CreateAnimation("Monster.bmp", "Die", 18, 20, 0.2f, true);
	MiniRenderer_->ChangeAnimation("MoveLeft");
	MiniRenderer_->Off();

	Collision_->SetScale(float4(50.0f, 80.0f));
	Collision_->SetPivot(float4(0.0f, -40.0f));
	SetHP(2);
	SetSpeed(100);
	Dir_ = float4::LEFT;
}

void Monster2::Render()
{
}

void Monster2::Update()
{
	UpdateMove();
	TakeDamage();
	Die();
}

void Monster2::ChangeAppearance()
{
	// �Ǿ� HP�� 1�� ������ ���� �Ǿ�� �ٲ���
	Renderer_->ChangeAnimation("");
	SetSpeed(70);
}

void Monster2::TakeDamage()
{
	Monster::TakeDamage();
	if (GetHP() == 1)
	{
		ChangeAppearance();
	}
}

void Monster2::UpdateMove()
{

		if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x - 20), int(GetPosition().y - 20)) &&// ������ ������ �ƴϰ�
			true != Renderer_->IsAnimationName("MoveRight") && // ���� �������̳�
			true != Renderer_->IsAnimationName("MoveDown")) // �Ʒ��� ���� �ִ� ��Ȳ�� �ƴ϶�� ���������� ����
		{
			Dir_ = float4::LEFT;
			Renderer_->ChangeAnimation("MoveLeft");
		}

		if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y - 20)) &&// �������� ������ �ƴϰ�
			true != Renderer_->IsAnimationName("MoveLeft") && // ���� �����̳�
			true != Renderer_->IsAnimationName("MoveUp")) // ���� ���� �ִ� ��Ȳ�� �ƴ϶�� ���������� ����
		{
			Dir_ = float4::RIGHT;
			Renderer_->ChangeAnimation("MoveRight");
		}

		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y)) && // �������� ����
			RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x - 20), int(GetPosition().y))) // ������ ������ �ƴ� ��
		{
			if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x), int(GetPosition().y + 20))) // �Ʒ����� �����̸� �������� ����
			{
				Dir_ = float4::LEFT;
				Renderer_->ChangeAnimation("MoveLeft");
			}

			else // �� �ƴϸ� ��������
			{
				Dir_ = float4::DOWN;
				Renderer_->ChangeAnimation("MoveDown");
			}
		}

		if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y)) && // �������� ������ �ƴϰ�,
			RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x - 20), int(GetPosition().y))) // ������ ������ ��,
		{
			if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x), int(GetPosition().y - 20))) // ������ �����̶�� ���������� ����
			{
				Dir_ = float4::RIGHT;
				Renderer_->ChangeAnimation("MoveRight");
			}

			else // �� �ƴϸ� �ö󰡶�
			{
				Dir_ = float4::UP;
				Renderer_->ChangeAnimation("MoveUp");
			}

		}

	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
}
