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

	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 800, 600 });

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

	{

		//맵 이미지
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("CrazyArcade");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("PlayLevel");
		ResourcesDir.Move("TileMap");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}
	{

		//콜리전 맵 이미지
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("CrazyArcade");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("PlayLevel");
		ResourcesDir.Move("TileMap");
		ResourcesDir.Move("ColMap");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}

	
    CreateLevel<IntroLevel>("IntroLevel");
	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<TitleLevel>("CampLevel");
	CreateLevel<TitleLevel>("VillageLevel");
	CreateLevel<TitleLevel>("CemeteryLevel");
	CreateLevel<TitleLevel>("Monster1Level");
	CreateLevel<TitleLevel>("Monster2Level");
	CreateLevel<TitleLevel>("BossLevel");
    ChangeLevel("CampLevel");
}

void CrazyArcade::GameLoop()
{
}

void CrazyArcade::GameEnd()
{
}