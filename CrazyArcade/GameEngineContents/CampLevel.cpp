#include"CampLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include "MapFront.h"
#include "MapGameObject.h"
#include"GameItemObject.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include<GameEngineBase/GameEngineInput.h>


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
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// 타일맵 만들어줌



	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor 만들고
	MapFrontBackGround_->GetRenderer()->SetImage("Camp_Front.bmp");//Actor에 이미지 세팅해주고
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고

	bubble_ = CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
	bubble_->SetMapTile(&MapBackGround_->MapTileMap_);


	Item_ = CreateActor<GameItemObject>(static_cast<int>(ORDER::MAPOBJECT), "Item");
	Item_->SetMapTile(&MapBackGround_->MapTileMap_);
	bubble_->CreateBoom({ 40,40 }, 3);


	bubble_->CreateBoom({ 200,40 }, 3);

	Item_->CreateItem({ 200,380 }, (ItemType::Fluid));



	if (false == GameEngineInput::GetInst()->IsKey("CreatBoom"))
	{
		GameEngineInput::GetInst()->CreateKey("CreatBoom", VK_SPACE);
	}
}

void CampLevel::Update()
{
	if (GameEngineInput::GetInst()->IsDown("CreatBoom")==true)
	{
		bubble_->CreateBoom({ 200,380 }, 3);
	}
}

void CampLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}

void CampLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
