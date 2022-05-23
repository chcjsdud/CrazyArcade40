#include "RoomBackGround.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

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
}

