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
		ItemType_(ItemType::Max),
		BlockCol(nullptr),
		Renderer(nullptr),
		TileX_(0),
		TileY_(0),
		TileIndex_()

	{

	}
	~BlockTile()
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
	float TileX_;
	float TileY_;
	TileIndex TileIndex_;
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

	inline void SetMapTile(GameEngineRendererTileMap* _MapTile)
	{
		MapTile_ = _MapTile;
	}

	BlockType CheckTile(float4 _Pos);
	ItemType CheckItem(float4 _Pos);
	void BubblePop(float4 _Pos, float Power);
	void CreateBoom(float4 _Pos, float Power);

protected:
	void Start() override;
	void Update() override;
private:

	std::vector<BlockTile*> AllBlockTiles_;
	std::vector<BlockTile*> WaveBlockTiles_;
	std::vector<BlockTile*> BoomBlockTiles_;
	GameEngineRendererTileMap* MapTile_;

	void MakeRightWave(TileIndex _Pos, float Power);
	void MakeLeftWave(TileIndex _Pos, float Power);
	void MakeDownWave(TileIndex _Pos, float Power);
	void MakeUpWave(TileIndex _Pos, float Power);
	void DestroyBoom();
	void DestroyWave();
	void WaveDeathAni();
	float Power;
	float BoomDeathTime;
	float WaveDeathTime;
	bool IsWaveDeath;
	bool IsWaveDeathAni;
	bool IsBoomDeath;
};