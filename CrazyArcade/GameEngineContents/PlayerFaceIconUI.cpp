#include "PlayerFaceIconUI.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"
#include "TimeUI.h"

PlayerFaceIconUI::PlayerFaceIconUI()
	: PlayerFaceIconUIRenderer_(nullptr)
{
}

PlayerFaceIconUI::~PlayerFaceIconUI()
{
}

void PlayerFaceIconUI::Start()
{
	PlayerFaceIconUIRenderer_ = CreateRenderer((int)UIType::Time);
	PlayerFaceIconUIRenderer_->SetPivot(float4{681.0f,119.0f});
	PlayerFaceIconUIRenderer_->CreateAnimation("BazziFace_Icon.bmp", "BazziFace_Icon_Idle", 0, 0, 0.1f, false);
	PlayerFaceIconUIRenderer_->CreateAnimation("BazziFace_Icon.bmp", "BazziFace_Icon_Blink", 1, 2, 0.2f, true);
	PlayerFaceIconUIRenderer_->CreateAnimation("BazziFace_Icon.bmp", "BazziFace_Icon_CryIdle", 3, 3, 0.1f, false);
	PlayerFaceIconUIRenderer_->CreateAnimation("BazziFace_Icon.bmp", "BazziFace_Icon_Cry", 4, 5, 0.15f, true);
			
	PlayerFaceIconUIRenderer_->ChangeAnimation("BazziFace_Icon_Idle");
}

void PlayerFaceIconUI::Update()
{
	if (islive == true) {
		BlinkTime_ += GameEngineTime::GetDeltaTime();
		if (BlinkTime_ > 4.0f && BlinkTime_ < 4.8f)
		{
			PlayerFaceIconUIRenderer_->ChangeAnimation("BazziFace_Icon_Blink");
		}
		else if (BlinkTime_ > 4.8f)
		{
			PlayerFaceIconUIRenderer_->ChangeAnimation("BazziFace_Icon_Idle");
			BlinkTime_ = 0.0f;
		}
	}
	else {
		CryTime_ += GameEngineTime::GetDeltaTime();
		if (CryTime_ > 2.0f && CryTime_ < 2.3f)
		{
			PlayerFaceIconUIRenderer_->ChangeAnimation("BazziFace_Icon_CryIdle");
		}
		else if (CryTime_ > 2.3f)
		{
			PlayerFaceIconUIRenderer_->ChangeAnimation("BazziFace_Icon_Cry");
			CryTime_ = 0.0f;
		}
	}
}