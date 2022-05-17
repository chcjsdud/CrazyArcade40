#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineBackGroundRenderer_;
class CreateRoomBackGround : public GameEngineActor
{
public:
	//construcuter destructer
	CreateRoomBackGround();
	~CreateRoomBackGround();

	//delete Function
	CreateRoomBackGround(const CreateRoomBackGround& _Other) = delete;
	CreateRoomBackGround(CreateRoomBackGround&& _Other) noexcept = delete;
	CreateRoomBackGround& operator=(const CreateRoomBackGround& _Other) = delete;
	CreateRoomBackGround& operator=(CreateRoomBackGround&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;

	GameEngineRenderer* CreateRoomBackGroundRenderer_;
	GameEngineRenderer* NormalModeBtnRenderer_;
	GameEngineRenderer* MonsterModeBtnRenderer_;

	GameEngineRenderer* NormalModeRenderer_;
	GameEngineRenderer* MonsterModeRenderer_;

	GameEngineCollision* NormalBtnCollision_;
	GameEngineCollision* MonsterBtnCollision_;

private:
	int SelectMode_ = 0;
};

