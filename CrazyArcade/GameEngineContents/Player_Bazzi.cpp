#include "Player_Bazzi.h"
#include <GameEngine/GameEngineRenderer.h>

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




	// 애니메이션
	{
		// Idle
		//PlayerAnimationRender_->CreateAnimation("Left.bmp", "Idle_Left", 0, 0, 1.f, false);
		//PlayerAnimationRender_->CreateAnimation("Right.bmp", "Idle_Right", 0, 0, 1.f, false);
		//PlayerAnimationRender_->CreateAnimation("Down.bmp", "Idle_Down", 0, 0, 1.f, false);
		//PlayerAnimationRender_->CreateAnimation("Up.bmp", "Idle_Up", 0, 0, 1.f, false);
	
		// Move
		PlayerAnimationRender_->CreateAnimation("Left.bmp", "Move_Left", 0, 5, 1.f, false);
		PlayerAnimationRender_->CreateAnimation("Right.bmp", "Move_Right", 0, 5, 1.f, false);
		PlayerAnimationRender_->CreateAnimation("Down.bmp", "Move_Down", 0, 7, 1.f, false);
		PlayerAnimationRender_->CreateAnimation("Up.bmp", "Move_Up", 0, 7, 1.f, false);
	}


	AnimationName_ = "Move_";
	PlayerAnimationRender_->ChangeAnimation("Move_Down");

	//AnimationName_ = "Idle_";
	//PlayerAnimationRender_->ChangeAnimation("Idle_Down");

}

void Player_Bazzi::Update()
{
	DirAnimationCheck();
	PlayerStateUpdate();
}

void Player_Bazzi::Render()
{
}
