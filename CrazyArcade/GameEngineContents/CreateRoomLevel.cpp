#include "CreateRoomLevel.h"
#include"UITeamTest.h"
#include"CreateRoomBackGround.h"
#include"LoginBackGround.h"
#include"Mouse.h"
#include"ContentsEnum.h"

CreateRoomLevel::CreateRoomLevel()
{
}

CreateRoomLevel::~CreateRoomLevel()
{
}

void CreateRoomLevel::Loading()
{
	CreateActor<LoginBackGround>((int)UIType::BackGround);
	CreateActor<CreateRoomBackGround>((int)UIType::PopUp);
	CreateActor<Mouse>((int)UIType::Mouse);

}
void CreateRoomLevel::Update()
{

}
void CreateRoomLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ShowCursor(false);
}

void CreateRoomLevel::LevelChangeEnd(GameEngineLevel* NextLevel)
{
	ShowCursor(true);
}
