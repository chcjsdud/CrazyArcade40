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

	{
		////// ���� //////
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("Boss_ColMap.bmp");

		for (int x = 0; x < 3; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
				float StartX = (600 / 3 * x) + 20;
				float StartY = (520 / 3 * y) + 40;
				float EndX = (600 / 3 * (x + 1)) + 20;
				float EndY = (520 / 3 * (y + 1)) + 40;

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
