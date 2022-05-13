#include "CrazyArcade.h"
#include "IntroLevel.h"
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
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("IntroLevel");

        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }
    }
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 800, 600 });
	
    CreateLevel<IntroLevel>("IntroLevel");
	CreateLevel<TitleLevel>("TitleLevel");
	
    ChangeLevel("IntroLevel");
}

void CrazyArcade::GameLoop()
{
}

void CrazyArcade::GameEnd()
{
}