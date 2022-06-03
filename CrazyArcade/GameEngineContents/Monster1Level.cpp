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
				BlockSet->CreateBlock(float4(x * 40, y * 40), Name);
			}
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

		Monster1* Mandarin1 = CreateActor<Monster1>((int)ORDER::MONSTER);
		Mandarin1->SetPosition(Areas_[55].GetCenter());
		Mandarin1->SetMapTile(&MapBackGround_->MapTileMap_);

		Monster1* Mandarin2 = CreateActor<Monster1>((int)ORDER::MONSTER);
		Mandarin2->SetPosition(Areas_[57].GetCenter());
		Mandarin2->SetMapTile(&MapBackGround_->MapTileMap_);

		Monster1* Mandarin3 = CreateActor<Monster1>((int)ORDER::MONSTER);
		Mandarin3->SetPosition(Areas_[102].GetCenter());
		Mandarin3->SetMapTile(&MapBackGround_->MapTileMap_);

		Monster1* Mandarin4 = CreateActor<Monster1>((int)ORDER::MONSTER);
		Mandarin4->SetPosition(Areas_[118].GetCenter());
		Mandarin4->SetMapTile(&MapBackGround_->MapTileMap_);

		Monster1* Mandarin5 = CreateActor<Monster1>((int)ORDER::MONSTER);
		Mandarin5->SetPosition(Areas_[125].GetCenter());
		Mandarin5->SetMapTile(&MapBackGround_->MapTileMap_);

		Monster1* Mandarin6 = CreateActor<Monster1>((int)ORDER::MONSTER);
		Mandarin6->SetPosition(Areas_[88].GetCenter());
		Mandarin6->SetMapTile(&MapBackGround_->MapTileMap_);

		Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::MONSTER);
		Crocodile1->SetPosition(Areas_[7].GetCenter());
		Crocodile1->SetMapTile(&MapBackGround_->MapTileMap_);

		Monster2* Crocodile2 = CreateActor<Monster2>((int)ORDER::MONSTER);
		Crocodile2->SetPosition(Areas_[174].GetCenter());
		Crocodile2->SetMapTile(&MapBackGround_->MapTileMap_);

	}


	//Player::MainPlayer_1->SetCharacter(Character::BAZZI);
	//Player::MainPlayer_1->SetPlayerType(PlayerType::Player1);
	//Player::MainPlayer_1->SetPosition({ 300.f, 360.f });
	//Player::MainPlayer_1->SetMapTile(&MapBackGround_->MapTileMap_);
	//Player::MainPlayer_1->On();
	}

void Monster1Level::Update()
{
	if (Monster::TTL_MONSTER_COUNT == 0)
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
}
void Monster1Level::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{

}