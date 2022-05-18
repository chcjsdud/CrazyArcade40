#pragma once
#include <GameEngine/GameEngineLevel.h>

class CreateRoomLevel : public GameEngineLevel
{
public:
	//construcuter destructer
	CreateRoomLevel();
	~CreateRoomLevel();

	//delete Function
	CreateRoomLevel(const CreateRoomLevel& _Other) = delete;
	CreateRoomLevel(CreateRoomLevel&& _Other) noexcept = delete;
	CreateRoomLevel& operator=(const CreateRoomLevel& _Other) = delete;
	CreateRoomLevel& operator=(CreateRoomLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
};

