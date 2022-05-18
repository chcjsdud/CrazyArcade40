#include "PlayBackGround.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"

PlayBackGround::PlayBackGround()
	: PlayBackGroundRenderer_(nullptr)
{
}

PlayBackGround::~PlayBackGround()
{
}

void PlayBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	PlayBackGroundRenderer_ = CreateRenderer("PlayBackGround.bmp");

}

void PlayBackGround::Update()
{
	
}