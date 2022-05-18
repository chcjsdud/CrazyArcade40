#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class TimeUI : public GameEngineActor
{
public:
	// constrcuter destructer
	TimeUI();
	~TimeUI();

	// delete Function
	TimeUI(const TimeUI& _Other) = delete;
	TimeUI(TimeUI&& _Other) noexcept = delete;
	TimeUI& operator=(const TimeUI& _Other) = delete;
	TimeUI& operator=(TimeUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	std::vector<GameEngineRenderer*> Renderer;
	float GameTime_;

public :
	void SetGameTime(float _GameTime)
	{
		GameTime_ = _GameTime;
	}

	float GetGameTime()
	{
		return GameTime_;
	}
};

