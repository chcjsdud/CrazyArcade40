#include"CemetoryLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include "MapFront.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include "MapGameObject.h"
CemetoryLevel::CemetoryLevel()
{

}
CemetoryLevel::~CemetoryLevel()
{

}

void CemetoryLevel::Loading()
{
	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
	MapBackGround_->GetRenderer()->SetImage("Cemetory_Back.bmp");//Actor�� �̹��� �������ְ�
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// Ÿ�ϸ� �������

	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor �����

	{
		MapGameObject* BlockSet = CreateActor<MapGameObject>();
		BlockSet->SetMapTile(&MapBackGround_->MapTileMap_);
		GameEngineDirectory Dir;

		Dir.MoveParent("CrazyArcade");
		Dir.Move("Resources");
		Dir.Move("Data");

		GameEngineFile LoadFile = (Dir.GetFullPath() + "\\CemetoryLevel.MapData").c_str();

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

	YSortOn(static_cast<int>(ORDER::PLAYER));
}

void CemetoryLevel::Update()
{
}

void CemetoryLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}

void CemetoryLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
}
