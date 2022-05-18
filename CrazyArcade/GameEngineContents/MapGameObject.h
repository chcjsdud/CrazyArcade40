#pragma once
#include "ContentsEnum.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>

class GameEngineRenderer;
class GameEngineCollision;
class BlockTile : public Tile
{
public:
	BlockTile()
		: BlockType_(BlockType::Max),
		BlockCol(nullptr),
		TileX_(0),
		TileY_(0)

	{

	}
	GameEngineRenderer* Renderer;
	GameEngineCollision* BlockCol;
	float TileX_;
	float TileY_;

	BlockType BlockType_;
	ItemType ItemType_;
};

class MapGameObject : public GameEngineActor
{
public:
	MapGameObject();
	~MapGameObject();


	MapGameObject(const MapGameObject& _Other) = delete;
	MapGameObject(MapGameObject&& _Other) noexcept = delete;
	MapGameObject& operator=(const MapGameObject& _Other) = delete;
	MapGameObject& operator=(MapGameObject&& _Other) noexcept = delete;

	void SetMapTile(GameEngineRendererTileMap* _MapTile)
	{
		MapTile_ = _MapTile;
	}

	void BubblePop(float4 _Pos, float Power);
	void CreateBoom(float _x, float _y);

protected:
	void Start() override;
	void Update() override;
private:
	std::vector<BlockTile*> AllBlockTiles_;
	GameEngineRendererTileMap* MapTile_;

	void CreateBlockTile(int x_, int y_);

	void MakeWave(float4 _Pos, float Power);
};