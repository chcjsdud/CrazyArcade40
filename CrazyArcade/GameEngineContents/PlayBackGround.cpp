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

	ExitBtnCollision_ = CreateCollision("Exit", { 120 ,40 }, { 320.0f,274.0f });
}

void PlayBackGround::Update()
{
	if (true == ExitBtnCollision_->CollisionCheck("MouseCol")) {

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GameEngine::GetInst().ChangeLevel("LoginLevel");
		}
	}

}

