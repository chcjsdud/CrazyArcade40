#include"BossLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include "Boss.h"
#include "BossBoom.h"
#include "MapGameObject.h"
#include "Player.h"
#include "PlayBackGround.h"
#include "StartIntroUI.h"
#include "TimeUI.h"
#include "PlayerFaceIconUI.h"
#include "Mouse.h"
#include "PlayNickName.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>


//UI 부분
#include "Mouse.h"
#include "PlayBackGround.h"
#include "TimeUI.h"
#include "StartIntroUI.h"
#include "PlayResultUI.h"
#include "PlayNickName.h"
#include "TimeUI.h"
#include "PlayerFaceIconUI.h"
BossLevel::BossLevel()
	: ColMapImage_(nullptr)
	, MapBackGround_(nullptr)
{

}
BossLevel::~BossLevel()
{

}

void BossLevel::Loading()
{
	CreateActor<PlayBackGround>((int)ORDER::PLAYER);
	CreateActor<StartIntroUI>((int)UIType::StartIntroUI);
	CreateActor<TimeUI>((int)UIType::Time);
	CreateActor<PlayerFaceIconUI>((int)UIType::Time);
	CreateActor<Mouse>((int)UIType::Mouse);
	CreateActor<PlayNickName>((int)UIType::PopUpButton);

	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor 만들고
	MapBackGround_->GetRenderer()->SetImage("BossStage_Back.bmp");//Actor에 이미지 세팅해주고
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// 타일맵 만들어줌

	{
		MapGameObject* BlockSet = CreateActor<MapGameObject>();
		BlockSet->SetMapTile(&MapBackGround_->MapTileMap_);
		GameEngineDirectory Dir;
	
		Dir.MoveParent("CrazyArcade");
		Dir.Move("Resources");
		Dir.Move("Data");
	
		GameEngineFile LoadFile = (Dir.GetFullPath() + "\\BossLevel.MapData").c_str();
	
		LoadFile.Open(OpenMode::Read);
	
		int Size = 0;
		LoadFile.Read(&Size, sizeof(int));
	
		for (size_t y = 0; y < Size; y++)
		{
			int XSize = 0;
			LoadFile.Read(&XSize, sizeof(int));
			for (size_t x = 0; x < XSize; x++)
			{
				std::string Name;
				LoadFile.Read(Name);
	
				if (Name == "None")
				{
					continue;
				}
	
				//                          5 7
				BlockSet->CreateBlock(float4(static_cast<float>(x * 40), static_cast<float>(y * 40)), Name);
			}
		}
	}

	{
		////// 몬스터 //////
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("Boss_ColMap.bmp");

		Boss* Seal = CreateActor<Boss>((int)ORDER::BOSS);
		Seal->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::BOSS_COUNT++;

		for (int i = 0; i < 9; ++i)
		{
			BossBoom* _BossBoom = CreateActor<BossBoom>(static_cast<int>(ORDER::UI), "Bubble");
			_BossBoom->SetMapTile(&MapBackGround_->MapTileMap_);
			Seal->AddBoom(_BossBoom);
		}
	}
	BossObject_ = CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
	BossObject_->SetMapTile(&MapBackGround_->MapTileMap_);
	BossObject_->SetGameItem();
	YSortOn(static_cast<int>(ORDER::PLAYER));
}

void BossLevel::Update()
{
}

void BossLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}

void BossLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
