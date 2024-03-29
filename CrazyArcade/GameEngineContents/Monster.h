#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Area.h"

enum class MonsterState
{
	IDLE,
	WALK,
	ATTCK,
	TAKEDAMAGE,
	DIE,
};

enum class MonsterClass
{
	DEFAULT,
	BOSS,
};

class GameEngineImage;
class GameEngineRenderer;
class BlockTile;
class Area;
class GameEngineRendererTileMap;
class Monster : public GameEngineActor
{
	friend Area;
public:
	static int LV1_MON_COUNT;
	static int LV2_MON_COUNT;
	static int BOSS_COUNT;


public:
	Monster();
	~Monster();
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

protected:
	virtual void UpdateMove();
	virtual void TakeDamage();
	void Start();
	void Render();
	virtual void Update();
	virtual void UpdateDirection();
	virtual void Die();
	virtual bool IsDie();
	virtual void AllMonsterDeathModeSwitch();

protected:
	GameEngineRendererTileMap* MapTile_;
	BlockTile* Tile_;
	BlockType CurBlockType_;
	GameEngineRenderer* Renderer_;
	GameEngineRenderer* SpeechBubble_;
	GameEngineImage* ColMapImage_;

	MonsterClass MonsterClass_;
	MonsterState MonsterState_;
	float4 Dir_;
	std::string Direction_;
	std::vector<Area> Areas_;
	Area EastArea;
	Area WestArea;
	Area NorthArea;
	Area SouthArea;
	Area CurArea;
	Area NorthEastArea;
	Area NorthWestArea;
	Area SouthEastArea;
	Area SouthWestArea;


	int HP_;
	int Index_;
	int AreaWidth_;
	int AreaHeight_;
	float Speed_;
	float GetAttTime_;
	int PrevIndex_;
	float MapSizeX_;
	float MapSizeY_;
	bool IndexCheck_;
	bool IsStageClear_;
	bool HasSpeechBubble_;

	GameEngineCollision* TopCol_;
	GameEngineCollision* LeftCol_;
	GameEngineCollision* RightCol_;
	GameEngineCollision* BottomCol_;
	GameEngineCollision* CenterCol_;
	std::vector<std::vector<Tile*>> Tiles_;
	std::map<int, Area> MovableAreas;

public:

	void SetMapSizeY(float _MapSizeY)
	{
		MapSizeY_ = _MapSizeY;
	}

	void SetMapSizeX(float _MapSizeX)
	{
		MapSizeX_ = _MapSizeX;
	}

	float4 GetPositionRelativeToTile()
	{
		return GetPosition() + float4(-20.0f, -40.0f);
	}

	BlockType CheckBlockTile(float4 _Pos);

	void SetColMapImage(std::string _Name);
	virtual GameEngineImage* GetColMapImage();

	void SetMonsterClass(MonsterClass _MonsterClass)
	{
		MonsterClass_ = _MonsterClass;
	}

	MonsterClass GetMonsterClass()
	{
		return MonsterClass_;
	}

	void SetMonsterState(MonsterState _MonsterState)
	{
		MonsterState_ = _MonsterState;
	}

	MonsterState GetMonsterState()
	{
		return MonsterState_;
	}

	void SetHP(int _HP)
	{
		HP_ = _HP;
	}

	int GetHp()
	{
		return HP_;
	}

	void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
	}

	float GetSpeed()
	{
		return Speed_;
	}

	int GetHP()
	{
		return HP_;
	}


	bool CheckWaveTile(float4 _Pos);
	inline void SetMapTile(GameEngineRendererTileMap* _MapTile)
	{
		MapTile_ = _MapTile;
		for (Area& _Area : Areas_)
		{
			_Area.SetMapTile(_MapTile);
		}
	}

	GameEngineRendererTileMap* GetMapTile()
	{
		return MapTile_;
	}

	int GetIndex()
	{
		return Index_;
	}
};


