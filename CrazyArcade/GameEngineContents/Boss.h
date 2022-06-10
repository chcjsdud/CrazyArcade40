#pragma once
#include "Monster.h"

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

    void SetBoom(MapGameObject* _BossBoom);


protected:
    void Start() override;
    void Render();
    void Update();
    void UpdateMove() override;
    void UpdateDirection() override;
    void TakeDamage() override;
    void Die() override;

private:
    Player* Player_;
    //BossState BassState_;
    //, BossState_(BossState::IDLE)
    int PlayerIndex_;
    float RollTime_;
    float WaterTime_;
    float WaterAttackStartTime_;
    float4 PlayerPos_;
    int CheckIndex_;
    int AreaChangeCount_;
    int RandomAction_;
    bool EndAttack_;
    bool WaterAttacOn_;
    GameEngineRenderer* BossHP_;
    GameEngineRenderer* HPUI_;
    MapGameObject* BossBoom_;
    Boss* Boss_;


private:
    void UpdateAttack();
    //void SetState(BossState _BossState);
    //BossState GetState() { return BossState_; }
    bool SameXLine();
    bool SameYLine();
    void RollAttack();
    void WaterAttack();
    void CheckCanAttackTile();
    void UpdateHP();

};