#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class GameEngineCollision;
class StartButton : public GameEngineActor
{
public:
	//construcuter destructer
	StartButton();
	~StartButton();

	//delete Function
	StartButton(const StartButton& _Other) = delete;
	StartButton(StartButton&& _Other) noexcept = delete;
	StartButton& operator=(const StartButton& _Other) = delete;
	StartButton& operator=(StartButton&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;
	void Render() override {};

	void StartButtonClick();
	GameEngineRenderer* StartRenderer_;
	GameEngineCollision* StartCollision_;
};

