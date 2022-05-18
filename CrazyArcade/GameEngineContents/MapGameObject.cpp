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
	for (int i = 1; i <= Power; i++)
	{
		MakeWave(TileCenterPos_, Power);
	}

}
void MapGameObject::MakeWave( float4 _Pos, float Power)
{
	float4 LeftPos = _Pos + float4{-40*Power, 0};
	float4 RightPos = _Pos + float4{40 * Power, 0 };
	float4 DownPos = _Pos + float4{ 0,40 * Power };
	float4 UpPos = _Pos + float4{  0,-40 * Power };


	BlockTile* BubbleLeft = MapTile_->CreateTile<BlockTile>(LeftPos, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
	BubbleLeft->BlockCol = CreateCollision("WaveCol", { 40,40 });
	BubbleLeft->BlockType_ = BlockType::WaveBlock;
	BubbleLeft->Renderer = CreateRenderer();
	BubbleLeft->Renderer->CreateAnimation("Left1.bmp", "Left1", 0, 1, 0.1f, true);
	BubbleLeft->Renderer->ChangeAnimation("Left1");
	BubbleLeft->Renderer->SetPivot(LeftPos);

	BlockTile* BubbleRight = MapTile_->CreateTile<BlockTile>(RightPos, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
	BubbleRight->BlockCol = CreateCollision("WaveCol", { 40,40 });
	BubbleRight->BlockType_ = BlockType::WaveBlock;
	BubbleRight->Renderer = CreateRenderer();
	BubbleRight->Renderer->CreateAnimation("Right1.bmp", "Right1", 0, 1, 0.1f, true);
	BubbleRight->Renderer->ChangeAnimation("Right1");
	BubbleRight->Renderer->SetPivot(RightPos);

	BlockTile* BubbleDown = MapTile_->CreateTile<BlockTile>(DownPos, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
	BubbleDown->BlockCol = CreateCollision("WaveCol", { 40,40 });
	BubbleDown->BlockType_ = BlockType::WaveBlock;
	BubbleDown->Renderer = CreateRenderer();
	BubbleDown->Renderer->CreateAnimation("Down1.bmp", "Down1", 0, 1, 0.1f, true);
	BubbleDown->Renderer->ChangeAnimation("Down1");
	BubbleDown->Renderer->SetPivot(DownPos);

	BlockTile* BubbleUp = MapTile_->CreateTile<BlockTile>(UpPos, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
	BubbleUp->BlockCol = CreateCollision("WaveCol", { 40,40 });
	BubbleUp->BlockType_ = BlockType::WaveBlock;
	BubbleUp->Renderer = CreateRenderer();
	BubbleUp->Renderer->CreateAnimation("Up1.bmp", "Up1", 0, 1, 0.1f, true);
	BubbleUp->Renderer->ChangeAnimation("Up1");
	BubbleUp->Renderer->SetPivot(UpPos);
}
void MapGameObject::CreateBlockTile(int x_ ,int y_)
{
	if (GetLevel()->GetNameCopy() == "VillageLevel")
	{
		
	}
}