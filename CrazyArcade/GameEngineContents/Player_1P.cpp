#include "Player_1P.h"
#include "GameEngineBase//GameEngineInput.h"

Player_1P::Player_1P()
	//: Type(PlayerType::Pla)
{

}
Player_1P::~Player_1P()
{

}

void Player_1P::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("1PLeft"))
	{
		// =============== 1P 이동 ===============
		GameEngineInput::GetInst()->CreateKey("1PLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("1PRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("1PUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("1PDown", VK_DOWN);

		// =============== 1P 공격 ===============
		GameEngineInput::GetInst()->CreateKey("1PAttack", VK_SPACE);
	}
}

void Player_1P::Update()
{
}

void Player_1P::Render()
{
}

bool Player_1P::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("1PLeft") &&
		false == GameEngineInput::GetInst()->IsPress("1PRight") &&
		false == GameEngineInput::GetInst()->IsPress("1PUp") &&
		false == GameEngineInput::GetInst()->IsPress("1PDown")
		)
	{
		return false;
	}

	return true;
}

