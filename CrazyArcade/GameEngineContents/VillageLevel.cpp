#include"VillageLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include "MapFront.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include "MapGameObject.h"
VillageLevel::VillageLevel()
	: MapBackGround_(nullptr)
	, MapFrontBackGround_(nullptr)
{

}
VillageLevel::~VillageLevel()
{

}

void VillageLevel::Loading()
{
	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor 만들고
	MapBackGround_->GetRenderer()->SetImage("Village_Back.bmp");//Actor에 이미지 세팅해주고
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// 타일맵 만들어줌
	{
		MapGameObject* BlockSet = CreateActor<MapGameObject>();
		BlockSet->SetMapTile(&MapBackGround_->MapTileMap_);
		GameEngineDirectory Dir;

		Dir.MoveParent("CrazyArcade");
		Dir.Move("Resources");
		Dir.Move("Data");

		GameEngineFile LoadFile = (Dir.GetFullPath() + "\\VillageLevel.MapData").c_str();

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
			BlockSet->CreateBlock(float4(static_cast<float>(10 * 40), (static_cast<float>(0 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(12 * 40), (static_cast<float>(0 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(14 * 40), (static_cast<float>(0 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(1 * 40), (static_cast<float>(1 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(1 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(5 * 40), (static_cast<float>(1 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(9 * 40), (static_cast<float>(1 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(10 * 40), (static_cast<float>(2 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(12 * 40), (static_cast<float>(2 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(14 * 40), (static_cast<float>(2 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(1 * 40), (static_cast<float>(3 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(3 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(5 * 40), (static_cast<float>(3 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(9 * 40), (static_cast<float>(3 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(10 * 40), (static_cast<float>(4 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(12 * 40), (static_cast<float>(4 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(14 * 40), (static_cast<float>(4 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(1 * 40), (static_cast<float>(5 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(5 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(5 * 40), (static_cast<float>(5 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(0 * 40), (static_cast<float>(6 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(2 * 40), (static_cast<float>(6 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(4 * 40), (static_cast<float>(6 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(10 * 40), (static_cast<float>(6 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(12 * 40), (static_cast<float>(6 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(14 * 40), (static_cast<float>(6 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(9 * 40), (static_cast<float>(7 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(7 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(13* 40), (static_cast<float>(7 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(0* 40), (static_cast<float>(8 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(2 * 40), (static_cast<float>(8 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(4 * 40), (static_cast<float>(8 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(5 * 40), (static_cast<float>(9 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(9 * 40), (static_cast<float>(9 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(9 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(13 * 40), (static_cast<float>(9 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(0 * 40), (static_cast<float>(10 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(2 * 40), (static_cast<float>(10 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(4 * 40), (static_cast<float>(10 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(5 * 40), (static_cast<float>(11 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(9 * 40), (static_cast<float>(11 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(11 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(13 * 40), (static_cast<float>(11 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(0 * 40), (static_cast<float>(12 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(2 * 40), (static_cast<float>(12 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(4 * 40), (static_cast<float>(12 * 40))), "WallBlock");

		}
	}
	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor 만들고

	YSortOn(static_cast<int>(ORDER::PLAYER));
}

void VillageLevel::Update()
{
}

void VillageLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}

void VillageLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
}
