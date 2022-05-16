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
};

enum class PlayerDir
{
	Left,
	Right,
	Down,
	Up,
	Max,
};


class Player : public GameEngineActor
{
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
	float Speed_;				// 플레이어 속도 
	float AttackLength_;		// 물줄기 길이
	float AttackCount_;			// 물풍선 개수 

protected:
	void Move();

protected:
	GameEngineRenderer* PlayerAnimationRender_;
	PlayerDir CurDir_;
	//PlayerDir InputDir_;
	std::string AnimationName_;
	std::string ChangeDirText_;

protected:
	// 충돌
	GameEngineCollision* PlayerCollision_;

	// 맵 관련
	GameEngineImage* MapColImage_;

	void ColMapUpdate();
	void StagePixelCheck(float _Speed);

protected:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void Start() override;
	void Update() override;
	void Render() override;

protected:
	float4 MoveDir;
	PlayerState CurState_;
	//PlayerState PrevState_;

	bool IsMoveKey();

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
