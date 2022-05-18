#include"CampLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include "MapFront.h"
#include "MapGameObject.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>


CampLevel::CampLevel()
:MapBackGround_(nullptr)
{

}
CampLevel::~CampLevel()
{

}

void CampLevel::Loading()
{
	MapBackGround_ = CreateActor<MapBackGround>(static_cast<int>(ORDER::BACKGROUND));//Actor 만들고
	MapBackGround_->GetRenderer()->SetImage("Camp_Back.bmp");//Actor에 이미지 세팅해주고
	MapBackGround_->GetRenderer()->SetPivot({320,280});//윈도우기준 그려줄 위치 정해주고
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// 타일맵 만들어줌



	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor 만들고
	MapFrontBackGround_->GetRenderer()->SetImage("Camp_Front.bmp");//Actor에 이미지 세팅해주고
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고

	MapGameObject* bubble = CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT),"Bubble");
	bubble->SetMapTile(&MapBackGround_->MapTileMap_);
	//bubble->BubblePop({ 60,60 }, 1);
	bubble->CreateBoom(1, 1);
}

void CampLevel::Update()
{
}

void CampLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}

void CampLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
