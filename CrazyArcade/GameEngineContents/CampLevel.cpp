#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

#include"CampLevel.h"
#include"TitleBackGround.h"

CampLevel::CampLevel()
{

}
CampLevel::~CampLevel()
{

}
void CampLevel::Loading()
{
		TitleBackGround_ = CreateActor<TitleBackGround>(1);
	TitleBackGround_->GetRenderer()->SetImage("1Test.bmp");
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