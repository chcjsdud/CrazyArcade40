#include"CampLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include "MapFront.h"
#include "MapGameObject.h"
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
	MapBackGround_ = CreateActor<MapBackGround>(static_cast<int>(ORDER::BACKGROUND));//Actor �����
	MapBackGround_->GetRenderer()->SetImage("Camp_Back.bmp");//Actor�� �̹��� �������ְ�
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// Ÿ�ϸ� �������



	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor �����
	MapFrontBackGround_->GetRenderer()->SetImage("Camp_Front.bmp");//Actor�� �̹��� �������ְ�
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�

	bubble_ = CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
	bubble_->SetMapTile(&MapBackGround_->MapTileMap_);
	bubble_->CreateBoom({ 240,380 }, 3);
	bubble_->CreateBoom({ 80,380 }, 3);
	//bubble_->CreateBoom({ 400,380 }, 3);
	//bubble_->CreateBoom({ 240,60 }, 3);
	//bubble_->CreateBoom({ 240,220 }, 3);

	bubble_->CreateItem({ 240,40 });

	if (false == GameEngineInput::GetInst()->IsKey("CreatBoom"))
	{
		GameEngineInput::GetInst()->CreateKey("CreatBoom", VK_SPACE);
	}
}

void CampLevel::Update()
{
	if (GameEngineInput::GetInst()->IsDown("CreatBoom")==true)
	{
		bubble_->CreateBoom({ 520,100 }, 3);
	}
}

void CampLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}

void CampLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
