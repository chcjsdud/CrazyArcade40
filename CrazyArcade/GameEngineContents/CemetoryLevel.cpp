#include"CemetoryLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include "MapFront.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

CemetoryLevel::CemetoryLevel()
{

}
CemetoryLevel::~CemetoryLevel()
{

}

void CemetoryLevel::Loading()
{
	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
	MapBackGround_->GetRenderer()->SetImage("Cemetory_Back.bmp");//Actor�� �̹��� �������ְ�
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�

	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor �����
	MapFrontBackGround_->GetRenderer()->SetImage("Cemetory_Front.bmp");//Actor�� �̹��� �������ְ�
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�
}

void CemetoryLevel::Update()
{
}

void CemetoryLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}

void CemetoryLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
}
