#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineRendererTileMap.h>
#include "ContentsEnum.h"

enum class PlayerState
{
	Wait,
	Ready,
	Idle, 
	Move,
	Jump,
	Attack,
	Damaged,	// 물방울 갇혔을 때 1차 애니메이션
	Revival,
	Fade,		// 물방울 갇혔을 때 2차 애니메이션
	Die,
	IdleOwl,
	IdleTurtle,
	RidingOwl,
	RidingTurtle,
	RidingUFO,

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

	// 플레이어 정보
protected:
	float CurSpeed_;			// 플레이어 속도 
	float MaxSpeed_;
	float CurAttPower_;		// 물줄기 길이
	float MaxAttPower_;		// 최대 물줄기 길이
	int CurAttCount_;			// 물풍선 개수 
	int MaxAttCount_;			// 최대 물풍선 개수

	float Time_;
	float AttMoveTime_;
	
	// 플레이어 정보 세팅
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

	bool IsLeftMove;
	bool IsRightMove;
	bool IsUpMove;
	bool IsDownMove;

	bool IsMoveKey();
	bool IsAttackKey();
	bool IsItemKey();

private:
	//블럭 체크하는 함수
	BlockType CheckBlockTile(float4 _Pos);
	BlockType CurBlockType1_;
	BlockType CurBlockType2_;
	
	BlockType LeftBlock;
	BlockType RightBlock;
	BlockType UpBlock;
	BlockType DownBlock;


	void TileCheckResultUpdate(BlockType _CurBlockType);
	void TileCheckResult();

	void FrontBlockCheckUpdate();
	void FrontBlockCheck();
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
	// 충돌
	GameEngineCollision* Collision1P_;
	GameEngineCollision* Collision2P_;

	GameEngineRenderer* BazziRenderer_;
	GameEngineRenderer* MaridRenderer_;
	GameEngineRenderer* DaoRenderer_;

private:
	GameEngineRendererTileMap* MapTile_;

////////////////////////////////////////////////////////////
private:
	// 맵 관련
	GameEngineImage* MapColImage_;
	GameEngineRenderer* MapColRenderer_;

	std::string CurrentLevel_;
	//std::string CurrentColMap_;

protected:
	void ColMapUpdate();
	void StagePixelCheck(float _Speed);

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
	void WaitStart();
	void ReadyStart();
	void IdleStart();
	void MoveStart();
	void JumpStart();
	void AttackStart();
	void DamagedStart();
	void RevivalStart();
	void FadeStart();
	void DieStart();
	void IdeOwlStart();
	void IdleTurtleStart();
	void RidingOwlStart();
	void RidingTurtleStart();
	void RidingUFOStart();

	void WaitUpdate();
	void ReadyUpdate();
	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void AttackUpdate();
	void DamagedUpdate();
	void RevivalUpdate();
	void FadeUpdate();
	void DieUpdate();
	void IdleOwlUpdate();
	void IdleTurtleUpdate();
	void RidingOwlUpdate();
	void RidingTurtleUpdate();
	void RidingUFOUpdate();
};
