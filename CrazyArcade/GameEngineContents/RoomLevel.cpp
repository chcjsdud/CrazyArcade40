#include "RoomLevel.h"
#include "Mouse.h"
#include "ContentsEnum.h"
#include "RoomBackGround.h"
#include "RoomCharaterSelectUI.h"
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
	CreateActor<RoomCharaterSelectUI>((int)UIType::PopUpButton);
	CreateActor<Mouse>((int)UIType::Mouse);

	if (false == GameEngineInput::GetInst()->IsKey("Play"))
	{
		GameEngineInput::GetInst()->CreateKey("Play", VK_SPACE);
	}
}

void RoomLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Play"))
	{
		GameEngine::GetInst().ChangeLevel("PlayerTeamTest");
	}
}
void RoomLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ShowCursor(false);
}

void RoomLevel::LevelChangeEnd(GameEngineLevel* NextLevel)
{
	ShowCursor(true);
}
