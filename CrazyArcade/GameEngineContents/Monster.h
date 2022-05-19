#pragma once
#include <GameEngine/GameEngineActor.h>

enum class MonsterState
{
	WALK,
	ATTCK,
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
class Monster : public GameEngineActor
{
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
	void Update();

protected:
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineImage* ColMapImage_;
	MonsterClass MonsterClass_;
	MonsterState MonsterState_;
	int HP_;
	int Speed_;
	float4 Dir_;
	float GetAttTime_;
	BlockTile* Tile_;

private:

public:
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

	void SetSpeed(int _Speed)
	{
		Speed_ = _Speed;
	}

	int GetSpeed()
	{
		return Speed_;
	}

	int GetHP()
	{
		return HP_;
	}

	void Die();
	bool IsDie();
};


