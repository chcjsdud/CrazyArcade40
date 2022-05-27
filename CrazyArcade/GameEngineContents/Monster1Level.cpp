#include"Monster1Level.h"
#include"ContentsEnum.h"
#include "MapFront.h"
#include "MapBackGround.h"
#include <GameEngine/GameEngine.h>
#include<GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Monster1.h"
#include "Monster2.h"
#include "Player.h"
#include "Area.h"
#include"ContentsEnum.h"
#include "MapGameObject.h"
#include"GameItemObject.h"
#include <GameEngine/GameEngineRendererTileMap.h>

Monster1Level::Monster1Level()
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

	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor 만들고
	MapFrontBackGround_->GetRenderer()->SetImage("MonsterStage1_Front.bmp");//Actor에 이미지 세팅해주고
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고
	
	
	{
		////// 몬스터 //////
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("MonsterStage1_ColMap.bmp");

		for (int x = 0; x < 15; ++x)
		{
			for (int y = 0; y < 13; ++y)
			{
				float StartX = (600 / 15 * x) + 20;
				float StartY = (520 / 13 * y) + 40;
				float EndX = (600 / 15 * (x + 1)) + 20;
				float EndY = (520 / 13 * (y + 1)) + 40;

				Area area(ColMapImage_, StartX, StartY, EndX, EndY);
				Areas_.push_back(area);
			}
		}

		Monster1* Mandarin1 = CreateActor<Monster1>((int)ORDER::MONSTER);
		Mandarin1->SetPosition(Areas_[0].GetCenter());
		Mandarin1->SetMapTile(&MapBackGround_->MapTileMap_);


		Monster1* Mandarin2 = CreateActor<Monster1>((int)ORDER::MONSTER);
		Mandarin2->SetPosition(Areas_[182].GetCenter());

		Monster1* Mandarin3 = CreateActor<Monster1>((int)ORDER::MONSTER);
		Mandarin3->SetPosition(Areas_[12].GetCenter());

		Monster1* Mandarin4 = CreateActor<Monster1>((int)ORDER::MONSTER);
		Mandarin4->SetPosition(Areas_[166].GetCenter());

		Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::MONSTER);
		Crocodile1->SetPosition(Areas_[6].GetCenter());

		Monster2* Crocodile2 = CreateActor<Monster2>((int)ORDER::MONSTER);
		Crocodile2->SetPosition(Areas_[188].GetCenter());
	

	}

	//Player* Player1 = CreateActor<Player>((int)ORDER::PLAYER);
	//Player1->SetPosition(float4(400.0f, 400.0f));
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