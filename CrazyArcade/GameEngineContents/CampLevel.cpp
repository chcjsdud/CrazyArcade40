#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

#include"CampLevel.h"


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
