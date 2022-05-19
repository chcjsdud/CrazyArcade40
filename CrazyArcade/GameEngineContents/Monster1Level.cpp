#include"Monster1Level.h"
#include"ContentsEnum.h"
#include "MapFront.h"
#include "MapBackGround.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Monster1.h"
#include "Monster2.h"

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
}
void Monster1Level::Update()
{

}
void Monster1Level::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	Monster1* Mandarin1 = CreateActor<Monster1>((int)ORDER::MONSTER);
	Mandarin1->SetPosition(float4(150.0f, 200.0f));

	Monster1* Mandarin2 = CreateActor<Monster1>((int)ORDER::MONSTER);
	Mandarin2->SetPosition(float4(500.0f, 80.0f));

	Monster1* Mandarin3 = CreateActor<Monster1>((int)ORDER::MONSTER);
	Mandarin3->SetPosition(float4(150.0f, 550.0f));

	Monster1* Mandarin4 = CreateActor<Monster1>((int)ORDER::MONSTER);
	Mandarin4->SetPosition(float4(500.0f, 500.0f));

	Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile1->SetPosition(float4(150.0f, 300.0f));

	Monster2* Crocodile2 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile2->SetPosition(float4(500.0f, 350.0f));

}
void Monster1Level::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{

}