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

	BackBtnCollision_ = CreateCollision("Back", { 40 ,40 }, { -365.0f,280.0f });
	ExitBtnCollision_ = CreateCollision("Exit", { 40 ,40 }, { 360.0f,280.0f });
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
	SetTextColor(GameEngine::BackBufferDC(), RGB(255, 255, 255));
	TextOut(GameEngine::BackBufferDC(), GetPosition().ix() - 56, GetPosition().iy() - 6, GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str()));
	TextOut(GameEngine::BackBufferDC(), GetPosition().ix() - 106, GetPosition().iy() - 6, GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str()));
}

