#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

class GameEngineBackGroundRenderer_;
class StartIntroUI : public GameEngineActor
{
public:
	//construcuter destructer
	StartIntroUI();
	~StartIntroUI();

	//delete Function
	StartIntroUI(const StartIntroUI& _Other) = delete;
	StartIntroUI(StartIntroUI&& _Other) noexcept = delete;
	StartIntroUI& operator=(const StartIntroUI& _Other) = delete;
	StartIntroUI& operator=(StartIntroUI&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;

	std::vector<GameEngineRenderer*> StartIntroUIRenderer_;

private:
	float IntroMoveTime_;
	float StartTime_ =0.1f;
};

