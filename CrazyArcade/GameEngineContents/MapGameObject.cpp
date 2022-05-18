#include"MapGameObject.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

MapGameObject::MapGameObject()
	:MapTile_(nullptr),
	AllBlockTiles_(),
	WaveDeathTime(0.0f),
	IsWaveDeath(false),
	IsWaveDeathAni(false)
{

}

MapGameObject::~MapGameObject()
{

}

void MapGameObject::Start()
{
	SetPosition({ 0.0f, 0.0f });

}

void MapGameObject::Update()
{
	if (IsWaveDeath ==true)
	{
		WaveDeathTime -= 1.0f * GameEngineTime::GetDeltaTime();
		if (WaveDeathTime < 0.0f)
		{
			WaveDeathAni();
			DestroyWave();
		}
	}
}

// 플레이어가 서있는 위치의 타일이 어떤 타입의 블럭인지 알려주는 함수 return 값이 Max이면 - 아무것도 없는 타일입니다.
BlockType MapGameObject::CheckTile(float4 _Pos) {
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
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
// 플레이어가 서있는 위치의 타일의 BlockType이 아이템블록이라면 , 아이템이 무슨아이템인지 체크하는 함수입니당. 위치넣어주면 아이템타입이 리턴됩니당. 
ItemType MapGameObject::CheckItem(float4 _Pos)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	if (Tiles_ == nullptr)
	{
		return ItemType::Max;
	}
	else
	{
		return Tiles_->ItemType_;
	}
}

void MapGameObject::CreateBoom(float4 _Pos)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	BlockTile* Boom_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::EFFECT));
	Boom_->BlockType_ = BlockType::BubbleBlock;
	Boom_->Renderer = CreateRenderer();
	Boom_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y+20 });
	Boom_->Renderer->CreateAnimation("Bubble_Dark.bmp", "BubbleDark", 0, 3, 0.1f, true);
	Boom_->Renderer->CreateAnimation("Bubble_Default.bmp", "BubbleDefault", 0, 3, 0.1f, true);
	Boom_->Renderer->CreateAnimation("Bubble_Boss.bmp", "BubbleBoss", 0, 3, 0.1f, true);
	Boom_->Renderer->ChangeAnimation("BubbleDefault");
BoomBlockTiles_.push_back(Boom_);
}

void MapGameObject::BubblePop(float4 _Pos, float Power)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);

	BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "Empty.bmp",static_cast<int>(ORDER::EFFECT));
	Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
	Wave_->BlockType_ = BlockType::WaveBlock;
	Wave_->TileIndex_ = TileIndex_;
	Wave_->Renderer = CreateRenderer();
	Wave_->Renderer->SetPivot({ TileCenterPos_.x,TileCenterPos_.y});
	Wave_->Renderer->CreateAnimation("Center.bmp", "Center", 0, 5, 0.1f, true);
	Wave_->Renderer->CreateAnimation("Center.bmp", "Death", 0, 5, 0.1f, false);
	Wave_->Renderer->ChangeAnimation("Center");
	WaveBlockTiles_.push_back(Wave_);

	MakeLeftWave(TileIndex_, Power);
	MakeRightWave(TileIndex_, Power);
	MakeDownWave(TileIndex_, Power);
	MakeUpWave(TileIndex_, Power);
	WaveDeathTime = 3.0f;
	IsWaveDeath = true;
	IsWaveDeathAni = true;

}
void MapGameObject::WaveDeathAni()
{
	if (IsWaveDeathAni == true)
	{
		MapTile_->DeleteTile(WaveBlockTiles_[0]->TileIndex_.X, WaveBlockTiles_[0]->TileIndex_.Y);

		for (int i = 1; i < WaveBlockTiles_.size(); i++)
		{
			WaveBlockTiles_[i]->Renderer->ChangeAnimation("Death");
	
		}
		IsWaveDeathAni = false;
	}
}
void MapGameObject::DestroyWave()
{
	if (WaveBlockTiles_[1]->Renderer->IsEndAnimation() == true)
	{
		for (int i = 1; i < WaveBlockTiles_.size(); i++)
		{
				MapTile_->DeleteTile(WaveBlockTiles_[i]->TileIndex_.X, WaveBlockTiles_[i]->TileIndex_.Y);
				IsWaveDeath = false;
		}
				WaveBlockTiles_.clear();
	}

}
void MapGameObject::MakeLeftWave(TileIndex _Pos, float Power)
{
	int IndexCount_ = static_cast<int>(Power);
	for (int i = 1; i <= Power; i++)
	{

		TileIndex TilePos = _Pos;

		if (TilePos.X - i < 0)
		{
			IndexCount_ = i - 1;
			i = static_cast<int>(Power) + 1;
		}
		else 
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X - i, TilePos.Y);
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X - i, TilePos.Y);

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::FixBlock)
			{
				IndexCount_ = i - 1;
			}
		}

		 

	}

	for (int i = 1; i <= IndexCount_; i++)
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X - i, TilePos.Y);

		if (i == IndexCount_)
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

			WaveBlockTiles_.push_back(Wave_);
		}
		else
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
			WaveBlockTiles_.push_back(Wave_);

		}

	}
}
void MapGameObject::MakeDownWave(TileIndex _Pos, float Power)
{
	int IndexCount_ = static_cast<int>(Power);
	for (int i = 1; i <= Power; i++)
	{

		TileIndex TilePos = _Pos;

		if (TilePos.Y + i > 13)
		{
			IndexCount_ = i - 1;
			i = static_cast<int>(Power) + 1;
		}
		else
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y + i);
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y + i);

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::FixBlock)
			{
				IndexCount_ = i - 1;
			}

		}

	}

	for (int i = 1; i <= IndexCount_; i++)
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y + i);

		if (i == IndexCount_)
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y + i, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			Wave_->TileIndex_.X = TilePos.X;
			Wave_->TileIndex_.Y = TilePos.Y + i;

			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Down1.bmp", "Down1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Down1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Down1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);
		}
		else
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y + i, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			Wave_->TileIndex_.X = TilePos.X;
			Wave_->TileIndex_.Y = TilePos.Y + i;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Down2.bmp", "Down2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Down2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Down2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);

		}

	}
}
void MapGameObject::MakeUpWave(TileIndex _Pos, float Power)
{
	int IndexCount_ = static_cast<int>(Power);
	for (int i = 1; i <= Power; i++)
	{
		TileIndex TilePos = _Pos;

		if (TilePos.Y - i < 0)
		{
			IndexCount_ = i - 1;
			i = static_cast<int>(Power) + 1;
		}
		else
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y - i);
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y - i);

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::FixBlock)
			{
				IndexCount_ = i - 1;
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y - i);

		if (i == IndexCount_)
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y - i, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			Wave_->TileIndex_.X = TilePos.X;
			Wave_->TileIndex_.Y = TilePos.Y - i;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Up1.bmp", "Up1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Up1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Up1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);
		}
		else
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y - i, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			Wave_->TileIndex_.X = TilePos.X;
			Wave_->TileIndex_.Y = TilePos.Y - i;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Up2.bmp", "Up2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Up2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Up2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);

		}

	}
}

void MapGameObject::MakeRightWave(TileIndex _Pos, float Power)
{
	int IndexCount_ = static_cast<int>(Power);
	for (int i = 1; i <= Power; i++)
	{
		TileIndex TilePos = _Pos;

		if (TilePos.X + i > 15)
		{
			IndexCount_ = i - 1;
			i = static_cast<int>(Power) + 1;
		}
		else
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y);
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X + i, TilePos.Y);

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::FixBlock)
			{
				IndexCount_ = i - 1;
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X + i, TilePos.Y);
		BlockTile* Tiles_= MapTile_->GetTile<BlockTile>(TilePos.X+i, TilePos.Y);

		if (i==IndexCount_)
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X + i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			Wave_->TileIndex_.X = TilePos.X + i;
			Wave_->TileIndex_.Y = TilePos.Y;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Right1.bmp", "Right1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Right1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Right1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);
		}
		else
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X + i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			Wave_->TileIndex_.X = TilePos.X + i;
			Wave_->TileIndex_.Y = TilePos.Y;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Right2.bmp", "Right2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Right2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Right2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);
		
		}

	}

}
