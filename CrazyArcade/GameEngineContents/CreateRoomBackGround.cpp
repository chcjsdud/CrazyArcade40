#include "CreateRoomBackGround.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"

CreateRoomBackGround::CreateRoomBackGround()
	: CreateRoomBackGroundRenderer_(nullptr)
{
}

CreateRoomBackGround::~CreateRoomBackGround()
{
}

void CreateRoomBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	CreateRoomBackGroundRenderer_ = CreateRenderer("CreateRoomUl.bmp");


	NormalModeBtnRenderer_ = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ -100.0f,-40.0f });
	MonsterModeBtnRenderer_ = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ 100.0f,-40.0f });
	ConfirmBtnRenderer_ = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ -57.0f,178.0f });
	CancelBtnRenderer_ = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ 58.0f,178.0f });

	NormalModeBtnRenderer_->CreateAnimation("NormalBtn_Animation.bmp", "NormalModeBtn_Idle", 0, 0, 0.1f, true);
	NormalModeBtnRenderer_->CreateAnimation("NormalBtn_Animation.bmp", "NormalModeBtn_Select", 0, 4, 0.1f, false);
	MonsterModeBtnRenderer_->CreateAnimation("MonsterBtn_Animation.bmp", "MonsterModeBtn_Idle", 0, 0, 0.1f, true);
	MonsterModeBtnRenderer_->CreateAnimation("MonsterBtn_Animation.bmp", "MonsterModeBtn_Select", 0, 4, 0.1f, false);
	ConfirmBtnRenderer_->CreateAnimation("ConfirmBtn.bmp", "ConfirmBtn_Idle", 4, 4, 0.1f, true);
	ConfirmBtnRenderer_->CreateAnimation("ConfirmBtn.bmp", "ConfirmBtn_Select", 0, 3, 0.1f, true);
	ConfirmBtnRenderer_->CreateAnimation("ConfirmBtn.bmp", "ConfirmBtn_Disable", 4, 4, 0.1f, true);
	ConfirmBtnRenderer_->CreateAnimation("ConfirmBtn.bmp", "ConfirmBtn_Click", 5, 5, 0.1f, true);
	CancelBtnRenderer_->CreateAnimation("CancelBtn.bmp", "CancelBtn_Idle", 4, 4, 0.1f, true);
	CancelBtnRenderer_->CreateAnimation("CancelBtn.bmp", "CancelBtn_Select", 0, 3, 0.1f, true);
	CancelBtnRenderer_->CreateAnimation("CancelBtn.bmp", "CancelBtn_Click", 5, 5, 0.1f, true);


	NormalModeBtnRenderer_->ChangeAnimation("NormalModeBtn_Idle");
	MonsterModeBtnRenderer_->ChangeAnimation("MonsterModeBtn_Idle");
	ConfirmBtnRenderer_->ChangeAnimation("ConfirmBtn_Idle");
	CancelBtnRenderer_->ChangeAnimation("CancelBtn_Idle");


	NormalBtnCollision_ = CreateCollision("NormalModeBtn", {110.0f,150.0f }, { -100.0f ,-40.0f });
	MonsterBtnCollision_ = CreateCollision("MonsterModeBtn", { 150.0f,150.0f }, { 100.0f ,-40.0f });
	ConfirmBtnCollision_ = CreateCollision("ConfirmBtn", { 90.0f,30.0f }, { -57.0f ,178.0f });
	CancelBtnCollision_ = CreateCollision("CancelBtn", { 90.0f,30.0f }, { 58.0f ,178.0f });

	NormalModeRenderer_ = CreateRenderer("NormalMode_Idle.bmp");
	MonsterModeRenderer_ = CreateRenderer("MonsterMode_Idle.bmp");
	NormalModeRenderer_->SetPivot(float4{-100.0f,-50.0f});
	MonsterModeRenderer_->SetPivot(float4{ 100.0f,-50.0f });
}

void CreateRoomBackGround::Update()
{
	///////////////일반 모드///////////////
	if (true == NormalBtnCollision_->CollisionCheck("MouseCol"))
	{
		if (SelectMode_ != 1) {
			NormalModeBtnRenderer_->ChangeAnimation("NormalModeBtn_Select");
		}
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			NormalModeRenderer_->SetImage("NormalMode_Select.bmp");
			NormalModeRenderer_->SetPivot(float4{ -100.0f,-55.0f });
			SelectMode_ = 1;
			
			MonsterModeRenderer_->SetImage("MonsterMode_Idle.bmp");
			MonsterModeRenderer_->SetPivot(float4{ 100.0f,-50.0f });
			MonsterModeBtnRenderer_->ChangeAnimation("MonsterModeBtn_Idle");
		}

	}
	else {
		if (SelectMode_ != 1) {
			NormalModeBtnRenderer_->ChangeAnimation("NormalModeBtn_Idle");
		}
	}

	///////////////몬스터 모드///////////////
	if (true == MonsterBtnCollision_->CollisionCheck("MouseCol"))
	{
		if (SelectMode_ != 2) {
			MonsterModeBtnRenderer_->ChangeAnimation("MonsterModeBtn_Select");
		}
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			MonsterModeRenderer_->SetImage("MonsterMode_Select.bmp");
			MonsterModeRenderer_->SetPivot(float4{ 100.0f,-55.0f });
			SelectMode_ = 2;

			NormalModeRenderer_->SetImage("NormalMode_Idle.bmp");
			NormalModeRenderer_->SetPivot(float4{ -100.0f,-50.0f });
			NormalModeBtnRenderer_->ChangeAnimation("NormalModeBtn_Idle");
		}
	}
	else {
		if (SelectMode_ != 2) {
			MonsterModeBtnRenderer_->ChangeAnimation("MonsterModeBtn_Idle");
		}
	}

	/////////////////확인 버튼///////////////
	
	if (SelectMode_ == 1 && Mode_ == PlayerMode::Play_1P)
	{
		ConfirmBtnRenderer_->ChangeAnimation("ConfirmBtn_Disable");
	}
	else
	{
		if (true == ConfirmBtnCollision_->CollisionCheck("MouseCol"))
		{
			ConfirmBtnRenderer_->ChangeAnimation("ConfirmBtn_Select");

			if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
			{
				ConfirmBtnRenderer_->ChangeAnimation("ConfirmBtn_Click");
			}
			if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
			{
				if (Mode_ == PlayerMode::Play_2P)
				{
					if (SelectMode_ == 1)
					{
						GameEngine::GetInst().ChangeLevel("RoomLevel");
					}
				}
				if (SelectMode_ == 2)
				{
					GameEngine::GetInst().ChangeLevel("MonsterRoomLevel");
				}
			}
		}
		else {

			ConfirmBtnRenderer_->ChangeAnimation("ConfirmBtn_Idle");
		}
	}
	

	/////////////////취소 버튼///////////////
	if (true == CancelBtnCollision_->CollisionCheck("MouseCol"))
	{
		CancelBtnRenderer_->ChangeAnimation("CancelBtn_Select");

		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			CancelBtnRenderer_->ChangeAnimation("CancelBtn_Click");
		}
		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			this->Off();
		}
	}
	else {
		CancelBtnRenderer_->ChangeAnimation("CancelBtn_Idle");
	}
}