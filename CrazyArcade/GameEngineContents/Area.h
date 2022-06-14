#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineContents/Player.h>

class GameEngineImage;
enum class BlockType;
class Monster;
struct TileIndex;
class BlockTile;
class Area
{
	friend GameEngineLevel;
public:
	Area() 
		:StartX_(0),
		StartY_(0), 
		EndX_(0), 
		EndY_(0),
		CenterX_(0),
		CenterY_(0),
		BlockType_(),
		ColMapImage_(),
		Monster_(),
		MapTile_(),
		TileIndex_()
	{
	}
	Area(GameEngineImage* _ColMapImage, float _StartX, float _StartY, float _EndX, float _EndY);
	~Area();

	//Area(const Area& _Other) = delete;
	//Area(Area&& _Other) noexcept = delete;
   // Area& operator=(const Area& _Other) = delete;
	//Area& operator=(Area&& _Other) noexcept = delete;
private:
	float StartX_;
	float StartY_;
	float EndX_;
	float EndY_;
	float CenterX_;
	float CenterY_;
	GameEngineImage* ColMapImage_;
	Monster* Monster_;
	BlockType* BlockType_;
	GameEngineRendererTileMap* MapTile_;
	TileIndex TileIndex_;

public:
	float4 GetCenter() const { return float4(CenterX_, CenterY_); }

	// �ش���ġ�� Area �ȿ� �ִ���
	bool Contains(float4 _Pos);
	// ColMap�� ������
	bool HasWall();
	bool BossHasWall();
	bool HasWaveTile();
	bool HasBlock();
	int ChooseWaterAttackAni();
	bool HasBubble();
	bool InCenter(float4 _Pos);
	bool GhostCanMoveTile();

	BlockTile* GetTile(float4 _Pos);

	inline void SetMapTile(GameEngineRendererTileMap* _MapTile)
	{
		MapTile_ = _MapTile;
	}

	GameEngineRendererTileMap* GetMapTile()
	{
		return MapTile_;
	}
};