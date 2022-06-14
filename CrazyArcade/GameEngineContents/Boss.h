#pragma once
#include "Monster.h"

class Player;
class BossBoom;
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
    void AddBoom(BossBoom* _BossBoom);

protected:
    void Start() override;
    void Render();
    void Update();
    void UpdateMove() override;
    void UpdateDirection() override;
    void TakeDamage() override;
    void Die() override;
    void AllMonsterDeathModeSwitch() override;

private:
    float RollTime_;
    float WaterTime_;
    float StartTime_;
    float WaterAttackInterval_;
    float WaterAttackStartTime_;
    int AreaChangeCount_;
    int RandomAction_;
    bool EndAttack_;
    bool WaterAttacOn_;
    bool LevelStart_;
    GameEngineRenderer* BossHP_;
    GameEngineRenderer* HPUI_;
    std::vector<BossBoom*> BossBooms_;
    int AttackIndex_;
    int SpeechNum_;
    int BossBoomIndex_;
    float SpeechTime_;
    float IntervalTime_;
    bool IsSppechEnd_;
    bool IsAreaChanged;
    int AttCount_;
    float DieBubbleTime_;


private:
    void UpdateAttack();
    void RollAttack();
    void WaterAttack();
    void CheckCanAttackTile(BossBoom* _BossBoom, int _AttackIndex);
    void UpdateHP();
    void Speech();
    void ZeroDirChng();
};