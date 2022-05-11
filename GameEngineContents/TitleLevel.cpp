#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include"TitleLevel.h"
#include"TitleBackGround.h"

TitleLevel::TitleLevel()
{

}
TitleLevel::~TitleLevel()
{

}
void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>(0);
}
void TitleLevel::Update()
{

}
void TitleLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{

}
void TitleLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{

}