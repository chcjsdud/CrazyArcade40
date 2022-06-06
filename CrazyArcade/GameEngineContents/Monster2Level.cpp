#include"Monster2Level.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include "MapFront.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include "MapGameObject.h"
#include "Monster2.h"
#include "Area.h"
#include <GameEngine/GameEngineImageManager.h>
Monster2Level::Monster2Level()
	:ColMapImage_(nullptr)
	, MapBackGround_(nullptr)
	, MapFrontBackGround_(nullptr)
{

}
Monster2Level::~Monster2Level()
{

}
void Monster2Level::Loading()
{
	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor 만들고
	MapBackGround_->GetRenderer()->SetImage("MonsterStage2_Back.bmp");//Actor에 이미지 세팅해주고
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// 타일맵 만들어줌

	{
		MapGameObject* BlockSet = CreateActor<MapGameObject>();
		BlockSet->SetMapTile(&MapBackGround_->MapTileMap_);
		GameEngineDirectory Dir;

		Dir.MoveParent("CrazyArcade");
		Dir.Move("Resources");
		Dir.Move("Data");

		GameEngineFile LoadFile = (Dir.GetFullPath() + "\\Monster2Level.MapData").c_str();

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
				BlockSet->CreateBlock(float4(static_cast<float>(x * 40),static_cast<float>( y * 40)), Name);
			}
		}
	}

	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor 만들고

	{// 몬스터

		ColMapImage_ = GameEngineImageManager::GetInst()->Find("MonsterStage2_ColMap.bmp");

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

		Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::PLAYER);
		Crocodile1->SetPosition(Areas_[12].GetCenter());
		Crocodile1->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV2_MON_COUNT++;

		Monster2* Crocodile2 = CreateActor<Monster2>((int)ORDER::PLAYER);
		Crocodile2->SetPosition(Areas_[13].GetCenter());
		Crocodile2->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV2_MON_COUNT++;

		Monster2* Crocodile3 = CreateActor<Monster2>((int)ORDER::PLAYER);
		Crocodile3->SetPosition(Areas_[48].GetCenter());
		Crocodile3->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV2_MON_COUNT++;

		Monster2* Crocodile4 = CreateActor<Monster2>((int)ORDER::PLAYER);
		Crocodile4->SetPosition(Areas_[89].GetCenter());
		Crocodile4->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV2_MON_COUNT++;

		Monster2* Crocodile5 = CreateActor<Monster2>((int)ORDER::PLAYER);
		Crocodile5->SetPosition(Areas_[131].GetCenter());
		Crocodile5->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV2_MON_COUNT++;

		Monster2* Crocodile6 = CreateActor<Monster2>((int)ORDER::PLAYER);
		Crocodile6->SetPosition(Areas_[179].GetCenter());
		Crocodile6->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::LV2_MON_COUNT++;
	}

	YSortOn(static_cast<int>(ORDER::PLAYER));
}
void Monster2Level::Update()
{
	if (Monster::LV2_MON_COUNT == 0)
	{
		// UI 나오고
		////if(UI 화면 끝나면)
		//{
		//	GameEngine::GetInst().ChangeLevel("BossLevel");
		//}
	}

	// else if 플레이어 수가 0이되면
	// UI 나오고
	// //if(UI 화면 끝나면)
	// {
	// 대기실로 이동
	//}
}
void Monster2Level::LevelChangeStart(GameEngineLevel* _NextLevel)
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
	Player::MainPlayer_1->SetPosition(Areas_[135].GetCenter());
	Player::MainPlayer_1->SetMapTile(&MapBackGround_->MapTileMap_);
}
void Monster2Level::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	
}