#include "PlayResultUI.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"
#include "PlayScoreBoard.h"
#include <GameEngineBase/GameEngineSound.h>

PlayResultUI::PlayResultUI()
	:ChangeLevelName_("LoginLevel")
{
}

PlayResultUI::~PlayResultUI()
{
}

void PlayResultUI::Start()
{
	FallWidth = 180.0f;
	FallHeight = 100.0f;


	//Death(10.0f);
}

void PlayResultUI::Update()
{
	IntroMoveTime_ += GameEngineTime::GetDeltaTime();

	
	if (setting == false && GameResult_ != GameResult::Max)
	{
		if (GameResult_ == GameResult::Win)
		{

			GameEngineSound::SoundPlayOneShot("Win.wav");
			for (size_t i = 0; i < 5; i++)
			{
				GameEngineRenderer* TempRenderer = CreateRenderer("WinText.bmp");
				PlayResultUIRenderer_.push_back(TempRenderer);
			}

			//Game
			PlayResultUIRenderer_[0]->SetIndex(0);
			PlayResultUIRenderer_[0]->SetPivot(float4(FallWidth, -50.0f));

			PlayResultUIRenderer_[1]->SetIndex(1);
			PlayResultUIRenderer_[1]->SetPivot(float4(FallWidth + 80.0f, -50.0f));

			PlayResultUIRenderer_[2]->SetIndex(2);
			PlayResultUIRenderer_[2]->SetPivot(float4(FallWidth + 160.0f, -50.0f));

			PlayResultUIRenderer_[3]->SetIndex(3);
			PlayResultUIRenderer_[3]->SetPivot(float4(FallWidth + 240.0f, -50.0f));

			PlayResultUIRenderer_[4]->SetIndex(4);
			PlayResultUIRenderer_[4]->SetPivot(float4(FallWidth + 270.0f, -50.0f));

		}
		else if (GameResult_ == GameResult::Lose) {

			GameEngineSound::SoundPlayOneShot("Lose.wav");
			for (size_t i = 0; i < 6; i++)
			{
				GameEngineRenderer* TempRenderer = CreateRenderer("LoseText.bmp");
				PlayResultUIRenderer_.push_back(TempRenderer);
			}

			//Game
			PlayResultUIRenderer_[0]->SetIndex(0);
			PlayResultUIRenderer_[0]->SetPivot(float4(FallWidth, -50.0f));

			PlayResultUIRenderer_[1]->SetIndex(1);
			PlayResultUIRenderer_[1]->SetPivot(float4(FallWidth + 80.0f, -50.0f));

			PlayResultUIRenderer_[2]->SetIndex(2);
			PlayResultUIRenderer_[2]->SetPivot(float4(FallWidth + 160.0f, -50.0f));

			PlayResultUIRenderer_[3]->SetIndex(3);
			PlayResultUIRenderer_[3]->SetPivot(float4(FallWidth + 240.0f, -50.0f));

			PlayResultUIRenderer_[4]->SetIndex(4);
			PlayResultUIRenderer_[4]->SetPivot(float4(FallWidth + 320.0f, -50.0f));

			PlayResultUIRenderer_[5]->SetIndex(5);
			PlayResultUIRenderer_[5]->SetPivot(float4(FallWidth + 350.0f, -50.0f));
		}
		else if (GameResult_ == GameResult::Draw) {

			GameEngineSound::SoundPlayOneShot("Draw.wav");
			for (size_t i = 0; i < 6; i++)
			{
				GameEngineRenderer* TempRenderer = CreateRenderer("DrawText.bmp");
				PlayResultUIRenderer_.push_back(TempRenderer);
			}

			//Game
			PlayResultUIRenderer_[0]->SetIndex(0);
			PlayResultUIRenderer_[0]->SetPivot(float4(FallWidth, -50.0f));

			PlayResultUIRenderer_[1]->SetIndex(1);
			PlayResultUIRenderer_[1]->SetPivot(float4(FallWidth + 80.0f, -50.0f));

			PlayResultUIRenderer_[2]->SetIndex(2);
			PlayResultUIRenderer_[2]->SetPivot(float4(FallWidth + 160.0f, -50.0f));

			PlayResultUIRenderer_[3]->SetIndex(3);
			PlayResultUIRenderer_[3]->SetPivot(float4(FallWidth + 240.0f, -50.0f));

			PlayResultUIRenderer_[4]->SetIndex(4);
			PlayResultUIRenderer_[4]->SetPivot(float4(FallWidth + 320.0f, -50.0f));

			PlayResultUIRenderer_[5]->SetIndex(5);
			PlayResultUIRenderer_[5]->SetPivot(float4(FallWidth + 350.0f, -50.0f));
		}
		setting = true;
	}

	if (GameResult_ == GameResult::Win) //// Win
	{
		if (PlayResultUIRenderer_[0]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[0]->SetPivot(PlayResultUIRenderer_[0]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[0]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[0]->SetPivot(float4(PlayResultUIRenderer_[0]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[1]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[1]->SetPivot(PlayResultUIRenderer_[1]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[1]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[1]->SetPivot(float4(PlayResultUIRenderer_[1]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[2]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[2]->SetPivot(PlayResultUIRenderer_[2]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[2]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[2]->SetPivot(float4(PlayResultUIRenderer_[2]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[3]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[3]->SetPivot(PlayResultUIRenderer_[3]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[3]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[3]->SetPivot(float4(PlayResultUIRenderer_[3]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[4]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[4]->SetPivot(PlayResultUIRenderer_[4]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[4]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[4]->SetPivot(float4(PlayResultUIRenderer_[4]->GetPivot().x, FallHeight));
			}
		}

		if (GetAccTime() > 1.5f && GetAccTime() < 2.5f)
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
	else if (GameResult_ == GameResult::Lose) ////Lose
	{

		if (PlayResultUIRenderer_[0]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[0]->SetPivot(PlayResultUIRenderer_[0]->GetPivot() + float4{ 0.0f, 6.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[0]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[0]->SetPivot(float4(PlayResultUIRenderer_[0]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[1]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[1]->SetPivot(PlayResultUIRenderer_[1]->GetPivot() + float4{ 0.0f, 6.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[1]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[1]->SetPivot(float4(PlayResultUIRenderer_[1]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[2]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[2]->SetPivot(PlayResultUIRenderer_[2]->GetPivot() + float4{ 0.0f, 6.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[2]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[2]->SetPivot(float4(PlayResultUIRenderer_[2]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[3]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[3]->SetPivot(PlayResultUIRenderer_[3]->GetPivot() + float4{ 0.0f, 6.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[3]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[3]->SetPivot(float4(PlayResultUIRenderer_[3]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[4]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[4]->SetPivot(PlayResultUIRenderer_[4]->GetPivot() + float4{ 0.0f, 6.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[4]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[4]->SetPivot(float4(PlayResultUIRenderer_[4]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[5]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[5]->SetPivot(PlayResultUIRenderer_[5]->GetPivot() + float4{ 0.0f, 6.0f * IntroMoveTime_ });
			if (PlayResultUIRenderer_[5]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[5]->SetPivot(float4(PlayResultUIRenderer_[5]->GetPivot().x, FallHeight));
			}
		}

		if (GetAccTime() > 2.0f && GetAccTime() < 3.0f)
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
	else if (GameResult_ == GameResult::Draw) ////Draw
	{

		if (PlayResultUIRenderer_[0]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[0]->SetPivot(PlayResultUIRenderer_[0]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[0]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[0]->SetPivot(float4(PlayResultUIRenderer_[0]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[1]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[1]->SetPivot(PlayResultUIRenderer_[1]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[1]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[1]->SetPivot(float4(PlayResultUIRenderer_[1]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[2]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[2]->SetPivot(PlayResultUIRenderer_[2]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[2]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[2]->SetPivot(float4(PlayResultUIRenderer_[2]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[3]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[3]->SetPivot(PlayResultUIRenderer_[3]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[3]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[3]->SetPivot(float4(PlayResultUIRenderer_[3]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[4]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[4]->SetPivot(PlayResultUIRenderer_[4]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });

			if (PlayResultUIRenderer_[4]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[4]->SetPivot(float4(PlayResultUIRenderer_[4]->GetPivot().x, FallHeight));
			}
		}
		else if (PlayResultUIRenderer_[5]->GetPivot().y < FallHeight) {
			PlayResultUIRenderer_[5]->SetPivot(PlayResultUIRenderer_[5]->GetPivot() + float4{ 0.0f, 7.0f * IntroMoveTime_ });
			if (PlayResultUIRenderer_[5]->GetPivot().y > FallHeight)
			{
				PlayResultUIRenderer_[5]->SetPivot(float4(PlayResultUIRenderer_[5]->GetPivot().x, FallHeight));
			}
		}

		if (GetAccTime() > 1.5f && GetAccTime() < 2.5f)
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
	
	if (IntroMoveTime_ >= 7.0f)
	{
		IntroMoveTime_ = 0.0f;
		GameEngine::GetInst().ChangeLevel(ChangeLevelName_);
	}
}