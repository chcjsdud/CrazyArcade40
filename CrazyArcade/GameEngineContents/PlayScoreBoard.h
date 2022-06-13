#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineBackGroundRenderer_;
class PlayScoreBoard : public GameEngineActor
{
public:
	//construcuter destructer
	PlayScoreBoard();
	~PlayScoreBoard();

	//delete Function
	PlayScoreBoard(const PlayScoreBoard& _Other) = delete;
	PlayScoreBoard(PlayScoreBoard&& _Other) noexcept = delete;
	PlayScoreBoard& operator=(const PlayScoreBoard& _Other) = delete;
	PlayScoreBoard& operator=(PlayScoreBoard&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;
	void Render() override;

	GameEngineRenderer* PlayScoreBoardRenderer_;
	GameEngineRenderer* PlayScoreTableRenderer_;
	GameEngineRenderer* WinLoseRenderer_1P;
	GameEngineRenderer* WinLoseRenderer_2P;
	GameEngineRenderer* NumRenderer_1P;
	GameEngineRenderer* NumRenderer_2P;


	GameEngineRenderer* Rank_1P;
	GameEngineRenderer* Rank_2P;

	GameResult Whowin_ = GameResult::Max;
public:
	void SetWhowin(GameResult _Whowin)
	{
		Whowin_ = _Whowin;
	}
};

