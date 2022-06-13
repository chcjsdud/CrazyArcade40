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
class CemetoryLevel : public GameEngineLevel
{
public:
	CemetoryLevel();
	~CemetoryLevel();


	CemetoryLevel(const CemetoryLevel& _Other) = delete;
	CemetoryLevel(CemetoryLevel&& _Other) noexcept = delete;
	CemetoryLevel& operator=(const CemetoryLevel& _Other) = delete;
	CemetoryLevel& operator=(CemetoryLevel&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;


private:
	MapBackGround* MapBackGround_;
	MapFront* MapFrontBackGround_;
	MapGameObject* CemetoryObject_;

private:
	std::vector<Area> Areas_;
	GameEngineImage* ColMapImage_;

	PlayScoreBoard* PlayScoreBoard_;
	PlayResultUI* PlayResultUI_;
	TimeUI* TimeUI_;
	bool IsGameEnd_;
};