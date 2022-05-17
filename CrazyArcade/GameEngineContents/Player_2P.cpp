#include "Player_2P.h"
#include "GameEngineBase/GameEngineInput.h"

Player_2P::Player_2P()
{

}
Player_2P::~Player_2P()
{

}

void Player_2P::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("2PLeft"))
	{
		// =============== 1P 이동 ===============
		GameEngineInput::GetInst()->CreateKey("2PLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("2PRight", 'D');
		GameEngineInput::GetInst()->CreateKey("2PUp", 'W');
		GameEngineInput::GetInst()->CreateKey("2PDown", 'S');

		// =============== 1P 공격 ===============
		GameEngineInput::GetInst()->CreateKey("2PAttack", VK_LSHIFT);
	}
}

void Player_2P::Update()
{
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
