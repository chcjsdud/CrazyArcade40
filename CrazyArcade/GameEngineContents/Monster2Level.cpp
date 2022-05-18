#include"Monster2Level.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include "MapFront.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Monster2.h"
Monster2Level::Monster2Level()
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

	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor 만들고
	MapFrontBackGround_->GetRenderer()->SetImage("MonsterStage2_Front.bmp");//Actor에 이미지 세팅해주고
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고
	
}
void Monster2Level::Update()
{

}
void Monster2Level::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile1->SetPosition(float4(50.0f, 100.0f));

	Monster2* Crocodile2 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile2->SetPosition(float4(80.0f, 200.0f));

	Monster2* Crocodile3 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile3->SetPosition(float4(500.0f, 200.0f));

	Monster2* Crocodile4 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile4->SetPosition(float4(600.0f, 100.0f));

	Monster2* Crocodile5 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile5->SetPosition(float4(400.0f, 500.0f));

	Monster2* Crocodile6 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile6->SetPosition(float4(300.0f, 300.0f));

}
void Monster2Level::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{

}