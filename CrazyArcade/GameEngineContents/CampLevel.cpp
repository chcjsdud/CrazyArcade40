#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

#include"CampLevel.h"
#include"MapBackGround.h"

CampLevel::CampLevel()
{

}
CampLevel::~CampLevel()
{

}
void CampLevel::Loading()
{
	MapBackGround_ = CreateActor<MapBackGround>(1);
	MapBackGround_->GetRenderer()->SetImage("BossStage_Back.bmp");
	MapBackGround_->GetRenderer()->SetPivot({ 320, 280 });//윈도우기준 그려줄 위치 정해주고
}
void CampLevel::Update()
{

}
void CampLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{

}
void CampLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{

}