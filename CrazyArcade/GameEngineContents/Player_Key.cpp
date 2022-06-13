#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>
#include "MapGameObject.h"
#include "MapBackGround.h"
#include "GameEngine/GameEngine.h"
#include "GameItemObject.h"

void Player::Move(float _CurSpeed)
{
	MoveDir = float4::ZERO;

	if (true == IsDevil)
	{
		if (Type == PlayerType::Player1)
		{
			_CurSpeed = MainPlayer_1->CurSpeed_;
			MovePos_ = _CurSpeed * 7.f;

			if (CurState_ != PlayerState::Ready)
			{
				if (true == GameEngineInput::GetInst()->IsPress("1PRight"))
				{
					CheckDir_ = PlayerDir::Right;
					ChangeDirText_ = "Left";
				}
				if (true == GameEngineInput::GetInst()->IsPress("1PLeft"))
				{
					CheckDir_ = PlayerDir::Left;
					ChangeDirText_ = "Right";
				}
				if (true == GameEngineInput::GetInst()->IsPress("1PUp"))
				{
					CheckDir_ = PlayerDir::Up;
					ChangeDirText_ = "Down";
				}
				if (true == GameEngineInput::GetInst()->IsPress("1PDown"))
				{
					CheckDir_ = PlayerDir::Down;
					ChangeDirText_ = "Up";
				}

				if ((true == GameEngineInput::GetInst()->IsUp("1PRight") && CheckDir_ == PlayerDir::Right)
					|| (true == GameEngineInput::GetInst()->IsUp("1PLeft") && CheckDir_ == PlayerDir::Left)
					|| (true == GameEngineInput::GetInst()->IsUp("1PUp") && CheckDir_ == PlayerDir::Up)
					|| (true == GameEngineInput::GetInst()->IsUp("1PDown") && CheckDir_ == PlayerDir::Down))
				{
					CheckDir_ = PlayerDir::None;
				}
			}

			///////////////////////////////////////////////////////////

			if (CheckDir_ == PlayerDir::Right)
			{
				if (true == IsRightMove)
				{
					MoveDir.x = -MovePos_;
				}

			}
			else if (CheckDir_ == PlayerDir::Left)
			{
				if (true == IsLeftMove)
				{
					MoveDir.x = MovePos_;
				}

			}
			else if (CheckDir_ == PlayerDir::Down)
			{
				if (true == IsDownMove)
				{
					MoveDir.y = -MovePos_;
				}

			}
			else if (CheckDir_ == PlayerDir::Up)
			{
				if (true == IsUpMove)
				{
					MoveDir.y = MovePos_;
				}
			}
		}
		else if (Type == PlayerType::Player2)
		{
			_CurSpeed = MainPlayer_2->CurSpeed_;
			MovePos_ = _CurSpeed * 7.f;

			if (CurState_ != PlayerState::Ready)
			{

				if (true == GameEngineInput::GetInst()->IsPress("2PRight"))
				{
					CheckDir_ = PlayerDir::Left;
					ChangeDirText_ = "Left";
				}
				if (true == GameEngineInput::GetInst()->IsPress("2PLeft"))
				{
					CheckDir_ = PlayerDir::Right;
					ChangeDirText_ = "Right";
				}
				if (true == GameEngineInput::GetInst()->IsPress("2PUp"))
				{
					CheckDir_ = PlayerDir::Down;
					ChangeDirText_ = "Down";
				}
				if (true == GameEngineInput::GetInst()->IsPress("2PDown"))
				{
					CheckDir_ = PlayerDir::Up;
					ChangeDirText_ = "Up";
				}


				if ((true == GameEngineInput::GetInst()->IsUp("2PRight") && CheckDir_ == PlayerDir::Left)
					|| (true == GameEngineInput::GetInst()->IsUp("2PLeft") && CheckDir_ == PlayerDir::Right)
					|| (true == GameEngineInput::GetInst()->IsUp("2PUp") && CheckDir_ == PlayerDir::Down)
					|| (true == GameEngineInput::GetInst()->IsUp("2PDown") && CheckDir_ == PlayerDir::Up))
				{
					CheckDir_ = PlayerDir::None;
				}


				///////////////////////////////////////////////////////////

				if (CheckDir_ == PlayerDir::Right)
				{
					if (true == IsLeftMove)
					{
						MoveDir.x = -MovePos_;
					}

				}
				else if (CheckDir_ == PlayerDir::Left)
				{
					if (true == IsRightMove)
					{
						MoveDir.x = MovePos_;
					}

				}
				else if (CheckDir_ == PlayerDir::Down)
				{
					if (true == IsUpMove)
					{
						MoveDir.y = -MovePos_;
					}

				}
				else if (CheckDir_ == PlayerDir::Up)
				{
					if (true == IsDownMove)
					{
						MoveDir.y = MovePos_;
					}
				}
			}

		}
	}
	else
	{
		if (Type == PlayerType::Player1)
		{
			_CurSpeed = MainPlayer_1->CurSpeed_;
			MovePos_ = _CurSpeed * 7.f;

			if (CurState_ != PlayerState::Ready)
			{
				if (true == GameEngineInput::GetInst()->IsPress("1PRight"))
				{
					CheckDir_ = PlayerDir::Right;
					ChangeDirText_ = "Right";
				}
				if (true == GameEngineInput::GetInst()->IsPress("1PLeft"))
				{
					CheckDir_ = PlayerDir::Left;
					ChangeDirText_ = "Left";
				}
				if (true == GameEngineInput::GetInst()->IsPress("1PUp"))
				{
					CheckDir_ = PlayerDir::Up;
					ChangeDirText_ = "Up";
				}
				if (true == GameEngineInput::GetInst()->IsPress("1PDown"))
				{
					CheckDir_ = PlayerDir::Down;
					ChangeDirText_ = "Down";
				}

				if ((true == GameEngineInput::GetInst()->IsUp("1PRight") && CheckDir_ == PlayerDir::Right)
					|| (true == GameEngineInput::GetInst()->IsUp("1PLeft") && CheckDir_ == PlayerDir::Left)
					|| (true == GameEngineInput::GetInst()->IsUp("1PUp") && CheckDir_ == PlayerDir::Up)
					|| (true == GameEngineInput::GetInst()->IsUp("1PDown") && CheckDir_ == PlayerDir::Down))
				{
					CheckDir_ = PlayerDir::None;
				}
			}

			///////////////////////////////////////////////////////////

			if (CheckDir_ == PlayerDir::Left)
			{
				if (true == IsLeftMove)
				{
					MoveDir.x = -MovePos_;
				}

			}
			else if (CheckDir_ == PlayerDir::Right)
			{
				if (true == IsRightMove)
				{
					MoveDir.x = MovePos_;
				}

			}
			else if (CheckDir_ == PlayerDir::Up)
			{
				if (true == IsUpMove)
				{
					MoveDir.y = -MovePos_;
				}

			}
			else if (CheckDir_ == PlayerDir::Down)
			{
				if (true == IsDownMove)
				{
					MoveDir.y = MovePos_;
				}
			}
		}
		else if (Type == PlayerType::Player2)
		{
			_CurSpeed = MainPlayer_2->CurSpeed_;
			MovePos_ = _CurSpeed * 7.f;

			if (CurState_ != PlayerState::Ready)
			{

				if (true == GameEngineInput::GetInst()->IsPress("2PRight"))
				{
					CheckDir_ = PlayerDir::Right;
					ChangeDirText_ = "Right";
				}
				if (true == GameEngineInput::GetInst()->IsPress("2PLeft"))
				{
					CheckDir_ = PlayerDir::Left;
					ChangeDirText_ = "Left";
				}
				if (true == GameEngineInput::GetInst()->IsPress("2PUp"))
				{
					CheckDir_ = PlayerDir::Up;
					ChangeDirText_ = "Up";
				}
				if (true == GameEngineInput::GetInst()->IsPress("2PDown"))
				{
					CheckDir_ = PlayerDir::Down;
					ChangeDirText_ = "Down";
				}


				if ((true == GameEngineInput::GetInst()->IsUp("2PRight") && CheckDir_ == PlayerDir::Right)
					|| (true == GameEngineInput::GetInst()->IsUp("2PLeft") && CheckDir_ == PlayerDir::Left)
					|| (true == GameEngineInput::GetInst()->IsUp("2PUp") && CheckDir_ == PlayerDir::Up)
					|| (true == GameEngineInput::GetInst()->IsUp("2PDown") && CheckDir_ == PlayerDir::Down))
				{
					CheckDir_ = PlayerDir::None;
				}


				///////////////////////////////////////////////////////////

				if (CheckDir_ == PlayerDir::Left)
				{
					if (true == IsLeftMove)
					{
						MoveDir.x = -MovePos_;
					}

				}
				else if (CheckDir_ == PlayerDir::Right)
				{
					if (true == IsRightMove)
					{
						MoveDir.x = MovePos_;
					}

				}
				else if (CheckDir_ == PlayerDir::Up)
				{
					if (true == IsUpMove)
					{
						MoveDir.y = -MovePos_;
					}

				}
				else if (CheckDir_ == PlayerDir::Down)
				{
					if (true == IsDownMove)
					{
						MoveDir.y = MovePos_;
					}
				}
			}
		}
	}
	
}


bool Player::IsMoveKey()
{
	if (true == IsMove)
	{
		if (Type == PlayerType::Player1)
		{
			if (CheckDir_ == PlayerDir::None)
			{
				return false;
			}
		}
		else if (Type == PlayerType::Player2)
		{
			if (CheckDir_ == PlayerDir::None)
			{
				return false;
			}
		}


		return true;
	}

	return false;
}

bool Player::IsAttackKey()
{
	if (Type == PlayerType::Player1)
	{
		if (true == GameEngineInput::GetInst()->IsDown("1PAttack"))
		{
			return true;
		}
	}
	else
	{
		if (true == GameEngineInput::GetInst()->IsDown("2PAttack"))
		{
			return true;
		}
	}

	return false;
}

bool Player::IsItemKey()
{
	if (Type == PlayerType::Player1)
	{
		if (true == GameEngineInput::GetInst()->IsDown("1PItem"))
		{
			return true;
		}
	}
	else
	{
		if (true == GameEngineInput::GetInst()->IsDown("2PItem"))
		{
			return true;
		}
	}

	return false;
}
