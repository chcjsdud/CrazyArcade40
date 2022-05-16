#pragma once
#include <GameEngine/GameEngineLevel.h>
class PlayerTeamTest : public GameEngineLevel
{
public:
	PlayerTeamTest();
	~PlayerTeamTest();


	PlayerTeamTest(const PlayerTeamTest& _Other) = delete;
	PlayerTeamTest(PlayerTeamTest&& _Other) noexcept = delete;
	PlayerTeamTest& operator=(const PlayerTeamTest& _Other) = delete;
	PlayerTeamTest& operator=(PlayerTeamTest&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

};