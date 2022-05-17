#pragma once
#include <GameEngine/GameEngineLevel.h>
class MapBackGround;
class Player;
class Monster1Level : public GameEngineLevel
{
public:
	Monster1Level();
	~Monster1Level();


	Monster1Level(const Monster1Level& _Other) = delete;
	Monster1Level(Monster1Level&& _Other) noexcept = delete;
	Monster1Level& operator=(const Monster1Level& _Other) = delete;
	Monster1Level& operator=(Monster1Level&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;
private:
	MapBackGround* MapBackGround_;
	MapBackGround* MapFrontBackGround_;
};