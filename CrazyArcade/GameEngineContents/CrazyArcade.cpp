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
////////���� ��//////////
#include "Monster1Level.h"
#include "Monster2Level.h"
#include "BossLevel.h"
////////�׽�Ʈ����//////////
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


    //////////////////////////////�Ʒ� ���ҽ� �ε�//////////////////////////////

    //��Ʈ�� ���ҽ�
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

    // Ÿ�ϸ�(�ݸ�����, ��UI ���� ��� ����) ��ũ�� 600*560 (15*14) (��Ÿ�� 40*40)
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

    ////// UI ���ҽ� ��Ÿ��(���콺 Ŀ��, ...)
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

    ////// UI ���ҽ� LoginLevel���� ���Ǵ� ���ҽ�
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

    ////// UI ���ҽ� CreateRoom���� ���Ǵ� ���ҽ�
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

    //////// UI ���ҽ� RoomLevel���� ���Ǵ� ���ҽ�
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

    ////// UI ���ҽ� Play���� ���Ǵ� ���ҽ�
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
    //�÷��̾� ����
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

    // ����
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
    // ȿ��
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

    //////////////////////////////�Ʒ� �̹��� ��//////////////////////////////

    //////////��ǳ�� ������ animationcut
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

   //////////////////////////////�Ʒ� ���� Ű ����//////////////////////////////

// �÷��̾�  Ű



    // Ű ����
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
    //////���ۺκ�
    CreateLevel<IntroLevel>("IntroLevel");
    CreateLevel<LoginLevel>("LoginLevel");
    CreateLevel<TitleLevel>("TitleLevel");
    //////������ ����
    CreateLevel<CampLevel>("CampLevel");
    CreateLevel<VillageLevel>("VillageLevel");
    CreateLevel<CemetoryLevel>("CemetoryLevel");
    //////���� �� ����
    CreateLevel<Monster1Level>("Monster1Level");
    CreateLevel<Monster2Level>("Monster2Level");
    CreateLevel<BossLevel>("BossLevel");
    //////�׽�Ʈ ����
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