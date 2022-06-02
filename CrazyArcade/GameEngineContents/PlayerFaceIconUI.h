#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineBackGroundRenderer_;
class PlayerFaceIconUI : public GameEngineActor
{
public:
	//construcuter destructer
	PlayerFaceIconUI();
	~PlayerFaceIconUI();

	//delete Function
	PlayerFaceIconUI(const PlayerFaceIconUI& _Other) = delete;
	PlayerFaceIconUI(PlayerFaceIconUI&& _Other) noexcept = delete;
	PlayerFaceIconUI& operator=(const PlayerFaceIconUI& _Other) = delete;
	PlayerFaceIconUI& operator=(PlayerFaceIconUI&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;

	GameEngineRenderer* PlayerFaceIconUIRenderer_;

	float BlinkTime_ = 0.0f;
	float CryTime_ = 0.0f;
	bool islive = true;
private:
};

