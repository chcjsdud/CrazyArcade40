#include"BossLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
BossLevel::BossLevel()
{

}
BossLevel::~BossLevel()
{

}

void BossLevel::Loading()
{
	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
	MapBackGround_->GetRenderer()->SetImage("Boss_Back.bmp");//Actor�� �̹��� �������ְ�
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�
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
