#include"BossLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include "Boss.h"
#include "MapGameObject.h"
#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
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
	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
	MapBackGround_->GetRenderer()->SetImage("BossStage_Back.bmp");//Actor�� �̹��� �������ְ�
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// Ÿ�ϸ� �������

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
		////// ���� //////
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("Boss_ColMap.bmp");

		Boss* Seal = CreateActor<Boss>((int)ORDER::BOSS);
		Seal->SetMapTile(&MapBackGround_->MapTileMap_);
		Monster::BOSS_COUNT++;

		MapGameObject* BossBoom_ = CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
		BossBoom_->SetMapTile(&MapBackGround_->MapTileMap_);
		Seal->SetBoom(BossBoom_);
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
