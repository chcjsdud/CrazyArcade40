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
	DamageStart,
	Damaged,	// 물방울 갇혔을 때 1차 애니메이션
	Revival,
	Fade,		// 물방울 갇혔을 때 2차 애니메이션
	Die,
	OnOwl,
	OnTurtle,
	OnUFO,
	OffOwl,
	OffTurtle,
	OffUFO,
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
	None,
	Max,
};

enum class PlayerType
{
	Player1,
	Player2,

	Max,
};


class GameEngineImage;
class GameEngineCollision;

class MapGameObject;
class MapBackGround;
class BlockTile;
class ItemBlockTile;
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

protected:
	float4 Position_;

	float4 Player1Pos_;
	float4 Player2Pos_;

	float4 LeftPos_1P;
	float4 RightPos_1P;
	float4 UpPos_1P;
	float4 DownPos_1P;	
	
	float4 LeftPos_2P;
	float4 RightPos_2P;
	float4 UpPos_2P;
	float4 DownPos_2P;

	void PositionUpdate();

	// 플레이어 정보
protected:
	int BazziAttCount_;
	int DaoAttCount_;
	int MaridAttCount_;

	float BazziAttPower_;
	float DaoAttPower_;
	float MaridAttPower_;

	float BazziSpeed_;
	float DaoSpeed_;
	float MaridSpeed_;

	int BazziMaxAttCount_;
	int DaoMaxAttCount_;
	int MaridMaxAttCount_;

	float BazziMaxAttPower_;
	float DaoMaxAttPower_;
	float MaridMaxAttPower_;

	float BazziMaxSpeed_;
	float DaoMaxSpeed_;
	float MaridMaxSpeed_;

	size_t Player1BoomCount_;
	size_t Player2BoomCount_;
	size_t CurAttCount_;			// 물풍선 개수 
	float CurAttPower_;			// 물줄기 길이
	float CurSpeed_;			// 플레이어 속도 

	int MaxAttCount_;			// 최대 물풍선 개수
	float MaxAttPower_;		// 최대 물줄기 길이
	float MaxSpeed_;

	float Time_;
	float AttMoveTime_;

	float MovePos_;
	// 플레이어 정보 세팅
	void AddTime();
	bool IsTimeAdd;

private:
	PlayerDir CheckDir_;
	bool IsBoomblock;
	bool IsLive;
	bool IsShield;
	bool IsDevil;
	bool IsInvincible;
	bool IsShoes;
	bool IsNiddle;
	bool IsJump;

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

	void SetCollision(GameEngineCollision* _Collision);

	void PlayerInit();
	void PlayerInfoUpdate();
	void ItemCheck(Player* _Player, ItemType _ItemType);
	void ItemTime();

	void Attack();

protected:
	PlayerType Type;
	Character CurCharacter;

protected:
	void CharTypeUpdate();

	bool IsReady;
	bool IsMove;
	void Move(float _CurSpeed);

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
	ItemType CheckItem(float4 _Pos);

	BlockType CurBlockType1_;
	BlockType CurBlockType2_;

	BlockType LeftBlock;
	BlockType RightBlock;
	BlockType UpBlock;
	BlockType DownBlock;

	ItemType CurItemType1_;
	ItemType CurItemType2_;

	void TileCheckResultUpdate(BlockType _CurBlockType);
	void TileCheckResult();

	void FrontBlockCheckUpdate();
	void FrontBlockCheck();
public:
	MapBackGround* GetMapBackGround()
	{
		return MapBackGround_;
	}

protected:
	MapGameObject* Boom_;
	MapGameObject* Box_;
	MapGameObject* Bubble_;

	MapBackGround* MapBackGround_;

public:
	inline Character GetCharacter()
	{
		return CurCharacter;
	}

	inline PlayerType GetPlayerType()
	{
		return Type;
	}

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

	inline bool GetIslive()
	{
		return IsLive;
	}

protected:
	GameEngineRenderer* PlayerAnimationRender_;
	PlayerDir CurDir_;
	PlayerDir InputDir_;
	std::string AnimationName_;
	std::string ChangeDirText_;


protected:
	// 충돌
	GameEngineCollision* Collision1P_;
	GameEngineCollision* Collision2P_;

	GameEngineRenderer* BazziRenderer_;
	GameEngineRenderer* MaridRenderer_;
	GameEngineRenderer* DaoRenderer_;
	GameEngineRenderer* EffectRenderer_;

	GameEngineRenderer* ArrowRenderer_1P;
	GameEngineRenderer* ArrowRenderer_2P;
private:
	GameEngineRendererTileMap* MapTile_;

	////////////////////////////////////////////////////////////
private:
	// 맵 관련
	GameEngineImage* MapColImage_;
	GameEngineRenderer* MapColRenderer_;
	int Playeractorvalue_ =0;
	std::string CurrentLevel_;
	//std::string CurrentColMap_;

protected:
	void ColMapUpdate();
	void StagePixelCheck(float _Speed);

	void PlayerCollisionUpdate();

	void CollisionCheck();

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
	void DamagedStartStart();
	void DamagedStart();
	void RevivalStart();
	void FadeStart();
	void DieStart();
	void OnOwlStart();
	void OnTurtleStart();
	void OnUFOStart();
	void OffOwlStart();
	void OffTurtleStart();
	void OffUFOStart();
	void IdleOwlStart();
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
	void DamagedStartUpdate();
	void DamagedUpdate();
	void RevivalUpdate();
	void FadeUpdate();
	void DieUpdate();
	void OnOwlUpdate();
	void OnTurtleUpdate();
	void OnUFOUpdate();
	void OffOwlUpdate();
	void OffTurtleUpdate();
	void OffUFOUpdate();
	void IdleOwlUpdate();
	void IdleTurtleUpdate();
	void RidingOwlUpdate();
	void RidingTurtleUpdate();
	void RidingUFOUpdate();
};
