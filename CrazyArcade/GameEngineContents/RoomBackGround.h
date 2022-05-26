#pragma once
#include <GameEngine/GameEngineActor.h>

class RoomBackGround : public GameEngineActor
{
public:
	//construcuter destructer
	RoomBackGround();
	~RoomBackGround();

	//delete Function
	RoomBackGround(const RoomBackGround& _Other) = delete;
	RoomBackGround(RoomBackGround&& _Other) noexcept = delete;
	RoomBackGround& operator=(const RoomBackGround& _Other) = delete;
	RoomBackGround& operator=(RoomBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineCollision* BackBtnCollision_;
	GameEngineCollision* ExitBtnCollision_;
};

