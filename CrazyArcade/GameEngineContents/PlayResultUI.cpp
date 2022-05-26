#include "PlayResultUI.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"

PlayResultUI::PlayResultUI()
{
}

PlayResultUI::~PlayResultUI()
{
}

void PlayResultUI::Start()
{
	if (GameResult ==1)
	{
		for (size_t i = 0; i < 5; i++)
		{
			GameEngineRenderer* TempRenderer = CreateRenderer("WinText.bmp");
			PlayResultUIRenderer_.push_back(TempRenderer);
		}

		//Game
		PlayResultUIRenderer_[0]->SetIndex(0);
		PlayResultUIRenderer_[0]->SetPivot(float4(230.0f, -50.0f));

		PlayResultUIRenderer_[1]->SetIndex(1);
		PlayResultUIRenderer_[1]->SetPivot(float4(310.0f, -50.0f));

		PlayResultUIRenderer_[2]->SetIndex(2);
		PlayResultUIRenderer_[2]->SetPivot(float4(390.0f, -50.0f));

		PlayResultUIRenderer_[3]->SetIndex(3);
		PlayResultUIRenderer_[3]->SetPivot(float4(470.0f, -50.0f));

		PlayResultUIRenderer_[4]->SetIndex(4);
		PlayResultUIRenderer_[4]->SetPivot(float4(500.0f, -50.0f));

	}
	else if (GameResult == 2) {
		for (size_t i = 0; i < 6; i++)
		{
			GameEngineRenderer* TempRenderer = CreateRenderer("LoseText.bmp");
			PlayResultUIRenderer_.push_back(TempRenderer);
		}

		//Game
		PlayResultUIRenderer_[0]->SetIndex(0);
		PlayResultUIRenderer_[0]->SetPivot(float4(230.0f, -50.0f));

		PlayResultUIRenderer_[1]->SetIndex(1);
		PlayResultUIRenderer_[1]->SetPivot(float4(310.0f, -50.0f));

		PlayResultUIRenderer_[2]->SetIndex(2);
		PlayResultUIRenderer_[2]->SetPivot(float4(390.0f, -50.0f));

		PlayResultUIRenderer_[3]->SetIndex(3);
		PlayResultUIRenderer_[3]->SetPivot(float4(470.0f, -50.0f));

		PlayResultUIRenderer_[4]->SetIndex(4);
		PlayResultUIRenderer_[4]->SetPivot(float4(530.0f, -50.0f));

		PlayResultUIRenderer_[5]->SetIndex(5);
		PlayResultUIRenderer_[5]->SetPivot(float4(560.0f, -50.0f));
	}
	else if (GameResult == 3) {
		for (size_t i = 0; i < 6; i++)
		{
			GameEngineRenderer* TempRenderer = CreateRenderer("DrawText.bmp");
			PlayResultUIRenderer_.push_back(TempRenderer);
		}

		//Game
		PlayResultUIRenderer_[0]->SetIndex(0);
		PlayResultUIRenderer_[0]->SetPivot(float4(230.0f, -50.0f));

		PlayResultUIRenderer_[1]->SetIndex(1);
		PlayResultUIRenderer_[1]->SetPivot(float4(310.0f, -50.0f));

		PlayResultUIRenderer_[2]->SetIndex(2);
		PlayResultUIRenderer_[2]->SetPivot(float4(390.0f, -50.0f));

		PlayResultUIRenderer_[3]->SetIndex(3);
		PlayResultUIRenderer_[3]->SetPivot(float4(470.0f, -50.0f));

		PlayResultUIRenderer_[4]->SetIndex(4);
		PlayResultUIRenderer_[4]->SetPivot(float4(530.0f, -50.0f));

		PlayResultUIRenderer_[5]->SetIndex(5);
		PlayResultUIRenderer_[5]->SetPivot(float4(560.0f, -50.0f));
	}

	Death(5.0f);
}

void PlayResultUI::Update()
{
	IntroMoveTime_ += GameEngineTime::GetDeltaTime();

	if (GameResult == 1) //// Win
	{ 
		if (GetAccTime() > 0.0f && GetAccTime() < 1.4f)
		{
			if (GetAccTime() < 0.6) {
				if (PlayResultUIRenderer_[0]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[0]->SetPivot(PlayResultUIRenderer_[0]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[0]->SetPivot(float4(PlayResultUIRenderer_[0]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 0.8) {
				if (PlayResultUIRenderer_[1]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[1]->SetPivot(PlayResultUIRenderer_[1]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[1]->SetPivot(float4(PlayResultUIRenderer_[1]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 1.0) {
				if (PlayResultUIRenderer_[2]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[2]->SetPivot(PlayResultUIRenderer_[2]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[2]->SetPivot(float4(PlayResultUIRenderer_[2]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 1.2) {
				if (PlayResultUIRenderer_[3]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[3]->SetPivot(PlayResultUIRenderer_[3]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[3]->SetPivot(float4(PlayResultUIRenderer_[3]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 1.4) {
				if (PlayResultUIRenderer_[4]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[4]->SetPivot(PlayResultUIRenderer_[4]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[4]->SetPivot(float4(PlayResultUIRenderer_[4]->GetPivot().x, 250.0f));
				}
			}
			
		}
		else if (GetAccTime() > 1.8f && GetAccTime() < 2.8f)
		{
			BlinkTime_ += GameEngineTime::GetDeltaTime();

			if (BlinkTime_ < 0.1f) {
				for (int i = 0; i < 5; i++)
				{
					PlayResultUIRenderer_[i]->SetIndex(i + 5);
				}
			}
			else if (BlinkTime_ > 0.1f && BlinkTime_ < 0.2f) {
				for (int i = 0; i < 5; i++)
				{ 
					PlayResultUIRenderer_[i]->SetIndex(i);
				}
			}
			else {
				BlinkTime_ = 0.0f;
			}

		}
	}
	else if(GameResult == 2) ////Lose
	{ 

		if (GetAccTime() > 0.0f && GetAccTime() < 1.6f)
		{
			if (GetAccTime() < 0.6) {
				if (PlayResultUIRenderer_[0]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[0]->SetPivot(PlayResultUIRenderer_[0]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[0]->SetPivot(float4(PlayResultUIRenderer_[0]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 0.8) {
				if (PlayResultUIRenderer_[1]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[1]->SetPivot(PlayResultUIRenderer_[1]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[1]->SetPivot(float4(PlayResultUIRenderer_[1]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 1.0) {
				if (PlayResultUIRenderer_[2]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[2]->SetPivot(PlayResultUIRenderer_[2]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[2]->SetPivot(float4(PlayResultUIRenderer_[2]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 1.2) {
				if (PlayResultUIRenderer_[3]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[3]->SetPivot(PlayResultUIRenderer_[3]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[3]->SetPivot(float4(PlayResultUIRenderer_[3]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 1.4) {
				if (PlayResultUIRenderer_[4]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[4]->SetPivot(PlayResultUIRenderer_[4]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[4]->SetPivot(float4(PlayResultUIRenderer_[4]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 1.6) {
				if (PlayResultUIRenderer_[5]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[5]->SetPivot(PlayResultUIRenderer_[5]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[5]->SetPivot(float4(PlayResultUIRenderer_[5]->GetPivot().x, 250.0f));
				}
			}
		}
		else if (GetAccTime() > 2.0f && GetAccTime() < 3.0f)
		{
			BlinkTime_ += GameEngineTime::GetDeltaTime();

			if (BlinkTime_ < 0.1f) {
				for (int i = 0; i < 6; i++)
				{
					PlayResultUIRenderer_[i]->SetIndex(i + 6);
				}
			}
			else if (BlinkTime_ > 0.1f && BlinkTime_ < 0.2f) {
				for (int i = 0; i < 6; i++)
				{
					PlayResultUIRenderer_[i]->SetIndex(i);
				}
			}
			else {
				BlinkTime_ = 0.0f;
			}

		}

	}
	else if (GameResult == 3) ////Draw
	{

		if (GetAccTime() > 0.0f && GetAccTime() < 1.6f)
		{
			if (GetAccTime() < 0.6) {
				if (PlayResultUIRenderer_[0]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[0]->SetPivot(PlayResultUIRenderer_[0]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[0]->SetPivot(float4(PlayResultUIRenderer_[0]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 0.8) {
				if (PlayResultUIRenderer_[1]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[1]->SetPivot(PlayResultUIRenderer_[1]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[1]->SetPivot(float4(PlayResultUIRenderer_[1]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 1.0) {
				if (PlayResultUIRenderer_[2]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[2]->SetPivot(PlayResultUIRenderer_[2]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[2]->SetPivot(float4(PlayResultUIRenderer_[2]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 1.2) {
				if (PlayResultUIRenderer_[3]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[3]->SetPivot(PlayResultUIRenderer_[3]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[3]->SetPivot(float4(PlayResultUIRenderer_[3]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 1.4) {
				if (PlayResultUIRenderer_[4]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[4]->SetPivot(PlayResultUIRenderer_[4]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[4]->SetPivot(float4(PlayResultUIRenderer_[4]->GetPivot().x, 250.0f));
				}
			}
			else if (GetAccTime() < 1.6) {
				if (PlayResultUIRenderer_[5]->GetPivot().y < 250.f) {
					PlayResultUIRenderer_[5]->SetPivot(PlayResultUIRenderer_[5]->GetPivot() + float4{ 0.0f, 10.0f * IntroMoveTime_ });
				}
				else {
					PlayResultUIRenderer_[5]->SetPivot(float4(PlayResultUIRenderer_[5]->GetPivot().x, 250.0f));
				}
			}
		}
		else if (GetAccTime() > 2.0f && GetAccTime() < 3.0f)
		{
			BlinkTime_ += GameEngineTime::GetDeltaTime();

			if (BlinkTime_ < 0.1f) {
				for (int i = 0; i < 6; i++)
				{
					PlayResultUIRenderer_[i]->SetIndex(i + 6);
				}
			}
			else if (BlinkTime_ > 0.1f && BlinkTime_ < 0.2f) {
				for (int i = 0; i < 6; i++)
				{
					PlayResultUIRenderer_[i]->SetIndex(i);
				}
			}
			else {
				BlinkTime_ = 0.0f;
			}

		}
	}
}