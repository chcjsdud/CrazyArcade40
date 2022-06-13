#include "Monster2.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineContents/MapGameObject.h>
#include <GameEngineBase/GameEngineInput.h>

Monster2::Monster2()
	: Monster()
	, MiniRenderer_(nullptr)
	, MiniRendererOn_(false)
	, GetBackTime_(0.0f)
{
}

Monster2::~Monster2()
{
}

void Monster2::Start()
{
	Monster::Start();
	// 미니 악어
	MiniRenderer_ = CreateRenderer("BasicMonster.bmp");
	GameEngineImage* MiniImage = MiniRenderer_->GetImage();
	MiniImage->CutCount(10, 6);
	MiniRenderer_->CreateAnimation("BasicMonster.bmp", "MoveRight", 44, 45, 0.2f, true);
	MiniRenderer_->CreateAnimation("BasicMonster.bmp", "MoveLeft", 48, 49, 0.2f, true);
	MiniRenderer_->CreateAnimation("BasicMonster.bmp", "MoveUp", 42, 43, 0.2f, true);
	MiniRenderer_->CreateAnimation("BasicMonster.bmp", "MoveDown", 46, 47, 0.2f, true);
	MiniRenderer_->CreateAnimation("BasicMonster.bmp", "Die", 50, 52, 0.2f, true);
	MiniRenderer_->ChangeAnimation("MoveLeft");

	//악어
	Renderer_ = CreateRenderer("BasicMonster.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 6);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveRight", 38, 39, 0.2f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveLeft", 40, 41, 0.2f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveUp", 34, 35, 0.2f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveDown", 36, 37, 0.2f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "Start", 53, 55, 0.1f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "Die", 50, 52, 0.2f, true);
	Renderer_->ChangeAnimation("Start");
	Dir_ = float4::ZERO;
	CenterCol_->SetScale(float4(30.0f, 30.0f));
	CenterCol_->SetPivot(float4(0.0f, -30.0f));
	SetHP(2);
	SetSpeed(100);
	MiniRenderer_->SetAlpha(0);
	MiniRenderer_->Off();
	MiniRendererOn_ = false;
	IsStageClear_ = false;

	SpeechBubble_ = CreateRenderer("SpeechBubble2.bmp");
	GameEngineImage* SpeechBubbleImage = SpeechBubble_->GetImage();
	SpeechBubbleImage->CutCount(10, 2);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble0", 0, 0, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble1", 1, 1, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble2", 2, 2, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble3", 3, 3, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble4", 4, 4, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble5", 5, 5, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble6", 6, 6, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble7", 7, 7, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble8", 8, 8, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble9", 9, 9, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble10", 10, 10, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble11", 11, 11, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble12", 12, 12, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble13", 13, 13, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble14", 14, 14, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble2.bmp", "Bubble15", 15, 15, 0.5f, true);
	SpeechBubble_->ChangeAnimation("Bubble15");
	SpeechBubble_->SetOrder((int)ORDER::UI);
	SpeechBubble_->SetPivot(float4(0.0f, -70.0f));
}


void Monster2::Update()
{
	GetBackTime_ += GameEngineTime::GetDeltaTime();
	GetAttTime_ += GameEngineTime::GetDeltaTime();
	SpeechTime_ += GameEngineTime::GetInst()->GetDeltaTime();

	UpdateDirection();
	UpdateMove();
	UpdateGetBack();
	AllMonsterDeathModeSwitch();
	Die();
	Speech();
}


void Monster2::AllMonsterDeathModeSwitch()
{
	if (true == GameEngineInput::GetInst()->IsDown("AllMonsterDeath"))
	{
		if (GetLevel()->GetNameCopy() == "Monster1Level" && GetHP() > 0 && IsStageClear_ == false)
		{
			MiniRendererOn_ = true;
			MiniRenderer_->On();
			MiniRenderer_->SetAlpha(255);
			Renderer_->Off();
			SetHP(0);
			LV1_MON_COUNT = 0;
		}

		if (GetLevel()->GetNameCopy() == "Monster2Level" && GetHP() > 0 && IsStageClear_ == false)
		{
			MiniRendererOn_ = true;
			MiniRenderer_->On();
			MiniRenderer_->SetAlpha(255);
			Renderer_->Off();
			SetHP(0);
			LV2_MON_COUNT = 0;
		}

		IsStageClear_ = true;

	}
}

void Monster2::TakeDamage()
{
	if (GetAttTime_ > 2.0) // 1초 안에 다시 맞으면 DMG를 입지 않는다. (Need to chk : TIME)
	{
		SetHP(GetHp() - 1);
		if (GetHP() >= 1)
		{
			MiniRendererOn_ = true;
			MiniRenderer_->On();
			MiniRenderer_->SetAlpha(255);
			Renderer_->Off();
			SetSpeed(50); // Need to chk : Speed_
			GetBackTime_ = 0.0f;
			GetAttTime_ = 0.0f;
		}
	}

}

void Monster2::UpdateMove()
{
	if (true == Renderer_->IsAnimationName("Start"))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			Renderer_->ChangeAnimation("MoveRight");
			Direction_ = "Right";
			Dir_ = float4::RIGHT;
		}
	}
	else if(false == Renderer_->IsAnimationName("Die"))
	{
		if (MiniRendererOn_ == true)
		{
			MiniRenderer_->ChangeAnimation("Move" + Direction_);
		}
		else
		{
			Renderer_->ChangeAnimation("Move" + Direction_);
		}

		SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
}

void Monster2::UpdateGetBack()
{
	if (GetHP() >= 1 &&
		GetBackTime_ > 7.0f)
	{
		MiniRendererOn_ = false;
		MiniRenderer_->Off();
		Renderer_->On();
		SetSpeed(100);
		SetHP(2);
	}
}


void Monster2::Die()
{
	if (true == IsDie()) // HP가 0이거나 0보다 작으면
	{
		if (true == MiniRenderer_->IsAnimationName("Die"))
		{
			if (true == MiniRenderer_->IsEndAnimation())
			{
				CenterCol_->Off();
				Death();

				if (GetLevel()->GetNameCopy() == "Monster1Level")
				{
					if(LV1_MON_COUNT != 0)
					{
						LV1_MON_COUNT--; // total 몬스터 수가 줄어든다.
					}
				}

				else if (GetLevel()->GetNameCopy() == "Monster2Level") // 만약 몬스터가 한마리 남으면
				{
					if (LV2_MON_COUNT != 0)
					{
						LV2_MON_COUNT--; // total 몬스터 수가 줄어든다.
					}
				}

				if (LV1_MON_COUNT == 1 || LV2_MON_COUNT == 1)
				{
					SetSpeed(Speed_ + 20); // 속도가 빨라져라
				}
			}
		}

		if (true != MiniRenderer_->IsAnimationName("Die"))
		{
			Dir_ = float4::ZERO;
			MiniRenderer_->ChangeAnimation("Die");
			Renderer_->ChangeAnimation("Die");
		}
	}
}

void Monster2::UpdateDirection()
{
	Monster::UpdateDirection();
}

bool Monster2::IsDie()
{
	if (GetHP() <= 0)
	{
		return true;
	}
	else return false;
}


void Monster2::Render()
{
	if (true == GetLevel()->GetIsDebug())
	{
		Monster::Render();
	}
}

void Monster2::Speech()
{
	if (SpeechTime_ > 2.0f)
	{
		int RandomSpeech = (rand() % 16);
		std::string SpeechNum = std::to_string(RandomSpeech);
		SpeechBubble_->ChangeAnimation("Bubble" + SpeechNum);
		SpeechTime_ = 0.0f;
	}
}
