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
    void Start() override;
    void Render();
    void Update();
    void UpdateMove() override;
    void UpdateDirection() override;

private:
    float AttTime_;
    float StayIdleTime_;
    Player* Player_;
    //BossState BassState_;
    //, BossState_(BossState::IDLE)
    int PlayerIndex_;
    float RollTime_;
    float WaterTime_;
    float4 PlayerPos_;
    int CheckIndex_;
    int AreaChangeCount_;
    int RandomAction_;
    bool EndAttack_;

private:
    void UpdateAttack();
    //void SetState(BossState _BossState);
    //BossState GetState() { return BossState_; }
    bool SameXLine();
    bool SameYLine();
    void RollAttack();
    void WaterAttack();
};