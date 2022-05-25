#include"BossLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Boss.h"
#include <GameEngine/GameEngineImageManager.h>
#include "Player.h"

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
	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor 만들고
	MapBackGround_->GetRenderer()->SetImage("BossStage_Back.bmp");//Actor에 이미지 세팅해주고
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고

	{
		////// 몬스터 //////
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("Boss_ColMap.bmp");

		for (int x = 0; x < 3; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
				float StartX = float(600.0 / 3.0 * x) + float(20.0);
				float StartY = float(520.0/ 3.0 * y) + float(40.0);
				float EndX = float(600.0 / 3.0 * (x + 1)) + float(20.0);
				float EndY = float(520.0 / 3.0 * (y + 1)) + float(40.0);

				Area area(ColMapImage_, StartX, StartY, EndX, EndY);
				Areas_.push_back(area);
			}
		}

		Boss* Seal = CreateActor<Boss>((int)ORDER::MONSTER);
		Seal->SetPosition(Areas_[3].GetCenter());

		Player* NewPlayer = CreateActor<Player>((int)ORDER::PLAYER, "Player1");
		NewPlayer->SetCharacter(Character::BAZZI);
		NewPlayer->SetPlayerType(PlayerType::Player1);
		NewPlayer->SetPosition({ 500.f, 300.f });

		Seal->SetPlayer(NewPlayer);
	}
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
