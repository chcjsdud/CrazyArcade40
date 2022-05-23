#include "Monster2.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineContents/MapGameObject.h>

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
	Renderer_->ChangeAnimation("MoveLeft");
	
	// �̴� �Ǿ�
	Renderer_->CreateAnimation("Monster.bmp", "MiniMoveRight", 16, 17, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MiniMoveLeft", 22, 23, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MiniMoveUp", 12, 13, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MiniMoveDown", 14, 15, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MiniDie", 18, 20, 0.2f, true);

	Index_ = 100;
	CenterCol_->SetScale(float4(50.0f, 80.0f));
	CenterCol_->SetPivot(float4(0.0f, -40.0f));
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

void Monster2::TakeDamage()
{
	if (GetAttTime_ > 2.0) // 2�� �ȿ� �ٽ� ������ DMG�� ���� �ʴ´�. (Need to chk : TIME)
	{
		std::vector<GameEngineCollision*> BubbleCol;
		if (CenterCol_->CollisionResult("WaveCol", BubbleCol, CollisionType::Rect, CollisionType::Rect))
		{
			for (GameEngineCollision* Collision : BubbleCol)
			{
				GameEngineActor* ColActor = Collision->GetActor();
				MapGameObject* Bubble = dynamic_cast<MapGameObject*>(ColActor);

				if (Bubble != nullptr)
				{
					SetHP(GetHp() - 1);
					if (GetHP() == 1)
					{
						Renderer_->ChangeAnimation("MiniMove" + Direction_);
						SetSpeed(70); // Need to chk : Speed_
					}
					GetAttTime_ = 0.0f;
					
				}
			}
		}
	}

}

void Monster2::UpdateMove()
{
	if (true != Renderer_->IsAnimationName("MiniMove" + Direction_))
	{
		Monster::UpdateMove();
	}

	else // ���� �Ǿ��
	{
		if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x - 20), int(GetPosition().y - 20))) // ������ ������ �ƴϰ�
		{
			if (true != Renderer_->IsAnimationName("MiniMoveRight") && true != Renderer_->IsAnimationName("MiniMoveDown")) // ���� �������̳� �Ʒ��� ���� �ִ� ��Ȳ�� �ƴ϶�� ���������� ����
			{
				Dir_ = float4::LEFT;
				Direction_ = "Left";
				Renderer_->ChangeAnimation("MiniMove" + Direction_);
			}

			else if (true == Renderer_->IsAnimationName("MiniMoveRight") &&
				RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x), int(GetPosition().y - 20)) && // ���� ������ �ƴϰ�
				RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x - 40), int(GetPosition().y - 25))) // ���� �밢�� ���� �����̸�
			{
				Dir_ = float4::UP;
				Direction_ = "Up";
				Renderer_->ChangeAnimation("MiniMove" + Direction_);
			}

		}

		if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y - 20))) // �������� ������ �ƴϰ�
		{
			if (true != Renderer_->IsAnimationName("MiniMoveLeft") && true != Renderer_->IsAnimationName("MiniMoveUp")) // ���� �����̳� ���� ���� �ִ� ��Ȳ�� �ƴ϶�� ���������� ����
			{
				Dir_ = float4::RIGHT;
				Direction_ = "Right";
				Renderer_->ChangeAnimation("MiniMove" + Direction_);
			}

			else if (true == Renderer_->IsAnimationName("MiniMoveLeft") &&
				RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x), int(GetPosition().y + 20)) && // �Ʒ��� ������ �ƴϰ�
				RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x + 40), int(GetPosition().y + 25))) // ������ �밢�� �Ʒ��� �����̸�
			{
				Dir_ = float4::DOWN;
				Direction_ = "Down";
				Renderer_->ChangeAnimation("MiniMove" + Direction_);
			}
		}

		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y)) && // �������� ����
			RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x - 20), int(GetPosition().y))) // ������ ������ �ƴ� ��
		{
			if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x), int(GetPosition().y + 20))) // �Ʒ����� �����̸� �������� ����
			{
				Dir_ = float4::LEFT;
				Direction_ = "Left";
				Renderer_->ChangeAnimation("MiniMove" + Direction_);
			}

			else // �� �ƴϸ� ��������
			{
				Dir_ = float4::DOWN;
				Direction_ = "Down";
				Renderer_->ChangeAnimation("MiniMove" + Direction_);
			}
		}

		if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y)) && // �������� ������ �ƴϰ�,
			RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x - 20), int(GetPosition().y))) // ������ ������ ��,
		{
			if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x), int(GetPosition().y - 20))) // ������ �����̶�� ���������� ����
			{
				Dir_ = float4::RIGHT;
				Direction_ = "Right";
				Renderer_->ChangeAnimation("MiniMove" + Direction_);
			}

			else // �� �ƴϸ� �ö󰡶�
			{
				Dir_ = float4::UP;
				Direction_ = "Up";
				Renderer_->ChangeAnimation("MiniMove" + Direction_);
			}

		}

		SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);

	}
}
