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

}

void MapGameObject::Update()
{

}

void MapGameObject::BubblePop(float4 _Pos, float Power)
{
	BlockTile* BubbleCenter = MapTile_->CreateTile<BlockTile>(_Pos, "Empty.bmp",static_cast<int>(ORDER::EFFECT));
	BubbleCenter->BlockCol = CreateCollision("WaveCol", { 40,40 });
	BubbleCenter->BlockType_ = BlockType::WaveBlock;
	BubbleCenter->Renderer = CreateRenderer();
	BubbleCenter->Renderer->CreateAnimation("Center.bmp", "Center", 0, 5, 0.1f, true);
	BubbleCenter->Renderer->ChangeAnimation("Center");
	for (int i = 1; i <= Power; i++)
	{
		MakeWave(_Pos, Power);
	}

}
void MapGameObject::MakeWave( float4 _Pos, float Power)
{
	float4 LeftPos = _Pos + float4{-40*Power, 0};
	float4 RightPos = _Pos + float4{40 * Power, 0 };
	float4 DownPos = _Pos + float4{ 0,40 * Power };
	float4 UpPos = _Pos + float4{  0,-40 * Power };


	BlockTile* BubbleLeft = MapTile_->CreateTile<BlockTile>(LeftPos, "Empty.bmp");
	BubbleLeft->BlockCol = CreateCollision("WaveCol", { 40,40 });
	BubbleLeft->BlockType_ = BlockType::WaveBlock;
	BubbleLeft->Renderer = CreateRenderer();
	BubbleLeft->Renderer->CreateAnimation("Left1.bmp", "Left1", 0, 1, 0.1f, true);
	BubbleLeft->Renderer->ChangeAnimation("Left1");

	BlockTile* BubbleRight = MapTile_->CreateTile<BlockTile>(RightPos, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
	BubbleRight->BlockCol = CreateCollision("WaveCol", { 40,40 });
	BubbleRight->BlockType_ = BlockType::WaveBlock;
	BubbleRight->Renderer = CreateRenderer();
	BubbleRight->Renderer->CreateAnimation("Right1.bmp", "Right1", 0, 1, 0.1f, true);
	BubbleRight->Renderer->ChangeAnimation("Right1");

	BlockTile* BubbleDown = MapTile_->CreateTile<BlockTile>(DownPos, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
	BubbleDown->BlockCol = CreateCollision("WaveCol", { 40,40 });
	BubbleDown->BlockType_ = BlockType::WaveBlock;
	BubbleDown->Renderer = CreateRenderer();
	BubbleDown->Renderer->CreateAnimation("Down1.bmp", "Down1", 0, 1, 0.1f, true);
	BubbleDown->Renderer->ChangeAnimation("Down1");

	BlockTile* BubbleUp = MapTile_->CreateTile<BlockTile>(UpPos, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
	BubbleUp->BlockCol = CreateCollision("WaveCol", { 40,40 });
	BubbleUp->BlockType_ = BlockType::WaveBlock;
	BubbleUp->Renderer = CreateRenderer();
	BubbleUp->Renderer->CreateAnimation("Up1.bmp", "Up1", 0, 1, 0.1f, true);
	BubbleUp->Renderer->ChangeAnimation("Up1");
}
void MapGameObject::CreateBlockTile(int x_ ,int y_)
{
	if (GetLevel()->GetNameCopy() == "VillageLevel")
	{
		
	}
}