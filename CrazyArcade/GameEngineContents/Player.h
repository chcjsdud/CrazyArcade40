#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineRendererTileMap.h>


enum class PlayerState
{
	Ready,
	Idle, 
	Move,
	Jump,
	Attack,
	Damaged,
	Live,
	Die,

	Max,
};

enum class PlayerDir
{
	Left,
	Right,
	Down,
	Up,
	Max,
};

enum class PlayerType
{
	Player1,
	Player2,
	
	Max,
};

enum class Character
{
	BAZZI,
	DAO,

	MAX,
};

class GameEngineImage;
class GameEngineCollision;

class MapGameObject;
class MapBackGround;
class BlockTile;
class Player : public GameEngineActor
{
public:
	static int PLAYER_COUNT;

	static Player* MainPlayer_1;
	static Player* MainPlayer_2;

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	bool IsDebug;

	void DebugModeSwitch();

	// �÷��̾� ����
protected:
	float CurSpeed_;			// �÷��̾� �ӵ� 
	float MaxSpeed_;
	float CurAttPower_;		// ���ٱ� ����
	float MaxAttPower_;		// �ִ� ���ٱ� ����
	int CurAttCount_;			// ��ǳ�� ���� 
	int MaxAttCount_;			// �ִ� ��ǳ�� ����
	
	// �÷��̾� ���� ����
protected:
	void SetSpeed(float _CurSpeed)
	{
		CurSpeed_ = _CurSpeed;
	}

	void SetAttPower(float _CurAttPower)
	{
		CurAttPower_ = _CurAttPower;
	}

	void SetAttCount(int _CurAttCount_)
	{
		CurAttCount_ = _CurAttCount_;
	}

	void SetMaxSpeed(float _MaxSpeed)
	{
		MaxSpeed_ = _MaxSpeed;
	}

	void SetMaxAttPower(float _MaxAttPower)
	{
		MaxAttPower_ = _MaxAttPower;
	}

	void SetMaxAttCount(int _MaxAttCount)
	{
		MaxAttCount_ = _MaxAttCount;
	}

	void PlayerInfoUpdate();

	void SpeedUpdate();
	void AttackCountUpdate();
	void AttackPowerUpdate();

protected:
	PlayerType Type;
	Character CurCharacter;

protected:
	void CharTypeUpdate();

	bool IsReady;
	bool IsMove;
	void Move();

	bool IsMoveKey();
	bool IsAttackKey();

public:
	MapGameObject* GetBoom()
	{
		return Boom_;
	}

	MapBackGround* GetMapBackGround()
	{
		return MapBackGround_;
	}

protected:
	MapGameObject* Boom_;
	MapGameObject* Wave_;
	MapBackGround* MapBackGround_;

public:
	void SetCharacter(Character _CurCharacter)
	{
		CurCharacter = _CurCharacter;
	}

	void SetPlayerType(PlayerType _Type)
	{
		Type = _Type;
	}
	inline void SetMapTile(GameEngineRendererTileMap* _MapTile)
	{
		MapTile_ = _MapTile;
	}

protected:
	GameEngineRenderer* PlayerAnimationRender_;
	PlayerDir CurDir_;
	//PlayerDir InputDir_;
	std::string AnimationName_;
	std::string ChangeDirText_;

protected:
	// �浹
	GameEngineCollision* Collision1P_;
	GameEngineCollision* Collision2P_;

	GameEngineRenderer* BazziRenderer_;
	GameEngineRenderer* DaoRenderer_;

private:
	GameEngineRendererTileMap* MapTile_;

////////////////////////////////////////////////////////////
private:
	// �� ����
	GameEngineImage* MapColImage_;
	GameEngineRenderer* MapColRenderer_;

	std::string CurrentLevel_;
	//std::string CurrentColMap_;

protected:
	void ColMapUpdate();
	void StagePixelCheck(float _Speed);

	void CollisionResultUpdate();

	void PlayerCollisionUpdate();

	std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameCopy();
	}

	//GameEngineImage* GetCurrentColMap(std::string _CurrentColMap)
	//{
	//	return GameEngineImageManager::GetInst()->Find(CurrentColMap_);
	//}

protected:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void Start() override;
	void Update() override;
	void Render() override;

protected:
	float4 MoveDir;
	PlayerState CurState_;
	PlayerState PrevState_;

protected:
	void ChangeState(PlayerState _State);
	void PlayerStateUpdate();
	virtual void DirAnimationCheck();

protected:
	virtual void ReadyStart();
	virtual void IdleStart();
	virtual void MoveStart();
	virtual void JumpStart();
	virtual void AttackStart();
	virtual void DamagedStart();
	virtual void LiveStart();
	virtual void DieStart();

	virtual void ReadyUpdate();
	virtual void IdleUpdate();
	virtual void MoveUpdate();
	virtual void JumpUpdate();
	virtual void AttackUpdate();
	virtual void DamagedUpdate();
	virtual void LiveUpdate();
	virtual void DieUpdate();
};
