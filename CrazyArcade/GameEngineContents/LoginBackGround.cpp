#include "LoginBackGround.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "CreateRoomBackGround.h"
#include "ContentsEnum.h"

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
	LoginBtnRenderer_ = CreateRenderer((int)UIType::BackGroundButton, RenderPivot::CENTER, float4{ -68.0f,274.0f });
	ExitBtnRenderer_ = CreateRenderer((int)UIType::BackGroundButton, RenderPivot::CENTER, float4{ 71.0f,274.0f });
	Change1PRenderer_ = CreateRenderer((int)UIType::BackGroundButton, RenderPivot::CENTER, float4{ -208.0f,173.0f });
	Change2PRenderer_ = CreateRenderer((int)UIType::BackGroundButton, RenderPivot::CENTER, float4{ 208.0f,173.0f });


	LoginBtnRenderer_->CreateAnimation("LoginBtn.bmp", "LoginBtn_Idle", 0, 0, 0.1f, false);
	LoginBtnRenderer_->CreateAnimation("LoginBtn.bmp", "LoginBtn_Select", 1, 1, 0.1f, false);
	LoginBtnRenderer_->CreateAnimation("LoginBtn.bmp", "LoginBtn_Click", 2, 2, 0.1f, false);
	ExitBtnRenderer_->CreateAnimation("ExitBtn.bmp", "ExitBtn_Idle", 0, 0, 0.1f, false);
	ExitBtnRenderer_->CreateAnimation("ExitBtn.bmp", "ExitBtn_Select", 1, 1, 0.1f, false);
	ExitBtnRenderer_->CreateAnimation("ExitBtn.bmp", "ExitBtn_Click", 2, 2, 0.1f, false);
	Change1PRenderer_->CreateAnimation("1pBtn.bmp", "1pBtn_Idle", 0, 0, 0.1f, false);
	Change1PRenderer_->CreateAnimation("1pBtn.bmp", "1pBtn_Select", 1, 1, 0.1f, false);
	Change1PRenderer_->CreateAnimation("1pBtn.bmp", "1pBtn_Click", 2, 2, 0.1f, false);
	Change2PRenderer_->CreateAnimation("2pBtn.bmp", "2pBtn_Idle", 0, 0, 0.1f, false);
	Change2PRenderer_->CreateAnimation("2pBtn.bmp", "2pBtn_Select", 1, 1, 0.1f, false);
	Change2PRenderer_->CreateAnimation("2pBtn.bmp", "2pBtn_Click", 2, 2, 0.1f, false);

	LoginBtnRenderer_->ChangeAnimation("LoginBtn_Idle");
	ExitBtnRenderer_->ChangeAnimation("ExitBtn_Idle");
	Change1PRenderer_->ChangeAnimation("1pBtn_Idle");
	Change2PRenderer_->ChangeAnimation("2pBtn_Idle");


	Change1PCollision_ = CreateCollision("Change1P", { 80 ,80 }, {-215, 173});
	Change2PCollision_ = CreateCollision("Change2P", { 80 ,80 }, { 215, 173 });
	LoginBtnCollision_ = CreateCollision("Login", { 90 ,30 }, { -68.0f,274.0f });
	ExitBtnCollision_ = CreateCollision("Exit", { 90 ,30 }, { 71.0f,274.0f });

	createRoomBackGround_ = GetLevel()->CreateActor<CreateRoomBackGround>((int)UIType::PopUp);
	createRoomBackGround_->Off();
}

void LoginBackGround::Update()
{
	//1p 버튼
	if (true == Change1PCollision_->CollisionCheck("MouseCol")) {

		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			Change1PRenderer_->ChangeAnimation("1pBtn_Click");
		}
		else if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			LoginBackGroundRenderer_->SetImage("LoginUI_1P.bmp");
			Change1PRenderer_->SetPivot({ -208,173 });
			Change2PRenderer_->SetPivot({ 208, 173 });
			Change1PCollision_->SetPivot({ -208, 173 });
			Change2PCollision_->SetPivot({ 208, 173 });
		}
		else {
			Change1PRenderer_->ChangeAnimation("1pBtn_Select");
		}
	}
	else
	{
		Change1PRenderer_->ChangeAnimation("1pBtn_Idle");
	}




	if (true == Change2PCollision_->CollisionCheck("MouseCol")) {

		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			Change2PRenderer_->ChangeAnimation("2pBtn_Click");
		}
		else if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			LoginBackGroundRenderer_->SetImage("LoginUI_2P.bmp");
			Change1PRenderer_->SetPivot({ -345, 173 });
			Change2PRenderer_->SetPivot({ 345, 173 });
			Change1PCollision_->SetPivot({ -345, 173 });
			Change2PCollision_->SetPivot({ 345, 173 });
		}
		else {
			Change2PRenderer_->ChangeAnimation("2pBtn_Select");
		}
	}
	else
	{
		Change2PRenderer_->ChangeAnimation("2pBtn_Idle");
	}
	

	
	//로그인 버튼
	if (true == LoginBtnCollision_->CollisionCheck("MouseCol")) {

		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			LoginBtnRenderer_->ChangeAnimation("LoginBtn_Click");
		}
		else if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			createRoomBackGround_->On();
		}
		else {
			LoginBtnRenderer_->ChangeAnimation("LoginBtn_Select");
		}
	}
	else
	{
		LoginBtnRenderer_->ChangeAnimation("LoginBtn_Idle");
	}
	


	//나가기 버튼
	if (true == ExitBtnCollision_->CollisionCheck("MouseCol")) {


		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			ExitBtnRenderer_->ChangeAnimation("ExitBtn_Click");
		}
		else if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GameEngineWindow::GetInst().Off();
		}
		else {
			ExitBtnRenderer_->ChangeAnimation("ExitBtn_Select");
		}
	}
	else
	{
		ExitBtnRenderer_->ChangeAnimation("ExitBtn_Idle");
	}



}