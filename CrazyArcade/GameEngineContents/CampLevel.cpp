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
	MapBackGround_ = CreateActor<MapBackGround>(static_cast<int>(ORDER::BACKGROUND));//Actor �����
	MapBackGround_->GetRenderer()->SetImage("Camp_Back.bmp");//Actor�� �̹��� �������ְ�
	MapBackGround_->GetRenderer()->SetPivot({320,280});//��������� �׷��� ��ġ �����ְ�
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// Ÿ�ϸ� �������



	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor �����
	MapFrontBackGround_->GetRenderer()->SetImage("Camp_Front.bmp");//Actor�� �̹��� �������ְ�
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�

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
