#pragma once
#include <GameEngine/GameEngineLevel.h>

class MonsterRoomLevel : public GameEngineLevel
{
public:
	//construcuter destructer
	MonsterRoomLevel();
	~MonsterRoomLevel();

	//delete Function
	MonsterRoomLevel(const MonsterRoomLevel& _Other) = delete;
	MonsterRoomLevel(MonsterRoomLevel&& _Other) noexcept = delete;
	MonsterRoomLevel& operator=(const MonsterRoomLevel& _Other) = delete;
	MonsterRoomLevel& operator=(MonsterRoomLevel&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
};

