#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineLevel.h>



#include "CrazyArcade.h"
#include "GlobalUIName.h"
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
///////////UI레벨///////////
#include "RoomLevel.h"
#include "MonsterRoomLevel.h"

#include "TileMapEditorLevel.h"

CrazyArcade::CrazyArcade()
{
}

CrazyArcade::~CrazyArcade()
{
}

void CrazyArcade::GameInit()
{

    GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 200, 80 }, { 800, 600 });


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

        GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("LoginBtn.bmp");
        Image->Cut({ 128,128 });

        Image = GameEngineImageManager::GetInst()->Find("ExitBtn.bmp");
        Image->Cut({ 128,128 });

        Image = GameEngineImageManager::GetInst()->Find("1pBtn.bmp");
        Image->Cut({ 128,128 });

        Image = GameEngineImageManager::GetInst()->Find("2pBtn.bmp");
        Image->Cut({ 128,128 });
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


    ////// UI 리소스 Room에서 사용되는 리소스
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

        GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("RandomCharSelecter.bmp");
        Image->Cut({ 128,100 });

        Image = GameEngineImageManager::GetInst()->Find("BazziCharSelecter.bmp");
        Image->Cut({ 128,100 });

        Image = GameEngineImageManager::GetInst()->Find("DaoCharSelecter.bmp");
        Image->Cut({ 128,100 });

        Image = GameEngineImageManager::GetInst()->Find("MaridCharSelecter.bmp");
        Image->Cut({ 128,100 });

        Image = GameEngineImageManager::GetInst()->Find("StartButton.bmp");
        Image->Cut({ 200,100 });

        Image = GameEngineImageManager::GetInst()->Find("MapChoiceButton.bmp");
        Image->Cut({ 200,100 });
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

        Image = GameEngineImageManager::GetInst()->Find("GameStartIntro.bmp");
        Image->Cut({ 128,128 });

        Image = GameEngineImageManager::GetInst()->Find("WinText.bmp");
        Image->Cut({ 192,192 });

        Image = GameEngineImageManager::GetInst()->Find("LoseText.bmp");
        Image->Cut({ 192,192 });

        Image = GameEngineImageManager::GetInst()->Find("DrawText.bmp");
        Image->Cut({ 192,192 });

        Image = GameEngineImageManager::GetInst()->Find("BazziFace_Icon.bmp");
        Image->Cut({ 64,64 });
    }

    ////// UI 리소스 ChoiceMap에서 사용되는 리소스
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("UILevel");
        ResourcesDir.Move("ChoiceMap");


        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }


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

    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("PlayLevel");
        ResourcesDir.Move("Item");

            std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }
    }


    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("PlayLevel");
        ResourcesDir.Move("TileMap");
        ResourcesDir.Move("Camp");

        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }
    }
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("PlayLevel");
        ResourcesDir.Move("TileMap");
        ResourcesDir.Move("Village");

        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }
    }
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("PlayLevel");
        ResourcesDir.Move("TileMap");
        ResourcesDir.Move("Cemetory");

        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }
    }
    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("CrazyArcade");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("PlayLevel");
        ResourcesDir.Move("TileMap");
        ResourcesDir.Move("MonsterStage1");

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

    //물풍선 이미지
    GameEngineImage* Bubble_Dark = GameEngineImageManager::GetInst()->Find("Bubble_Dark.bmp");
    Bubble_Dark->CutCount(4, 1);
    GameEngineImage* Bubble_Boss = GameEngineImageManager::GetInst()->Find("Bubble_Boss.bmp");
    Bubble_Boss->CutCount(4, 1);
    GameEngineImage* Bubble_Default = GameEngineImageManager::GetInst()->Find("Bubble_Default.bmp");
    Bubble_Default->CutCount(5, 1);
    //아이템 이미지
    GameEngineImage* Fluid = GameEngineImageManager::GetInst()->Find("Fluid.bmp");
    Fluid->CutCount(6, 1);
    //맵 박스, 오브젝트이미지
    GameEngineImage* CampMoveBox2 = GameEngineImageManager::GetInst()->Find("CampMoveBox2.bmp");
    CampMoveBox2->CutCount(3, 1);
    GameEngineImage* CampBush1 = GameEngineImageManager::GetInst()->Find("CampBush1.bmp");
    CampBush1->CutCount(5, 1);
    GameEngineImage* CampBush2 = GameEngineImageManager::GetInst()->Find("CampBush2.bmp");
    CampBush2->CutCount(6, 1);
    GameEngineImage* VillageBush = GameEngineImageManager::GetInst()->Find("VillageBush1.bmp");
    VillageBush->CutCount(5, 1);
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
        GameEngineInput::GetInst()->CreateKey("LoginLevel", '6');
        GameEngineInput::GetInst()->CreateKey("TileMapEditorLevel", '0');

        GameEngineInput::GetInst()->CreateKey("NextLevel", 'Z');
        GameEngineInput::GetInst()->CreateKey("MonsterLevel", '9');
        GameEngineInput::GetInst()->CreateKey("Debug_Col", VK_OEM_6); // ]키
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
    //////UI 레벨
    CreateLevel<RoomLevel>("RoomLevel");
    CreateLevel<MonsterRoomLevel>("MonsterRoomLevel");
    //////테스트 레벨
    CreateLevel<MapTeamTest>("MapTeamTest");
    CreateLevel<PlayerTeamTest>("PlayerTeamTest");
    CreateLevel<UITeamTest>("UITeamTest");

    CreateLevel<TileMapEditorLevel>("TileMapEditorLevel");

    ChangeLevel("Monster2Level");

}

void CrazyArcade::GameLoop()
{
    if (true == GameEngineInput::GetInst()->IsDown("Debug_Col"))
    {
        GameEngineLevel::IsDebugModeSwitch();
    }
    
    if (true == GameEngineInput::GetInst()->IsDown("MapTeamTest"))
    {
        GameEngine::GetInst().ChangeLevel("MapTeamTest");
    }
    if (true == GameEngineInput::GetInst()->IsDown("PlayerTeamTest"))
    {
        GameEngine::GetInst().ChangeLevel("PlayerTeamTest");
    }
    if (true == GameEngineInput::GetInst()->IsDown("UITeamTest"))
    {
        GameEngine::GetInst().ChangeLevel("UITeamTest");
    }
    if (true == GameEngineInput::GetInst()->IsDown("CampLevel"))
    {
        GameEngine::GetInst().ChangeLevel("CampLevel");
    }
    if (true == GameEngineInput::GetInst()->IsDown("LoginLevel"))
    {
        GameEngine::GetInst().ChangeLevel("LoginLevel");
    }
    if (true == GameEngineInput::GetInst()->IsDown("TileMapEditorLevel"))
    {
        GameEngine::GetInst().ChangeLevel("TileMapEditorLevel");
    }
    if (true == GameEngineInput::GetInst()->IsDown("MonsterLevel"))
    {
        GameEngine::GetInst().ChangeLevel("Monster1Level");
    }
}

void CrazyArcade::GameEnd()
{
    GlobalUIName::Destroy();
}