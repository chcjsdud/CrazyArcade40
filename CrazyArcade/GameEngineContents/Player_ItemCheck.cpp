#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "MapGameObject.h"
#include "MapBackGround.h"
#include "GameEngine/GameEngine.h"
#include "GameItemObject.h"

void Player::ItemCheck(Player* _Player, ItemType _ItemType)
{
	CurCharacter = GetCharacter();

	switch (_ItemType)
	{
	case ItemType::Roller:
	{
		float Speed = _Player->CurSpeed_;

		if (_Player->CurSpeed_ > Speed)
		{
			return;
		}

		if (_Player->CurSpeed_ >= _Player->MaxSpeed_)
		{
			return;
		}

		_Player->CurSpeed_ += 1;
	
		
		/*	switch (CurCharacter)
			{
			case Character::BAZZI:
			{
				if (CurSpeed_ >= BazziMaxSpeed_)
				{
					return;
				}
			}
			break;
			case Character::LUXMARID:
			{
				if (CurSpeed_ >= MaridMaxSpeed_)
				{
					return;
				}
			}
			break;
			case Character::DAO:
			{
				if (CurSpeed_ >= DaoMaxSpeed_)
				{
					return;
				}
			}
			break;
			default:
				break;

			}

			_Player->CurSpeed_ += 1;*/
	}
	break;
	case ItemType::Bubble:
	{
		if (_Player->CurAttCount_ >= _Player->MaxAttCount_)
		{
			return;
		}

		_Player->CurAttCount_ += 1;

		/*switch (CurCharacter)
		{
		case Character::BAZZI:
		{
			if (CurAttCount_ >= BazziMaxAttCount_)
			{
				return;
			}
		}
		break;
		case Character::LUXMARID:
		{
			if (CurAttCount_ >= MaridMaxAttCount_)
			{
				return;
			}
		}
		break;
		case Character::DAO:
		{
			if (CurAttCount_ >= DaoMaxAttCount_)
			{
				return;
			}
		}
		break;
		default:
			break;
		}

		_Player->CurAttCount_ += 1;*/
	}
	break;
	case ItemType::Fluid:
	{
		if (_Player->CurAttPower_ >= _Player->MaxAttPower_)
		{
			return;
		}

		_Player->CurAttPower_ += 1;

		/*switch (CurCharacter)
		{
		case Character::BAZZI:
		{
			if (CurAttPower_ >= BazziMaxAttPower_)
			{
				return;
			}
		}
		break;
		case Character::LUXMARID:
		{
			if (CurAttPower_ >= MaridMaxAttPower_)
			{
				return;
			}
		}
		break;
		case Character::DAO:
		{
			if (CurAttPower_ >= DaoMaxAttPower_)
			{
				return;
			}
		}
		break;
		default:
			break;
		}

		_Player->CurAttCount_ += 1;*/
	}
	break;
	case ItemType::RedDevil:
	{
		if (_Player->CurSpeed_ == _Player->MaxSpeed_)
		{
			return;
		}

		_Player->CurSpeed_ = _Player->MaxSpeed_;

	}
	break;
	case ItemType::UltraBubble:
	{
		if (_Player->CurAttPower_ == _Player->MaxAttPower_)
		{
			return;
		}

		_Player->CurAttPower_ = _Player->MaxAttPower_;
	}
	break;
	case ItemType::Niddle:
	{
		ChangeState(PlayerState::Revival);
		return;
	}
	break;
	case ItemType::Devil:
	{
		IsDevil = true;

		// 1. ���� ����Ű�� �ݴ�� �̵�


		// 2. CurAttCount��ŭ �������� �ڵ� ���� 


	}
	break;
	case ItemType::Shoes:
	{
		// ����� ������ 
	}
	break;
	case ItemType::Shield:
	{
		AddAccTime(Time_);

		IsShield = true;
		EffectRenderer_->On();

		// 3�ʰ� ������ ���� ���� �� ResetTime
		if (3.f < GetAccTime())
		{
			IsShield = false;
			EffectRenderer_->Off();
			ReSetAccTime();
		}
	}
	break;
	case ItemType::SuperJump:
	{

	}
	break;
	case ItemType::Owl:
	{
		ChangeState(PlayerState::OnOwl);
		return;
	}
	break;
	case ItemType::Turtle:
	{
		ChangeState(PlayerState::OnTurtle);
		return;
	}
	break;
	case ItemType::SpaceShip:
	{
		ChangeState(PlayerState::OnUFO);
		return;
	}
	break;
	case ItemType::Bubble_Dark:
	{
		// ��ǳ�� �̹��� ����
	}
	break;
	default:
	{
		CurSpeed_ = CurSpeed_;
		CurAttCount_ = CurAttCount_;
		CurAttPower_ = CurAttPower_;

		IsShield = false;
		IsDevil = false;
	}
		break;
	}

}

ItemType Player::CheckItem(float4 _Pos)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	ItemBlockTile* Tiles_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y);
	if (Tiles_ == nullptr)
	{
		return ItemType::Max;
	}
	else
	{
		return Tiles_->ItemType_;
	}

	return ItemType();
}
