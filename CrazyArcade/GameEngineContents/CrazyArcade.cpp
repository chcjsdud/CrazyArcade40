#include "CrazyArcade.h"
#include "IntroLevel.h"
#include "TitleLevel.h"

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
    if (false == GameEngineInput::GetInst()->IsKey("Test1"))    // 테스트 레벨 생성 
    {
        GameEngineInput::GetInst()->CreateKey("Test1", '1');    // 캐릭터 이동 테스트 용도 
        GameEngineInput::GetInst()->CreateKey("Test2", '2');
    }

	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 800, 600 });
	
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