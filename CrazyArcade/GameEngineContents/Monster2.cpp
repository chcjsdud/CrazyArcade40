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

	//악어
	Renderer_ = CreateRenderer("Monster.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 7);
	Renderer_->CreateAnimation("Monster.bmp", "MoveRight", 16, 17, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveLeft", 22, 23, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveUp", 12, 13, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "MoveDown", 14, 15, 0.2f, true);
	Renderer_->CreateAnimation("Monster.bmp", "Die", 18, 20, 0.2f, true);
	Renderer_->ChangeAnimation("MoveLeft");
	
	// 미니 악어
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
	// 악어 HP가 1이 됐으면 작은 악어로 바껴라
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

		if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x - 20), int(GetPosition().y - 20)) &&// 왼쪽이 검정이 아니고
			true != Renderer_->IsAnimationName("MoveRight") && // 현재 오른쪽이나
			true != Renderer_->IsAnimationName("MoveDown")) // 아래로 가고 있는 상황이 아니라면 오른쪽으로 가라
		{
			Dir_ = float4::LEFT;
			Renderer_->ChangeAnimation("MoveLeft");
		}

		if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y - 20)) &&// 오른쪽이 검정이 아니고
			true != Renderer_->IsAnimationName("MoveLeft") && // 현재 왼쪽이나
			true != Renderer_->IsAnimationName("MoveUp")) // 위로 가고 있는 상황이 아니라면 오른쪽으로 가라
		{
			Dir_ = float4::RIGHT;
			Renderer_->ChangeAnimation("MoveRight");
		}

		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y)) && // 오른쪽이 검정
			RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x - 20), int(GetPosition().y))) // 왼쪽이 검정이 아닐 때
		{
			if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x), int(GetPosition().y + 20))) // 아래쪽이 검정이면 왼쪽으로 가라
			{
				Dir_ = float4::LEFT;
				Renderer_->ChangeAnimation("MoveLeft");
			}

			else // 다 아니면 내려가라
			{
				Dir_ = float4::DOWN;
				Renderer_->ChangeAnimation("MoveDown");
			}
		}

		if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y)) && // 오른쪽이 검정이 아니고,
			RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x - 20), int(GetPosition().y))) // 왼쪽이 검정일 때,
		{
			if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x), int(GetPosition().y - 20))) // 위쪽이 검정이라면 오른쪽으로 가라
			{
				Dir_ = float4::RIGHT;
				Renderer_->ChangeAnimation("MoveRight");
			}

			else // 다 아니면 올라가라
			{
				Dir_ = float4::UP;
				Renderer_->ChangeAnimation("MoveUp");
			}

		}

	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
}
