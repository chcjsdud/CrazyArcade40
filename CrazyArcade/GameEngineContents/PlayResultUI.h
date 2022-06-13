#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include "ContentsEnum.h"

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
	GameResult GameResult_ = GameResult::Max;
	GameResult WhoWin_ = GameResult::Max;
	float FallHeight = 0.0f;
	float FallWidth = 0.0f;

	bool onetime = false;
	bool setting = false;
	std::string ChangeLevelName_;
public:
	void SetGameResult(GameResult _GameResult)
	{
		GameResult_ = _GameResult;
	}

	void SetWhowin(GameResult _WhoWin)
	{
		WhoWin_ = _WhoWin;
	}
	
	void SetChangeLevel(std::string _ChangeLevelName) {
		ChangeLevelName_ = _ChangeLevelName;
	}
};

