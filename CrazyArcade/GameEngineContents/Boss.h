#pragma once
#include "Monster.h"
#include <GameEngineContents/Area.h>

enum class BossState
{
    IDLE,
    WALK,
    BUBBLEATTACK,
    ROLLATTACK,
    TAKEDAMAGE,
    DIE,
};

class Player;
class GameEngineImage;
class GameEngineRenderer;
class Boss : public Monster
{
public:
    Boss();
    ~Boss();

    Boss(const Boss& _Other) = delete;
    Boss(Boss&& _Other) noexcept = delete;
    Boss& operator=(const Boss& _Other) = delete;
    Boss& operator=(Boss&& _Other) noexcept = delete;

public:
    void SetPlayer(Player* _Player)
    {
        Player_ = _Player;
    }
protected:
    void Start();
    void Render();
    void Update();
    void UpdateMove() override;
    void UpdateState();

private:
    bool StartMove_;
    float WaterTime_;
    float MoveTime_;
    float RollTime_;
    float4 PlayerPos_;
    Player* Player_;
    BossState BossState_;
    std::string Direction_;
    std::string CurrentLevel_;
    int PlayerIndex_;	
    float SettingTime_;


private:
    void SetState(BossState _BossState);
    BossState GetState() { return BossState_; }
    void StateUpdate();
    void UpdateIdle();
    void UpdateWalk();
    void UpdateBubbleAttack();
    void UpdateRollAttack();
    void UpdateTakeDamage();
    void UpdateDie();
    void CollisionCheck();
    bool SameXLine();
    bool SameYLine();
};