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
	, StatusRenderer(nullptr)
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
	SetPosition({ 670, 95 });
	RoomCharacterRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, { -594.0f, 48.0f });
	RoomCharacterRenderer->SetImage("RandomCharacter.bmp");
	StatusRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, { -294.0f, 22.0f });
	StatusRenderer->SetImage("RandomStatusUI.bmp");
	StatusRenderer->Off();
	BannerRenderer = CreateRenderer((int)UIType::PopUp, RenderPivot::CENTER, { -40.0f, -50.0f });
	BannerRenderer->SetImage("RandomSelect_Image.bmp");
	RandomRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ -146.0f, -8.0f });
	BazziRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ -72.0f, -7.0f });
	DaoRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ -3.0f,0 });
	MaridRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ 68.0f, -5.0f });

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

	StatusUISet(); 
	BannerSet();
}

void RoomCharaterSelectUI::StatusUISet()
{
	if (true == RandomCollision->CollisionCheck("MouseCol"))
	{
		StatusRenderer->SetPivot({ -291.0f, 15.0f });
		StatusRenderer->SetImage("RandomStatusUI.bmp");
		StatusRenderer->On();
	}

	else if (true == DaoCollision->CollisionCheck("MouseCol"))
	{
		StatusRenderer->SetPivot({ -294.0f, 22.0f });
		StatusRenderer->SetImage("DaoStatusUI.bmp");
		StatusRenderer->On();
	}

	else if (true == BazziCollision->CollisionCheck("MouseCol"))
	{
		StatusRenderer->SetPivot({ -294.0f, 22.0f });
		StatusRenderer->SetImage("BazziStatusUI.bmp");
		StatusRenderer->On();
	}

	else if (true == MaridCollision->CollisionCheck("MouseCol"))
	{
		StatusRenderer->SetPivot({ -294.0f, 22.0f });
		StatusRenderer->SetImage("MaridStatusUI.bmp");
		StatusRenderer->On();
	}

	if (false == RandomCollision->CollisionCheck("MouseCol") &&
		false == MaridCollision->CollisionCheck("MouseCol") &&
		false == DaoCollision->CollisionCheck("MouseCol") &&
		false == BazziCollision->CollisionCheck("MouseCol"))
	{
		StatusRenderer->Off();
	}
}

void RoomCharaterSelectUI::BannerSet()
{
	switch (SelectCharater)
	{
	case 0:
		BannerRenderer->SetPivot({ -40.0f, -50.0f });
		BannerRenderer->SetImage("RandomSelect_Image.bmp");
		RoomCharacterRenderer->SetImage("RandomCharacter.bmp");
		break;
	case 1:
		BannerRenderer->SetPivot({ -42.0f, -49.0f });
		BannerRenderer->SetImage("BazziSelect_Image.bmp");
		RoomCharacterRenderer->SetImage("BazziCharacter.bmp");
		break;
	case 2:
		BannerRenderer->SetPivot({ -42.0f, -49.0f });
		BannerRenderer->SetImage("DaoSelect_Image.bmp");
		break;
	case 3:
		BannerRenderer->SetPivot({ -42.0f, -49.0f });
		BannerRenderer->SetImage("MaridSelect_Image.bmp");
		break;
	default:
		break;
	}
}