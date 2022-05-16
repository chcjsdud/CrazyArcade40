#include "LoginBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <Windows.h>
#include <GameEngine/GameEngineCollision.h>

LoginBackGround::LoginBackGround()
	: LoginBackGroundRenderer_(nullptr)
{
}

LoginBackGround::~LoginBackGround()
{
}

void LoginBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	LoginBackGroundRenderer_ = CreateRenderer("LoginUI_1P.bmp");
}

void LoginBackGround::Update()
{
		
}