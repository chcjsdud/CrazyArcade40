#include "StartMonsterModeUI.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineSound.h>

StartMonsterModeUI::StartMonsterModeUI()
	:StartTime_(0.0f)
{
}

StartMonsterModeUI::~StartMonsterModeUI()
{
}

void StartMonsterModeUI::Start()
{
	StartMonsterModeRenderer_ = CreateRenderer("MonsterModeStart.bmp");
	StartMonsterModeRenderer_->SetPivot(GameEngineWindow::GetScale().Half() + float4{ -100.0f,0.0f});

	
	Death(5.0f);
}

void StartMonsterModeUI::Update()
{
	StartTime_ += GameEngineTime::GetDeltaTime();

	if (StartTime_ > 0.4f) {
		StartMonsterModeRenderer_->SetPivot(StartMonsterModeRenderer_->GetPivot() + float4{ -500.0f * GameEngineTime::GetDeltaTime(), 0.0f });
	}
}

void StartMonsterModeUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void StartMonsterModeUI::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	this->Death();
}
