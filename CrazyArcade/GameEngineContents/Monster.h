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
	static int TTL_MONSTER_COUNT;

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

protected:
	GameEngineRendererTileMap* MapTile_;
	BlockTile* Tile_;
	BlockType CurBlockType_;
	GameEngineRenderer* Renderer_;
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

	int HP_;
	int Index_;
	int AreaWidth_;
	int AreaHeight_;
	float Speed_;
	float GetAttTime_;
	int PrevIndex_;
	const float MapSizeX_;
	const float MapSizeY_;
	bool IndexCheck_;

	GameEngineCollision* TopCol_;
	GameEngineCollision* LeftCol_;
	GameEngineCollision* RightCol_;
	GameEngineCollision* BottomCol_;
	GameEngineCollision* CenterCol_;
	std::vector<std::vector<Tile*>> Tiles_;
	std::map<int, Area> MovableAreas;

public:
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


	void CheckWaveTile(float4 _Pos);
	inline void SetMapTile(GameEngineRendererTileMap* _MapTile)
	{
		MapTile_ = _MapTile;
		for (Area _Area : Areas_)
		{
			_Area.SetMapTile(_MapTile);
		}
	}

	GameEngineRendererTileMap* GetMapTile()
	{
		return MapTile_;
	}
};


