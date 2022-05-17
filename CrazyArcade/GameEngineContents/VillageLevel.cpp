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
	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor 만들고
	MapBackGround_->GetRenderer()->SetImage("Village_Back.bmp");//Actor에 이미지 세팅해주고
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고

	MapFrontBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor 만들고
	MapFrontBackGround_->GetRenderer()->SetImage("Village_Front.bmp");//Actor에 이미지 세팅해주고
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고
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
