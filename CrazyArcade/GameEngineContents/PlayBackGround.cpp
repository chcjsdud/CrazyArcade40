#include "PlayBackGround.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"
#include "TimeUI.h"
#include "PlayerFaceIconUI.h"

PlayBackGround::PlayBackGround()
	: PlayBackGroundRenderer_(nullptr)
{
}

PlayBackGround::~PlayBackGround()
{
}

void PlayBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	PlayBackGroundRenderer_ = CreateRenderer((int)ORDER::FRONTBACKGROUND);
	PlayBackGroundRenderer_->SetImage("PlayBackGroundUI.bmp");

	ExitBtnRenderer_ = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ 318.0f,277.0f });

	ExitBtnRenderer_->CreateAnimation("PlayExitBtn.bmp", "PlayExitBtn_Idle", 0, 0, 0.1f, false);
	ExitBtnRenderer_->CreateAnimation("PlayExitBtn.bmp", "PlayExitBtn_Select", 1, 2, 0.2f, true);
	ExitBtnRenderer_->CreateAnimation("PlayExitBtn.bmp", "PlayExitBtn_Click", 3, 3, 0.1f, false);
	ExitBtnRenderer_->ChangeAnimation("PlayExitBtn_Idle");

	ExitBtnCollision_ = CreateCollision("Exit", { 130 ,35 }, { 320.0f,274.0f });


}

void PlayBackGround::Update()
{

	if (true == ExitBtnCollision_->CollisionCheck("MouseCol"))
	{
		ExitBtnRenderer_->ChangeAnimation("PlayExitBtn_Select");

		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			ExitBtnRenderer_->ChangeAnimation("PlayExitBtn_Click");
		}
		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GameEngine::GetInst().ChangeLevel("LoginLevel");
		}
	}
	else {
		ExitBtnRenderer_->ChangeAnimation("PlayExitBtn_Idle");
	}
}