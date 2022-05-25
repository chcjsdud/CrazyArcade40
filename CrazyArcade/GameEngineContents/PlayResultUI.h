#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

class GameEngineBackGroundRenderer_;
class PlayResultUI : public GameEngineActor
{
public:
	//construcuter destructer
	PlayResultUI();
	~PlayResultUI();

	//delete Function
	PlayResultUI(const PlayResultUI& _Other) = delete;
	PlayResultUI(PlayResultUI&& _Other) noexcept = delete;
	PlayResultUI& operator=(const PlayResultUI& _Other) = delete;
	PlayResultUI& operator=(PlayResultUI&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;

	std::vector<GameEngineRenderer*> PlayResultUIRenderer_;

private:
	float IntroMoveTime_;
	float StartTime_ =0.1f;
	float BlinkTime_ =0.0f;
	int GameResult = 1;
};

