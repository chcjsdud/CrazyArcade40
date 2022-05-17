#include"Monster1Level.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
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