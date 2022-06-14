#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

class GameEngineBackGroundRenderer_;
class StartMonsterModeUI : public GameEngineActor
{
public:
	//construcuter destructer
	StartMonsterModeUI();
	~StartMonsterModeUI();

	//delete Function
	StartMonsterModeUI(const StartMonsterModeUI& _Other) = delete;
	StartMonsterModeUI(StartMonsterModeUI&& _Other) noexcept = delete;
	StartMonsterModeUI& operator=(const StartMonsterModeUI& _Other) = delete;
	StartMonsterModeUI& operator=(StartMonsterModeUI&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	GameEngineRenderer* StartMonsterModeRenderer_;
private:
	float StartTime_ =0.0f;
};

