#include"Monster1Level.h"
#include"ContentsEnum.h"
#include "MapFront.h"
#include "MapBackGround.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Monster1.h"
#include "Monster2.h"
#include "Player.h"
#include "Area.h"
#include <GameEngine/GameEngineImageManager.h>

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

	//TODO chowon : Edge 처리 후 주석 풀기
	//Monster1* Mandarin1 = CreateActor<Monster1>((int)ORDER::MONSTER);
	//Mandarin1->SetPosition(Areas_[87].GetCenter());

	//Monster1* Mandarin2 = CreateActor<Monster1>((int)ORDER::MONSTER);
	//Mandarin2->SetPosition(Areas_[0].GetCenter());

	//Monster1* Mandarin3 = CreateActor<Monster1>((int)ORDER::MONSTER);
	//Mandarin3->SetPosition(Areas_[182].GetCenter());

	//Monster1* Mandarin4 = CreateActor<Monster1>((int)ORDER::MONSTER);
	//Mandarin4->SetPosition(Areas_[193].GetCenter());

	//Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::MONSTER);
	//Crocodile1->SetPosition(Areas_[6].GetCenter());

	//Monster2* Crocodile2 = CreateActor<Monster2>((int)ORDER::MONSTER);
	//Crocodile1->SetPosition(Areas_[188].GetCenter());
}
void Monster1Level::Update()
{

}
void Monster1Level::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}
void Monster1Level::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{

}