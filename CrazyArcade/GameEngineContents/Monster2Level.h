#pragma once
#include <GameEngine/GameEngineLevel.h>
class MapBackGround;
class Player;
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
	MapBackGround* MapFrontBackGround_;
};