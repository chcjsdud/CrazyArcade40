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
		//float Speed = _Player->CurSpeed_;

		//if (_Player->CurSpeed_ > Speed)
		//{
		//	return;
		//}

		if (_Player->CurSpeed_ >= _Player->MaxSpeed_)
		{
			return;
		}

		_Player->CurSpeed_ = _Player->CurSpeed_ + 1.0f;
	
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
		ChangeState(PlayerState::Revival);
		return;
	}
	break;
	case ItemType::Devil:
	{
		IsDevil = true;

		// 1. 누른 방향키와 반대로 이동


		// 2. CurAttCount만큼 연속으로 자동 공격 


	}
	break;
	case ItemType::Shoes:
	{
		// 물방울 던지기 
	}
	break;
	case ItemType::Shield:
	{
		IsShield = true;
		EffectRenderer_->On();
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
		// 물풍선 이미지 변경
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
	if (true == IsDevil)
	{
		AddAccTime(Time_);

		// 10초가 지나면 데빌 모드 해제
		if (10.f < GetAccTime())
		{
			IsDevil = false;
			ReSetAccTime();
		}
	}

	if (true == IsShield)
	{
		AddAccTime(Time_);

		// 3초가 지나면 무적 해제 및 ResetTime
		if (3.f < GetAccTime())
		{
			IsShield = false;
			EffectRenderer_->Off();
			ReSetAccTime();
		}
	}

	//if (nullptr != MainPlayer_1)
	//{

	//	Boom_ = GetLevel()->CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
	//	Boom_->SetMapTile(MapTile_);

	//	BoomCount_ = Boom_->ReturnPlayer1BoomCount();	// 내가 놓은 물풍선 개수 체크

	//	if (BoomCount_ >= CurAttCount_)	// 내가 놓은 물풍선 개수가 공격 가능 개수보다 같거나 크다 -> 공격하지 않는다
	//	{
	//		CanAttack = false;
	//	}
	//	
	//	if (BoomCount_ < CurAttCount_)
	//	{
	//		BoomCount_ = Boom_->ReturnPlayer1BoomCount();	// 내가 놓은 물풍선 개수 체크
	//		CanAttack = true;
	//	}

	//	//if (BoomCount_ < CurAttCount_)		// 내가 놓은 물풍선 개수가 공격 가능 개수보다 작으면 공격 가능
	//	//{
	//	//	
	//	//}
	//}

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
		ItemType ItemType_= Tiles_->ItemType_;
		MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y);
		return ItemType_;
	}

	return ItemType();
}
