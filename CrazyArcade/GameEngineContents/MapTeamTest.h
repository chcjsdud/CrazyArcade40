#pragma once
#include <GameEngine/GameEngineLevel.h>
class MapTeamTest : public GameEngineLevel
{
public:
	MapTeamTest();
	~MapTeamTest();


	MapTeamTest(const MapTeamTest& _Other) = delete;
	MapTeamTest(MapTeamTest&& _Other) noexcept = delete;
	MapTeamTest& operator=(const MapTeamTest& _Other) = delete;
	MapTeamTest& operator=(MapTeamTest&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};