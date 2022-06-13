#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
class MapBackGround;
class MapFront;
class Player;
class MapGameObject;
class Area;
class PlayScoreBoard;
class PlayResultUI;
class TimeUI;
class VillageLevel : public GameEngineLevel
{
public:
	VillageLevel();
	~VillageLevel();


	VillageLevel(const VillageLevel& _Other) = delete;
	VillageLevel(VillageLevel&& _Other) noexcept = delete;
	VillageLevel& operator=(const VillageLevel& _Other) = delete;
	VillageLevel& operator=(VillageLevel&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	MapBackGround* MapBackGround_;
	MapFront* MapFrontBackGround_;
	MapGameObject* VillageObject_;

private:
	std::vector<Area> Areas_;
	GameEngineImage* ColMapImage_;

	PlayScoreBoard* PlayScoreBoard_;
	PlayResultUI* PlayResultUI_;
	TimeUI* TimeUI_;
	bool IsGameEnd_;
};