#include "Mypage.h"
#include "GlobalUIName.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"
#include "GlobalUIName.h"

Mypage::Mypage()
	: MypageRenderer_(nullptr)
{
}

Mypage::~Mypage()
{
}

void Mypage::Start()
{
	LevelRegist("Mypage");
	SetPosition(GameEngineWindow::GetScale().Half());
	MypageRenderer_ = CreateRenderer((int)UIType::Time);
	MypageRenderer_->SetImage("MyPage.bmp");

	BubbleSelectRenderer_1 = CreateRenderer((int)UIType::Time);
	BubbleSelectRenderer_1->SetImage("BubbleSelect.bmp");
	BubbleSelectRenderer_1->SetPivot(float4{-210.0f,-110.0f});
	BubbleSelectRenderer_1->SetAlpha(100);

	BubbleSelectRenderer_2 = CreateRenderer((int)UIType::Time);
	BubbleSelectRenderer_2->SetImage("BubbleSelect.bmp");
	BubbleSelectRenderer_2->SetPivot(float4{ -70.0f,-110.0f });
	BubbleSelectRenderer_2->SetAlpha(100);

	BubbleSelectRenderer_3 = CreateRenderer((int)UIType::Time);
	BubbleSelectRenderer_3->SetImage("BubbleSelect.bmp");
	BubbleSelectRenderer_3->SetPivot(float4{ 70.0f,-110.0f });
	BubbleSelectRenderer_3->SetAlpha(100);


	BubbleSelectRenderer_4 = CreateRenderer((int)UIType::Time);
	BubbleSelectRenderer_4->SetImage("BubbleSelect.bmp");
	BubbleSelectRenderer_4->SetPivot(float4{ 210.0f,-110.0f });
	BubbleSelectRenderer_4->SetAlpha(100);


	BubbleSelectRenderer_5 = CreateRenderer((int)UIType::Time);
	BubbleSelectRenderer_5->SetImage("BubbleSelect.bmp");
	BubbleSelectRenderer_5->SetPivot(float4{ -210.0f,50.0f });
	BubbleSelectRenderer_5->SetAlpha(100);

	BubbleSelectRenderer_6 = CreateRenderer((int)UIType::Time);
	BubbleSelectRenderer_6->SetImage("BubbleSelect.bmp");
	BubbleSelectRenderer_6->SetPivot(float4{ -70.0f,50.0f });
	BubbleSelectRenderer_6->SetAlpha(100);

	BubbleSelectRenderer_7 = CreateRenderer((int)UIType::Time);
	BubbleSelectRenderer_7->SetImage("BubbleSelect.bmp");
	BubbleSelectRenderer_7->SetPivot(float4{ 70.0f,50.0f });
	BubbleSelectRenderer_7->SetAlpha(100);


	BubbleSelectRenderer_8 = CreateRenderer((int)UIType::Time);
	BubbleSelectRenderer_8->SetImage("BubbleSelect.bmp");
	BubbleSelectRenderer_8->SetPivot(float4{ 210.0f,50.0f });
	BubbleSelectRenderer_8->SetAlpha(100);


	///////////////////////////////////////////////////////////////


	BubbleRenderer_1 = CreateRenderer((int)UIType::Time);
	BubbleRenderer_1->SetPivot(float4{ -210.0f,-95.0f });
	BubbleRenderer_1->CreateAnimation("Bubble_Default.bmp", "BubbleDefault_Idle", 0, 0, 0.2f, false);
	BubbleRenderer_1->CreateAnimation("Bubble_Default.bmp", "BubbleDefault_Select", 0, 3, 0.2f, true);
	BubbleRenderer_1->ChangeAnimation("BubbleDefault_Select");


	BubbleRenderer_2 = CreateRenderer((int)UIType::Time);
	BubbleRenderer_2->SetPivot(float4{ -70.0f,-95.0f });
	BubbleRenderer_2->CreateAnimation("Bubble_1.bmp", "Bubble1_Idle", 0, 0, 0.2f, false);
	BubbleRenderer_2->CreateAnimation("Bubble_1.bmp", "Bubble1_Select", 0, 3, 0.2f, true);
	BubbleRenderer_2->ChangeAnimation("Bubble1_Select");


	BubbleRenderer_3 = CreateRenderer((int)UIType::Time);
	BubbleRenderer_3->SetPivot(float4{ 70.0f,-95.0f });
	BubbleRenderer_3->CreateAnimation("Bubble_2.bmp", "Bubble2_Idle", 0, 0, 0.2f, false);
	BubbleRenderer_3->CreateAnimation("Bubble_2.bmp", "Bubble2_Select", 0, 3, 0.2f, true);
	BubbleRenderer_3->ChangeAnimation("Bubble2_Select");


	BubbleRenderer_4 = CreateRenderer((int)UIType::Time);
	BubbleRenderer_4->SetPivot(float4{ 210.0f,-95.0f });
	BubbleRenderer_4->CreateAnimation("Bubble_3.bmp", "Bubble3_Idle", 0, 0, 0.2f, false);
	BubbleRenderer_4->CreateAnimation("Bubble_3.bmp", "Bubble3_Select", 0, 3, 0.2f, true);
	BubbleRenderer_4->ChangeAnimation("Bubble3_Select");


	BubbleRenderer_5 = CreateRenderer((int)UIType::Time);
	BubbleRenderer_5->SetPivot(float4{ -210.0f,65.0f });
	BubbleRenderer_5->CreateAnimation("Bubble_4.bmp", "Bubble4_Idle", 0, 0, 0.2f, false);
	BubbleRenderer_5->CreateAnimation("Bubble_4.bmp", "Bubble4_Select", 0, 3, 0.2f, true);
	BubbleRenderer_5->ChangeAnimation("Bubble4_Select");


	BubbleRenderer_6 = CreateRenderer((int)UIType::Time);
	BubbleRenderer_6->SetPivot(float4{ -70.0f,65.0f });
	BubbleRenderer_6->CreateAnimation("Bubble_5.bmp", "Bubble5_Idle", 0, 0, 0.2f, false);
	BubbleRenderer_6->CreateAnimation("Bubble_5.bmp", "Bubble5_Select", 0, 3, 0.2f, true);
	BubbleRenderer_6->ChangeAnimation("Bubble5_Select");


	BubbleRenderer_7 = CreateRenderer((int)UIType::Time);
	BubbleRenderer_7->SetPivot(float4{ 70.0f, 65.0f });
	BubbleRenderer_7->CreateAnimation("Bubble_6.bmp", "Bubble6_Idle", 0, 0, 0.2f, false);
	BubbleRenderer_7->CreateAnimation("Bubble_6.bmp", "Bubble6_Select", 0, 3, 0.2f, true);
	BubbleRenderer_7->ChangeAnimation("Bubble6_Select");


	BubbleRenderer_8 = CreateRenderer((int)UIType::Time);
	BubbleRenderer_8->SetPivot(float4{ 210.0f, 65.0f });
	BubbleRenderer_8->CreateAnimation("Bubble_Dark.bmp", "BubbleDark_Idle", 0, 0, 0.2f, false);
	BubbleRenderer_8->CreateAnimation("Bubble_Dark.bmp", "BubbleDark_Select", 0, 3, 0.2f, true);
	BubbleRenderer_8->ChangeAnimation("BubbleDark_Select");
	

	MyPageCloseBtnRenderer_ = CreateRenderer((int)UIType::Time);
	MyPageCloseBtnRenderer_->SetPivot(float4{ 0.0f, 236.0f });
	MyPageCloseBtnRenderer_->CreateAnimation("MyPageCloseBtn.bmp", "MyPageCloseBtn_Idle", 0, 0, 0.2f, false);
	MyPageCloseBtnRenderer_->CreateAnimation("MyPageCloseBtn.bmp", "MyPageCloseBtn_Select", 1, 2, 0.2f, true);
	MyPageCloseBtnRenderer_->CreateAnimation("MyPageCloseBtn.bmp", "MyPageCloseBtn_Click", 3, 3, 0.2f, false);
	MyPageCloseBtnRenderer_->ChangeAnimation("MyPageCloseBtn_Idle");



	BubbleNameRenderer_1 = CreateRenderer((int)UIType::Time);
	BubbleNameRenderer_1->SetImage("BubbleName1.bmp");
	BubbleNameRenderer_1->SetPivot(float4{ -210.0f,-63.0f });

	BubbleNameRenderer_2 = CreateRenderer((int)UIType::Time);
	BubbleNameRenderer_2->SetImage("BubbleName2.bmp");
	BubbleNameRenderer_2->SetPivot(float4{ -70.0f,-63.0f });

	BubbleNameRenderer_3 = CreateRenderer((int)UIType::Time);
	BubbleNameRenderer_3->SetImage("BubbleName3.bmp");
	BubbleNameRenderer_3->SetPivot(float4{ 70.0f,-63.0f });

	BubbleNameRenderer_4 = CreateRenderer((int)UIType::Time);
	BubbleNameRenderer_4->SetImage("BubbleName4.bmp");
	BubbleNameRenderer_4->SetPivot(float4{ 210.0f,-63.0f });

	BubbleNameRenderer_5 = CreateRenderer((int)UIType::Time);
	BubbleNameRenderer_5->SetImage("BubbleName5.bmp");
	BubbleNameRenderer_5->SetPivot(float4{ -210.0f, 97.0f });

	BubbleNameRenderer_6 = CreateRenderer((int)UIType::Time);
	BubbleNameRenderer_6->SetImage("BubbleName6.bmp");
	BubbleNameRenderer_6->SetPivot(float4{ -70.0f, 97.0f });

	BubbleNameRenderer_7 = CreateRenderer((int)UIType::Time);
	BubbleNameRenderer_7->SetImage("BubbleName7.bmp");
	BubbleNameRenderer_7->SetPivot(float4{ 70.0f, 97.0f });

	BubbleNameRenderer_8 = CreateRenderer((int)UIType::Time);
	BubbleNameRenderer_8->SetImage("BubbleName8.bmp");
	BubbleNameRenderer_8->SetPivot(float4{ 210.0f, 97.0f });


	BubbleCheckRenderer_1P = CreateRenderer((int)UIType::Time);
	BubbleCheckRenderer_1P->SetImage("BubbleCheck_1P.bmp");
	BubbleCheckRenderer_1P->SetPivot(float4{ -250.0f,-160.0f });


	BubbleCheckRenderer_2P = CreateRenderer((int)UIType::Time);
	BubbleCheckRenderer_2P->SetImage("BubbleCheck_2P.bmp");
	BubbleCheckRenderer_2P->SetPivot(float4{ -170.0f,-160.0f });
	BubbleCheckRenderer_2P->Off();


	/// Collision ///

	BubbleSelectCollision_1 = CreateCollision("BubbleSelect1", { 130.0f,130.0f }, float4{ -210.0f,-110.0f });
	BubbleSelectCollision_2 = CreateCollision("BubbleSelect2", { 130.0f,130.0f }, float4{ -70.0f,-110.0f });
	BubbleSelectCollision_3 = CreateCollision("BubbleSelect3", { 130.0f,130.0f }, float4{ 70.0f,-110.0f });
	BubbleSelectCollision_4 = CreateCollision("BubbleSelect4", { 130.0f,130.0f }, float4{ 210.0f,-110.0f });
	BubbleSelectCollision_5 = CreateCollision("BubbleSelect5", { 130.0f,130.0f }, float4{ -210.0f,50.0f });
	BubbleSelectCollision_6 = CreateCollision("BubbleSelect6", { 130.0f,130.0f }, float4{ -70.0f,50.0f });
	BubbleSelectCollision_7 = CreateCollision("BubbleSelect7", { 130.0f,130.0f }, float4{ 70.0f,50.0f });
	BubbleSelectCollision_8 = CreateCollision("BubbleSelect8", { 130.0f,130.0f }, float4{ 210.0f,50.0f });

	MyPageCloseBtnCollision_ = CreateCollision("MyPageCloseBtn", { 130.0f,30.0f }, float4{ 0.0f, 236.0f });


}

void Mypage::Update()
{

	if (true == BubbleSelectCollision_1->CollisionCheck("MouseCol"))
	{
		BubbleSelectRenderer_1->SetAlpha(190);

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_1P("BubbleDefault");
		}
		if (true == GameEngineInput::GetInst()->IsUp("RightMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_2P("BubbleDefault");
		}
	}
	else {
		BubbleSelectRenderer_1->SetAlpha(100);
	}





	if (true == BubbleSelectCollision_2->CollisionCheck("MouseCol"))
	{
		BubbleSelectRenderer_2->SetAlpha(190);

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_1P("Bubble1");
		}
		if (true == GameEngineInput::GetInst()->IsUp("RightMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_2P("Bubble1");
		}
	}
	else {
		BubbleSelectRenderer_2->SetAlpha(100);
	}





	if (true == BubbleSelectCollision_3->CollisionCheck("MouseCol"))
	{
		BubbleSelectRenderer_3->SetAlpha(190);

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_1P("Bubble2");
		}
		if (true == GameEngineInput::GetInst()->IsUp("RightMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_2P("Bubble2");
		}
	}
	else {
		BubbleSelectRenderer_3->SetAlpha(100);
	}





	if (true == BubbleSelectCollision_4->CollisionCheck("MouseCol"))
	{
		BubbleSelectRenderer_4->SetAlpha(190);

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_1P("Bubble3");
		}
		if (true == GameEngineInput::GetInst()->IsUp("RightMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_2P("Bubble3");
		}
	}
	else {
		BubbleSelectRenderer_4->SetAlpha(100);
	}





	if (true == BubbleSelectCollision_5->CollisionCheck("MouseCol"))
	{
		BubbleSelectRenderer_5->SetAlpha(190);

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_1P("Bubble4");
		}
		if (true == GameEngineInput::GetInst()->IsUp("RightMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_2P("Bubble4");
		}
	}
	else {
		BubbleSelectRenderer_5->SetAlpha(100);
	}




	if (true == BubbleSelectCollision_6->CollisionCheck("MouseCol"))
	{
		BubbleSelectRenderer_6->SetAlpha(190);

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_1P("Bubble5");
		}
		if (true == GameEngineInput::GetInst()->IsUp("RightMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_2P("Bubble5");
		}
	}
	else {
		BubbleSelectRenderer_6->SetAlpha(100);
	}




	if (true == BubbleSelectCollision_7->CollisionCheck("MouseCol"))
	{
		BubbleSelectRenderer_7->SetAlpha(190);

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_1P("Bubble6");
		}
		if (true == GameEngineInput::GetInst()->IsUp("RightMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_2P("Bubble6");
		}
	}
	else {
		BubbleSelectRenderer_7->SetAlpha(100);
	}





	if (true == BubbleSelectCollision_8->CollisionCheck("MouseCol"))
	{
		BubbleSelectRenderer_8->SetAlpha(190);

		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_1P("BubbleDark");
		}
		if (true == GameEngineInput::GetInst()->IsUp("RightMouse"))
		{
			GlobalUIName::GetInst()->SetBubble_2P("BubbleDark");
		}
	}
	else {
		BubbleSelectRenderer_8->SetAlpha(100);
	}



	//닫기버튼

	if (true == MyPageCloseBtnCollision_->CollisionCheck("MouseCol"))
	{
		MyPageCloseBtnRenderer_->ChangeAnimation("MyPageCloseBtn_Select");

		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			MyPageCloseBtnRenderer_->ChangeAnimation("MyPageCloseBtn_Click");
		}
		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			this->Off();
		}
	}
	else {
		MyPageCloseBtnRenderer_->ChangeAnimation("MyPageCloseBtn_Idle");
	}


	//////// 1P, 2P 체크//////////

	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		BubbleCheckRenderer_2P->On();
	}
	else
	{
		BubbleCheckRenderer_2P->Off();
	}

	//1P
	if (GlobalUIName::GetInst()->GetBubble_1P() == "BubbleDefault")
	{
		BubbleCheckRenderer_1P->SetPivot(float4{ -250.0f,-160.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_1P() == "Bubble1")
	{
		BubbleCheckRenderer_1P->SetPivot(float4{ -110.0f,-160.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_1P() == "Bubble2")
	{
		BubbleCheckRenderer_1P->SetPivot(float4{ 30.0f,-160.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_1P() == "Bubble3")
	{
		BubbleCheckRenderer_1P->SetPivot(float4{ 170.0f,-160.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_1P() == "Bubble4")
	{
		BubbleCheckRenderer_1P->SetPivot(float4{ -250.0f, 0.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_1P() == "Bubble5")
	{
		BubbleCheckRenderer_1P->SetPivot(float4{ -110.0f, 0.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_1P() == "Bubble6")
	{
		BubbleCheckRenderer_1P->SetPivot(float4{ 30.0f, 0.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_1P() == "BubbleDark")
	{
		BubbleCheckRenderer_1P->SetPivot(float4{ 170.0f, 0.0f });
	}

	//2P
	if (GlobalUIName::GetInst()->GetBubble_2P() == "BubbleDefault")
	{
		BubbleCheckRenderer_2P->SetPivot(float4{ -170.0f,-160.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_2P() == "Bubble1")
	{
		BubbleCheckRenderer_2P->SetPivot(float4{ -30.0f,-160.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_2P() == "Bubble2")
	{
		BubbleCheckRenderer_2P->SetPivot(float4{ 110.0f,-160.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_2P() == "Bubble3")
	{
		BubbleCheckRenderer_2P->SetPivot(float4{ 250.0f,-160.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_2P() == "Bubble4")
	{
		BubbleCheckRenderer_2P->SetPivot(float4{ -170.0f, 0.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_2P() == "Bubble5")
	{
		BubbleCheckRenderer_2P->SetPivot(float4{ -30.0f, 0.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_2P() == "Bubble6")
	{
		BubbleCheckRenderer_2P->SetPivot(float4{ 110.0f, 0.0f });
	}
	else if (GlobalUIName::GetInst()->GetBubble_2P() == "BubbleDark")
	{
		BubbleCheckRenderer_2P->SetPivot(float4{ 250.0f, 0.0f });
	}
}

void Mypage::Render()
{
	
}