#include"MapGameObject.h"
#include"GameItemObject.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

size_t MapGameObject::Player1BoomNum_;
size_t MapGameObject::Player2BoomNum_;
MapGameObject::MapGameObject()
	:MapTile_(nullptr),
	GameItem_(nullptr),
	ItemValue_(ItemType::Max),
	AllBlockTiles_(),
	MaxValue_(0),
	RollerValue_(0),
	BubbleValue_(0),
	FluidValue_(0),
	UltraBubbleValue_(0),
	RedDevilValue_(0),
	DevilValue_(0),
	ShoesValue_(0),
	NiddleValue_(0),
	ShieldValue_(0),
	SuperJumpValue_(0),
	TurtleValue_(0),
	SpaceShipValue_(0),
	OwlValue_(0),
	Bubble_DarkValue_(0),
	Bubble_BossValue_(0),
	Bubble_DefaultValue_(0),
	GhostValue_(0)

{

}

MapGameObject::~MapGameObject()
{

}

void MapGameObject::Start()
{
	SetPosition({ 0.0f, 0.0f });
	BlockValueSetting();
}

void MapGameObject::Update()
{
	if (MapTile_ == nullptr)
	{
		return;
	}
	WaveDeathAni();
	BossWaveDeath();
	DestroyWave();
	DestroyBoom();
	DestroyBlock();
	BlockMoveUpdate();
	BubbleMoveUpdate();

}


void MapGameObject::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BlockValueSetting();
}

BlockType MapGameObject::CheckTile(float4 _Pos) {
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	if (0 > TileIndex_.X)
	{
		return BlockType::NoBlock;
	}
	if (0 > TileIndex_.Y)
	{
		return BlockType::NoBlock;
	}
	if (14 < TileIndex_.X)
	{
		return BlockType::NoBlock;
	}
	if (12 < TileIndex_.Y)
	{
		return BlockType::NoBlock;
	}

	BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	if (Tiles_ == nullptr)
	{
		return BlockType::Max;
	}
	else
	{
		return Tiles_->BlockType_;
	}
	}


void MapGameObject::CreateBlock(float4 _Pos, std::string _Box)
{
	GameEngineString::ToUpper(_Box);

	if (BlockType::NoBlock == CheckTile(_Pos))
	{
		return;
	}

	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	BlockTile* Check = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	if (Check != nullptr)
	{
		return;
	}
	BlockTile* Block_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
	Block_->Renderer = CreateRenderer();
	Block_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y - 4});
	Block_->Renderer->SetOrder(static_cast<int>(ORDER::PLAYER));
	Block_->Renderer->CreateAnimation("DestroyBlock.bmp", "Death", 0, 3, 0.1f, false);
	Block_->TilePos_=TileCenterPos_;
	if (_Box == "WALLBLOCK")
	{
		Block_->Renderer->SetImage("TIleBase.BMP");
		Block_->BlockType_ = BlockType::WallBlock;
	}
	//////////////////////////////////////////캠 프///////////////////////////////////////////////

	if (_Box == "CAMPBLOCK1")
	{
		Block_->Renderer->SetImage("CampBlock1.BMP");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CAMPBLOCK2")
	{
		Block_->Renderer->SetImage("CampBlock2.BMP");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CAMPBUSH1")
	{
		Block_->Renderer->CreateAnimation("CampBush1.bmp", "CampBush1", 0, 4, 0.1f, false);
		Block_->Renderer->ChangeAnimation("CampBush1");
		Block_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y - 13.0f });
		Block_->BlockType_ = BlockType::BushBlock;
	}
	else if (_Box == "CAMPBUSH2")
	{
		Block_->Renderer->CreateAnimation("CampBush2.bmp", "CampBush2", 0, 5, 0.1f, false);
		Block_->Renderer->ChangeAnimation("CampBush2");
		Block_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y -10.0f});
		Block_->BlockType_ = BlockType::BushBlock;
	}
	else if (_Box == "CAMPMOVEBOX1")
	{
		Block_->Renderer->SetImage("CampMoveBox1.bmp");
		Block_->BlockType_ = BlockType::PullBlock;
	}
	else if (_Box == "CAMPMOVEBOX2")
	{
		Block_->Renderer->CreateAnimation("CampMoveBox2.bmp", "CampMoveBox2_1", 0, 0, 0.0f, false);
		Block_->Renderer->ChangeAnimation("CampMoveBox2_1");
		Block_->BlockHp_ = 3; 
		Block_->BlockType_ = BlockType::PullBlock;
	}
	else if (_Box == "CAMPMOVEBOX3")
	{
		Block_->Renderer->CreateAnimation("CampMoveBox2.bmp", "CampMoveBox2_3", 2, 2, 0.0f, false);
		Block_->Renderer->ChangeAnimation("CampMoveBox2_3");
		Block_->BlockHp_ = 1;
		Block_->BlockType_ = BlockType::PullBlock;
	}

	//////////////////////////////////////////공동 묘지///////////////////////////////////////////////

	if (_Box == "CEMETORYBLOCK1")
	{
		Block_->Renderer->SetImage("CemetoryBlock1.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK2")
	{
		Block_->Renderer->SetImage("CemetoryBlock2.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK3")
	{
		Block_->Renderer->SetImage("CemetoryBlock3.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK4")
	{
		Block_->Renderer->SetImage("CemetoryBlock4.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK5")
	{
		Block_->Renderer->SetImage("CemetoryBlock5.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK6")
	{
		Block_->Renderer->SetImage("CemetoryBlock6.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK7")
	{
		Block_->Renderer->SetImage("CemetoryBlock7.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK8")
	{
		Block_->Renderer->SetImage("CemetoryBlock8.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYSTONE1")
	{
		Block_->Renderer->SetImage("CemetoryStone1.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYSTONE2")
	{
		Block_->Renderer->SetImage("CemetoryStone2.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYMOVEBOX1")
	{
		Block_->Renderer->SetImage("CemetoryMoveBox1.bmp");
		Block_->BlockType_ = BlockType::PullBlock;
	}
	else if (_Box == "CEMETORYMOVEBOX2")
	{
		Block_->Renderer->SetImage("CemetoryMoveBox2.bmp");
		Block_->BlockType_ = BlockType::PullBlock;
	}
	else if (_Box == "CEMETORYMOVEBOX2")
	{
		Block_->Renderer->SetImage("CemetoryMoveBox3.bmp");
		Block_->BlockType_ = BlockType::PullBlock;
	}

	////////////////////////////////////////// 빌리지 ///////////////////////////////////////////////

	if (_Box == "VILLAGEBLOCK1")
	{
		Block_->Renderer->SetImage("VillageBlock1.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "VILLAGEBLOCK2")
	{
		Block_->Renderer->SetImage("VillageBlock2.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "VILLAGEMOVEBOX1")
	{
		Block_->Renderer->SetImage("VillageMoveBox1.bmp");
		Block_->BlockType_ = BlockType::PullBlock;
	}
	else if (_Box == "VILLAGEBUSH1")
	{
		Block_->Renderer->CreateAnimation("VillageBush1.bmp", "VillageBush1", 0, 4, 0.1f, false);
		Block_->Renderer->ChangeAnimation("VillageBush1");
		Block_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y - 20 });
		Block_->BlockType_ = BlockType::BushBlock;
	}

	////////////////////////////////////////// 몬스터 ///////////////////////////////////////////////

	if (_Box == "MONSTERBLOCK1")
	{
		Block_->Renderer->SetImage("MonsterBlock1.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK2")
	{
		Block_->Renderer->SetImage("MonsterBlock2.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK3")
	{
		Block_->Renderer->SetImage("MonsterBlock3.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK4")
	{
		Block_->Renderer->SetImage("MonsterBlock4.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK5")
	{
		Block_->Renderer->SetImage("MonsterBlock5.bmp");
		Block_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y - 20 });
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK6")
	{
		Block_->Renderer->SetImage("MonsterBlock6.bmp");
		Block_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y - 20 });
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK7")
	{
		Block_->Renderer->SetImage("MonsterBlock7.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK8")
	{
		Block_->Renderer->SetImage("MonsterBlock8.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERMOVEBOX1")
	{
		Block_->Renderer->SetImage("MonsterMoveBox1.bmp");
		Block_->BlockType_ = BlockType::PullBlock;
	}
	AllBlockTiles_.push_back(Block_);
}


void MapGameObject::CreateBoom(float4 _Pos, float _Power, int _PlayerNum)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	BlockTile* CheckBlock = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	ItemBlockTile* CheckItemBlock = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y);
	
	if (CheckBlock != nullptr && CheckBlock->BlockType_ == BlockType::BushBlock)
	{
		CheckBlock->BlockType_ = BlockType::BoomBlock;
		CheckBlock->TileIndex_ = TileIndex_;
		CheckBlock->TilePos_ = _Pos;
		CheckBlock->DeathTime_ = 3.0f;
		CheckBlock->Power_ = _Power;
		if (_PlayerNum == 1)
		{
			Player1BlockTiles_.push_back(CheckBlock);
			Player1BoomNum_ += 1;
		}
		else if (_PlayerNum == 2)
		{
			Player2BlockTiles_.push_back(CheckBlock);
			Player2BoomNum_ += 1;
		}
	}
	else if (CheckBlock != nullptr && CheckItemBlock->BlockType_ == BlockType::ItemBlock)
	{
		MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y);
		BlockTile* Boom_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
		Boom_->BlockType_ = BlockType::BoomBlock;
		Boom_->Renderer = CreateRenderer();
		Boom_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y + 20 });
		Boom_->Renderer->CreateAnimation("Bubble_Dark.bmp", "BubbleDark", 0, 3, 0.2f, true);
		Boom_->Renderer->CreateAnimation("Bubble_Default.bmp", "BubbleDefault", 0, 3, 0.2f, true);
		Boom_->Renderer->CreateAnimation("Bubble_Boss.bmp", "BubbleBoss", 0, 3, 0.2f, true);
		Boom_->Renderer->ChangeAnimation("BubbleDefault");
		Boom_->TileIndex_ = TileIndex_;
		Boom_->TilePos_ = _Pos;
		Boom_->DeathTime_ = 3.0f;
		Boom_->Power_ = _Power;	
		if (_PlayerNum == 1)
		{
			Player1BlockTiles_.push_back(Boom_);
			Player1BoomNum_ += 1;
		}
		else if (_PlayerNum == 2)
		{
			Player2BlockTiles_.push_back(Boom_);
			Player2BoomNum_ += 1;
		}
	}
	else if (CheckBlock != nullptr)
	{
		return;
	}
	else if (CheckBlock == nullptr)
	{
		BlockTile* Boom_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
		Boom_->BlockType_ = BlockType::BoomBlock;
		Boom_->Renderer = CreateRenderer();
		Boom_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y + 20 });
		Boom_->Renderer->CreateAnimation("Bubble_Dark.bmp", "BubbleDark", 0, 3, 0.2f, true);
		Boom_->Renderer->CreateAnimation("Bubble_Default.bmp", "BubbleDefault", 0, 3, 0.2f, true);
		Boom_->Renderer->CreateAnimation("Bubble_Boss.bmp", "BubbleBoss", 0, 3, 0.2f, true);
		Boom_->Renderer->ChangeAnimation("BubbleDefault");
		Boom_->TileIndex_ = TileIndex_;
		Boom_->TilePos_ = _Pos;
		Boom_->DeathTime_ = 3.0f;
		Boom_->Power_ = _Power;
		if (_PlayerNum == 1)
		{
			Player1BlockTiles_.push_back(Boom_);
			Player1BoomNum_ += 1;
		}
		else if (_PlayerNum == 2)
		{
			Player2BlockTiles_.push_back(Boom_);
			Player2BoomNum_ += 1;
		}
	}

}
void MapGameObject::PushBubble(float4 _Pos, BlockDir _Dir, int _PlayerNum)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	BlockTile* PushTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	if (PushTile_ == nullptr)
	{
		return;
	}

	if (BlockDir::LEFT == _Dir)
	{
		if (TileIndex_.X - 1 < 0)
		{
			return;
		}
		int count = 0;
		for (int i = 1; 0 <= TileIndex_.X - i; i++)
		{
			BlockTile* NextTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X - i, TileIndex_.Y);
			ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X - i, TileIndex_.Y);
			if (NextTile_ != nullptr&& ItemTile_->BlockType_ != BlockType::ItemBlock && NextTile_->BlockType_ != BlockType::BushBlock)
			{
				count = i-1;
				break;
			}
		}
		if (count == 0)
		{
			return;
		}
		BlockTile* NextTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X - count, TileIndex_.Y);
		ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X - count, TileIndex_.Y);
		if (ItemTile_ != nullptr && ItemTile_->BlockType_ == BlockType::ItemBlock)
		{
			MapTile_->DeleteTile(TileIndex_.X - count, TileIndex_.Y);
		}
		if (NextTile_ == nullptr)
		{
			BlockTile* NextTile_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X - count, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
			NextTile_->Renderer = PushTile_->Renderer;
			NextTile_->Renderer->SetPivot({ TileCenterPos_.x - count*40, TileCenterPos_.y + 20 });
			NextTile_->TilePos_ = PushTile_->TilePos_;
			NextTile_->TileIndex_ = TileIndex_;
			NextTile_->TileIndex_.X -= count;
			NextTile_->BlockType_ = PushTile_->BlockType_;
			NextTile_->DeathTime_ = 3.0f;
			NextTile_->Power_ = PushTile_->Power_;
			NextTile_->BlockDir_ = BlockDir::LEFT;
			float4 NextTileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X - count, TileIndex_.Y);
			NextTile_->MoveNextTilePos_ = NextTileCenterPos_;
			MoveBubble_.push_back(NextTile_);
			PushTile_->MoveOn = true;
			MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y);
			if (_PlayerNum == 1)
			{
				for (int i = 0; i < Player1BlockTiles_.size(); i++)
				{
					if (Player1BlockTiles_[i] == PushTile_)
					{
						Player1BlockTiles_.erase(Player1BlockTiles_.begin() + i);
						Player1BlockTiles_.push_back(NextTile_);

					}
				}
			}
			if (_PlayerNum == 2)
			{
				for (int i = 0; i < Player2BlockTiles_.size(); i++)
				{
					if (Player1BlockTiles_[i] == PushTile_)
					{
						Player2BlockTiles_.erase(Player1BlockTiles_.begin() + i);
						Player2BlockTiles_.push_back(NextTile_);

					}
				}
			}

		}
	}
	if (BlockDir::RIGHT == _Dir)
	{
		if (TileIndex_.X + 1 > 14)
		{
			return;
		}	
		int count = 0;
		for (int i = 0; 14 >= TileIndex_.X + i; i++)
		{
			BlockTile* NextTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X + i, TileIndex_.Y);
			ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X + i, TileIndex_.Y);
			if (NextTile_ != nullptr && ItemTile_->BlockType_ != BlockType::ItemBlock && NextTile_->BlockType_ != BlockType::BushBlock)
			{
				count = i - 1;
				break;
			}
		}
		BlockTile* NextTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X + count, TileIndex_.Y);
		ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X + count, TileIndex_.Y);
		if (ItemTile_ != nullptr && ItemTile_->BlockType_ == BlockType::ItemBlock)
		{
			MapTile_->DeleteTile(TileIndex_.X + count, TileIndex_.Y);
		}
		if (NextTile_ == nullptr)
		{
			BlockTile* NextTile_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X + count, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
			NextTile_->Renderer = PushTile_->Renderer;
			NextTile_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y + 20 });
			NextTile_->TilePos_ = PushTile_->TilePos_;
			NextTile_->BlockType_ = PushTile_->BlockType_;
			NextTile_->TileIndex_ = TileIndex_;
			NextTile_->TileIndex_.X += count;
			NextTile_->DeathTime_ = 3.0f;
			NextTile_->Power_ = PushTile_->Power_;
			NextTile_->BlockDir_ = BlockDir::RIGHT;
			float4 NextTileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X + count, TileIndex_.Y);
			NextTile_->MoveNextTilePos_ = NextTileCenterPos_;
			MoveBubble_.push_back(NextTile_);
			PushTile_->MoveOn = true;
			MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y);
			if (_PlayerNum == 1)
			{
				for (int i = 0; i < Player1BlockTiles_.size(); i++)
				{
					if (Player1BlockTiles_[i] == PushTile_)
					{
						Player1BlockTiles_.erase(Player1BlockTiles_.begin() + i);
						Player1BlockTiles_.push_back(NextTile_);

					}
				}
			}
			if (_PlayerNum == 2)
			{
				for (int i = 0; i < Player2BlockTiles_.size(); i++)
				{
					if (Player1BlockTiles_[i] == PushTile_)
					{
						Player2BlockTiles_.erase(Player1BlockTiles_.begin() + i);
						Player2BlockTiles_.push_back(NextTile_);

					}
				}
			}
		}
	}
	if (BlockDir::DOWN == _Dir)
	{
		if (TileIndex_.Y + 1 > 12)
		{
			return;
		}
		int count = 0;
		for (int i = 0; 12 >= TileIndex_.Y + i; i++)
		{
			BlockTile* NextTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X , TileIndex_.Y + i);
			ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y + i);
			if (NextTile_ != nullptr && ItemTile_->BlockType_ != BlockType::ItemBlock && NextTile_->BlockType_ != BlockType::BushBlock)
			{
				count = i - 1;
				break;
			}
		}
		BlockTile* NextTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y + count);
		ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y + count);
		if (ItemTile_ != nullptr && ItemTile_->BlockType_ == BlockType::ItemBlock)
		{
			MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y + count);
		}
		if (NextTile_ == nullptr)
		{
			BlockTile* NextTile_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y + count, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
			NextTile_->Renderer = PushTile_->Renderer;
			NextTile_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y + 20 });
			NextTile_->TilePos_ = PushTile_->TilePos_;
			NextTile_->BlockType_ = PushTile_->BlockType_;
			NextTile_->TileIndex_ = TileIndex_;
			NextTile_->TileIndex_.Y += count;
			NextTile_->DeathTime_ = 3.0f;
			NextTile_->Power_ = PushTile_->Power_;
			NextTile_->BlockDir_ = BlockDir::DOWN;
			float4 NextTileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y + count);
			NextTile_->MoveNextTilePos_ = NextTileCenterPos_;
			MoveBubble_.push_back(NextTile_);
			PushTile_->MoveOn = true;
			MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y);
			if (_PlayerNum == 1)
			{
				for (int i = 0; i < Player1BlockTiles_.size(); i++)
				{
					if (Player1BlockTiles_[i] == PushTile_)
					{
						Player1BlockTiles_.erase(Player1BlockTiles_.begin() + i);
						Player1BlockTiles_.push_back(NextTile_);

					}
				}
			}
			if (_PlayerNum == 2)
			{
				for (int i = 0; i < Player2BlockTiles_.size(); i++)
				{
					if (Player1BlockTiles_[i] == PushTile_)
					{
						Player2BlockTiles_.erase(Player1BlockTiles_.begin() + i);
						Player2BlockTiles_.push_back(NextTile_);

					}
				}
			}
		}
	}
	if (BlockDir::UP == _Dir)
	{
		if (TileIndex_.Y - 1 < 0)
		{
			return;
		}
		int count = 0;
		for (int i = 0; 0 <= TileIndex_.Y - i; i++)
		{
			BlockTile* NextTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y - i);
			ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y - i);
			if (NextTile_ != nullptr && ItemTile_->BlockType_ != BlockType::ItemBlock && NextTile_->BlockType_ != BlockType::BushBlock)
			{
				count = i - 1;
				break;
			}
		}
		BlockTile* NextTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y - count);
		ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y - count);
		if (ItemTile_ != nullptr && ItemTile_->BlockType_ == BlockType::ItemBlock)
		{
			MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y + 1);
		}
		if (NextTile_ == nullptr)
		{
			BlockTile* NextTile_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y - count, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
			NextTile_->Renderer = PushTile_->Renderer;
			NextTile_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y + 20 });
			NextTile_->TilePos_ = PushTile_->TilePos_;
			NextTile_->BlockType_ = PushTile_->BlockType_;
			NextTile_->TileIndex_ = TileIndex_;
			NextTile_->TileIndex_.Y -= count;
			NextTile_->DeathTime_ = 3.0f;
			NextTile_->Power_ = PushTile_->Power_;
			NextTile_->BlockDir_ = BlockDir::UP;
			float4 NextTileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y - count);
			NextTile_->MoveNextTilePos_ = NextTileCenterPos_;
			MoveBubble_.push_back(NextTile_);
			PushTile_->MoveOn = true;
			MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y);
			if (_PlayerNum == 1)
			{
				for (int i = 0; i < Player1BlockTiles_.size(); i++)
				{
					if (Player1BlockTiles_[i] == PushTile_)
					{
						Player1BlockTiles_.erase(Player1BlockTiles_.begin() + i);
						Player1BlockTiles_.push_back(NextTile_);

					}
				}
			}
			if (_PlayerNum == 2)
			{
				for (int i = 0; i < Player2BlockTiles_.size(); i++)
				{
					if (Player1BlockTiles_[i] == PushTile_)
					{
						Player2BlockTiles_.erase(Player1BlockTiles_.begin() + i);
						Player2BlockTiles_.push_back(NextTile_);

					}
				}
			}
		}
	}


}
void MapGameObject::PushBlock(float4 _Pos, BlockDir _Dir)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	BlockTile* PushTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	if (PushTile_ == nullptr)
	{
		return;
	}
	if (PushTile_->MoveOn ==true)
	{
		return;
	}
	if (BlockDir::LEFT == _Dir)
	{
		if (TileIndex_.X - 1 < 0)
		{
			return;
		}
		BlockTile* NextTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X - 1, TileIndex_.Y);
		ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X - 1, TileIndex_.Y);
		if (ItemTile_ != nullptr && ItemTile_->BlockType_ == BlockType::ItemBlock)
		{
			MapTile_->DeleteTile(TileIndex_.X - 1, TileIndex_.Y);
		}
		if (NextTile_ == nullptr)
		{
			BlockTile* NextTile_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X - 1, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
			NextTile_->Renderer = PushTile_->Renderer;
			NextTile_->TilePos_ = PushTile_->TilePos_;
			NextTile_->BlockType_ = PushTile_->BlockType_;
			NextTile_->ItemType_ = PushTile_->ItemType_;
			NextTile_->BlockHp_ = PushTile_->BlockHp_;
			NextTile_->BlockDir_ = BlockDir::LEFT;
			float4 NextTileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X - 1, TileIndex_.Y);
			NextTile_->MoveNextTilePos_ = NextTileCenterPos_;
			MoveBlocks_.push_back(NextTile_);
			PushTile_->MoveOn = true;
			MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y);
		}
	}
	if (BlockDir::RIGHT == _Dir)
	{
		if (TileIndex_.X + 1 > 14)
		{
			return;
		}
		BlockTile* NextTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X + 1, TileIndex_.Y);
		ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X + 1, TileIndex_.Y);
		if (ItemTile_ != nullptr && ItemTile_->BlockType_ == BlockType::ItemBlock)
		{
			MapTile_->DeleteTile(TileIndex_.X + 1, TileIndex_.Y);
		}
		if (NextTile_ == nullptr)
		{
			BlockTile* NextTile_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X + 1, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
			NextTile_->Renderer = PushTile_->Renderer;
			NextTile_->TilePos_ = PushTile_->TilePos_;
			NextTile_->BlockType_ = PushTile_->BlockType_;
			NextTile_->ItemType_ = PushTile_->ItemType_;
			NextTile_->BlockHp_ = PushTile_->BlockHp_;
			NextTile_->BlockDir_ = BlockDir::RIGHT;
			float4 NextTileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X + 1, TileIndex_.Y);
			NextTile_->MoveNextTilePos_ = NextTileCenterPos_;
			MoveBlocks_.push_back(NextTile_);
			PushTile_->MoveOn = true;
			MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y);
		}
	}
	if (BlockDir::DOWN == _Dir)
	{
		if (TileIndex_.Y + 1 > 12)
		{
			return;
		}
		BlockTile* NextTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X , TileIndex_.Y + 1);
		ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y + 1);
		if (ItemTile_ != nullptr && ItemTile_->BlockType_ == BlockType::ItemBlock)
		{
			MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y+1);
		}
		if (NextTile_ == nullptr)
		{
			BlockTile* NextTile_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y + 1, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
			NextTile_->Renderer = PushTile_->Renderer;
			NextTile_->TilePos_ = PushTile_->TilePos_;
			NextTile_->BlockType_ = PushTile_->BlockType_;
			NextTile_->ItemType_ = PushTile_->ItemType_;
			NextTile_->BlockHp_ = PushTile_->BlockHp_;
			NextTile_->BlockDir_ = BlockDir::DOWN;
			float4 NextTileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y + 1);
			NextTile_->MoveNextTilePos_ = NextTileCenterPos_;
			MoveBlocks_.push_back(NextTile_);
			PushTile_->MoveOn = true;
			MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y);
		}
	}
	if (BlockDir::UP == _Dir)
	{
		if (TileIndex_.Y - 1 < 0)
		{
			return;
		}
		BlockTile* NextTile_ = MapTile_->GetTile<BlockTile>(TileIndex_.X , TileIndex_.Y - 1);
		ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y - 1);
		if (ItemTile_ != nullptr && ItemTile_->BlockType_ == BlockType::ItemBlock)
		{
			MapTile_->DeleteTile(TileIndex_.X , TileIndex_.Y + 1);
		}
		if (NextTile_ == nullptr)
		{
			BlockTile* NextTile_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y - 1, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
			NextTile_->Renderer = PushTile_->Renderer;
			NextTile_->TilePos_ = PushTile_->TilePos_;
			NextTile_->BlockType_ = PushTile_->BlockType_;
			NextTile_->ItemType_ = PushTile_->ItemType_;
			NextTile_->BlockHp_ = PushTile_->BlockHp_;
			NextTile_->BlockDir_ = BlockDir::UP;
			float4 NextTileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y - 1);
			NextTile_->MoveNextTilePos_ = NextTileCenterPos_;
			MoveBlocks_.push_back(NextTile_);
			PushTile_->MoveOn = true;
			MapTile_->DeleteTile(TileIndex_.X, TileIndex_.Y);
		}
	}


}
void MapGameObject::BubbleMoveUpdate()
{

	for (int i = 0; i < MoveBubble_.size(); i++)
	{

		if (BlockDir::LEFT == MoveBubble_[i]->BlockDir_)
		{
			if (MoveBubble_[i]->TilePos_.x > MoveBubble_[i]->MoveNextTilePos_.x)
			{
				Move_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 100.0f;
				float4 MovePos_ = { MoveBubble_[i]->TilePos_.x,MoveBubble_[i]->TilePos_.y };
				MovePos_ += Move_;
				MoveBubble_[i]->Renderer->SetPivot(MovePos_ + float4{ 0,60 });
				MoveBubble_[i]->TilePos_ = MovePos_;
				MoveBubble_[i]->MoveOn = true;
			}
			else
			{
				MoveBubble_[i]->MoveOn = false;
			}

		}
		if (BlockDir::RIGHT == MoveBubble_[i]->BlockDir_)
		{
			if (MoveBubble_[i]->TilePos_.x < MoveBubble_[i]->MoveNextTilePos_.x)
			{
				Move_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * 100.0f;
				float4 MovePos_ = { MoveBubble_[i]->TilePos_.x,MoveBubble_[i]->TilePos_.y };
				MovePos_ += Move_;
				MoveBubble_[i]->Renderer->SetPivot(MovePos_ + float4{ 0,60 });
				MoveBubble_[i]->TilePos_ = MovePos_;
				MoveBubble_[i]->MoveOn = true;
			}
			else
			{
				MoveBubble_[i]->MoveOn = false;
			}
		}
		if (BlockDir::DOWN == MoveBubble_[i]->BlockDir_)
		{
			if (MoveBubble_[i]->TilePos_.y < MoveBubble_[i]->MoveNextTilePos_.y)
			{
				Move_ = float4::DOWN * GameEngineTime::GetDeltaTime() * 100.0f;
				float4 MovePos_ = { MoveBubble_[i]->TilePos_.x,MoveBubble_[i]->TilePos_.y };
				MovePos_ += Move_;
				MoveBubble_[i]->Renderer->SetPivot(MovePos_ + float4{ 0,60 });
				MoveBubble_[i]->TilePos_ = MovePos_;
				MoveBubble_[i]->MoveOn = true;
			}
			else
			{
				MoveBubble_[i]->MoveOn = false;
			}
		}
		if (BlockDir::UP == MoveBubble_[i]->BlockDir_)
		{
			if (MoveBubble_[i]->TilePos_.y > MoveBubble_[i]->MoveNextTilePos_.y)
			{
				Move_ = float4::UP * GameEngineTime::GetDeltaTime() * 100.0f;
				float4 MovePos_ = { MoveBubble_[i]->TilePos_.x,MoveBubble_[i]->TilePos_.y };
				MovePos_ += Move_;
				MoveBubble_[i]->Renderer->SetPivot(MovePos_ + float4{ 0,60});
				MoveBubble_[i]->TilePos_ = MovePos_;
				MoveBubble_[i]->MoveOn = true;
			}
			else
			{
				MoveBlocks_[i]->MoveOn = false;
			}
		}
	}
}
void MapGameObject::BlockMoveUpdate()
{

	for (int i = 0; i < MoveBlocks_.size(); i++)
	{

		if (BlockDir::LEFT == MoveBlocks_[i]->BlockDir_)
		{
			if (MoveBlocks_[i]->TilePos_.x > MoveBlocks_[i]->MoveNextTilePos_.x)
			{
				Move_ = float4::LEFT * GameEngineTime::GetDeltaTime()*100.0f;
				float4 MovePos_ = { MoveBlocks_[i]->TilePos_.x,MoveBlocks_[i]->TilePos_.y };
				MovePos_ += Move_;
				MoveBlocks_[i]->Renderer->SetPivot(MovePos_ + float4{0,-4});
				MoveBlocks_[i]->TilePos_ = MovePos_;
				MoveBlocks_[i]->MoveOn = true;
			}
			else
			{
				MoveBlocks_[i]->MoveOn = false;
			}

		}
		if (BlockDir::RIGHT == MoveBlocks_[i]->BlockDir_)
		{
			if (MoveBlocks_[i]->TilePos_.x < MoveBlocks_[i]->MoveNextTilePos_.x)
			{
				Move_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * 100.0f;
				float4 MovePos_ = { MoveBlocks_[i]->TilePos_.x,MoveBlocks_[i]->TilePos_.y };
				MovePos_ += Move_;
				MoveBlocks_[i]->Renderer->SetPivot(MovePos_ + float4{ 0,-4 });
				MoveBlocks_[i]->TilePos_ = MovePos_;
				MoveBlocks_[i]->MoveOn = true;
			}
			else
			{
				MoveBlocks_[i]->MoveOn = false;
			}
		}
		if (BlockDir::DOWN == MoveBlocks_[i]->BlockDir_)
		{
			if (MoveBlocks_[i]->TilePos_.y < MoveBlocks_[i]->MoveNextTilePos_.y)
			{
				Move_ = float4::DOWN * GameEngineTime::GetDeltaTime() * 100.0f;
				float4 MovePos_ = { MoveBlocks_[i]->TilePos_.x,MoveBlocks_[i]->TilePos_.y };
				MovePos_ += Move_;
				MoveBlocks_[i]->Renderer->SetPivot(MovePos_ + float4{ 0,-4 });
				MoveBlocks_[i]->TilePos_ = MovePos_;
				MoveBlocks_[i]->MoveOn = true;
			}
			else
			{
				MoveBlocks_[i]->MoveOn = false;
			}
		}
		if (BlockDir::UP == MoveBlocks_[i]->BlockDir_)
		{
			if (MoveBlocks_[i]->TilePos_.y > MoveBlocks_[i]->MoveNextTilePos_.y)
			{
				Move_ = float4::UP * GameEngineTime::GetDeltaTime() * 100.0f;
				float4 MovePos_ = { MoveBlocks_[i]->TilePos_.x,MoveBlocks_[i]->TilePos_.y };
				MovePos_ += Move_;
				MoveBlocks_[i]->Renderer->SetPivot(MovePos_ + float4{ 0,-4 });
				MoveBlocks_[i]->TilePos_ = MovePos_;
				MoveBlocks_[i]->MoveOn = true;
			}
			else
			{
				MoveBlocks_[i]->MoveOn = false;
			}
		}
	}
}

void MapGameObject::BubblePop(float4 _Pos, float Power)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	BlockTile* Check = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	
	
	if (Check != nullptr)
	{
		return;
	}
	else
	{
		BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
		Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
		Wave_->BlockType_ = BlockType::BubbleBlock;
		Wave_->TileIndex_ = TileIndex_;
		Wave_->Renderer = CreateRenderer();
		Wave_->Renderer->SetPivot({ TileCenterPos_.x,TileCenterPos_.y });
		Wave_->Renderer->CreateAnimation("Center.bmp", "Center", 0, 5, 0.05f, true);
		Wave_->Renderer->CreateAnimation("Center.bmp", "Death", 0, 5, 0.05f, false);
		Wave_->Renderer->ChangeAnimation("Center");
		Wave_->DeathTime_ = 1.5f;
		Wave_->IsWaveDeath;
		Wave_->IsWaveDeathAni;
		Wave_->DeathAniTime_ = 1.5f;

		WaveBlockTiles_.push_back(Wave_);

		MakeLeftWave(TileIndex_, Power);
		MakeRightWave(TileIndex_, Power);
		MakeDownWave(TileIndex_, Power);
		MakeUpWave(TileIndex_, Power);
	}
}
void MapGameObject::DestroyBoom()//폭탄마다 각자 타이머 돌림
{

	for (int i = 0; i < Player1BlockTiles_.size(); i++)
	{
		Player1BlockTiles_[i]->DeathTime_ -= 1.0f * GameEngineTime::GetDeltaTime();
		if (Player1BlockTiles_[i]->DeathTime_ <= 0.0f)
		{

			Player1BoomNum_ -= 1;
			float4 _Poss = Player1BlockTiles_[i]->TilePos_;
			float _Power = Player1BlockTiles_[i]->Power_;
			MapTile_->DeleteTile(Player1BlockTiles_[i]->TileIndex_.X, Player1BlockTiles_[i]->TileIndex_.Y);
			Player1BlockTiles_.erase(Player1BlockTiles_.begin() + i);
			BubblePop(_Poss, _Power);//폭탄 지워진 자리에 웨이브 만들어줌
		}
	}
	for (int i = 0; i < Player2BlockTiles_.size(); i++)
	{
		Player2BlockTiles_[i]->DeathTime_ -= 1.0f * GameEngineTime::GetDeltaTime();
		if (Player2BlockTiles_[i]->DeathTime_ <= 0.0f)
		{
			Player2BoomNum_ -= 1;
			float4 _Poss = Player2BlockTiles_[i]->TilePos_;
			float _Power = Player2BlockTiles_[i]->Power_;
			MapTile_->DeleteTile(Player2BlockTiles_[i]->TileIndex_.X, Player2BlockTiles_[i]->TileIndex_.Y);
			Player2BlockTiles_.erase(Player2BlockTiles_.begin() + i);
			BubblePop(_Poss, _Power);//폭탄 지워진 자리에 웨이브 만들어줌
		}
	}
}
void MapGameObject::WaveDeathAni()
{
	for (int i = 0; i < WaveBlockTiles_.size(); i++) // 물풍선 중앙 탐색
	{
		if (WaveBlockTiles_[i]->IsWaveDeath == true) // 물풍선 파도가 다 만들어졌으면
		{
			for (int j = 0; j < WaveBlockTiles_[i]->MyLeftWave_.size(); j++)//물풍선 중앙에서 보관하던 물줄기 백터돌면서
			{

				if (nullptr != WaveBlockTiles_[i]->MyLeftWave_[j]->Renderer)
				{

					WaveBlockTiles_[i]->MyLeftWave_[j]->Renderer->ChangeAnimation("Death");
					WaveBlockTiles_[i]->MyLeftWave_[j]->IsWaveDeathAni = true;
				}

			}

			for (int j = 0; j < WaveBlockTiles_[i]->MyRightWave_.size(); j++)//물풍선 중앙에서 보관하던 물줄기 백터돌면서
			{
				if (nullptr != WaveBlockTiles_[i]->MyRightWave_[j]->Renderer)
				{

					WaveBlockTiles_[i]->MyRightWave_[j]->Renderer->ChangeAnimation("Death");
					WaveBlockTiles_[i]->MyRightWave_[j]->IsWaveDeathAni = true;
				}

			}
		

			for (int j = 0; j < WaveBlockTiles_[i]->MyDownWave_.size(); j++)//물풍선 중앙에서 보관하던 물줄기 백터돌면서
			{
				if (nullptr != WaveBlockTiles_[i]->MyDownWave_[j]->Renderer)
				{

					WaveBlockTiles_[i]->MyDownWave_[j]->Renderer->ChangeAnimation("Death");
					WaveBlockTiles_[i]->MyDownWave_[j]->IsWaveDeathAni = true;
				}

			}

			for (int j = 0; j < WaveBlockTiles_[i]->MyUpWave_.size(); j++)//물풍선 중앙에서 보관하던 물줄기 백터돌면서
			{
				if (nullptr != WaveBlockTiles_[i]->MyUpWave_[j]->Renderer)
				{

					WaveBlockTiles_[i]->MyUpWave_[j]->Renderer->ChangeAnimation("Death");
					WaveBlockTiles_[i]->MyUpWave_[j]->IsWaveDeathAni = true;
				}

			}

			WaveBlockTiles_[i]->Renderer->ChangeAnimation("Death");
			WaveBlockTiles_[i]->IsWaveDeath = false;
			
		}
		if (WaveBlockTiles_[i]->Renderer->IsEndAnimation() == true)//시간이 다줄었으면
		{
			WaveBlockTiles_[i]->IsWaveDeathAni = true;

		}

	}
}
void MapGameObject::DestroyBlock()
{

	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			BlockTile* BlockCheck = MapTile_->GetTile<BlockTile>(x, y);

			if (BlockCheck != nullptr && BlockCheck->BlockType_ == BlockType::FixBlock)//블럭있는게 맞아?
			{
				if (BlockCheck->IsBlockDeath_ == true)//죽어야하는 타일이라면
				{
					BlockCheck->Renderer->ChangeAnimation("Death");
					if (BlockCheck->Renderer->IsEndAnimation() == true)//애니메이션이 끝났다면
					{
						BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(x, y);//현재 검사중인 타일 정보
						ItemType ItemValue = Tiles_->ItemType_;
						MapTile_->DeleteTile(x, y);
						if (ItemValue != ItemType::Max)
						{
							GameItemObject* Item = GetLevel()->CreateActor<GameItemObject>(static_cast<int>(ORDER::MAPOBJECT));
							Item->SetMapTile(MapTile_);
							Item->CreateItem({ float(x) * 40,float(y) * 40 }, ItemValue);
						}
					}
				}
			}
			else if (BlockCheck != nullptr && BlockCheck->BlockType_ == BlockType::PullBlock)
			{
				if (BlockCheck->IsBlockDeath_ == true)//죽어야하는 타일이라면
				{
					BlockCheck->Renderer->ChangeAnimation("Death");
					if (BlockCheck->Renderer->IsEndAnimation() == true)//애니메이션이 끝났다면
					{
						BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(x, y);//현재 검사중인 타일 정보
						ItemType ItemValue = Tiles_->ItemType_;
						MapTile_->DeleteTile(x, y);
						if (ItemValue != ItemType::Max)
						{
							GameItemObject* Item = GetLevel()->CreateActor<GameItemObject>(static_cast<int>(ORDER::MAPOBJECT));
							Item->SetMapTile(MapTile_);
							Item->CreateItem({ float(x) * 40,float(y) * 40 }, ItemValue);
						}
					}
				}
			}
		}
	}
}
void MapGameObject::DestroyWave()
{

	for (int i = 0; i < WaveBlockTiles_.size(); i++)//물풍선 백터 돌다가
	{
		if (WaveBlockTiles_[i]->IsWaveDeathAni == true)//죽는 애니재생이면
		{
			{
				for (int j = 0; j < WaveBlockTiles_[i]->MyLeftWave_.size(); j++)
				{

					MapTile_->DeleteTile(WaveBlockTiles_[i]->MyLeftWave_[j]->TileIndex_.X, WaveBlockTiles_[i]->MyLeftWave_[j]->TileIndex_.Y);//물줄기 지워라
				}
				for (int j = 0; j < WaveBlockTiles_[i]->MyRightWave_.size(); j++)
				{	

					MapTile_->DeleteTile(WaveBlockTiles_[i]->MyRightWave_[j]->TileIndex_.X, WaveBlockTiles_[i]->MyRightWave_[j]->TileIndex_.Y);//물줄기 지워라
				}
				for (int j = 0; j < WaveBlockTiles_[i]->MyDownWave_.size(); j++)
				{

					MapTile_->DeleteTile(WaveBlockTiles_[i]->MyDownWave_[j]->TileIndex_.X, WaveBlockTiles_[i]->MyDownWave_[j]->TileIndex_.Y);//물줄기 지워라
				}
				for (int j = 0; j < WaveBlockTiles_[i]->MyUpWave_.size(); j++)
				{

					MapTile_->DeleteTile(WaveBlockTiles_[i]->MyUpWave_[j]->TileIndex_.X, WaveBlockTiles_[i]->MyUpWave_[j]->TileIndex_.Y);//물줄기 지워라
				}

				WaveBlockTiles_[i]->MyUpWave_.clear(); //물줄기 백터 클리어
				MapTile_->DeleteTile(WaveBlockTiles_[i]->TileIndex_.X, WaveBlockTiles_[i]->TileIndex_.Y);//중앙부분지우기
				WaveBlockTiles_.erase(WaveBlockTiles_.begin() + i);//중앙벡터 지우기
			}
		}

	}
}

void MapGameObject::MakeLeftWave(TileIndex _Pos, float _Power)
{

	int IndexCount_ = static_cast<int>(_Power);//파도 만들어줄 거리
	int PowerCount_ = static_cast<int>(_Power);//체크해줘야할 칸


	 for (int i = 1; i <= PowerCount_; i++)//파워가 0이될때까지 체크
	{

		TileIndex TilePos = _Pos;

		if (TilePos.X - i < 0)//--------------------------------------------맵에 부딪혔다면
		{
			IndexCount_ = i - 1;//이만큼 가면된다.
			i = PowerCount_ + 1;//여기서 for문 종료
		}
		else//맵에 안 부딪혔다면
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X - i, TilePos.Y);//현재 검사중인 타일 위치
		 	BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X - i, TilePos.Y);//현재 검사중인 타일 정보
			ItemBlockTile* Ti_ = MapTile_->GetTile<ItemBlockTile>(TilePos.X - i, TilePos.Y);

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WallBlock) //-----------------------------------------안부서지는 벽이 있을 때

			{
				IndexCount_ = i - 1;//이만큼 가면된다.
			 	i = PowerCount_ + 1;//여기서 for문 
			}
			else if (Tiles_ != nullptr &&Tiles_->BlockType_ == BlockType::FixBlock ) //------------------------------------------------부서지는벽
			{
	
				Tiles_->IsBlockDeath_ = true;
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = static_cast<int>(_Power) + 1;//여기서 for문 종료
				//여기서 해당 오브젝트부숴주면됨
			}

			else if (Tiles_ != nullptr&& Tiles_->BlockType_ == BlockType::PullBlock)//밀리는상자
			{
				Tiles_->IsBlockDeath_ = true;
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = static_cast<int>(_Power) + 1;//여기서 for문 종료
				//여기서 해당 오브젝트부숴주면됨
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BushBlock)
			{
				MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);

			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------이미 터지고 있을때
			{
				{
					BlockTile*CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_,Tiles_->CenterWaveY_ );//검사하고 있는 웨이브의 시작점
					MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);//웨이브 지워주고
					for (int i = 0; i < CenterPos_->MyLeftWave_.size(); i++)
					{
						if (CenterPos_->MyLeftWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyLeftWave_.erase(CenterPos_->MyLeftWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyRightWave_.size(); i++)
					{
						if (CenterPos_->MyRightWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyRightWave_.erase(CenterPos_->MyRightWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyDownWave_.size(); i++)
					{
						if (CenterPos_->MyDownWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyDownWave_.erase(CenterPos_->MyDownWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyUpWave_.size(); i++)
					{
						if (CenterPos_->MyUpWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyUpWave_.erase(CenterPos_->MyUpWave_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//------------------------------wave중앙
			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료


			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BoomBlock)//-------------------------------물풍선이 있을때
			{
				Tiles_->DeathTime_ = 0.0f;
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료


			}
		
			 else if (Ti_ != nullptr && Ti_-> BlockType_ == BlockType::ItemBlock )//-----------------------------아이템이 있을때
			{

				MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);
 			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)//가면되는곳까지 반복, 0은 따로 뿌려줄것임
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X - i, TilePos.Y);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y);//시작 타일
		if (i == IndexCount_) //마지막지점이 되면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X - i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X - i;
			Wave_->TileIndex_.Y = TilePos.Y;

			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Left1.bmp", "Left1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Left1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Left1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyLeftWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 
			Tiles_->IsWaveDeath = true;
		}
		else//마지막지점 아니면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X - i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X - i;
			Wave_->TileIndex_.Y = TilePos.Y;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Left2.bmp", "Left2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Left2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Left2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyLeftWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 

		}

	}
}
void MapGameObject::MakeRightWave(TileIndex _Pos, float _Power)
{

	int IndexCount_ = static_cast<int>(_Power);//파도 만들어줄 거리
	int PowerCount_ = static_cast<int>(_Power);//체크해줘야할 칸


	for (int i = 1; i <= PowerCount_; i++)//파워가 0이될때까지 체크
	{

		TileIndex TilePos = _Pos;

		if (TilePos.X + i > 14)//--------------------------------------------벽에 부딪혔다면
		{
			IndexCount_ = i - 1;//이만큼 가면된다.
			i = PowerCount_ + 1;//여기서 for문 종료
		}
		else//벽에 안 부딪혔다면
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X + i, TilePos.Y);//현재 검사중인 타일위치
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X + i, TilePos.Y);//현재 검사중인 타일 정보
			ItemBlockTile* Ti_ = MapTile_->GetTile<ItemBlockTile>(TilePos.X + i, TilePos.Y);

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WallBlock) //-----------------------------------------안부서지는 벽이 있을 때

			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료
			}

			else if (Tiles_ != nullptr &&Tiles_->BlockType_ == BlockType::FixBlock)//------------------------------------------------부서지는벽
			{
				Tiles_->IsBlockDeath_ = true;
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = static_cast<int>(_Power) + 1;//여기서 for문 종료
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BushBlock)
			{
				MapTile_->DeleteTile(TilePos.X + i, TilePos.Y);
			}

			else if (Tiles_ != nullptr&& Tiles_->BlockType_ == BlockType::PullBlock)//밀리는상자
			{
				Tiles_->IsBlockDeath_ = true;
				IndexCount_ = i - 1;//이만큼 가면된다.
					i = static_cast<int>(_Power) + 1;//여기서 for문 종료
					//여기서 해당 오브젝트부숴주면됨
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------이미 터지고 있을때
			{
				{

					BlockTile* CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_, Tiles_->CenterWaveY_);//검사하고 있는 웨이브의 시작점
					MapTile_->DeleteTile(TilePos.X + i, TilePos.Y);//웨이브 지워주고
					for (int i = 0; i < CenterPos_->MyLeftWave_.size(); i++)
					{
						if (CenterPos_->MyLeftWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyLeftWave_.erase(CenterPos_->MyLeftWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyRightWave_.size(); i++)
					{
						if (CenterPos_->MyRightWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyRightWave_.erase(CenterPos_->MyRightWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyDownWave_.size(); i++)
					{
						if (CenterPos_->MyDownWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyDownWave_.erase(CenterPos_->MyDownWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyUpWave_.size(); i++)
					{
						if (CenterPos_->MyUpWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyUpWave_.erase(CenterPos_->MyUpWave_.begin() + i);
						}
					}
				}

			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//------------------------------wave중앙
			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료


			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BoomBlock)//-------------------------------물풍선이 있을때
			{
				Tiles_->DeathTime_ = 0.0f;
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료


			}
			else if (Ti_ != nullptr && Ti_->BlockType_ == BlockType::ItemBlock )//-----------------------------아이템이 있을때
			{
				MapTile_->DeleteTile(TilePos.X +i, TilePos.Y);
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)//가면되는곳까지 반복, 0은 따로 뿌려줄것임
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X + i, TilePos.Y);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y);//시작 타일
		if (i == IndexCount_) //마지막지점이 되면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X + i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X + i;
			Wave_->TileIndex_.Y = TilePos.Y;

			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Right1.bmp", "Right1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Right1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Right1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyRightWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 
			Tiles_->IsWaveDeath = true;
		}
		else//마지막지점 아니면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X + i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X + i;
			Wave_->TileIndex_.Y = TilePos.Y;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Right2.bmp", "Right2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Right2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Right2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyRightWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 

		}

	}
}
void MapGameObject::MakeDownWave(TileIndex _Pos, float _Power)
{

	int IndexCount_ = static_cast<int>(_Power);
	int PowerCount_ = static_cast<int>(_Power);

	for (int i = 1; i <= PowerCount_; i++)
	{

		TileIndex TilePos = _Pos;

		if (TilePos.Y + i > 12)
		{
			IndexCount_ = i - 1;
			i = PowerCount_ + 1;
		}
		else
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y+i);
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X , TilePos.Y+i);
			ItemBlockTile* Ti_ = MapTile_->GetTile<ItemBlockTile>(TilePos.X, TilePos.Y+i);

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WallBlock)

			{
				IndexCount_ = i - 1;
				i = PowerCount_ + 1;
			}
			else if (Tiles_ != nullptr &&Tiles_->BlockType_ == BlockType::FixBlock ) //------------------------------------------------부서지는벽
			{
				Tiles_->IsBlockDeath_ = true;
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = static_cast<int>(_Power) + 1;//여기서 for문 종료
				//여기서 해당 오브젝트부숴주면됨
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BushBlock) //------------------------------------------------부쉬
			{
				MapTile_->DeleteTile(TilePos.X, TilePos.Y + i);
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::PullBlock)//밀리는상자
			{
				Tiles_->IsBlockDeath_ = true;
				IndexCount_ = i - 1;
				i = static_cast<int>(_Power) + 1;

			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------이미 터지고 있을때
			{
				{

					BlockTile* CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_, Tiles_->CenterWaveY_);//검사하고 있는 웨이브의 시작점
					MapTile_->DeleteTile(TilePos.X, TilePos.Y + i);//웨이브 지워주고
					for (int i = 0; i < CenterPos_->MyLeftWave_.size(); i++)
					{
						if (CenterPos_->MyLeftWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyLeftWave_.erase(CenterPos_->MyLeftWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyRightWave_.size(); i++)
					{
						if (CenterPos_->MyRightWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyRightWave_.erase(CenterPos_->MyRightWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyDownWave_.size(); i++)
					{
						if (CenterPos_->MyDownWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyDownWave_.erase(CenterPos_->MyDownWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyUpWave_.size(); i++)
					{
						if (CenterPos_->MyUpWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyUpWave_.erase(CenterPos_->MyUpWave_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//------------------------------wave중앙
			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료


			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BoomBlock)//-------------------------------물풍선이 있을때
			{
				Tiles_->DeathTime_ = 0.0f;
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료

			}
			else if (Ti_ != nullptr && Ti_->BlockType_ == BlockType::ItemBlock)//-----------------------------아이템이 있을때
			{
				MapTile_->DeleteTile(TilePos.X, TilePos.Y+i);
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)//가면되는곳까지 반복, 0은 따로 뿌려줄것임
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y+i);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y);//시작 타일
		if (i == IndexCount_) //마지막지점이 되면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y + i, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X ;
			Wave_->TileIndex_.Y = TilePos.Y+i;

			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Down1.bmp", "Down1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Down1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Down1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyDownWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 
			Tiles_->IsWaveDeath = true;
		}
		else//마지막지점 아니면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y + i, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X ;
			Wave_->TileIndex_.Y = TilePos.Y + i;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Down2.bmp", "Down2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Down2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Down2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyDownWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 

		}

	}
}

void MapGameObject::MakeUpWave(TileIndex _Pos, float _Power)
{

	int IndexCount_ = static_cast<int>(_Power);//파도 만들어줄 거리
	int PowerCount_ = static_cast<int>(_Power);//체크해줘야할 칸


	for (int i = 1; i <= PowerCount_; i++)//파워가 0이될때까지 체크
	{

		TileIndex TilePos = _Pos;

		if (TilePos.Y - i < 0)//--------------------------------------------벽에 부딪혔다면
		{
			IndexCount_ = i - 1;//이만큼 가면된다.
			i = PowerCount_ + 1;//여기서 for문 종료
		}
		else//벽에 안 부딪혔다면
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y - i);//현재 검사중인 타일위치
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y - i);//현재 검사중인 타일 정보
			ItemBlockTile* Ti_ = MapTile_->GetTile<ItemBlockTile>(TilePos.X , TilePos.Y - i);

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WallBlock) //-----------------------------------------안부서지는 벽이 있을 때

			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료
			}
			else if (Tiles_ != nullptr &&Tiles_->BlockType_ == BlockType::FixBlock ) //------------------------------------------------부서지는벽//밀리는상자
			{
				Tiles_->IsBlockDeath_ = true;
				IndexCount_ = i - 1;
				i = static_cast<int>(_Power) + 1;

			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BushBlock)
			{
				MapTile_->DeleteTile(TilePos.X, TilePos.Y - i);
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::PullBlock)
			{
				Tiles_->IsBlockDeath_ = true;
				IndexCount_ = i - 1;
				i = static_cast<int>(_Power) + 1;
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------이미 터지고 있을때
			{
				{

					BlockTile* CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_, Tiles_->CenterWaveY_);//검사하고 있는 웨이브의 시작점
 					MapTile_->DeleteTile(TilePos.X, TilePos.Y - i);//웨이브 지워주고
					for (int i = 0; i < CenterPos_->MyLeftWave_.size(); i++)
					{
						if (CenterPos_->MyLeftWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyLeftWave_.erase(CenterPos_->MyLeftWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyRightWave_.size(); i++)
					{
						if (CenterPos_->MyRightWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyRightWave_.erase(CenterPos_->MyRightWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyDownWave_.size(); i++)
					{
						if (CenterPos_->MyDownWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyDownWave_.erase(CenterPos_->MyDownWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyUpWave_.size(); i++)
					{
						if (CenterPos_->MyUpWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyUpWave_.erase(CenterPos_->MyUpWave_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//------------------------------wave중앙
			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료

			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BoomBlock)//-------------------------------물풍선이 있을때
			{
				Tiles_->DeathTime_ = 0.0f;
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료


			}
			else if (Ti_ != nullptr && Ti_->BlockType_ == BlockType::ItemBlock)
			{
				MapTile_->DeleteTile(TilePos.X, TilePos.Y - i);
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)//가면되는곳까지 반복, 0은 따로 뿌려줄것임
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y - i);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y);//시작 타일
		if (i == IndexCount_) //마지막지점이 되면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y - i, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X;
			Wave_->TileIndex_.Y = TilePos.Y - i;

			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Up1.bmp", "Up1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Up1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Up1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyUpWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 
			Tiles_->IsWaveDeath = true;
	
		}
		else//마지막지점 아니면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y - i, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X;
			Wave_->TileIndex_.Y = TilePos.Y - i;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Up2.bmp", "Up2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Up2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Up2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyUpWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 

		}

	}
}

void MapGameObject::SetGameItem()
{
	GameEngineRandom ItemRandom;
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			if (MapTile_->GetTile<BlockTile>(x, y) != nullptr)
			{
				if (MapTile_->GetTile<BlockTile>(x, y)->BlockType_ == BlockType::FixBlock)
				{
					ItemValue_ = static_cast<ItemType>(ItemRandom.RandomInt(0,17));
					if (ItemValue_ == ItemType::Roller && RollerValue_>0)
					{
						RollerValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Bubble && RollerValue_ > 0)
					{
						BubbleValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Fluid && FluidValue_ > 0)
					{
						FluidValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::UltraBubble && UltraBubbleValue_ > 0)
					{
						UltraBubbleValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::RedDevil && RedDevilValue_ > 0)
					{
						RedDevilValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Devil && DevilValue_ > 0)
					{
						DevilValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Shoes && ShoesValue_ > 0)
					{
						ShoesValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Niddle && NiddleValue_ > 0)
					{
						NiddleValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Shield && ShieldValue_ > 0)
					{
						ShieldValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::SuperJump && SuperJumpValue_ > 0)
					{
						SuperJumpValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Turtle && TurtleValue_ > 0)
					{
						TurtleValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::SpaceShip && SpaceShipValue_ > 0)
					{
						SpaceShipValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Owl && OwlValue_ > 0)
					{
						OwlValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Bubble_Dark && Bubble_DarkValue_ > 0)
					{
						Bubble_DarkValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Bubble_Boss && Bubble_BossValue_ > 0)
					{
						Bubble_BossValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Bubble_Default && Bubble_DefaultValue_ > 0)
					{
						Bubble_DefaultValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Ghost && GhostValue_ > 0)
					{
						GhostValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
					else if (ItemValue_ == ItemType::Max && MaxValue_ > 0)
					{
						MaxValue_ -= 1;
						MapTile_->GetTile<BlockTile>(x, y)->ItemType_ = ItemValue_;
					}
				}
			}
		}
	}
}

void MapGameObject::BlockValueSetting()
{
	if (GetLevel()->GetNameConstRef() == "CampLevel")//총 71개
	{

		MaxValue_ = 20;
		RollerValue_ = 7;
		BubbleValue_ = 13;
		FluidValue_ = 7;
		UltraBubbleValue_ = 2;
		RedDevilValue_ = 1;
		DevilValue_ = 5;
		ShoesValue_ = 1;
		NiddleValue_ = 2;
		ShieldValue_ = 1;
		SuperJumpValue_ = 2;
		TurtleValue_ = 2;
		SpaceShipValue_ = 1;
		OwlValue_ = 2;
		Bubble_DarkValue_ = 0;
		Bubble_BossValue_ = 0;
		Bubble_DefaultValue_ = 0;
		GhostValue_ = 0;
	}
	else if (GetLevel()->GetNameConstRef() == "VillageLevel")//총57
	{
		MaxValue_ = 8;
		RollerValue_ = 7;
		BubbleValue_ = 7;
		FluidValue_ = 7;
		UltraBubbleValue_ = 3;
		RedDevilValue_ = 2;
		DevilValue_ = 5;
		ShoesValue_ = 3;
		NiddleValue_ = 3;
		ShieldValue_ = 3;
		SuperJumpValue_ = 3;
		TurtleValue_ = 2;
		SpaceShipValue_ = 2;
		OwlValue_ = 2;
		Bubble_DarkValue_ = 0;
		Bubble_BossValue_ = 0;
		Bubble_DefaultValue_ = 0;
		GhostValue_ = 0;
	}
	else if (GetLevel()->GetNameConstRef() == "CemetoryLevel")//총30
	{
		MaxValue_ = 6;
		RollerValue_ = 3;
		BubbleValue_ = 3;
		FluidValue_ = 4;
		UltraBubbleValue_ = 1;
		RedDevilValue_ = 2;
		DevilValue_ = 2;
		ShoesValue_ = 0;
		NiddleValue_ = 2;
		ShieldValue_ = 0;
		SuperJumpValue_ = 0;
		TurtleValue_ = 2;
		SpaceShipValue_ = 2;
		OwlValue_ = 2;
		Bubble_DarkValue_ = 0;
		Bubble_BossValue_ = 0;
		Bubble_DefaultValue_ = 0;
		GhostValue_ = 1;
	}
	else if (GetLevel()->GetNameConstRef() == "Monster1Level")//총36
	{
		MaxValue_ = 4;
		RollerValue_ = 6;
		BubbleValue_ = 6;
		FluidValue_ = 6;
		UltraBubbleValue_ = 2;
		RedDevilValue_ = 1;
		DevilValue_ = 5;
		ShoesValue_ =2;
		NiddleValue_ = 2;
		ShieldValue_ = 2;
		SuperJumpValue_ = 0;
		TurtleValue_ = 0;
		SpaceShipValue_ = 0;
		OwlValue_ = 0;
		Bubble_DarkValue_ = 0;
		Bubble_BossValue_ = 0;
		Bubble_DefaultValue_ = 0;
		GhostValue_ = 0;
	}
	else if (GetLevel()->GetNameConstRef() == "Monster2Level")//총6
	{
		MaxValue_ = 5;
		RollerValue_ = 2;
		BubbleValue_ = 2;
		FluidValue_ = 2;
		UltraBubbleValue_ = 2;
		RedDevilValue_ = 1;
		DevilValue_ = 2;
		ShoesValue_ = 2;
		NiddleValue_ = 1;
		ShieldValue_ = 1;
		SuperJumpValue_ = 0;
		TurtleValue_ = 0;
		SpaceShipValue_ = 0;
		OwlValue_ = 0;
		Bubble_DarkValue_ = 0;
		Bubble_BossValue_ = 0;
		Bubble_DefaultValue_ = 0;
		GhostValue_ = 0;
	}
		else if (GetLevel()->GetNameConstRef() == "BossLevel")//총81
	{
		MaxValue_ = 38;
		RollerValue_ = 7;
		BubbleValue_ = 7;
		FluidValue_ = 7;
		UltraBubbleValue_ = 3;
		RedDevilValue_ = 2;
		DevilValue_ = 5;
		ShoesValue_ = 3;
		NiddleValue_ = 3;
		ShieldValue_ = 3;
		SuperJumpValue_ = 3;
		TurtleValue_ = 0;
		SpaceShipValue_ = 0;
		OwlValue_ = 0;
		Bubble_DarkValue_ = 0;
		Bubble_BossValue_ = 0;
		Bubble_DefaultValue_ = 0;
		GhostValue_ = 0;
	}
}

void MapGameObject::BossBubblePop(float4 _Pos, float _Power)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	BlockTile* Check = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);

	if (Check != nullptr)
	{
		return;
	}
	else
	{
		BlockTile* BossWave_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
		BossWave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
		BossWave_->BlockType_ = BlockType::BubbleBlock;
		BossWave_->TileIndex_ = TileIndex_;
		BossWave_->Renderer = CreateRenderer();
		BossWave_->Renderer->SetPivot({ TileCenterPos_.x,TileCenterPos_.y });
		BossWave_->Renderer->CreateAnimation("Center.bmp", "Center", 0, 5, 0.05f, true);
		BossWave_->Renderer->CreateAnimation("Center.bmp", "Death", 0, 5, 0.05f, false);
		BossWave_->Renderer->ChangeAnimation("Center");
		BossWave_->IsWaveDeath = false;
		BossWaveTiles_.push_back(BossWave_);
	}
}
void MapGameObject::BossWaveDeath()
{
	for (int i = 0; i < BossWaveTiles_.size(); i++)//물풍선 백터 돌다가
	{
		if (BossWaveTiles_[i]->IsWaveDeath == false&& BossWaveTiles_[i]->Renderer->IsEndAnimation() == true)
		{
			BossWaveTiles_[i]->Renderer->ChangeAnimation("Death");
			BossWaveTiles_[i]->IsWaveDeath = true;
		}
		else if (BossWaveTiles_[i]->IsWaveDeath == true&&BossWaveTiles_[i]->Renderer->IsEndAnimation() == true)
		{
			MapTile_->DeleteTile(BossWaveTiles_[i]->TileIndex_.X, BossWaveTiles_[i]->TileIndex_.Y);//중앙부분지우기
			BossWaveTiles_.erase(BossWaveTiles_.begin() + i);//중앙벡터 지우기
		}

	}
}