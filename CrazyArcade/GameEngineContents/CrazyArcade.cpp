#include "CrazyArcade.h"
#include "IntroLevel.h"
#include "TitleLevel.h"
#include "CampLevel.h"
#include "VillageLevel.h"
#include "CemeteryLevel.h"
//#include "Monster1Level.h"
//#include "Monster2Level.h"
#include "BossLevel.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineInput.h>

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

    // 배찌 리소스 
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("PlayLevel");
        ResourcesDir.Move("Player");


        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }
    }

    // 리소스 로드

    // 플레이어 
    {
        GameEngineImage* Left = GameEngineImageManager::GetInst()->Find("Left.bmp");
        Left->CutCount(6, 1);
        GameEngineImage* Right = GameEngineImageManager::GetInst()->Find("Right.bmp");
        Right->CutCount(6, 1);
        GameEngineImage* Down = GameEngineImageManager::GetInst()->Find("Down.bmp");
        Down->CutCount(8, 1);
        GameEngineImage* Up = GameEngineImageManager::GetInst()->Find("Up.bmp");
        Up->CutCount(8, 1);
    }


    // 키 생성
    if (false == GameEngineInput::GetInst()->IsKey("TitleLevel"))    
    {
        GameEngineInput::GetInst()->CreateKey("TitleLevel", 'P');    
        GameEngineInput::GetInst()->CreateKey("CampLevel", '1');
        GameEngineInput::GetInst()->CreateKey("VillageLevel", '2');

        GameEngineInput::GetInst()->CreateKey("NextLevel", 'Z');
    }

	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 800, 600 });
	
    CreateLevel<IntroLevel>("IntroLevel");
	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<CampLevel>("CampLevel");
	CreateLevel<VillageLevel>("VillageLevel");
	CreateLevel<CemeteryLevel>("CemeteryLevel");
	//CreateLevel<Monster1Level>("Monster1Level");
	//CreateLevel<Monster2Level>("Monster2Level");
	CreateLevel<BossLevel>("BossLevel");
    ChangeLevel("CampLevel");
}

void CrazyArcade::GameLoop()
{
}

void CrazyArcade::GameEnd()
{
}