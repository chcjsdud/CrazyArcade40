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
		IsWaveDeath(false),
		IsWaveDeathAni(false),
		TilePos_(),
		TileIndex_(),
		DeathTime_(),
		Power_()

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
	float DeathTime_;
	float DeathAniTime_;
	float Power_;
	bool IsWaveDeath;
	bool IsWaveDeathAni;
	GameEngineRenderer* Renderer;
	GameEngineCollision* BlockCol;
	float4 TilePos_;
	TileIndex TileIndex_;
	BlockType BlockType_;
	ItemType ItemType_;
	std::vector<BlockTile*> MyWave_;
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
	void BubblePop(float4 _Pos, float _Power);
	void CreateBoom(float4 _Pos, float _Power);

protected:
	void Start() override;
	void Update() override;
private:

	std::vector<BlockTile*> AllBlockTiles_;
	std::vector<BlockTile*> WaveBlockTiles_;
	std::vector<BlockTile*> BoomBlockTiles_;
	GameEngineRendererTileMap* MapTile_;

	void MakeRightWave(TileIndex _Pos, float _Power);
	void MakeLeftWave(TileIndex _Pos, float _Power);
	//void MakeDownWave(TileIndex _Pos, float _Power);
	//void MakeUpWave(TileIndex _Pos, float _Power);
	void DestroyBoom();
	void DestroyWave();
	void WaveDeathAni();

};