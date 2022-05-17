#include"VillageLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

VillageLevel::VillageLevel()
{

}
VillageLevel::~VillageLevel()
{

}

void VillageLevel::Loading()
{
	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
	MapBackGround_->GetRenderer()->SetImage("Village_Back.bmp");//Actor�� �̹��� �������ְ�
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�

	MapFrontBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
	MapFrontBackGround_->GetRenderer()->SetImage("Village_Front.bmp");//Actor�� �̹��� �������ְ�
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�
}

void VillageLevel::Update()
{
}

void VillageLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}

void VillageLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
}
