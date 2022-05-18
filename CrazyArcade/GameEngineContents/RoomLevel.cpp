#include "RoomLevel.h"
#include "Mouse.h"
#include"ContentsEnum.h"

RoomLevel::RoomLevel()
{
}

RoomLevel::~RoomLevel()
{
}

void RoomLevel::Loading()
{

	CreateActor<Mouse>((int)UIType::Mouse);

}
void RoomLevel::Update()
{

}
void RoomLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ShowCursor(false);
}

void RoomLevel::LevelChangeEnd(GameEngineLevel* NextLevel)
{
	ShowCursor(true);
}
