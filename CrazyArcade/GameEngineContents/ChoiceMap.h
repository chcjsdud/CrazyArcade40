#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineBackGroundRenderer_;
class ChoiceMap : public GameEngineActor
{
public:
	//construcuter destructer
	ChoiceMap();
	~ChoiceMap();

	//delete Function
	ChoiceMap(const ChoiceMap& _Other) = delete;
	ChoiceMap(ChoiceMap&& _Other) noexcept = delete;
	ChoiceMap& operator=(const ChoiceMap& _Other) = delete;
	ChoiceMap& operator=(ChoiceMap&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;

	GameEngineRenderer* ChoiceMapRenderer_;
	GameEngineRenderer* ChoiceMapRenderer_1;
	GameEngineRenderer* ChoiceMapRenderer_2;
	GameEngineRenderer* ChoiceMapRenderer_3;
	GameEngineCollision* ChoiceMapCollision_1;
	GameEngineCollision* ChoiceMapCollision_2;
	GameEngineCollision* ChoiceMapCollision_3;



	GameEngineRenderer* ConfirmBtnRenderer_;
	GameEngineRenderer* CancelBtnRenderer_;
	GameEngineCollision* ConfirmBtnCollision_;
	GameEngineCollision* CancelBtnCollision_;

private:
	int ChoiceMap_ = 0;
	int TempChoiceMap_ = 0;
};

