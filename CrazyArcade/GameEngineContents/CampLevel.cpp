#include"CampLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Player_Bazzi.h"
#include "ContentsEnum.h"


CampLevel::CampLevel()
{

}
CampLevel::~CampLevel()
{

}

void CampLevel::Loading()
{
	Player_Bazzi* NewPlayer = CreateActor<Player_Bazzi>((int)ORDER::PLAYER);
	NewPlayer->SetPosition({ 100.f, 100.f });

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
