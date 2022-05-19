#include "RoomCharaterSelectUI.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"


RoomCharaterSelectUI::RoomCharaterSelectUI()
	: BannerRenderer(nullptr)
	, RandomRenderer(nullptr)
	, RandomCollision(nullptr)
	, BazziRenderer(nullptr)
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
	BannerRenderer = CreateRenderer((int)UIType::PopUp, RenderPivot::CENTER, { -33.0f, -49.0f });
	BannerRenderer->SetImage("BazziSelect_Image.bmp");
	RandomRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ -146.0f, -8.0f });
	BazziRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ -67.0f, -7.0f });
	DaoRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ 0,0 });
	MaridRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ 70.0f, -5.0f });

	RandomRenderer->CreateAnimation("RandomCharSelecter.bmp", "RandomCharSelecter_Idle", 0, 0, 0.1f, false);
	RandomRenderer->CreateAnimation("RandomCharSelecter.bmp", "RandomCharSelecter_Approach", 0, 6, 0.1f, false);
	RandomRenderer->CreateAnimation("RandomCharSelecter.bmp", "RandomCharSelecter_Cilck", 7, 7, 0.1f, false);
	RandomRenderer->CreateAnimation("RandomCharSelecter.bmp", "RandomCharSelecter_CilckUp", 8, 8, 0.1f, false);


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

	RandomCollision = CreateCollision("CharSelecter", { 64,50 }, { -144.0f, 8.0f });
	BazziCollision = CreateCollision("CharSelecter", { 64,50 }, { -74.0f, 8.0f });
	DaoCollision = CreateCollision("CharSelecter", { 64,50 }, { -4.0f, 8.0f });
	MaridCollision = CreateCollision("CharSelecter", { 64,50 }, { 66.0f, 8.0f });

	RandomRenderer->ChangeAnimation("RandomCharSelecter_CilckUp");
	BazziRenderer->ChangeAnimation("BazziCharSelecter_Idle");
	DaoRenderer->ChangeAnimation("DaoCharSelecter_Idle");
	MaridRenderer->ChangeAnimation("MaridCharSelecter_Idle");

	SelectCharater = 0;
}

void RoomCharaterSelectUI::Update()
{
	if (SelectCharater != 0)
	{
		if (true == RandomCollision->CollisionCheck("MouseCol"))
		{
			RandomRenderer->ChangeAnimation("RandomCharSelecter_Approach");
		}


		else if (false == RandomCollision->CollisionCheck("MouseCol"))
		{
			RandomRenderer->ChangeAnimation("RandomCharSelecter_Idle");
		}

		if (true == RandomCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			RandomRenderer->ChangeAnimation("RandomCharSelecter_Cilck");
		}

		if (true == RandomCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			RandomRenderer->ChangeAnimation("RandomCharSelecter_CilckUp");
			BannerRenderer->SetImage("BazziSelect_Image.bmp");
			SelectCharater = 0;
		}
	}

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

		if (true == BazziCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			BazziRenderer->ChangeAnimation("BazziCharSelecter_Cilck");
		}

		if (true == BazziCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			BazziRenderer->ChangeAnimation("BazziCharSelecter_CilckUp");
			BannerRenderer->SetImage("BazziSelect_Image.bmp");
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
			BannerRenderer->SetImage("DaoSelect_Image.bmp");
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
			BannerRenderer->SetImage("MaridSelect_Image.bmp");
			SelectCharater = 3;
		}
	}
}