#include "LoginBackGround.h"
#include "GlobalUIName.h"
#include "TextArea.h"
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


	NickName_One_ = GetLevel()->CreateActor<TextArea>((int)UIType::Time);
	NickName_One_->TextAreaInit({ 150.0f, 23.0f }, 13);
	NickName_One_->SetPosition(float4(442.0f + 10.0f, 16.0f + 482.0f));
	NickName_One_->On();

	NickName_Two_ = GetLevel()->CreateActor<TextArea>((int)UIType::Time);
	NickName_Two_->TextAreaInit({ 150.0f, 23.0f }, 13);
	NickName_Two_->SetPosition(float4(582.0f + 10.0f, 16.0f + 482.0f));
	NickName_Two_->Off();
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
			NickName_One_->SetPosition(float4(442.0f + 10.0f, 16.0f + 482.0f));
			NickName_One_->On();
			NickName_Two_->Off();
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



	// 2p 버튼
	if (true == Change2PCollision_->CollisionCheck("MouseCol")) {

		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			Change2PRenderer_->ChangeAnimation("2pBtn_Click");
		}
		else if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			LoginBackGroundRenderer_->SetImage("LoginUI_2P.bmp");
			NickName_One_->SetPosition(float4(298.0f + 10.0f, 16.0f + 482.0f));
			NickName_One_->On();
			NickName_Two_->On();
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
	if (false == (NickName_One_->GetText() == "" && NickName_Two_->GetText() == ""))
	{
		if (false == (NickName_Two_->IsUpdate() == true && NickName_Two_->GetText() == ""))
		{
			if (true == LoginBtnCollision_->CollisionCheck("MouseCol")) {

				if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
				{
					LoginBtnRenderer_->ChangeAnimation("LoginBtn_Click");
				}
				else if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
				{
					GlobalUIName::GetInst()->SetNickName_1(NickName_One_->GetText());
					if (false == NickName_Two_->IsUpdate())
					{
						GlobalUIName::GetInst()->SetNickName_2("");
						GlobalUIName::GetInst()->On1P();
						GlobalUIName::GetInst()->Off2P();
					}
					else {
						GlobalUIName::GetInst()->SetNickName_2(NickName_Two_->GetText());
						GlobalUIName::GetInst()->On1P();
						GlobalUIName::GetInst()->On2P();
					}

					NickName_One_->Off();
					NickName_Two_->Off();
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
		}	
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

void LoginBackGround::Render()
{
}

void LoginBackGround::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (GlobalUIName::GetInst()->GetNickName_2ConstRef() != "")
	{
		LoginBackGroundRenderer_->SetImage("LoginUI_2P.bmp");
		createRoomBackGround_->Off();
		NickName_One_->SetPosition(float4(298.0f + 10.0f, 16.0f + 482.0f));
		NickName_One_->On();
		NickName_Two_->On();
		Change1PRenderer_->SetPivot({ -345, 173 });
		Change2PRenderer_->SetPivot({ 345, 173 });
		Change1PCollision_->SetPivot({ -345, 173 });
		Change2PCollision_->SetPivot({ 345, 173 });
	}
	else 
	{
		LoginBackGroundRenderer_->SetImage("LoginUI_1P.bmp");
		NickName_One_->SetPosition(float4(442.0f + 10.0f, 16.0f + 482.0f));
		NickName_One_->On();
		NickName_Two_->Off();
		createRoomBackGround_->Off();
		Change1PRenderer_->SetPivot({ -208,173 });
		Change2PRenderer_->SetPivot({ 208, 173 });
		Change1PCollision_->SetPivot({ -208, 173 });
		Change2PCollision_->SetPivot({ 208, 173 });
	}

}