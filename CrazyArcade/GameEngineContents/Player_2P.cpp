#include "Player_2P.h"
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Player_2P::Player_2P()
{

}
Player_2P::~Player_2P()
{

}

void Player_2P::Start()
{
	/*GameEngineImage* Left = GameEngineImageManager::GetInst()->Find("Left.bmp");
	Left->CutCount(6, 1);*/

	//PlayerAnimationRender_->CreateAnimation("Left.bmp", "Move_Left", 0, 5, 0.09f, true);


	if (false == GameEngineInput::GetInst()->IsKey("2PLeft"))
	{
		// =============== 2P 이동 ===============
		GameEngineInput::GetInst()->CreateKey("2PLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("2PRight", 'D');
		GameEngineInput::GetInst()->CreateKey("2PUp", 'W');
		GameEngineInput::GetInst()->CreateKey("2PDown", 'S');

		// =============== 2P 공격 ===============
		GameEngineInput::GetInst()->CreateKey("2PAttack", VK_LSHIFT);
	}
}

void Player_2P::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("2PLeft"))
	{
		MoveDir.x = -100.f;
	}

	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * CurSpeed_);
}

void Player_2P::Render()
{
}

bool Player_2P::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("2PLeft") &&
	false == GameEngineInput::GetInst()->IsPress("2PRight") &&
	false == GameEngineInput::GetInst()->IsPress("2PUp") &&
	false == GameEngineInput::GetInst()->IsPress("2PDown")
	)
	{
		return false;
	}

	return true;
}
