#pragma once
#include <GameEngine/GameEngineLevel.h>
class MapBackGround;
class Player;
class BossLevel : public GameEngineLevel
{
public:
	BossLevel();
	~BossLevel();


	BossLevel(const BossLevel& _Other) = delete;
	BossLevel(BossLevel&& _Other) noexcept = delete;
	BossLevel& operator=(const BossLevel& _Other) = delete;
	BossLevel& operator=(BossLevel&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	MapBackGround* MapBackGround_;
};