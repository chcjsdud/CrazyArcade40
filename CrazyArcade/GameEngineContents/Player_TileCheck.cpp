#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "MapGameObject.h"
#include "MapBackGround.h"
#include "GameEngine/GameEngine.h"
#include "GameItemObject.h"


// �÷��̾��� ���� Ÿ�� üũ 
void Player::TileCheckResultUpdate(BlockType _CurBlockType)
{
	switch (_CurBlockType)
	{
	case BlockType::WaveBlock:
	{
		// ������ �ƴ� ����
		if (false == IsInvincible)
		{
			// Ż ���� Ÿ�� �ִ� ���¿����� -> Idle
			if (CurState_ == PlayerState::IdleOwl
				|| CurState_ == PlayerState::IdleTurtle
				|| CurState_ == PlayerState::RidingOwl
				|| CurState_ == PlayerState::RidingTurtle
				|| CurState_ == PlayerState::RidingUFO)
			{
				ChangeState(PlayerState::Idle);
				return;
			}

			if (CurState_ != PlayerState::Die
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
		// ������ �ƴ� ����
		if (false == IsInvincible)
		{
			// Ż ���� Ÿ�� �ִ� ���¿����� -> Idle
			if (CurState_ == PlayerState::IdleOwl
				|| CurState_ == PlayerState::IdleTurtle
				|| CurState_ == PlayerState::RidingOwl
				|| CurState_ == PlayerState::RidingTurtle
				|| CurState_ == PlayerState::RidingUFO)
			{
				ChangeState(PlayerState::Idle);
				return;
			}

			if (CurState_ != PlayerState::Die
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
	case BlockType::ItemBlock:		// ������ üũ�ϴ� �κ� 
	{
		GameEngineSound::SoundPlayOneShot("eat_item.mp3");
		//int a = 0;
		PlayerInfoUpdate();
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

	// UFO�� ź ���°� �ƴ� ���� ������ üũ 
	//if (CurState_ != PlayerState::RidingUFO)
	//{
	//	PlayerInfoUpdate();
	//}
	//
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

// �� �� �翷 ������ üũ�� �� �� ��
void Player::FrontBlockCheckUpdate()
{
	LeftPos_1P = MainPlayer_1->GetPosition() + float4{ -40.0f, -20.0f };
	RightPos_1P = MainPlayer_1->GetPosition() + float4{ 0.0f, -20.0f };
	UpPos_1P = MainPlayer_1->GetPosition() + float4{ -20.0f, -40.0f };
	DownPos_1P = MainPlayer_1->GetPosition() + float4{ -20.0f, 0.0f };

	LeftPos_2P = MainPlayer_2->GetPosition() + float4{ -40.0f, -20.0f };
	RightPos_2P = MainPlayer_2->GetPosition() + float4{ 0.0f, -20.0f };
	UpPos_2P = MainPlayer_2->GetPosition() + float4{ -20.0f, -40.0f };
	DownPos_2P = MainPlayer_2->GetPosition() + float4{ -20.0f, 0.0f };

	// ���� ����
	switch (LeftBlock)
	{
	case BlockType::BoomBlock:
	{
		if (IsBoomblock == false) {
			IsLeftMove = false;
		}
	}
	break;
	case BlockType::FixBlock:
	{
		IsLeftMove = false;
	}
	break;
	case BlockType::PullBlock:
	{
		IsLeftMove = false;

		Box_ = GetLevel()->CreateActor<MapGameObject>();
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
	break;
	default:
	{
		IsLeftMove = true;
	}
	break;
	}

	// ������ ����
	switch (RightBlock)
	{
	case BlockType::BoomBlock:
	{
		if (IsBoomblock == false) {
			IsRightMove = false;
		}
	}
	break;
	case BlockType::FixBlock:
	{
		IsRightMove = false;
	}
	break;
	case BlockType::PullBlock:
	{
		IsRightMove = false;

		Box_ = GetLevel()->CreateActor<MapGameObject>();
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
	break;
	default:
	{
		IsRightMove = true;
	}
	break;
	}

	// ���� ����
	switch (UpBlock)
	{
	case BlockType::BoomBlock:
	{
		if (IsBoomblock == false) {
			IsUpMove = false;
		}
	}
	break;
	case BlockType::FixBlock:
	{
		IsUpMove = false;
	}
	break;
	case BlockType::PullBlock:
	{
		IsUpMove = false;

		Box_ = GetLevel()->CreateActor<MapGameObject>();
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
	break;
	default:
	{
		IsUpMove = true;
	}
	break;
	}


	// �Ʒ��� ����
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
		IsDownMove = false;
	}
	break;
	case BlockType::PullBlock:
	{
		IsDownMove = false;

		Box_ = GetLevel()->CreateActor<MapGameObject>();
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

// �÷��̾ ���ִ� ��ġ�� Ÿ���� � Ÿ���� �������� �˷��ִ� �Լ� return ���� Max�̸� - �ƹ��͵� ���� Ÿ���Դϴ�.
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

	if (ItemTiles_ != nullptr && ItemTiles_->ItemType_ != ItemType::Max)
	{
		return ItemTiles_->BlockType_;

	}


	return Tiles_->BlockType_;



}