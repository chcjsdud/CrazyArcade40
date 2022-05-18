#include"MapGameObject.h"
#include <GameEngine/GameEngineRenderer.h>

MapGameObject::MapGameObject()
	:MapTile_(nullptr),
	AllBlockTiles_()
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

	BlockTile* BubbleCenter = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "Empty.bmp",static_cast<int>(ORDER::EFFECT));
	BubbleCenter->BlockCol = CreateCollision("WaveCol", { 40,40 });
	BubbleCenter->BlockType_ = BlockType::WaveBlock;

	
	BubbleCenter->Renderer = CreateRenderer();
	BubbleCenter->Renderer->SetPivot({ TileCenterPos_.x,TileCenterPos_.y});
	BubbleCenter->Renderer->CreateAnimation("Center.bmp", "Center", 0, 5, 0.1f, true);
	BubbleCenter->Renderer->ChangeAnimation("Center");


	MakeLeftWave(TileIndex_, Power);
	MakeRightWave(TileIndex_, Power);
	MakeDownWave(TileIndex_, Power);
	MakeUpWave(TileIndex_, Power);


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
			BlockTile* BubbleLeft = MapTile_->CreateTile<BlockTile>(TilePos.X - i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			BubbleLeft->BlockCol = CreateCollision("WaveCol", { 40,40 });
			BubbleLeft->BlockType_ = BlockType::WaveBlock;
			BubbleLeft->Renderer = CreateRenderer();
			BubbleLeft->Renderer->CreateAnimation("Left1.bmp", "Left1", 0, 1, 0.1f, true);
			BubbleLeft->Renderer->ChangeAnimation("Left1");
			BubbleLeft->Renderer->SetPivot(TileCenterPos_);
		}
		else
		{
			BlockTile* BubbleLeft = MapTile_->CreateTile<BlockTile>(TilePos.X - i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			BubbleLeft->BlockCol = CreateCollision("WaveCol", { 40,40 });
			BubbleLeft->BlockType_ = BlockType::WaveBlock;
			BubbleLeft->Renderer = CreateRenderer();
			BubbleLeft->Renderer->CreateAnimation("Left2.bmp", "Left2", 0, 1, 0.1f, true);
			BubbleLeft->Renderer->ChangeAnimation("Left2");
			BubbleLeft->Renderer->SetPivot(TileCenterPos_);

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
			BlockTile* BubbleDown = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y + i, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			BubbleDown->BlockCol = CreateCollision("WaveCol", { 40,40 });
			BubbleDown->BlockType_ = BlockType::WaveBlock;
			BubbleDown->Renderer = CreateRenderer();
			BubbleDown->Renderer->CreateAnimation("Down1.bmp", "Down1", 0, 1, 0.1f, true);
			BubbleDown->Renderer->ChangeAnimation("Down1");
			BubbleDown->Renderer->SetPivot(TileCenterPos_);
		}
		else
		{
			BlockTile* BubbleDown = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y + i, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			BubbleDown->BlockCol = CreateCollision("WaveCol", { 40,40 });
			BubbleDown->BlockType_ = BlockType::WaveBlock;
			BubbleDown->Renderer = CreateRenderer();
			BubbleDown->Renderer->CreateAnimation("Down2.bmp", "Down2", 0, 1, 0.1f, true);
			BubbleDown->Renderer->ChangeAnimation("Down2");
			BubbleDown->Renderer->SetPivot(TileCenterPos_);

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
			BlockTile* BubbleUp = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y - i, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			BubbleUp->BlockCol = CreateCollision("WaveCol", { 40,40 });
			BubbleUp->BlockType_ = BlockType::WaveBlock;
			BubbleUp->Renderer = CreateRenderer();
			BubbleUp->Renderer->CreateAnimation("Up1.bmp", "Up1", 0, 1, 0.1f, true);
			BubbleUp->Renderer->ChangeAnimation("Up1");
			BubbleUp->Renderer->SetPivot(TileCenterPos_);
		}
		else
		{
			BlockTile* BubbleUp = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y - i, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			BubbleUp->BlockCol = CreateCollision("WaveCol", { 40,40 });
			BubbleUp->BlockType_ = BlockType::WaveBlock;
			BubbleUp->Renderer = CreateRenderer();
			BubbleUp->Renderer->CreateAnimation("Up2.bmp", "Up2", 0, 1, 0.1f, true);
			BubbleUp->Renderer->ChangeAnimation("Up2");
			BubbleUp->Renderer->SetPivot(TileCenterPos_);

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
			BlockTile* BubbleRight = MapTile_->CreateTile<BlockTile>(TilePos.X + i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			BubbleRight->BlockCol = CreateCollision("WaveCol", { 40,40 });
			BubbleRight->BlockType_ = BlockType::WaveBlock;
			BubbleRight->Renderer = CreateRenderer();
			BubbleRight->Renderer->CreateAnimation("Right1.bmp", "Right1", 0, 1, 0.1f, true);
			BubbleRight->Renderer->ChangeAnimation("Right1");
			BubbleRight->Renderer->SetPivot(TileCenterPos_);
		}
		else
		{
			BlockTile* BubbleRight = MapTile_->CreateTile<BlockTile>(TilePos.X + i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			BubbleRight->BlockCol = CreateCollision("WaveCol", { 40,40 });
			BubbleRight->BlockType_ = BlockType::WaveBlock;
			BubbleRight->Renderer = CreateRenderer();
			BubbleRight->Renderer->CreateAnimation("Right2.bmp", "Right2", 0, 1, 0.1f, true);
			BubbleRight->Renderer->ChangeAnimation("Right2");
			BubbleRight->Renderer->SetPivot(TileCenterPos_);
		
		}

	}

}
void MapGameObject::CreateBlockTile(int x_ ,int y_)
{
	if (GetLevel()->GetNameCopy() == "VillageLevel")
	{
		
	}
}