#include "RoomCharaterSelectUI.h"
#include <GameEngineBase/GameEngineSound.h>
#include "Player.h"
#include "GlobalUIName.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineRandom.h>
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
	, ChoiceCharacter1P(0)
	, ChoiceCharacter2P(0)
	, RoomCharacterRenderer1P(nullptr)
	, RoomCharacterRenderer2P(nullptr)
{
}

RoomCharaterSelectUI::~RoomCharaterSelectUI()
{
}

void RoomCharaterSelectUI::Start()
{
	Rank_1P = CreateRenderer((int)UIType::StartIntroUI);
	Rank_2P = CreateRenderer((int)UIType::StartIntroUI);
	Rank_1P->SetImage("rank_High.bmp");
	Rank_2P->SetImage("rank_low.bmp");
	Rank_1P->SetScale(float4{ 20.0f, 20.0f });
	Rank_2P->SetScale(float4{ 22.0f, 22.0f });
	if (GetLevel()->GetNameConstRef() == "RoomLevel")
	{
		RoomCharacterRenderer1P = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, { -594.0f, 48.0f });
		RoomCharacterRenderer2P = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, { -488.0f, 48.0f });
		Rank_1P->SetPivot({ -563.0f, 60.0f });
		Rank_2P->SetPivot({ -457.0f, 60.0f });
	}
	else if (GetLevel()->GetNameConstRef() == "MonsterRoomLevel")
	{
		RoomCharacterRenderer1P = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, { -594.0f, 67.0f });
		RoomCharacterRenderer2P = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, { -488.0f, 67.0f });
		Rank_1P->SetPivot({ -563.0f, 79.0f });
		Rank_2P->SetPivot({ -457.0f, 79.0f });
	}
	SetPosition({ 670, 95 });
	
	RoomCharacterRenderer1P->SetImage("RandomCharacter.bmp");
	RoomCharacterRenderer2P->SetImage("RandomCharacter.bmp");
	StatusRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, { -294.0f, 22.0f });
	StatusRenderer->SetImage("RandomStatusUI.bmp");
	StatusRenderer->Off();
	BannerRenderer = CreateRenderer((int)UIType::PopUp, RenderPivot::CENTER, { -40.0f, -50.0f });
	BannerRenderer->SetImage("RandomSelect_Image.bmp");
	MaridRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ 68.0f, -5.0f });
	DaoRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ -3.0f,0 });
	BazziRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ -72.0f, -7.0f });
	RandomRenderer = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, float4{ -146.0f, -7.0f });

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

	Choice2PRenderer = CreateRenderer("2P_Check.bmp");
	Choice2PRenderer->SetPivot({ 4.0f, 10.0f });
	Choice2PRenderer->Off();
	RoomCharacterRenderer2P->Off();
	Rank_2P->Off();

	ChoiceCharacter1P = 0;
	ChoiceCharacter2P = 0;

	
}

void RoomCharaterSelectUI::Update()
{
	RendererMouseCheck();
	ChoiceCharacter();

	
	ChoiceCheck();
	PivotReset();
	StatusUISet(); 
	BannerSet();
}

void RoomCharaterSelectUI::RendererMouseCheck()
{
	// 랜덤 캐릭터 렌더러 애니메이션 변경
	if (ChoiceCharacter1P != 0 && ChoiceCharacter2P != 0)
	{
		if (false == RandomCollision->CollisionCheck("MouseCol"))
		{
			RandomRenderer->ChangeAnimation("RandomCharSelecter_Idle");
		}

		else if (true == RandomCollision->CollisionCheck("MouseCol"))
		{
			RandomRenderer->ChangeAnimation("RandomCharSelecter_Approach");
		}


		if (true == RandomCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			RandomRenderer->ChangeAnimation("RandomCharSelecter_Cilck");
			GameEngineSound::SoundPlayOneShot("Click.wav");
		}

		if (true == GlobalUIName::GetInst()->Is2pUpdate())
		{
			if (true == RandomCollision->CollisionCheck("MouseCol") &&
				true == GameEngineInput::GetInst()->IsPress("RightMouse"))
			{
				RandomRenderer->ChangeAnimation("RandomCharSelecter_Cilck");
				GameEngineSound::SoundPlayOneShot("Click.wav");
			}
		}
	}

	// 배찌 애니메이션 변경
	if (ChoiceCharacter1P != 1 && ChoiceCharacter2P != 1)
	{
		if (false == BazziCollision->CollisionCheck("MouseCol"))
		{
			BazziRenderer->ChangeAnimation("BazziCharSelecter_Idle");
		}

		else if (true == BazziCollision->CollisionCheck("MouseCol"))
		{
			BazziRenderer->ChangeAnimation("BazziCharSelecter_Approach");
		}

		if (true == BazziCollision->CollisionCheck("MouseCol") &&
				true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			BazziRenderer->ChangeAnimation("BazziCharSelecter_Cilck");
			GameEngineSound::SoundPlayOneShot("Click.wav");
		}

		if (true == GlobalUIName::GetInst()->Is2pUpdate())
		{
			if (true == BazziCollision->CollisionCheck("MouseCol") &&
				true == GameEngineInput::GetInst()->IsPress("RightMouse"))
			{
				BazziRenderer->ChangeAnimation("BazziCharSelecter_Cilck");
				GameEngineSound::SoundPlayOneShot("Click.wav");
			}
		}
	}

	// 다오 애니메이션 변경
	if (ChoiceCharacter1P != 2 && ChoiceCharacter2P != 2)
	{
		if (false == DaoCollision->CollisionCheck("MouseCol"))
		{
			DaoRenderer->ChangeAnimation("DaoCharSelecter_Idle");
		}

		else if (true == DaoCollision->CollisionCheck("MouseCol"))
		{
			DaoRenderer->ChangeAnimation("DaoCharSelecter_Approach");
		}


		if (true == DaoCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			DaoRenderer->ChangeAnimation("DaoCharSelecter_Cilck");
			GameEngineSound::SoundPlayOneShot("Click.wav");
		}

		if (true == GlobalUIName::GetInst()->Is2pUpdate())
		{
			if (true == DaoCollision->CollisionCheck("MouseCol") &&
				true == GameEngineInput::GetInst()->IsPress("RightMouse"))
			{
				DaoRenderer->ChangeAnimation("DaoCharSelecter_Cilck");
				GameEngineSound::SoundPlayOneShot("Click.wav");
			}
		}
	}

	if (ChoiceCharacter1P != 3 && ChoiceCharacter2P != 3)
	{
		if (false == MaridCollision->CollisionCheck("MouseCol"))
		{
			MaridRenderer->ChangeAnimation("MaridCharSelecter_Idle");
		}

		else if (true == MaridCollision->CollisionCheck("MouseCol"))
		{
			MaridRenderer->ChangeAnimation("MaridCharSelecter_Approach");
		}


		if (true == MaridCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			MaridRenderer->ChangeAnimation("MaridCharSelecter_Cilck");
			GameEngineSound::SoundPlayOneShot("Click.wav");

		}

		if (true == GlobalUIName::GetInst()->Is2pUpdate())
		{
			if (true == MaridCollision->CollisionCheck("MouseCol") &&
				true == GameEngineInput::GetInst()->IsPress("RightMouse"))
			{
				MaridRenderer->ChangeAnimation("MaridCharSelecter_Cilck");
				GameEngineSound::SoundPlayOneShot("Click.wav");
			}
		}
	
	}

	
}

void RoomCharaterSelectUI::ChoiceCharacter()
{
	if (ChoiceCharacter1P != 0)
	{
		if (true == RandomCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			ChoiceCharacter1P = 0;
			GlobalUIName::GetInst()->Set1P(4);
		}
	}

	if (ChoiceCharacter1P != 1)
	{
		if (true == BazziCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			ChoiceCharacter1P = 1;
			GlobalUIName::GetInst()->Set1P(0);
		}
	}

	if (ChoiceCharacter1P != 2)
	{
		if (true == DaoCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			ChoiceCharacter1P = 2;
			GlobalUIName::GetInst()->Set1P(2);
		}
	}

	if (ChoiceCharacter1P != 3)
	{
		if (true == MaridCollision->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			ChoiceCharacter1P = 3;
			GlobalUIName::GetInst()->Set1P(1);
		}
	}


	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		if (ChoiceCharacter2P != 0)
		{
			if (true == RandomCollision->CollisionCheck("MouseCol") &&
				true == GameEngineInput::GetInst()->IsUp("RightMouse"))
			{
				ChoiceCharacter2P = 0;
				GlobalUIName::GetInst()->Set2P(4);
			}
		}

		if (ChoiceCharacter2P != 1)
		{
			if (true == BazziCollision->CollisionCheck("MouseCol") &&
				true == GameEngineInput::GetInst()->IsUp("RightMouse"))
			{
				ChoiceCharacter2P = 1;
				GlobalUIName::GetInst()->Set2P(0);
			}
		}

		if (ChoiceCharacter2P != 2)
		{
			if (true == DaoCollision->CollisionCheck("MouseCol") &&
				true == GameEngineInput::GetInst()->IsUp("RightMouse"))
			{
				ChoiceCharacter2P = 2;
				GlobalUIName::GetInst()->Set2P(2);
			}
		}

		if (ChoiceCharacter2P != 3)
		{
			if (true == MaridCollision->CollisionCheck("MouseCol") &&
				true == GameEngineInput::GetInst()->IsUp("RightMouse"))
			{
				ChoiceCharacter2P = 3;
				GlobalUIName::GetInst()->Set2P(1);
			}
		}
	}

}

void RoomCharaterSelectUI::ChoiceCheck()
{
	if (ChoiceCharacter1P == ChoiceCharacter2P)
	{
		Choice2PRenderer->On();
	}
	else
	{
		Choice2PRenderer->Off();
	}

	if (ChoiceCharacter1P == 0)
	{	
		RandomRenderer->ChangeAnimation("RandomCharSelecter_CilckUp");
		if (ChoiceCharacter1P == ChoiceCharacter2P)
		{
			Choice2PRenderer->SetPivot({ -136.0f, 10.0f });
			RandomRenderer->SetPivot({ -146.0f, -7.0f });
		}
	}

	else if (ChoiceCharacter1P == 1)
	{
		BazziRenderer->ChangeAnimation("BazziCharSelecter_CilckUp");
		if (ChoiceCharacter1P == ChoiceCharacter2P)
		{
			Choice2PRenderer->SetPivot({-70.0f, 10.0f });
			BazziRenderer->SetPivot({ -72.0f, -7.0f });
		}
	}
	
	else if (ChoiceCharacter1P == 2)
	{
		DaoRenderer->ChangeAnimation("DaoCharSelecter_CilckUp");
		if (ChoiceCharacter1P == ChoiceCharacter2P)
		{
			Choice2PRenderer->SetPivot({ 4.0f, 10.0f });
			DaoRenderer->SetPivot({ -3.0f,0 });
		}
	}

	else if (ChoiceCharacter1P == 3)
	{
		MaridRenderer->ChangeAnimation("MaridCharSelecter_CilckUp");
		if (ChoiceCharacter1P == ChoiceCharacter2P)
		{
			Choice2PRenderer->SetPivot({ 78.0f, 10.0f });
			MaridRenderer->SetPivot({ 68.0f, -5.0f });
		}
	}

	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		if (ChoiceCharacter1P != ChoiceCharacter2P)
		{
			if (ChoiceCharacter2P == 0)
			{
				RandomRenderer->SetPivot({ -146.0f, -19.0f });
				RandomRenderer->SetImageAnimationReset("2P_RandomChoice.bmp");
			}

			else if (ChoiceCharacter2P == 1)
			{
				BazziRenderer->SetPivot({ -75.0f, -22.0f });
				BazziRenderer->SetImageAnimationReset("2P_BazziChoice.bmp");
			}


			else if (ChoiceCharacter2P == 2)
			{
				DaoRenderer->SetPivot({ -2.0f,-23.0f });
				DaoRenderer->SetImageAnimationReset("2P_DaoChoice.bmp");
			}


			else if (ChoiceCharacter2P == 3)
			{
				MaridRenderer->SetPivot({ 73.0f, -27.0f });
				MaridRenderer->SetImageAnimationReset("2P_MaridChoice.bmp");
			}
		}
	}
}

void RoomCharaterSelectUI::PivotReset()
{
	
	if (ChoiceCharacter2P == 0)
	{
		BazziRenderer->SetPivot({ -72.0f, -7.0f });
		DaoRenderer->SetPivot({ -3.0f,0 });
		MaridRenderer->SetPivot({ 68.0f, -5.0f });
	}

	if (ChoiceCharacter2P == 1)
	{
		RandomRenderer->SetPivot({ -146.0f, -7.0f });
		DaoRenderer->SetPivot({ -3.0f,0 });
		MaridRenderer->SetPivot({ 68.0f, -5.0f });
	}

	if (ChoiceCharacter2P == 2)
	{
		RandomRenderer->SetPivot({ -146.0f, -7.0f });
		BazziRenderer->SetPivot({ -72.0f, -7.0f });
		MaridRenderer->SetPivot({ 68.0f, -5.0f });
	}

	if (ChoiceCharacter2P == 3)
	{
		RandomRenderer->SetPivot({ -146.0f, -7.0f });
		BazziRenderer->SetPivot({ -72.0f, -7.0f });
		DaoRenderer->SetPivot({ -3.0f,0 });
	}

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
	switch (ChoiceCharacter1P)
	{
	case 0:
		BannerRenderer->SetPivot({ -40.0f, -50.0f });
		BannerRenderer->SetImage("RandomSelect_Image.bmp");
		RoomCharacterRenderer1P->SetImage("RandomCharacter.bmp");
		break;
	case 1:
		BannerRenderer->SetPivot({ -42.0f, -49.0f });
		BannerRenderer->SetImage("BazziSelect_Image.bmp");
		RoomCharacterRenderer1P->SetImage("BazziCharacter.bmp");
		break;
	case 2:
		BannerRenderer->SetPivot({ -42.0f, -49.0f });
		BannerRenderer->SetImage("DaoSelect_Image.bmp");
		RoomCharacterRenderer1P->SetImage("DaoCharacter.bmp");
		break;
	case 3:
		BannerRenderer->SetPivot({ -42.0f, -49.0f });
		BannerRenderer->SetImage("MaridSelect_Image.bmp");
		RoomCharacterRenderer1P->SetImage("luxMaridCharacter.bmp");
		break;
	default:
		break;
	}

	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		RoomCharacterRenderer2P->On();
		switch (ChoiceCharacter2P)
		{
		case 0:
			RoomCharacterRenderer2P->SetImage("RandomCharacter.bmp");
			break;
		case 1:
			RoomCharacterRenderer2P->SetImage("BazziCharacter.bmp");
			break;
		case 2:
			RoomCharacterRenderer2P->SetImage("DaoCharacter.bmp");
			break;
		case 3:
			RoomCharacterRenderer2P->SetImage("luxMaridCharacter.bmp");
			break;
		default:
			break;
		}
	}
}

void RoomCharaterSelectUI::LevelChangeStart(GameEngineLevel * _PrevLevel)
{
	ChoiceCharacter1P = 0;
	ChoiceCharacter2P = 0;
	GameEngineRandom a;
	GlobalUIName::GetInst()->Set1P(4);
	GlobalUIName::GetInst()->Set2P(4);
	Rank_2P->On();
	if (false == GlobalUIName::GetInst()->Is2pUpdate())
	{
		ChoiceCharacter2P = 5;
		Choice2PRenderer->Off();
		Rank_2P->Off();
		RoomCharacterRenderer2P->Off();
	}
}