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
	CreateRenderer((int)UIType::PopUp)->SetImage("RoomBackGround.bmp");
}

