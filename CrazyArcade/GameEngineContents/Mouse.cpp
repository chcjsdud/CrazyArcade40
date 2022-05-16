#include "Mouse.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineCollision.h>

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::Start()
{

	//ShowCursor(false);
	GetCurPos();
	SetPosition({ CurPos_.x,CurPos_.y });
    MouseRenderer_ = CreateRenderer("Mouse_1.bmp");
	MouseCol_ = CreateCollision("MouseCol", { 16,20 }, { -8,-10 });
	MouseCol_->CameraEffectOff();
	if (false == GameEngineInput::GetInst()->IsKey("LeftMouse"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftMouse", VK_LBUTTON);

	}
}

void Mouse::Update()
{
	GetCurPos();
	SetPosition({ CurPos_.x,CurPos_.y });
	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		MouseRenderer_->SetImage("Mouse_2.bmp");
	}
	else
	{
		MouseRenderer_->SetImage("Mouse_1.bmp");
	}
}