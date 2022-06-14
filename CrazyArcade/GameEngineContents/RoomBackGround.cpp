#include "RoomBackGround.h"
#include "ContentsEnum.h"
#include "GlobalUIName.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineCollision.h>

RoomBackGround::RoomBackGround()
{
}

RoomBackGround::~RoomBackGround()
{
}

void RoomBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	if (GetLevel()->GetNameConstRef() == "MonsterRoomLevel")
	{
		CreateRenderer((int)UIType::PopUp)->SetImage("MonsterRoomBackGround.bmp");
	}
	else
	{
		CreateRenderer((int)UIType::PopUp)->SetImage("RoomBackGround.bmp");
	}

	BackBtnCollision_ = CreateCollision("Back", { 25 ,25 }, { -370.0f,280.0f });
	ExitBtnCollision_ = CreateCollision("Exit", { 25 ,25 }, { 363.0f,280.0f });
}


void RoomBackGround::Update()
{
	


	if (true == BackBtnCollision_->CollisionCheck("MouseCol")) {

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GameEngine::GetInst().ChangeLevel("LoginLevel");
		}
	}


	if (true == ExitBtnCollision_->CollisionCheck("MouseCol")) {

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GameEngineWindow::GetInst().Off();
		}
	}
}

void RoomBackGround::Render()
{
	
}

