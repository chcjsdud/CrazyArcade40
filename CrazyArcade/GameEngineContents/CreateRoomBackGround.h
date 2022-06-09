#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

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


	inline void SetPlayerMode(PlayerMode _Mode)
	{
		Mode_ = _Mode;
	}

protected:


private:
	void Start() override;
	void Update() override;


	PlayerMode Mode_;
	GameEngineRenderer* CreateRoomBackGroundRenderer_;
	GameEngineRenderer* NormalModeBtnRenderer_;
	GameEngineRenderer* MonsterModeBtnRenderer_;

	GameEngineRenderer* NormalModeRenderer_;
	GameEngineRenderer* MonsterModeRenderer_;

	GameEngineRenderer* ConfirmBtnRenderer_;
	GameEngineRenderer* CancelBtnRenderer_;

	GameEngineCollision* NormalBtnCollision_;
	GameEngineCollision* MonsterBtnCollision_;
	GameEngineCollision* ConfirmBtnCollision_;
	GameEngineCollision* CancelBtnCollision_;

private:
	int SelectMode_ = 0;
};

