#include "Player_Bazzi.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Player_Bazzi::Player_Bazzi()
    : Player()
{

}
Player_Bazzi::~Player_Bazzi()
{

}

void Player_Bazzi::Start()
{
    Player::Start();

	{
		GameEngineImage* Left = GameEngineImageManager::GetInst()->Find("Left.bmp");
		Left->CutCount(6, 1);
		GameEngineImage* Right = GameEngineImageManager::GetInst()->Find("Right.bmp");
		Right->CutCount(6, 1);
		GameEngineImage* Down = GameEngineImageManager::GetInst()->Find("Down.bmp");
		Down->CutCount(8, 1);
		GameEngineImage* Up = GameEngineImageManager::GetInst()->Find("Up.bmp");
		Up->CutCount(8, 1);
	}

	// 애니메이션
	{
		// Idle
		PlayerAnimationRender_->CreateAnimation("Left.bmp", "Idle_Left", 0, 0, 1.f, false);
		PlayerAnimationRender_->CreateAnimation("Right.bmp", "Idle_Right", 0, 0, 1.f, false);
		PlayerAnimationRender_->CreateAnimation("Down.bmp", "Idle_Down", 0, 0, 1.f, false);
		PlayerAnimationRender_->CreateAnimation("Up.bmp", "Idle_Up", 0, 0, 1.f, false);
	
		// Move
		PlayerAnimationRender_->CreateAnimation("Left.bmp", "Move_Left", 0, 5, 0.09f, true);
		PlayerAnimationRender_->CreateAnimation("Right.bmp", "Move_Right", 0, 5, 0.09f, true);
		PlayerAnimationRender_->CreateAnimation("Down.bmp", "Move_Down", 0, 7, 0.09f, true);
		PlayerAnimationRender_->CreateAnimation("Up.bmp", "Move_Up", 0, 7, 0.09f, true);
	}


	//AnimationName_ = "Move_";
	//PlayerAnimationRender_->ChangeAnimation("Move_Down");

	AnimationName_ = "Idle_";
	PlayerAnimationRender_->ChangeAnimation("Idle_Down");


	// 플레이어 정보 세팅
	SetSpeed(1.f);				
	SetAttCount(1);
	SetAttPower(10.f);			// 일단 10배

	SetMaxSpeed(90.f);
	SetMaxAttCount(6);
	SetMaxAttPower(70.f);
}

void Player_Bazzi::Update()
{
	DirAnimationCheck();
	PlayerStateUpdate();

	//StagePixelCheck(CurSpeed_);
}

void Player_Bazzi::Render()
{
}
