#include "RoomCharaterSelectUI.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"


RoomCharaterSelectUI::RoomCharaterSelectUI()
	: BazziRenderer(nullptr)
	, DaoRenderer(nullptr)
	, MaridRenderer(nullptr)
	, BazziCollision(nullptr)
	, DaoCollision(nullptr)
	, MaridCollision(nullptr)
	, SelectCharater(0)
{
}

RoomCharaterSelectUI::~RoomCharaterSelectUI()
{
}

void RoomCharaterSelectUI::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	BazziRenderer = CreateRenderer((int)UIType::PopUpButton,RenderPivot::CENTER, float4{ -70.0f, -8.0f });
	DaoRenderer = CreateRenderer((int)UIType::PopUpButton , RenderPivot::CENTER, float4{0,0 });
	MaridRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ 70.0f, -4.0f  });

	BazziRenderer->CreateAnimation("BazziCharSelecter.bmp", "BazziCharSelecter_Idle", 0, 0, 0.1f, false);
	BazziRenderer->CreateAnimation("BazziCharSelecter.bmp", "BazziCharSelecter_Approach", 0, 6, 0.1f, false);
	BazziRenderer->CreateAnimation("BazziCharSelecter.bmp", "BazziCharSelecter_Cilck", 7, 8, 0.1f, false);
	BazziRenderer->CreateAnimation("BazziCharSelecter.bmp", "BazziCharSelecter_CilckUp", 9, 11, 0.1f, false);

	DaoRenderer->CreateAnimation("DaoCharSelecter.bmp", "DaoCharSelecter_Idle", 0, 0, 0.1f, false);
	DaoRenderer->CreateAnimation("DaoCharSelecter.bmp", "DaoCharSelecter_Approach", 0, 5, 0.1f, false);
	DaoRenderer->CreateAnimation("DaoCharSelecter.bmp", "DaoCharSelecter_Cilck", 6, 7, 0.1f, false);
	DaoRenderer->CreateAnimation("DaoCharSelecter.bmp", "DaoCharSelecter_CilckUp", 8, 9, 0.1f, false);

	MaridRenderer->CreateAnimation("MaridCharSelecter.bmp", "MaridCharSelecter_Idle", 0, 0, 0.1f, false);
	MaridRenderer->CreateAnimation("MaridCharSelecter.bmp", "MaridCharSelecter_Approach", 0, 6, 0.1f, false);
	MaridRenderer->CreateAnimation("MaridCharSelecter.bmp", "MaridCharSelecter_Cilck", 7, 8, 0.1f, false);
	MaridRenderer->CreateAnimation("MaridCharSelecter.bmp", "MaridCharSelecter_CilckUp", 9, 11, 0.1f, false);

	BazziCollision = CreateCollision("CharSelecter", { 64,50 } ,{-74.0f, 8.0f});
	DaoCollision = CreateCollision("CharSelecter", { 64,50 } , { -4.0f, 8.0f });
	MaridCollision = CreateCollision("CharSelecter", { 64,50 } , {66.0f, 8.0f});


	BazziRenderer->ChangeAnimation("BazziCharSelecter_CilckUp");
	DaoRenderer->ChangeAnimation("DaoCharSelecter_Idle");
	MaridRenderer->ChangeAnimation("MaridCharSelecter_Idle");

	SelectCharater = 1;
}

void RoomCharaterSelectUI::Update()
{
	if (SelectCharater != 1)
	{
		if (true == BazziCollision->CollisionCheck("MouseCol"))
		{
			BazziRenderer->ChangeAnimation("BazziCharSelecter_Approach");
		}


		else if (false == BazziCollision->CollisionCheck("MouseCol"))
		{
			BazziRenderer->ChangeAnimation("BazziCharSelecter_Idle");
		}

		if(true == BazziCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			BazziRenderer->ChangeAnimation("BazziCharSelecter_Cilck");
		}

		if (true == BazziCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			BazziRenderer->ChangeAnimation("BazziCharSelecter_CilckUp");
			SelectCharater = 1;
		}
	}

	if (SelectCharater != 2)
	{

		if (true == DaoCollision->CollisionCheck("MouseCol"))
		{
			DaoRenderer->ChangeAnimation("DaoCharSelecter_Approach");
		}

		else if (false == DaoCollision->CollisionCheck("MouseCol"))
		{
			DaoRenderer->ChangeAnimation("DaoCharSelecter_Idle");
		}

		if (true == DaoCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			DaoRenderer->ChangeAnimation("DaoCharSelecter_Cilck");

		}

		if (true == DaoCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			DaoRenderer->ChangeAnimation("DaoCharSelecter_CilckUp");
			SelectCharater = 2;
		}
	}

	if (SelectCharater != 3)
	{

		if (true == MaridCollision->CollisionCheck("MouseCol"))
		{
			MaridRenderer->ChangeAnimation("MaridCharSelecter_Approach");
		}


		else if (false == MaridCollision->CollisionCheck("MouseCol"))
		{
			MaridRenderer->ChangeAnimation("MaridCharSelecter_Idle");
		}

		if (true == MaridCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			MaridRenderer->ChangeAnimation("MaridCharSelecter_Cilck");

		}
		if (true == MaridCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			MaridRenderer->ChangeAnimation("MaridCharSelecter_CilckUp");
			SelectCharater = 3;
		}
	}
}