#include "ChoiceMap.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"

ChoiceMap::ChoiceMap()
	: ChoiceMapRenderer_(nullptr)
{
}

ChoiceMap::~ChoiceMap()
{
}

void ChoiceMap::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	ChoiceMapRenderer_ = CreateRenderer((int)UIType::PopUp);
	ChoiceMapRenderer_1 = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ -178.0f,0.0f });
	ChoiceMapRenderer_2 = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ 0.0f, 0.0f });
	ChoiceMapRenderer_3 = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ 178.0f,0.0f });
	ConfirmBtnRenderer_ = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ -59.0f,216.0f });
	CancelBtnRenderer_ = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ 58.0f,216.0f });


	//랜더러
	ChoiceMapRenderer_->SetImage("ChoiceMapUI.bmp");
	ChoiceMapRenderer_1->SetImage("ChoiceMap_Village.bmp");
	ChoiceMapRenderer_2->SetImage("ChoiceMap_Tumb.bmp");
	ChoiceMapRenderer_3->SetImage("ChoiceMap_Camp.bmp");
	ChoiceMapRenderer_1->SetAlpha(130);
	ChoiceMapRenderer_2->SetAlpha(130);
	ChoiceMapRenderer_3->SetAlpha(130);
	ConfirmBtnRenderer_->CreateAnimation("ConfirmBtn.bmp", "ConfirmBtn_Idle", 4, 4, 0.1f, true);
	ConfirmBtnRenderer_->CreateAnimation("ConfirmBtn.bmp", "ConfirmBtn_Select", 0, 3, 0.1f, true);
	CancelBtnRenderer_->CreateAnimation("CancelBtn.bmp", "CancelBtn_Idle", 4, 4, 0.1f, true);
	CancelBtnRenderer_->CreateAnimation("CancelBtn.bmp", "CancelBtn_Select", 0, 3, 0.1f, true);
	ConfirmBtnRenderer_->ChangeAnimation("ConfirmBtn_Idle");
	CancelBtnRenderer_->ChangeAnimation("CancelBtn_Idle");


	//콜리젼
	ChoiceMapCollision_1 = CreateCollision("ChoiceMapCollision_1", { 160.0f,350.0f }, float4{ -178.0f,0.0f });
	ChoiceMapCollision_2 = CreateCollision("ChoiceMapCollision_2", { 160.0f,350.0f }, float4{ 0.0f, 0.0f });
	ChoiceMapCollision_3 = CreateCollision("ChoiceMapCollision_3", { 160.0f,350.0f }, float4{ 178.0f,0.0f });
	ConfirmBtnCollision_ = CreateCollision("ConfirmBtn", { 90.0f,30.0f }, float4{ -59.0f,216.0f });
	CancelBtnCollision_ = CreateCollision("CancelBtn", { 90.0f,30.0f }, float4{ 58.0f,216.0f });

}

void ChoiceMap::Update()
{


	if (true == ChoiceMapCollision_1->CollisionCheck("MouseCol"))
	{
		ChoiceMapRenderer_1->SetAlpha(190);

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			TempChoiceMap_ = 1;
		}
	}
	else {
		ChoiceMapRenderer_1->SetAlpha(130);
	}
	

	if (true == ChoiceMapCollision_2->CollisionCheck("MouseCol"))
	{
		ChoiceMapRenderer_2->SetAlpha(190);

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			TempChoiceMap_ = 2;
		}
	}
	else {
		ChoiceMapRenderer_2->SetAlpha(130);
	}

	if (true == ChoiceMapCollision_3->CollisionCheck("MouseCol"))
	{
		ChoiceMapRenderer_3->SetAlpha(190);

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			TempChoiceMap_ = 3;
		}
	}
	else {
		ChoiceMapRenderer_3->SetAlpha(130);
	}
	
	if (TempChoiceMap_ == 1) {
		ChoiceMapRenderer_1->SetAlpha(255);
	}
	else if (TempChoiceMap_ == 2) {
		ChoiceMapRenderer_2->SetAlpha(255);
	}
	else if (TempChoiceMap_ == 3) {
		ChoiceMapRenderer_3->SetAlpha(255);
	}




	/////////////////확인 버튼///////////////
	if (true == ConfirmBtnCollision_->CollisionCheck("MouseCol"))
	{
		ConfirmBtnRenderer_->ChangeAnimation("ConfirmBtn_Select");
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			ChoiceMap_ = TempChoiceMap_;
			this->Off();
		}
	}
	else {
		ConfirmBtnRenderer_->ChangeAnimation("ConfirmBtn_Idle");
	}


	/////////////////취소 버튼///////////////
	if (true == CancelBtnCollision_->CollisionCheck("MouseCol"))
	{
		CancelBtnRenderer_->ChangeAnimation("CancelBtn_Select");
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			TempChoiceMap_ = ChoiceMap_;
			this->Off();
		}
	}
	else {
		CancelBtnRenderer_->ChangeAnimation("CancelBtn_Idle");
	}
}