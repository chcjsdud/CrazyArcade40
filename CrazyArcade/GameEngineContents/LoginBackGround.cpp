#include "LoginBackGround.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
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
	Change1PCollision_ = CreateCollision("Change1P", {80  ,80 }, {-215, 175});
	Change2PCollision_ = CreateCollision("Change2P", { 80 ,80 }, { 215, 175 });
}

void LoginBackGround::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LeftMouse") &&
		true == Change1PCollision_->CollisionCheck("MouseCol"))
	{
		LoginBackGroundRenderer_->SetImage("LoginUI_1P.bmp");
		Change1PCollision_ ->SetPivot({ -215, 175 });
		Change2PCollision_ ->SetPivot({ 215, 175 });
	}

	if (true == GameEngineInput::GetInst()->IsDown("LeftMouse") &&
		true == Change2PCollision_->CollisionCheck("MouseCol"))
	{
		LoginBackGroundRenderer_->SetImage("LoginUI_2P.bmp");
		Change1PCollision_->SetPivot({ -345, 175 });
		Change2PCollision_->SetPivot({ 345, 175 });
	}
}