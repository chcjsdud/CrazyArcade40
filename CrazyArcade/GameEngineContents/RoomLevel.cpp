#include "RoomLevel.h"
#include "ChattingInput.h"
#include "ChattingHistory.h"
#include "Mouse.h"
#include "MapChoiceUI.h"
#include "RoomNickName.h"
#include "ContentsEnum.h"
#include "RoomBackGround.h"
#include "RoomCharaterSelectUI.h"
#include "StartButton.h"
#include "MapChoiceUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

RoomLevel::RoomLevel()
{
}

RoomLevel::~RoomLevel()
{
}

void RoomLevel::Loading()
{
	CreateActor<RoomBackGround>((int)UIType::PopUp);
	CreateActor<StartButton>((int)UIType::PopUpButton);
	CreateActor<RoomCharaterSelectUI>((int)UIType::PopUpButton);
	CreateActor<MapChoiceUI>((int)UIType::PopUpButton);
	CreateActor<ChattingInput>((int)UIType::PopUpButton);
	CreateActor<ChattingHistory>((int)UIType::PopUpButton);
	CreateActor<RoomNickName>((int)UIType::PopUpButton);
	CreateActor<Mouse>((int)UIType::Mouse);

}

void RoomLevel::Update()
{
	
}
void RoomLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetTextColor(GameEngine::BackBufferDC(), RGB(0, 0,0));
	ShowCursor(false);
}

void RoomLevel::LevelChangeEnd(GameEngineLevel* NextLevel)
{
	ShowCursor(true);
}
