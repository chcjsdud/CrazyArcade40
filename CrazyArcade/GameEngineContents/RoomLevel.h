#pragma once
#include <GameEngine/GameEngineLevel.h>

class RoomLevel : public GameEngineLevel
{
public:
	//construcuter destructer
	RoomLevel();
	~RoomLevel();

	//delete Function
	RoomLevel(const RoomLevel& _Other) = delete;
	RoomLevel(RoomLevel&& _Other) noexcept = delete;
	RoomLevel& operator=(const RoomLevel& _Other) = delete;
	RoomLevel& operator=(RoomLevel&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
};

