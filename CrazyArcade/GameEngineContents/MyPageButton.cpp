#include "MyPageButton.h"
#include "GlobalUIName.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"
#include "GlobalUIName.h"
#include "Mypage.h"

MyPageButton::MyPageButton()
{
}

MyPageButton::~MyPageButton()
{
}

void MyPageButton::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	MyPageBtnRenderer_ = CreateRenderer((int)UIType::PopScreen);
	MyPageBtnRenderer_->SetPivot(float4{ 285.0f, 284.0f });
	MyPageBtnRenderer_->CreateAnimation("MyPageBtn.bmp", "MyPageBtn_Idle", 0, 0, 0.2f, false);
	MyPageBtnRenderer_->CreateAnimation("MyPageBtn.bmp", "MyPageBtn_Select", 1, 2, 0.2f, true);
	MyPageBtnRenderer_->CreateAnimation("MyPageBtn.bmp", "MyPageBtn_Click", 3, 3, 0.2f, false);
	MyPageBtnRenderer_->ChangeAnimation("MyPageBtn_Idle");


	MyPageBtnCollision_ = CreateCollision("MyPageBtn", { 70.0f,22.0f }, float4{ 285.0f, 284.0f });


	mypage = GetLevel()->CreateActor<Mypage>((int)UIType::PopScreen);
	mypage->Off();
}

void MyPageButton::Update()
{

	if (true == MyPageBtnCollision_->CollisionCheck("MouseCol"))
	{
		MyPageBtnRenderer_->ChangeAnimation("MyPageBtn_Select");

		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			MyPageBtnRenderer_->ChangeAnimation("MyPageBtn_Click"); 
		}
		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			mypage->On();
		}
	}
	else {
		MyPageBtnRenderer_->ChangeAnimation("MyPageBtn_Idle");
	}

}