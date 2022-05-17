#include "CreateRoomBackGround.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

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


	NormalModeBtnRenderer_ = CreateRenderer(5, RenderPivot::CENTER, float4{ -100.0f,-40.0f });
	MonsterModeBtnRenderer_ = CreateRenderer(5, RenderPivot::CENTER, float4{ 100.0f,-40.0f });

	NormalModeBtnRenderer_->CreateAnimation("NormalBtn_Animation.bmp", "NormalModeBtn_Idle", 0, 0, 0.1f, true);
	NormalModeBtnRenderer_->CreateAnimation("NormalBtn_Animation.bmp", "NormalModeBtn_Select", 0, 4, 0.1f, false);
	MonsterModeBtnRenderer_->CreateAnimation("MonsterBtn_Animation.bmp", "MonsterModeBtn_Idle", 0, 0, 0.1f, true);
	MonsterModeBtnRenderer_->CreateAnimation("MonsterBtn_Animation.bmp", "MonsterModeBtn_Select", 0, 4, 0.1f, false);



	NormalModeBtnRenderer_->ChangeAnimation("NormalModeBtn_Idle");
	MonsterModeBtnRenderer_->ChangeAnimation("MonsterModeBtn_Idle");


	NormalBtnCollision_ = CreateCollision("NormalModeBtn", {110.0f,150.0f }, { -100.0f ,-40.0f });
	MonsterBtnCollision_ = CreateCollision("MonsterModeBtn", { 150.0f,150.0f }, { 100.0f ,-40.0f });


	NormalModeRenderer_ = CreateRenderer("NormalMode_Idle.bmp");
	MonsterModeRenderer_ = CreateRenderer("MonsterMode_Idle.bmp");


	NormalModeRenderer_->SetPivot(float4{-100.0f,-50.0f});
	MonsterModeRenderer_->SetPivot(float4{ 100.0f,-50.0f });
}

void CreateRoomBackGround::Update()
{
	///////////////�Ϲ� ���///////////////
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

	///////////////���� ���///////////////
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
}