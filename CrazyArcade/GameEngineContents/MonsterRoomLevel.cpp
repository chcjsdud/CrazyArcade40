#include "MonsterRoomLevel.h"
#include "Mouse.h"
#include "MapChoiceUI.h"
#include "ContentsEnum.h"
#include "RoomBackGround.h"
#include "RoomCharaterSelectUI.h"
#include "StartButton.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

MonsterRoomLevel::MonsterRoomLevel()
{
}

MonsterRoomLevel::~MonsterRoomLevel()
{
}

void MonsterRoomLevel::Loading()
{
	CreateActor<RoomBackGround>((int)UIType::PopUp);
	CreateActor<StartButton>((int)UIType::PopUpButton);
	CreateActor<RoomCharaterSelectUI>((int)UIType::PopUpButton);
	CreateActor<MapChoiceUI>((int)UIType::PopUpButton);
	CreateActor<Mouse>((int)UIType::Mouse);

	
}

void MonsterRoomLevel::Update()
{
	
}
void MonsterRoomLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ShowCursor(false);
}

void MonsterRoomLevel::LevelChangeEnd(GameEngineLevel* NextLevel)
{
	ShowCursor(true);
}
