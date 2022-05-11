#include "CrazyArcade.h"
#include "TitleLevel.h"


#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>

CrazyArcade::CrazyArcade()
{
}

CrazyArcade::~CrazyArcade()
{
}

void CrazyArcade::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });
	CreateLevel<TitleLevel>("TitleLevel");
	ChangeLevel("TitleLevel");
}

void CrazyArcade::GameLoop()
{

}
void CrazyArcade::GameEnd()
{

}