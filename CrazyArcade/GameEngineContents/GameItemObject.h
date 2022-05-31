#pragma once
#include "ContentsEnum.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>

class GameEngineRenderer;

class ItemBlockTile : public Tile
{
public:
	ItemBlockTile()
		: BlockType_(BlockType::Max),
		ItemType_(ItemType::Max),
		Renderer(nullptr),
		BlockCol(nullptr),
		TilePos_(float4::ZERO),
		TileIndex_()
	{

	}
	~ItemBlockTile()
	{
		if (Renderer != nullptr)
		{
			Renderer->Death();
			Renderer = nullptr;
		}
		BlockType_ = BlockType::Max;
		ItemType_ = ItemType::Max;
	}
	GameEngineRenderer* Renderer;
	GameEngineCollision* BlockCol;
	float4 TilePos_;
	TileIndex TileIndex_;
	BlockType BlockType_;
	ItemType ItemType_;
};


class GameItemObject : public GameEngineActor
{
public:
	GameItemObject();
	~GameItemObject();


	GameItemObject(const GameItemObject& _Other) = delete;
	GameItemObject(GameItemObject&& _Other) noexcept = delete;
	GameItemObject& operator=(const GameItemObject& _Other) = delete;
	GameItemObject& operator=(GameItemObject&& _Other) noexcept = delete;

	static GameItemObject* GameItemObject_;

	inline void SetMapTile(GameEngineRendererTileMap* _MapTile)
	{
		MapTile_ = _MapTile;
	}
	inline GameEngineRendererTileMap* ReturnGameTileObejctMap_()
	{
		return MapTile_;
	}
	GameEngineRendererTileMap* MapTile_;

	void CreateItem(float4 _Pos, ItemType _Type);
	ItemType CheckItem(float4 _Pos);
protected:
	void Start() override;
	void Update() override;

private:

};