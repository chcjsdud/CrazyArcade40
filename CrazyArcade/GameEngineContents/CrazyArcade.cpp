#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineInput.h>

#include "CrazyArcade.h"

#include "IntroLevel.h"
#include "TitleLevel.h"
#include "LoginLevel.h"
#include "CampLevel.h"
#include "VillageLevel.h"
#include "CemetoryLevel.h"
////////몬스터 맵//////////
#include "Monster1Level.h"
#include "Monster2Level.h"
#include "BossLevel.h"
////////테스트레벨//////////
#include "MapTeamTest.h"
#include "PlayerTeamTest.h"
#include "UITeamTest.h"



CrazyArcade::CrazyArcade()
{
}

CrazyArcade::~CrazyArcade()
{
}

void CrazyArcade::GameInit()
{

    GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 800, 600 });


    //////////////////////////////아래 리소스 로드//////////////////////////////

    //인트로 리소스
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

    // 타일맵(콜리전맵, 맵UI 같이 들어 있음) 맵크기 600*560 (15*14) (한타일 40*40)
    {
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

    ////// UI 리소스 기타들(마우스 커서, ...)
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("UILevel");
        ResourcesDir.Move("etc");


        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }
    }

    ////// UI 리소스 LoginLevel에서 사용되는 리소스
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("UILevel");
        ResourcesDir.Move("Login");


        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }
    }

    ////// UI 리소스 CreateRoom에서 사용되는 리소스
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("UILevel");
        ResourcesDir.Move("CreateRoom");


        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }



        GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("NormalBtn_Animation.bmp");
        Image->Cut({ 256,256 });

        Image = GameEngineImageManager::GetInst()->Find("MonsterBtn_Animation.bmp");
        Image->Cut({ 256,256 });

        Image = GameEngineImageManager::GetInst()->Find("ConfirmBtn.bmp");
        Image->Cut({ 128,128 });

        Image = GameEngineImageManager::GetInst()->Find("CancelBtn.bmp");
        Image->Cut({ 128,128 });

        
    }

    //////// UI 리소스 RoomLevel에서 사용되는 리소스
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("UILevel");
        ResourcesDir.Move("Room");


        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }


        GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("BazziCharSelecter.bmp");
        Image->Cut({ 128,100 });
    }

    ////// UI 리소스 Play에서 사용되는 리소스
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("UILevel");
        ResourcesDir.Move("Play");


        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }

        GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("TimeNumber.bmp");
        Image->Cut({ 12,10 });

    }
    //플레이어 배찌
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

    // 몬스터
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("PlayLevel");
        ResourcesDir.Move("Monster");


        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }
    }
    // 효과
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("PlayLevel");
        ResourcesDir.Move("Effect");


        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }
    }

    //////////////////////////////아래 이미지 컷//////////////////////////////

    //////////물풍선 터지는 animationcut
    GameEngineImage* Center = GameEngineImageManager::GetInst()->Find("Center.bmp");
    Center->CutCount(6,1);
    GameEngineImage* Right1 = GameEngineImageManager::GetInst()->Find("Right1.bmp");
    Right1->CutCount(11,1);
    GameEngineImage* Right2 = GameEngineImageManager::GetInst()->Find("Right2.bmp");
    Right2->CutCount(11, 1);
    GameEngineImage* Up1 = GameEngineImageManager::GetInst()->Find("Up1.bmp");
    Up1->CutCount(11, 1);
    GameEngineImage* Up2 = GameEngineImageManager::GetInst()->Find("Up2.bmp");
    Up2->CutCount(11, 1);
    GameEngineImage* Left1 = GameEngineImageManager::GetInst()->Find("Left1.bmp");
    Left1->CutCount(11, 1);
    GameEngineImage* Left2 = GameEngineImageManager::GetInst()->Find("Left2.bmp");
    Left2->CutCount(11, 1);
    GameEngineImage* Down1 = GameEngineImageManager::GetInst()->Find("Down1.bmp");
    Down1->CutCount(11, 1);
    GameEngineImage* Down2 = GameEngineImageManager::GetInst()->Find("Down2.bmp");
    Down2->CutCount(11, 1);

   //////////////////////////////아래 게임 키 설정//////////////////////////////

// 플레이어  키



    // 키 생성
    if (false == GameEngineInput::GetInst()->IsKey("TitleLevel"))
    {
        GameEngineInput::GetInst()->CreateKey("TitleLevel", 'P');
        GameEngineInput::GetInst()->CreateKey("MapTeamTest", '1');
        GameEngineInput::GetInst()->CreateKey("PlayerTeamTest", '2');
        GameEngineInput::GetInst()->CreateKey("UITeamTest", '3');

        GameEngineInput::GetInst()->CreateKey("CampLevel", '4');
        GameEngineInput::GetInst()->CreateKey("VillageLevel", '5');

        GameEngineInput::GetInst()->CreateKey("NextLevel", 'Z');
    }
    //////시작부분
    CreateLevel<IntroLevel>("IntroLevel");
    CreateLevel<LoginLevel>("LoginLevel");
    CreateLevel<TitleLevel>("TitleLevel");
    //////결투맵 레벨
    CreateLevel<CampLevel>("CampLevel");
    CreateLevel<VillageLevel>("VillageLevel");
    CreateLevel<CemetoryLevel>("CemetoryLevel");
    //////몬스터 맵 레벨
    CreateLevel<Monster1Level>("Monster1Level");
    CreateLevel<Monster2Level>("Monster2Level");
    CreateLevel<BossLevel>("BossLevel");
    //////테스트 레벨
    CreateLevel<MapTeamTest>("MapTeamTest");
    CreateLevel<PlayerTeamTest>("PlayerTeamTest");
    CreateLevel<UITeamTest>("UITeamTest");

    ChangeLevel("UITeamTest");

}

void CrazyArcade::GameLoop()
{
}

void CrazyArcade::GameEnd()
{
}