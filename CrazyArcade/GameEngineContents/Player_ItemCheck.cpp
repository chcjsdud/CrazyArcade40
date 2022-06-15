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
		if (_Player->CurSpeed_ >= _Player->MaxSpeed_)
		{
			return;
		}

		_Player->CurSpeed_ += 0.5f;

	}
	break;
	case ItemType::Bubble:
	{
		if (_Player->CurAttCount_ >= _Player->MaxAttCount_)
		{
			return;
		}

		_Player->CurAttCount_ += 1;
	}
	break;
	case ItemType::Fluid:
	{
		if (_Player->CurAttPower_ >= _Player->MaxAttPower_)
		{
			return;
		}

		_Player->CurAttPower_ += 1.f;
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
		CurItem_ = ItemType::Niddle; // ItemUI 띄우기용

		if (true == IsItemKey())
		{
			IsShield = false;
		}
		else if (true == IsJump)
		{
			IsJump = false;
		}

		IsNiddle = true;
	}
	break;
	case ItemType::Devil:
	{
		if (true == IsDevil)
		{
			IsMove = true;
			return;
		}
		// 누른 방향키와 반대로 이동 + CurAttCount만큼 연속으로 자동 공격 
		AddAccTime(Time_);

		IsDevil = true;
		IsMove = false;

		CurDir_ = PlayerDir::None;
		CheckDir_ = PlayerDir::None;
		MoveDir = float4::ZERO;
	}
	break;
	case ItemType::Shoes:
	{
		// 물방울 던지기 
		//	IsShoes = true;
	}
	break;
	case ItemType::Shield:
	{
		CurItem_ = ItemType::Shield;
		if (true == IsNiddle)
		{
			IsNiddle = false;
		}
		else if (true == IsJump)
		{
			IsJump = false;
		}

		IsShield = true;
	}
	break;
	case ItemType::SuperJump:
	{
		CurItem_ = ItemType::SuperJump;
		IsJump = true;
	}
	break;
	case ItemType::Owl:
	{
		PlayerRideState_ = PlayerRideState::Owl;
		ChangeState(PlayerState::OnRide);
		return;
	}
	break;
	case ItemType::Turtle:
	{
		PlayerRideState_ = PlayerRideState::Turtle;
		ChangeState(PlayerState::OnRide);
		return;
	}
	break;
	case ItemType::SpaceShip:
	{
		Position_ = _Player->GetPosition();
		PlayerRideState_ = PlayerRideState::UFO;

		IsUFO = true;
		ChangeState(PlayerState::OnRide);
		return;
	}
	break;
	default:
	{
		//CurSpeed_ = CurSpeed_;
		//CurAttCount_ = CurAttCount_;
		//CurAttPower_ = CurAttPower_;

		//IsShield = false;
		//IsDevil = false;
	}
	break;
	}

}

void Player::ItemTime()
{

	if (true == UseShield)
	{
		// 3초가 지나면 무적 해제 및 ResetTime
		if (3.f < GetAccTime())
		{
			IsShield = false;
			IsInvincible = false;
			EffectRenderer_->Off();
			ReSetAccTime();
		}
	}


	if (true == IsDevil)
	{
		float Time = GetAccTime();
		// 10초가 지나면 데빌 모드 해제
		if (3.f < Time)
		{
			IsDevil = false;
			CurDir_ = PlayerDir::None;
			MoveDir = float4::ZERO;
			CheckDir_ = PlayerDir::None;

			ReSetAccTime();
		}

		Attack();

	}

	if (true == IsShield)
	{
		if (CurState_ != PlayerState::Damaged
			&& CurState_ != PlayerState::Fade
			&& CurState_ != PlayerState::Die)
		{
			if (true == IsItemKey())
			{
				GameEngineSound::SoundPlayOneShot("Shield.wav");
				IsInvincible = true;

				AddAccTime(Time_);
				EffectRenderer_->On();

				UseShield = true;
			}
		}
	}


	if (true == IsNiddle)
	{
		if (true == IsItemKey())
		{
			ChangeState(PlayerState::Revival);
			return;
		}

	}

	if (true == IsJump)
	{
		if (true == IsItemKey())
		{
			//ChangeState(PlayerState::Jump);
			//return;
		}
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
		ItemType ItemType_ = Tiles_->ItemType_;
		MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y);
		return ItemType_;
	}

	return ItemType();
}
