#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

class GameEngineImage;
class GameEngineCollision;

enum class PlayerState
{
	Idle, 
	Move,
	Jump,
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

class Player : public GameEngineActor
{
	static int PLAYER_COUNT;

public:
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

	// 플레이어 정보
protected:
	float CurSpeed_;			// 플레이어 속도 
	float MaxSpeed_;
	float CurAttLength_;		// 물줄기 길이
	float MaxAttLength_;		// 최대 물줄기 길이
	int CurAttCount_;			// 물풍선 개수 
	int MaxAttCount_;			// 최대 물풍선 개수
	
	// 플레이어 정보 세팅
protected:
	void SetSpeed(float _CurSpeed)
	{
		CurSpeed_ = _CurSpeed;
	}

	void SetAttLength(float _CurAttLength_)
	{
		CurAttLength_ = _CurAttLength_;
	}

	void SetAttCount(int _CurAttCount_)
	{
		CurAttCount_ = _CurAttCount_;
	}

	void SetMaxSpeed(float _MaxSpeed)
	{
		MaxSpeed_ = _MaxSpeed;
	}

	void SetMaxAttLength(float _MaxAttLength)
	{
		MaxAttLength_ = _MaxAttLength;
	}

	void SetMaxAttCount(int _MaxAttCount)
	{
		MaxAttCount_ = _MaxAttCount;
	}

	void PlayerInfoUpdate();

	void SpeedUpdate();
	void AttackCountUpdate();
	void AttackLengthUpdate();

protected:
	PlayerType Type;
	Character CurCharacter;

protected:
	void CharTypeUpdate();

	void Move();

	virtual bool IsMoveKey();

public:
	void SetCharacter(Character _CurCharacter)
	{
		CurCharacter = _CurCharacter;
	}

	void SetPlayerType(PlayerType _Type)
	{
		Type = _Type;
	}

	

protected:
	GameEngineRenderer* PlayerAnimationRender_;
	PlayerDir CurDir_;
	//PlayerDir InputDir_;
	std::string AnimationName_;
	std::string ChangeDirText_;

protected:
	// 충돌
	GameEngineCollision* Collision1P_;
	GameEngineCollision* Collision2P_;

	GameEngineRenderer* BazziRenderer_;
	GameEngineRenderer* DaoRenderer_;




////////////////////////////////////////////////////////////
private:
	// 맵 관련
	GameEngineImage* MapColImage_;

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
	//PlayerState PrevState_;

protected:
	void ChangeState(PlayerState _State);
	void PlayerStateUpdate();
	virtual void DirAnimationCheck();

protected:
	virtual void IdleStart();
	virtual void MoveStart();
	virtual void JumpStart();
	virtual void DamagedStart();
	virtual void LiveStart();
	virtual void DieStart();

	virtual void IdleUpdate();
	virtual void MoveUpdate();
	virtual void JumpUpdate();
	virtual void DamagedUpdate();
	virtual void LiveUpdate();
	virtual void DieUpdate();
};
