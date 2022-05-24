#pragma once
#include <GameEngine/GameEngineLevel.h>

class Area;
class MapBackGround;
class Player;
class GameEngineImage;
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
	std::vector<Area> Areas_;
	GameEngineImage* ColMapImage_;
};