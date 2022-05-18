#include"BossLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Boss.h"

BossLevel::BossLevel()
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


}

void BossLevel::Update()
{
}

void BossLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Boss* Seal = CreateActor<Boss>((int)ORDER::MONSTER);
	Seal->SetPosition(float4(320.0f, 200.0f));
}

void BossLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
