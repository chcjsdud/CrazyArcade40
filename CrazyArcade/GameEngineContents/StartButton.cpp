#include "StartButton.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEngine/GameEngine.h>


StartButton::StartButton()
	: StartRenderer_(nullptr)
	, StartCollision_(nullptr)
{
}

StartButton::~StartButton()
{
	
}

void StartButton::Start()
{
	SetPosition({625, 509});
	StartRenderer_ = CreateRenderer((int)UIType::PopUpButton);
	StartRenderer_->SetImage("StartButton.bmp");

	StartRenderer_->CreateAnimation("StartButton.bmp", "StartButton_Idle", 0, 0, 0.1f, false);
	StartRenderer_->CreateAnimation("StartButton.bmp", "StartButton_Approach", 10, 14, 0.1f, true);
	StartRenderer_->CreateAnimation("StartButton.bmp", "StartButton_Cilck", 19, 19, 0.1f, false);

	StartRenderer_->ChangeAnimation("StartButton_Idle");

	StartCollision_ = CreateCollision("StartButton", { 200.0f, 66.0f });
	StartCollision_->SetPivot(float4{0.0f,20.0f});

}

void StartButton::Update()
{
	if (true == StartCollision_->CollisionCheck("MouseCol"))
	{
		StartRenderer_->ChangeAnimation("StartButton_Approach");
	}


	else if (false == StartCollision_->CollisionCheck("MouseCol"))
	{
		StartRenderer_->ChangeAnimation("StartButton_Idle");
	}

	if (true == StartCollision_->CollisionCheck("MouseCol") &&
		true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		StartRenderer_->ChangeAnimation("StartButton_Cilck");
	}

	if (true == StartCollision_->CollisionCheck("MouseCol") &&
		true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		StartButtonClick();
	}
}

void StartButton::StartButtonClick()
{
	GameEngine::GetInst().ChangeLevel("PlayerTeamTest");
}