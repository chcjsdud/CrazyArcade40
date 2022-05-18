#include"MapGameObject.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

MapGameObject::MapGameObject()
	:MapTile_(nullptr),
	AllBlockTiles_(),
	WaveDeathTime(0.0f),
	IsWaveDeath(false)
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
			DestroyWave();
			IsWaveDeath = false;
		}
	}
}


void MapGameObject::CreateBoom(float _x, float _y)
{
	BlockTile* Boom = MapTile_->CreateTile<BlockTile>(_x, _y, "TIleBase.bmp", static_cast<int>(ORDER::UI));
	Boom->BlockType_ = BlockType::Max;
	Boom->Renderer = CreateRenderer();
	Boom->Renderer->SetPivot( {(_x * 40)+20, (_y * 40)+20});
	Boom->Renderer->CreateAnimation("Bubble_Dark.bmp", "BubbleDark", 0, 3, 0.1f, true);
	Boom->Renderer->ChangeAnimation("BubbleDark");
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
	Wave_->Renderer->ChangeAnimation("Center");
	WaveBlockTiles_.push_back(Wave_);

	MakeLeftWave(TileIndex_, Power);
	MakeRightWave(TileIndex_, Power);
	MakeDownWave(TileIndex_, Power);
	MakeUpWave(TileIndex_, Power);
	WaveDeathTime = 5.0f;
	IsWaveDeath = true;

}
void MapGameObject::DestroyWave()
{
	for (int i = 0; i < WaveBlockTiles_.size(); i++)
	{
		MapTile_->DeleteTile(WaveBlockTiles_[i]->TileIndex_.X, WaveBlockTiles_[i]->TileIndex_.Y);
	}
}
void MapGameObject::MakeLeftWave(TileIndex _Pos, float Power)
{
	float IndexCount_ = Power;
	for (int i = 1; i <= Power; i++)
	{

		TileIndex TilePos = _Pos;

		if (TilePos.X - i < 0)
		{
			IndexCount_ = i - 1;
			i = Power + 1;
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
			Wave_->Renderer->ChangeAnimation("Left2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);

		}

	}
}
void MapGameObject::MakeDownWave(TileIndex _Pos, float Power)
{
	float IndexCount_ = Power;
	for (int i = 1; i <= Power; i++)
	{

		TileIndex TilePos = _Pos;

		if (TilePos.Y + i > 13)
		{
			IndexCount_ = i - 1;
			i = Power + 1;
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
			Wave_->Renderer->ChangeAnimation("Down2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);

		}

	}
}
void MapGameObject::MakeUpWave(TileIndex _Pos, float Power)
{
	float IndexCount_ = Power;
	for (int i = 1; i <= Power; i++)
	{
		TileIndex TilePos = _Pos;

		if (TilePos.Y - i < 0)
		{
			IndexCount_ = i - 1;
			i = Power + 1;
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
			Wave_->Renderer->ChangeAnimation("Up2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);

		}

	}
}

void MapGameObject::MakeRightWave(TileIndex _Pos, float Power)
{
	float IndexCount_=Power;
	for (int i = 1; i <= Power; i++)
	{
		TileIndex TilePos = _Pos;

		if (TilePos.X + i > 15)
		{
			IndexCount_ = i - 1;
			i = Power + 1;
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
			Wave_->Renderer->ChangeAnimation("Right2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);
		
		}

	}

}
void MapGameObject::CreateBlockTile(int x_ ,int y_)
{
	if (GetLevel()->GetNameCopy() == "VillageLevel")
	{
		
	}
}