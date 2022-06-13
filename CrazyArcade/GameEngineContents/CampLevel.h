#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>

class MapGameObject;
class GameItemObject;
class MapBackGround;
class Player;
class MapFront;
class Area;
class PlayScoreBoard;
class PlayResultUI;
class TimeUI;
class CampLevel : public GameEngineLevel
{
private:
	MapBackGround* MapBackGround_;
	MapFront* MapFrontBackGround_;
	MapGameObject* CampObject_;
public:
	CampLevel();
	~CampLevel();


	CampLevel(const CampLevel& _Other) = delete;
	CampLevel(CampLevel&& _Other) noexcept = delete;
	CampLevel& operator=(const CampLevel& _Other) = delete;
	CampLevel& operator=(CampLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	std::vector<Area> Areas_;
	GameEngineImage* ColMapImage_;

	PlayScoreBoard* PlayScoreBoard_;
	PlayResultUI* PlayResultUI_;
	TimeUI* TimeUI_;
	bool IsGameEnd_;
};
