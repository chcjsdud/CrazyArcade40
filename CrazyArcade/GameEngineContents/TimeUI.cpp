#include "TimeUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Player.h"

TimeUI::TimeUI()
	:GameTime_(180.0f)
{
}

TimeUI::~TimeUI()
{
}

void TimeUI::Start()
{
	for (size_t i = 0; i < 4; i++)
	{
		GameEngineRenderer* TempRenderer = CreateRenderer("TimeNumber.bmp");
		Renderer.push_back(TempRenderer);
	}

}

void TimeUI::Update()
{
	GameTime_ -= GameEngineTime::GetDeltaTime();

	Renderer[0]->SetIndex((static_cast<int>(GameTime_) / 60) / 10);
	Renderer[0]->SetPivot(float4(717.0f, 82.0f));

	Renderer[1]->SetIndex((static_cast<int>(GameTime_) / 60) %10);
	Renderer[1]->SetPivot(float4(732.0f, 82.0f));

	Renderer[2]->SetIndex((static_cast<int>(GameTime_) % 60) / 10);
	Renderer[2]->SetPivot(float4(752.0f, 82.0f));

	Renderer[3]->SetIndex(((static_cast<int>(GameTime_) % 60) % 10));
	Renderer[3]->SetPivot(float4(767.0f, 82.0f));
	
	if (GameTime_ < 0) {
		GameTime_ = 0.0f;
	}
}
