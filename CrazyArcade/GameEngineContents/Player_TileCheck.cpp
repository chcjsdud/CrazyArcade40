#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "MapGameObject.h"
#include "MapBackGround.h"
#include "GameEngine/GameEngine.h"
#include "GameItemObject.h"


// 플레이어의 현재 타일 체크 
void Player::TileCheckResultUpdate(BlockType _CurBlockType)
{
	switch (_CurBlockType)
	{
	case BlockType::WaveBlock:
	{
		// 무적이 아닐 때만
		if (false == IsInvincible)
		{
			// 탈 것을 타고 있는 상태에서는 -> Idle
			if (PlayerRideState_ != PlayerRideState::Max)
			{
				ChangeState(PlayerState::Idle);
				return;
			}
			else if(CurState_ != PlayerState::Die
					&& CurState_ != PlayerState::DamageStart
					&& CurState_ != PlayerState::Damaged
					&& CurState_ != PlayerState::Fade)
			{
				ChangeState(PlayerState::DamageStart);
				return;
			}
		}
		else
		{
			return;

		}
	}
	break;
	case BlockType::BubbleBlock:
	{
		// 무적이 아닐 때만
		if (false == IsInvincible)
		{
			// 탈 것을 타고 있는 상태에서는 -> Idle
			if (PlayerRideState_ != PlayerRideState::Max)
			{
				ChangeState(PlayerState::Idle);
				return;
			}
			else if(CurState_ != PlayerState::Die
				&& CurState_ != PlayerState::DamageStart
				&& CurState_ != PlayerState::Damaged
				&& CurState_ != PlayerState::Fade)
			{
				ChangeState(PlayerState::DamageStart);
				return;
			}
		}
		else
		{
			return;
		}
	}
	break;
	case BlockType::BushBlock:
	{
		PlayerAnimationRender_->SetAlpha(0);

	}
	break;
	case BlockType::ItemBlock:		// 아이템 체크하는 부분 
	{
		if (PlayerRideState_ != PlayerRideState::UFO)
		{
			GameEngineSound::SoundPlayOneShot("eat_item.mp3");
			PlayerInfoUpdate();
		}
	}
	break;
	case BlockType::BoomBlock:
	{
		IsBoomblock = true;
		break;
	}
	break;
	default:
	{
		IsBoomblock = false;
		PlayerAnimationRender_->SetAlpha(255);
	}
	break;
	}
}

void Player::TileCheckResult()
{
	//PositionUpdate();

	if (Type == PlayerType::Player1)
	{
		float4 Pos = MainPlayer_1->GetPosition();
		CurBlockType1_ = CheckBlockTile(Pos + float4{ -20.0f,-20.0f });
		TileCheckResultUpdate(CurBlockType1_);
	}

	if (nullptr != MainPlayer_2)
	{

		if (Type == PlayerType::Player2)
		{
			float4 Pos = MainPlayer_2->GetPosition();
			CurBlockType2_ = CheckBlockTile(Pos + float4{ -20.0f, -20.0f });
			TileCheckResultUpdate(CurBlockType2_);
		}

	}

}

// 앞 뒤 양옆 블럭을 체크한 뒤 할 일
void Player::FrontBlockCheckUpdate()
{
	if (nullptr != MainPlayer_1)
	{
		LeftPos_1P = MainPlayer_1->GetPosition() + float4{ -40.0f, -20.0f };
		RightPos_1P = MainPlayer_1->GetPosition() + float4{ 0.0f, -20.0f };
		UpPos_1P = MainPlayer_1->GetPosition() + float4{ -20.0f, -40.0f };
		DownPos_1P = MainPlayer_1->GetPosition() + float4{ -20.0f, 0.0f };
	}

	if(nullptr != MainPlayer_2)
	{
		LeftPos_2P = MainPlayer_2->GetPosition() + float4{ -40.0f, -20.0f };
		RightPos_2P = MainPlayer_2->GetPosition() + float4{ 0.0f, -20.0f };
		UpPos_2P = MainPlayer_2->GetPosition() + float4{ -20.0f, -40.0f };
		DownPos_2P = MainPlayer_2->GetPosition() + float4{ -20.0f, 0.0f };
	}


	// 왼쪽 블럭
	switch (LeftBlock)
	{
	case BlockType::BoomBlock:
	{
		if (IsBoomblock == false)
		{
			if (true == IsShoes)
			{
				IsLeftMove = false;
				if (Playeractorvalue_ < 2)
				{
					Bubble_ = GetLevel()->CreateActor<MapGameObject>();
					Playeractorvalue_ += 1;
				}

				Bubble_->SetMapTile(MapTile_);
				if (PlayerDir::Left == CurDir_
					&& true == IsMoveKey())
				{
					if (Type == PlayerType::Player1)
					{
						Bubble_->PushBubble(LeftPos_1P, BlockDir::LEFT, 1);

					}
					else if (Type == PlayerType::Player2)
					{
						Bubble_->PushBubble(LeftPos_2P, BlockDir::LEFT, 2);
					}
				}
			}
			else
			{
				IsLeftMove = false;
			}
		}
		
	}
	break;
	case BlockType::FixBlock:
	{
		if (CurState_ == PlayerState::RidingRide&& PlayerRideState_ != PlayerRideState::UFO)
		{
			IsLeftMove = true;
		}
		else
		{
			IsLeftMove = false;
		}
	}
	break;
	case BlockType::PullBlock:
	{
		if (CurState_ == PlayerState::RidingRide && PlayerRideState_ != PlayerRideState::UFO)
		{
			IsLeftMove = true;
		}
		else
		{
			IsLeftMove = false;
			if (Playeractorvalue_ < 2)
			{
				Box_ = GetLevel()->CreateActor<MapGameObject>();
				Playeractorvalue_ += 1;
			}
			Box_->SetMapTile(MapTile_);
			if (PlayerDir::Left == CurDir_
				&& true == IsMoveKey())
			{
				if (Type == PlayerType::Player1)
				{
					Box_->PushBlock(LeftPos_1P, BlockDir::LEFT);

				}
				else if (Type == PlayerType::Player2)
				{
					Box_->PushBlock(LeftPos_2P, BlockDir::LEFT);
				}
			}
		}

	}
	break;
	default:
	{
		IsLeftMove = true;
	}
	break;
	}

	// 오른쪽 블럭
	switch (RightBlock)
	{
	case BlockType::BoomBlock:
	{
		if (IsBoomblock == false)
		{
			if (true == IsShoes)
			{
				IsRightMove = false;
				InputDir_ = CurDir_;

			/*	if (Playeractorvalue_ < 2)
				{

					Playeractorvalue_ += 1;
				}*/

				Bubble_->SetMapTile(MapTile_);
				if (PlayerDir::Right == CurDir_
					&& true == IsMoveKey())
				{
					if(InputDir_ == CurDir_)
					{
						if (Type == PlayerType::Player1)
						{
							Bubble_->PushBubble(RightPos_1P, BlockDir::RIGHT, 1);

						}
						else if (Type == PlayerType::Player2)
						{
							Bubble_->PushBubble(RightPos_2P, BlockDir::RIGHT, 2);
						}
					}
				
				}
			}
			else
			{
				IsRightMove = false;
			}
		}

	}
	break;
	case BlockType::FixBlock:
	{
		if (CurState_ == PlayerState::RidingRide && PlayerRideState_ != PlayerRideState::UFO)
		{
			IsRightMove = true;
		}
		else
		{
			IsRightMove = false;
		}
	}
	break;
	case BlockType::PullBlock:
	{
		if (CurState_ == PlayerState::RidingRide && PlayerRideState_ != PlayerRideState::UFO)
		{
			IsRightMove = true;
		}
		else
		{
			IsRightMove = false;

			if (Playeractorvalue_ < 2)
			{
				Box_ = GetLevel()->CreateActor<MapGameObject>();
				Playeractorvalue_ += 1;
			}
			Box_->SetMapTile(MapTile_);
			if (PlayerDir::Right == CurDir_
				&& true == IsMoveKey())
			{
				if (Type == PlayerType::Player1)
				{
					Box_->PushBlock(RightPos_1P, BlockDir::RIGHT);

				}
				else if (Type == PlayerType::Player2)
				{
					Box_->PushBlock(RightPos_2P, BlockDir::RIGHT);
				}
			}
		}
	
	}
	break;
	default:
	{
		IsRightMove = true;
	}
	break;
	}

	// 위쪽 블럭
	switch (UpBlock)
	{
	case BlockType::BoomBlock:
	{
		if (IsBoomblock == false)
		{
			if (true == IsShoes)
			{
				IsUpMove = false;
				if (Playeractorvalue_ < 2)
				{
					Bubble_ = GetLevel()->CreateActor<MapGameObject>();
					Playeractorvalue_ += 1;
				}

				Bubble_->SetMapTile(MapTile_);
				if (PlayerDir::Up == CurDir_
					&& true == IsMoveKey())
				{
					if (Type == PlayerType::Player1)
					{
						Bubble_->PushBubble(UpPos_1P, BlockDir::UP, 1);

					}
					else if (Type == PlayerType::Player2)
					{
						Bubble_->PushBubble(UpPos_2P, BlockDir::UP, 2);
					}
				}
			}
			else
			{
				IsUpMove = false;
			}
		}

	}
	break;
	case BlockType::FixBlock:
	{
		if (CurState_ == PlayerState::RidingRide && PlayerRideState_ != PlayerRideState::UFO)
		{
			IsUpMove = true;
		}
		else
		{
			IsUpMove = false;
		}
	}
	break;
	case BlockType::PullBlock:
	{
		if (CurState_ == PlayerState::RidingRide && PlayerRideState_ != PlayerRideState::UFO)
		{
			IsUpMove = true;
		}
		else
		{
			IsUpMove = false;

			if (Playeractorvalue_ < 2)
			{
				Box_ = GetLevel()->CreateActor<MapGameObject>();
				Playeractorvalue_ += 1;
			}
			Box_->SetMapTile(MapTile_);
			if (PlayerDir::Up == CurDir_
				&& true == IsMoveKey())
			{
				if (Type == PlayerType::Player1)
				{
					Box_->PushBlock(UpPos_1P, BlockDir::UP);

				}
				else if (Type == PlayerType::Player2)
				{
					Box_->PushBlock(UpPos_2P, BlockDir::UP);
				}
			}
		}
	}
	break;
	default:
	{
		IsUpMove = true;
	}
	break;
	}


	// 아래쪽 블럭
	switch (DownBlock)
	{
	case BlockType::BoomBlock:
	{
		if (IsBoomblock == false) {
			IsDownMove = false;
		}
	}
	break;
	case BlockType::FixBlock:
	{
		if (CurState_ == PlayerState::RidingRide && PlayerRideState_ != PlayerRideState::UFO)
		{
			IsDownMove = true;
		}
		else
		{
			IsDownMove = false;
		}
	}
	break;
	case BlockType::PullBlock:
	{
		if (CurState_ == PlayerState::RidingRide && PlayerRideState_ != PlayerRideState::UFO)
		{
			IsDownMove = true;
		}
		else
		{
			IsDownMove = false;

			if (Playeractorvalue_ < 2)
			{
				Box_ = GetLevel()->CreateActor<MapGameObject>();
				Playeractorvalue_ += 1;
			}
			Box_->SetMapTile(MapTile_);
			if (PlayerDir::Down == CurDir_
				&& true == IsMoveKey())
			{
				if (Type == PlayerType::Player1)
				{
					Box_->PushBlock(DownPos_1P, BlockDir::DOWN);

				}
				else if (Type == PlayerType::Player2)
				{
					Box_->PushBlock(DownPos_2P, BlockDir::DOWN);
				}
			}
		}
	}
	break;
	default:
	{
		IsDownMove = true;
	}
	break;
	}
}

void Player::FrontBlockCheck()
{
	if (Type == PlayerType::Player1)
	{
		float4 Pos = MainPlayer_1->GetPosition();

		TileIndex RightIndex = MapTile_->GetTileIndex(Pos + float4{ 10.f, 0.f });
		TileIndex DownIndex = MapTile_->GetTileIndex(Pos + float4{ 0.f, 10.f });



		LeftBlock = CheckBlockTile(Pos + float4{ -40.0f, -20.0f });
		UpBlock = CheckBlockTile(Pos + float4{ -20.0f, -40.0f });

		if (RightIndex.X != 15)
		{
			RightBlock = CheckBlockTile(Pos + float4{ 0.0f, -20.0f });
		}
		if (DownIndex.Y != 13)
		{
			DownBlock = CheckBlockTile(Pos + float4{ -20.0f, 0.0f });
		}

		FrontBlockCheckUpdate();
	}

	if (nullptr != MainPlayer_2)
	{
		if (Type == PlayerType::Player2)
		{
			float4 Pos = MainPlayer_2->GetPosition();


			TileIndex RightIndex = MapTile_->GetTileIndex(Pos + float4{ 10.f, 0.f });
			TileIndex DownIndex = MapTile_->GetTileIndex(Pos + float4{ 0.f, 10.f });



			LeftBlock = CheckBlockTile(Pos + float4{ -40.0f, -20.0f });
			UpBlock = CheckBlockTile(Pos + float4{ -20.0f, -40.0f });

			if (RightIndex.X != 15)
			{
				RightBlock = CheckBlockTile(Pos + float4{ 0.0f, -20.0f });
			}
			if (DownIndex.Y != 13)
			{
				DownBlock = CheckBlockTile(Pos + float4{ -20.0f, 0.0f });
			}

			FrontBlockCheckUpdate();
		}
	}

}

// 플레이어가 서있는 위치의 타일이 어떤 타입의 블럭인지 알려주는 함수 return 값이 Max이면 - 아무것도 없는 타일입니다.
BlockType Player::CheckBlockTile(float4 _Pos)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	ItemBlockTile* ItemTiles_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y);

	if (Tiles_ == nullptr)
	{
		return BlockType::Max;
	}


	if (Tiles_->BlockType_ == BlockType::WaveBlock)
	{
		return  BlockType::WaveBlock;
	}
	if (Tiles_->BlockType_ == BlockType::BubbleBlock)
	{
		return  BlockType::BubbleBlock;
	}

	if (ItemTiles_ != nullptr && ItemTiles_->ItemType_ != ItemType::Max)
	{
		return ItemTiles_->BlockType_;

	}


	return Tiles_->BlockType_;



}
