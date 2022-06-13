#include "PlayerFaceIconUI.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"
#include "TimeUI.h"
#include "Player.h"
#include "GlobalUIName.h"

PlayerFaceIconUI::PlayerFaceIconUI()
	: PlayerFaceIconUIRenderer_1P(nullptr),
	BlinkTime_1P(0.0f),
	CryTime_1P(0.0f),
	Islive_1P(true),
	BlinkTime_2P(0.0f),
	CryTime_2P(0.0f),
	Islive_2P(true),
	onetime(true)
{
}

PlayerFaceIconUI::~PlayerFaceIconUI()
{
}

void PlayerFaceIconUI::Start()
{

}

void PlayerFaceIconUI::Update()
{
	Islive_1P = Player::MainPlayer_1->GetIslive();

	if (nullptr != Player::MainPlayer_2)
	{
		Islive_2P = Player::MainPlayer_2->GetIslive();
	}


	if (onetime == true) {

		if (CharacterType_1P == Character::BAZZI)
		{
			PlayerFaceIconUIRenderer_1P->ChangeAnimation("BazziFace_Icon_Idle");
		}
		else if (CharacterType_1P == Character::DAO)
		{
			PlayerFaceIconUIRenderer_1P->ChangeAnimation("DaoFace_Icon_Idle");
		}
		else if (CharacterType_1P == Character::LUXMARID)
		{
			PlayerFaceIconUIRenderer_1P->ChangeAnimation("MaridFace_Icon_Idle");
		}

		if (true == GlobalUIName::GetInst()->Is2pUpdate())
		{
			if (CharacterType_2P == Character::BAZZI)
			{
				PlayerFaceIconUIRenderer_2P->ChangeAnimation("BazziFace_Icon_Idle");
			}
			else if (CharacterType_2P == Character::DAO)
			{
				PlayerFaceIconUIRenderer_2P->ChangeAnimation("DaoFace_Icon_Idle");
			}
			else if (CharacterType_2P == Character::LUXMARID)
			{
				PlayerFaceIconUIRenderer_2P->ChangeAnimation("MaridFace_Icon_Idle");
			}
		}
		onetime = false;
	}




	if (CharacterType_1P== Character::BAZZI)
	{
		if (Islive_1P == true) {
			BlinkTime_1P += GameEngineTime::GetDeltaTime();
			if (BlinkTime_1P > 4.0f && BlinkTime_1P < 4.8f)
			{
				PlayerFaceIconUIRenderer_1P->ChangeAnimation("BazziFace_Icon_Blink");
			}
			else if (BlinkTime_1P > 4.8f)
			{
				PlayerFaceIconUIRenderer_1P->ChangeAnimation("BazziFace_Icon_Idle");
				BlinkTime_1P = 0.0f;
			}
		}
		else {
			CryTime_1P += GameEngineTime::GetDeltaTime();
			if (CryTime_1P > 2.0f && CryTime_1P < 2.3f)
			{
				PlayerFaceIconUIRenderer_1P->ChangeAnimation("BazziFace_Icon_CryIdle");
			}
			else if (CryTime_1P > 2.3f)
			{
				PlayerFaceIconUIRenderer_1P->ChangeAnimation("BazziFace_Icon_Cry");
				CryTime_1P = 0.0f;
			}
		}
	}
	else if (CharacterType_1P == Character::DAO)
	{
		if (Islive_1P == true) {
			BlinkTime_1P += GameEngineTime::GetDeltaTime();
			if (BlinkTime_1P > 4.0f && BlinkTime_1P < 4.8f)
			{
				PlayerFaceIconUIRenderer_1P->ChangeAnimation("DaoFace_Icon_Blink");
			}
			else if (BlinkTime_1P > 4.8f)
			{
				PlayerFaceIconUIRenderer_1P->ChangeAnimation("DaoFace_Icon_Idle");
				BlinkTime_1P = 0.0f;
			}
		}
		else {
			CryTime_1P += GameEngineTime::GetDeltaTime();
			if (CryTime_1P > 2.0f && CryTime_1P < 2.3f)
			{
				PlayerFaceIconUIRenderer_1P->ChangeAnimation("DaoFace_Icon_CryIdle");
			}
			else if (CryTime_1P > 2.3f)
			{
				PlayerFaceIconUIRenderer_1P->ChangeAnimation("DaoFace_Icon_Cry");
				CryTime_1P = 0.0f;
			}
		}
	}
	else if (CharacterType_1P == Character::LUXMARID)
	{
		if (Islive_1P == true) {
			BlinkTime_1P += GameEngineTime::GetDeltaTime();
			if (BlinkTime_1P > 4.0f && BlinkTime_1P < 4.8f)
			{
				PlayerFaceIconUIRenderer_1P->ChangeAnimation("MaridFace_Icon_Blink");
			}
			else if (BlinkTime_1P > 4.8f)
			{
				PlayerFaceIconUIRenderer_1P->ChangeAnimation("MaridFace_Icon_Idle");
				BlinkTime_1P = 0.0f;
			}
		}
		else {
			CryTime_1P += GameEngineTime::GetDeltaTime();
			if (CryTime_1P > 2.0f && CryTime_1P < 2.3f)
			{
				PlayerFaceIconUIRenderer_1P->ChangeAnimation("MaridFace_Icon_CryIdle");
			}
			else if (CryTime_1P > 2.3f)
			{
				PlayerFaceIconUIRenderer_1P->ChangeAnimation("MaridFace_Icon_Cry");
				CryTime_1P = 0.0f;
			}
		}
	}





	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		if (CharacterType_2P == Character::BAZZI)
		{
			if (Islive_2P == true) {
				BlinkTime_2P += GameEngineTime::GetDeltaTime();
				if (BlinkTime_2P > 4.0f && BlinkTime_2P < 4.8f)
				{
					PlayerFaceIconUIRenderer_2P->ChangeAnimation("BazziFace_Icon_Blink");
				}
				else if (BlinkTime_2P > 4.8f)
				{
					PlayerFaceIconUIRenderer_2P->ChangeAnimation("BazziFace_Icon_Idle");
					BlinkTime_2P = 0.0f;
				}
			}
			else {
				CryTime_2P += GameEngineTime::GetDeltaTime();
				if (CryTime_2P > 2.0f && CryTime_2P < 2.3f)
				{
					PlayerFaceIconUIRenderer_2P->ChangeAnimation("BazziFace_Icon_CryIdle");
				}
				else if (CryTime_2P > 2.3f)
				{
					PlayerFaceIconUIRenderer_2P->ChangeAnimation("BazziFace_Icon_Cry");
					CryTime_2P = 0.0f;
				}
			}
		}
		else if (CharacterType_2P == Character::DAO)
		{
			if (Islive_2P == true) {
				BlinkTime_2P += GameEngineTime::GetDeltaTime();
				if (BlinkTime_2P > 4.0f && BlinkTime_2P < 4.8f)
				{
					PlayerFaceIconUIRenderer_2P->ChangeAnimation("DaoFace_Icon_Blink");
				}
				else if (BlinkTime_2P > 4.8f)
				{
					PlayerFaceIconUIRenderer_2P->ChangeAnimation("DaoFace_Icon_Idle");
					BlinkTime_2P = 0.0f;
				}
			}
			else {
				CryTime_2P += GameEngineTime::GetDeltaTime();
				if (CryTime_2P > 2.0f && CryTime_2P < 2.3f)
				{
					PlayerFaceIconUIRenderer_2P->ChangeAnimation("DaoFace_Icon_CryIdle");
				}
				else if (CryTime_2P > 2.3f)
				{
					PlayerFaceIconUIRenderer_2P->ChangeAnimation("DaoFace_Icon_Cry");
					CryTime_2P = 0.0f;
				}
			}
		}
		else if (CharacterType_2P == Character::LUXMARID)
		{
			if (Islive_2P == true) {
				BlinkTime_2P += GameEngineTime::GetDeltaTime();
				if (BlinkTime_2P > 4.0f && BlinkTime_2P < 4.8f)
				{
					PlayerFaceIconUIRenderer_2P->ChangeAnimation("MaridFace_Icon_Blink");
				}
				else if (BlinkTime_2P > 4.8f)
				{
					PlayerFaceIconUIRenderer_2P->ChangeAnimation("MaridFace_Icon_Idle");
					BlinkTime_2P = 0.0f;
				}
			}
			else {
				CryTime_2P += GameEngineTime::GetDeltaTime();
				if (CryTime_2P > 2.0f && CryTime_2P < 2.3f)
				{
					PlayerFaceIconUIRenderer_2P->ChangeAnimation("MaridFace_Icon_CryIdle");
				}
				else if (CryTime_2P > 2.3f)
				{
					PlayerFaceIconUIRenderer_2P->ChangeAnimation("MaridFace_Icon_Cry");
					CryTime_2P = 0.0f;
				}
			}
		}
	}
}

void PlayerFaceIconUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	onetime = true;

	if (nullptr != Player::MainPlayer_1)
	{
		CharacterType_1P = Player::MainPlayer_1->GetCharacter();

		PlayerFaceIconUIRenderer_1P = CreateRenderer((int)UIType::Time);
		PlayerFaceIconUIRenderer_1P->SetPivot(float4{ 682.0f,119.0f });

		PlayerFaceIconUIRenderer_1P->CreateAnimation("BazziFace_Icon.bmp", "BazziFace_Icon_Idle", 0, 0, 0.1f, false);
		PlayerFaceIconUIRenderer_1P->CreateAnimation("BazziFace_Icon.bmp", "BazziFace_Icon_Blink", 1, 2, 0.2f, true);
		PlayerFaceIconUIRenderer_1P->CreateAnimation("BazziFace_Icon.bmp", "BazziFace_Icon_CryIdle", 3, 3, 0.1f, false);
		PlayerFaceIconUIRenderer_1P->CreateAnimation("BazziFace_Icon.bmp", "BazziFace_Icon_Cry", 4, 5, 0.15f, true);

		PlayerFaceIconUIRenderer_1P->CreateAnimation("DaoFace_Icon.bmp", "DaoFace_Icon_Idle", 0, 0, 0.1f, false);
		PlayerFaceIconUIRenderer_1P->CreateAnimation("DaoFace_Icon.bmp", "DaoFace_Icon_Blink", 1, 2, 0.2f, true);
		PlayerFaceIconUIRenderer_1P->CreateAnimation("DaoFace_Icon.bmp", "DaoFace_Icon_CryIdle", 3, 3, 0.1f, false);
		PlayerFaceIconUIRenderer_1P->CreateAnimation("DaoFace_Icon.bmp", "DaoFace_Icon_Cry", 4, 5, 0.15f, true);

		PlayerFaceIconUIRenderer_1P->CreateAnimation("MaridFace_Icon.bmp", "MaridFace_Icon_Idle", 0, 0, 0.1f, false);
		PlayerFaceIconUIRenderer_1P->CreateAnimation("MaridFace_Icon.bmp", "MaridFace_Icon_Blink", 1, 2, 0.2f, true);
		PlayerFaceIconUIRenderer_1P->CreateAnimation("MaridFace_Icon.bmp", "MaridFace_Icon_CryIdle", 3, 3, 0.1f, false);
		PlayerFaceIconUIRenderer_1P->CreateAnimation("MaridFace_Icon.bmp", "MaridFace_Icon_Cry", 4, 5, 0.15f, true);


		RankRenderer_1P = CreateRenderer((int)UIType::Time);
		RankRenderer_1P->SetImage("Rank_High.bmp");
		RankRenderer_1P->SetPivot(float4{ 716.0f,112.0f });
		RankRenderer_1P->SetScale(float4{ 20.0f,20.0f });

	}

	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		CharacterType_2P = Player::MainPlayer_2->GetCharacter();

		PlayerFaceIconUIRenderer_2P = CreateRenderer((int)UIType::Time);
		PlayerFaceIconUIRenderer_2P->SetPivot(float4{ 682.0f,162.0f });
		PlayerFaceIconUIRenderer_2P->CreateAnimation("BazziFace_Icon.bmp", "BazziFace_Icon_Idle", 0, 0, 0.1f, false);
		PlayerFaceIconUIRenderer_2P->CreateAnimation("BazziFace_Icon.bmp", "BazziFace_Icon_Blink", 1, 2, 0.2f, true);
		PlayerFaceIconUIRenderer_2P->CreateAnimation("BazziFace_Icon.bmp", "BazziFace_Icon_CryIdle", 3, 3, 0.1f, false);
		PlayerFaceIconUIRenderer_2P->CreateAnimation("BazziFace_Icon.bmp", "BazziFace_Icon_Cry", 4, 5, 0.15f, true);

		PlayerFaceIconUIRenderer_2P->CreateAnimation("DaoFace_Icon.bmp", "DaoFace_Icon_Idle", 0, 0, 0.1f, false);
		PlayerFaceIconUIRenderer_2P->CreateAnimation("DaoFace_Icon.bmp", "DaoFace_Icon_Blink", 1, 2, 0.2f, true);
		PlayerFaceIconUIRenderer_2P->CreateAnimation("DaoFace_Icon.bmp", "DaoFace_Icon_CryIdle", 3, 3, 0.1f, false);
		PlayerFaceIconUIRenderer_2P->CreateAnimation("DaoFace_Icon.bmp", "DaoFace_Icon_Cry", 4, 5, 0.15f, true);

		PlayerFaceIconUIRenderer_2P->CreateAnimation("MaridFace_Icon.bmp", "MaridFace_Icon_Idle", 0, 0, 0.1f, false);
		PlayerFaceIconUIRenderer_2P->CreateAnimation("MaridFace_Icon.bmp", "MaridFace_Icon_Blink", 1, 2, 0.2f, true);
		PlayerFaceIconUIRenderer_2P->CreateAnimation("MaridFace_Icon.bmp", "MaridFace_Icon_CryIdle", 3, 3, 0.1f, false);
		PlayerFaceIconUIRenderer_2P->CreateAnimation("MaridFace_Icon.bmp", "MaridFace_Icon_Cry", 4, 5, 0.15f, true);


		RankRenderer_2P = CreateRenderer((int)UIType::Time);
		RankRenderer_2P->SetImage("Rank_low.bmp");
		RankRenderer_2P->SetPivot(float4{ 716.0f,155.0f });
		RankRenderer_2P->SetScale(float4{ 20.0f,20.0f });
	}
}



void PlayerFaceIconUI::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (PlayerFaceIconUIRenderer_1P != nullptr) {
		PlayerFaceIconUIRenderer_1P->Death();
		RankRenderer_1P->Death();
		PlayerFaceIconUIRenderer_1P = nullptr;
		RankRenderer_1P = nullptr;
	}
	if (PlayerFaceIconUIRenderer_2P != nullptr) {
		PlayerFaceIconUIRenderer_2P->Death();
		RankRenderer_2P->Death();
		PlayerFaceIconUIRenderer_2P = nullptr;
		RankRenderer_2P = nullptr;
	}
}