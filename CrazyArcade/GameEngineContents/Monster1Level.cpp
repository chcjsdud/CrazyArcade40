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
	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
	MapBackGround_->GetRenderer()->SetImage("MonsterStage1_Back.bmp");//Actor�� �̹��� �������ְ�
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�

	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor �����
	MapFrontBackGround_->GetRenderer()->SetImage("MonsterStage1_Front.bmp");//Actor�� �̹��� �������ְ�
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�

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

	//TODO chowon : Edge ó�� �� �ּ� Ǯ��
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