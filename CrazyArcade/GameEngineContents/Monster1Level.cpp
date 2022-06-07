#include"Monster1Level.h"
#include"ContentsEnum.h"
#include "MapFront.h"
#include "MapBackGround.h"
#include <GameEngine/GameEngine.h>
#include<GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include "Monster1.h"
#include "Monster2.h"
#include "Player.h"
#include "Area.h"
#include"ContentsEnum.h"
#include "MapGameObject.h"
#include"GameItemObject.h"
#include <GameEngine/GameEngineRendererTileMap.h>

Monster1Level::Monster1Level()
	: ColMapImage_(nullptr)
	, MapBackGround_(nullptr)
	, MapFrontBackGround_(nullptr)
{

}
Monster1Level::~Monster1Level()
{

}
void Monster1Level::Loading()
{
	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor 만들고
	MapBackGround_->GetRenderer()->SetImage("MonsterStage1_Back.bmp");//Actor에 이미지 세팅해주고
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// 타일맵 만들어줌

	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor 만들고

	{
		MapGameObject* BlockSet = CreateActor<MapGameObject>();
		BlockSet->SetMapTile(&MapBackGround_->MapTileMap_);
		GameEngineDirectory Dir;

		Dir.MoveParent("CrazyArcade");
		Dir.Move("Resources");
		Dir.Move("Data");

		GameEngineFile LoadFile = (Dir.GetFullPath() + "\\Monster1Level.MapData").c_str();

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
			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(0 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(0 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(3 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(3 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(0 * 40), (static_cast<float>(4 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(1 * 40), (static_cast<float>(4 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(2 * 40), (static_cast<float>(4 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(4 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(4 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(12 * 40), (static_cast<float>(4 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(13 * 40), (static_cast<float>(4 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(14 * 40), (static_cast<float>(4 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(5 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(5 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(7 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(7 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(0 * 40), (static_cast<float>(8 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(1 * 40), (static_cast<float>(8 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(2 * 40), (static_cast<float>(8 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(8 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(8 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(12 * 40), (static_cast<float>(8 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(13 * 40), (static_cast<float>(8 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(14 * 40), (static_cast<float>(8 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(9 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(9 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(12 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(12 * 40))), "WallBlock");

		}
	}
	{
		////// 몬스터 //////
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("MonsterStage1_ColMap.bmp");

		for (int x = 0; x < 15; ++x)
		{
			for (int y = 0; y < 13; ++y)
			{
				float StartX = static_cast<float>((600 / 15 * x) + 20);
				float StartY = static_cast<float>((520 / 13 * y) + 40);
				float EndX = static_cast<float>((600 / 15 * (x + 1)) + 20);
				float EndY = static_cast<float>((520 / 13 * (y + 1)) + 40);

				Area area(ColMapImage_, StartX, StartY, EndX, EndY);
				Areas_.push_back(area);
			}
		}

		Monster1* Mandarin1 = CreateActor<Monster1>((int)ORDER::PLAYER);
		Mandarin1->SetPosition(Areas_[66].GetCenter());
		Mandarin1->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV1_MON_COUNT++;

		Monster1* Mandarin2 = CreateActor<Monster1>((int)ORDER::PLAYER);
		Mandarin2->SetPosition(Areas_[118].GetCenter());
		Mandarin2->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV1_MON_COUNT++;

		Monster1* Mandarin3 = CreateActor<Monster1>((int)ORDER::PLAYER);
		Mandarin3->SetPosition(Areas_[71].GetCenter());
		Mandarin3->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV1_MON_COUNT++;

		Monster1* Mandarin4 = CreateActor<Monster1>((int)ORDER::PLAYER);
		Mandarin4->SetPosition(Areas_[123].GetCenter());
		Mandarin4->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV1_MON_COUNT++;

		Monster1* Mandarin5 = CreateActor<Monster1>((int)ORDER::PLAYER);
		Mandarin5->SetPosition(Areas_[76].GetCenter());
		Mandarin5->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV1_MON_COUNT++;

		Monster1* Mandarin6 = CreateActor<Monster1>((int)ORDER::PLAYER);
		Mandarin6->SetPosition(Areas_[128].GetCenter());
		Mandarin6->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV1_MON_COUNT++;

		Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::PLAYER);
		Crocodile1->SetPosition(Areas_[19].GetCenter());
		Crocodile1->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV1_MON_COUNT++;

		Monster2* Crocodile2 = CreateActor<Monster2>((int)ORDER::PLAYER);
		Crocodile2->SetPosition(Areas_[175].GetCenter());
		Crocodile2->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV1_MON_COUNT++;

	}


	YSortOn(static_cast<int>(ORDER::PLAYER));
}

void Monster1Level::Update()
{
	if (Monster::LV1_MON_COUNT == 0)
	{
		// UI 나오고
		////if(UI 화면 끝나면)
		//{
		//	GameEngine::GetInst().ChangeLevel("Monster2Level");
		//}
	}

	//else if 플레이어 수가 0이되면
	//	UI 나오고
	//	//if(UI 화면 끝나면)
	//{
	//대기실로 이동
	//}
}
void Monster1Level::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	if (nullptr != Player::MainPlayer_1)
	{
		Player::MainPlayer_1 = nullptr;
	}

	if (nullptr != Player::MainPlayer_2)
	{
		Player::MainPlayer_2 = nullptr;
	}


	Player::MainPlayer_1 = CreateActor<Player>((int)ORDER::PLAYER, "Player1");
	Player::MainPlayer_1->SetCharacter(Character::BAZZI);
	Player::MainPlayer_1->SetPlayerType(PlayerType::Player1);
	Player::MainPlayer_1->SetPosition(Areas_[23].GetCenter());
	Player::MainPlayer_1->SetMapTile(&MapBackGround_->MapTileMap_);

}
void Monster1Level::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{

}