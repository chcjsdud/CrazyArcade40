#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <vector>

class MapGameObject;
class GameEngineImage;
class MapBackGround;
class Player;
class MapFront;
class Area;
class PlayScoreBoard;
class PlayResultUI;
class TimeUI;
class Monster2Level : public GameEngineLevel
{
public:
	Monster2Level();
	~Monster2Level();


	Monster2Level(const Monster2Level& _Other) = delete;
	Monster2Level(Monster2Level&& _Other) noexcept = delete;
	Monster2Level& operator=(const Monster2Level& _Other) = delete;
	Monster2Level& operator=(Monster2Level&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;
private:
	MapBackGround* MapBackGround_;
	MapFront* MapFrontBackGround_;
	MapGameObject* Monster2Object_;
	std::vector<Area> Areas_;
	GameEngineImage* ColMapImage_;

	PlayScoreBoard* PlayScoreBoard_;
	PlayResultUI* PlayResultUI_;
	TimeUI* TimeUI_;
	bool IsGameEnd_;
};