#include "StartIntroUI.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineSound.h>

StartIntroUI::StartIntroUI()
{
}

StartIntroUI::~StartIntroUI()
{
}

void StartIntroUI::Start()
{
	StartScreenRenderer_ = CreateRenderer("StartScreen.bmp");
	StartScreenRenderer_->SetAlpha(60);
	StartScreenRenderer_->SetPivot(GameEngineWindow::GetScale().Half());


	for (size_t i = 0; i < 11; i++)
	{
		GameEngineRenderer* TempRenderer = CreateRenderer("GameStartIntro.bmp");
		StartIntroUIRenderer_.push_back(TempRenderer);
	}

	//Game
	StartIntroUIRenderer_[0]->SetIndex(0);
	StartIntroUIRenderer_[0]->SetPivot(float4(230.0f, -50.0f));

	StartIntroUIRenderer_[1]->SetIndex(1);
	StartIntroUIRenderer_[1]->SetPivot(float4(310.0f, -50.0f));

	StartIntroUIRenderer_[2]->SetIndex(2);
	StartIntroUIRenderer_[2]->SetPivot(float4(390.0f, -50.0f));

	StartIntroUIRenderer_[3]->SetIndex(3);
	StartIntroUIRenderer_[3]->SetPivot(float4(470.0f, -50.0f));

	//------------------------------------------------------------------//

	//Start
	StartIntroUIRenderer_[4]->SetIndex(4);
	StartIntroUIRenderer_[4]->SetPivot(float4(100.0f, 350.0f));
	StartIntroUIRenderer_[4]->Off();

	StartIntroUIRenderer_[5]->SetIndex(5);
	StartIntroUIRenderer_[5]->SetPivot(float4(200.0f, 350.0f));
	StartIntroUIRenderer_[5]->Off();

	StartIntroUIRenderer_[6]->SetIndex(6);
	StartIntroUIRenderer_[6]->SetPivot(float4(300.0f, 350.0f));
	StartIntroUIRenderer_[6]->Off();

	StartIntroUIRenderer_[7]->SetIndex(7);
	StartIntroUIRenderer_[7]->SetPivot(float4(400.0f, 350.0f));
	StartIntroUIRenderer_[7]->Off();

	StartIntroUIRenderer_[8]->SetIndex(8);
	StartIntroUIRenderer_[8]->SetPivot(float4(500.0f, 350.0f));
	StartIntroUIRenderer_[8]->Off();

	StartIntroUIRenderer_[9]->SetIndex(9);
	StartIntroUIRenderer_[9]->SetPivot(float4(600.0f, 350.0f));
	StartIntroUIRenderer_[9]->Off();

	StartIntroUIRenderer_[10]->SetIndex(10);
	StartIntroUIRenderer_[10]->SetPivot(float4(650.0f, 350.0f));
	StartIntroUIRenderer_[10]->Off();


	

	Death(5.0f);
}

void StartIntroUI::Update()
{
	IntroMoveTime_ += GameEngineTime::GetDeltaTime();

	if (onetime_ == false) {
		GameEngineSound::SoundPlayOneShot("GameStart.wav");
		onetime_ = true;
	}

	if (GetAccTime() > 0.0f && GetAccTime() < 2.5f)
	{
			
			if (StartIntroUIRenderer_[0]->GetPivot().y < 250.f) 
			{
				StartIntroUIRenderer_[0]->SetPivot(StartIntroUIRenderer_[0]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });
				if (StartIntroUIRenderer_[0]->GetPivot().y > 250.f) 
				{
					StartIntroUIRenderer_[0]->SetPivot(float4(StartIntroUIRenderer_[0]->GetPivot().x, 250.0f));
				}

			}
			else if (StartIntroUIRenderer_[1]->GetPivot().y < 250.f) 
			{
				StartIntroUIRenderer_[1]->SetPivot(StartIntroUIRenderer_[1]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });
				if (StartIntroUIRenderer_[1]->GetPivot().y > 250.f) 
				{
					StartIntroUIRenderer_[1]->SetPivot(float4(StartIntroUIRenderer_[1]->GetPivot().x, 250.0f));
				}

			}
			else if (StartIntroUIRenderer_[2]->GetPivot().y < 250.f) 
			{
				StartIntroUIRenderer_[2]->SetPivot(StartIntroUIRenderer_[2]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });
				if (StartIntroUIRenderer_[2]->GetPivot().y > 250.f) 
				{
					StartIntroUIRenderer_[2]->SetPivot(float4(StartIntroUIRenderer_[2]->GetPivot().x, 250.0f));
				}
			}
			else if (StartIntroUIRenderer_[3]->GetPivot().y < 250.f) 
			{
				StartIntroUIRenderer_[3]->SetPivot(StartIntroUIRenderer_[3]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });
				if (StartIntroUIRenderer_[3]->GetPivot().y > 250.f)
				{
					StartIntroUIRenderer_[3]->SetPivot(float4(StartIntroUIRenderer_[3]->GetPivot().x, 250.0f));
				}
			}
			else
			{
				StartIntroUIRenderer_[0]->SetPivot(float4(StartIntroUIRenderer_[0]->GetPivot().x, 250.0f));
				StartIntroUIRenderer_[1]->SetPivot(float4(StartIntroUIRenderer_[1]->GetPivot().x, 250.0f));
				StartIntroUIRenderer_[2]->SetPivot(float4(StartIntroUIRenderer_[2]->GetPivot().x, 250.0f));
				StartIntroUIRenderer_[3]->SetPivot(float4(StartIntroUIRenderer_[3]->GetPivot().x, 250.0f));

				for (int i = 4; i < 11; i++)
				{
					StartIntroUIRenderer_[i]->On();
				}
			}
		

	}
	
	
	if (GetAccTime() > 2.5f )
	{
		StartScreenRenderer_->Off();

		for (int i = 0; i < 11; i++)
		{
			if (i < 4) {
				StartIntroUIRenderer_[i]->SetPivot(StartIntroUIRenderer_[i]->GetPivot() + float4{ 0.0f, -0.4f * IntroMoveTime_ });
			}
			else if (i >= 4)
			{
				StartIntroUIRenderer_[i]->SetPivot(StartIntroUIRenderer_[i]->GetPivot() + float4{ 0.0f, 0.4f * IntroMoveTime_ });
			}
		}
	}
}

void StartIntroUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void StartIntroUI::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	this->Death();
}
