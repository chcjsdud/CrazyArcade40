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
		BlockCol(nullptr)
	{

	}
	GameEngineRenderer* Renderer;
	GameEngineCollision* BlockCol;
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

protected:
	void Start() override;
	void Update() override;
private:
	std::vector<BlockTile*> AllBlockTiles_;
	GameEngineRendererTileMap* MapTile_;
	void CreateBlockTile();
};