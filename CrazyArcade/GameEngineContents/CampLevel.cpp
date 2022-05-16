#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

#include"CampLevel.h"
#include"Player_Bazzi.h"
#include"ContentsEnum.h"
#include"MapBackGround.h."


CampLevel::CampLevel()
:MapBackGround_(nullptr)
{

}
CampLevel::~CampLevel()
{

}

void CampLevel::Loading()
{
	Player_Bazzi* NewPlayer = CreateActor<Player_Bazzi>((int)ORDER::PLAYER);
	NewPlayer->SetPosition({ 100.f, 100.f });

	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
	MapBackGround_->GetRenderer()->SetImage("Camp_Back.bmp");//Actor�� �̹��� �������ְ�d
	MapBackGround_->GetRenderer()->SetPivot({320,280});//��������� �׷��� ��ġ �����ְ�

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