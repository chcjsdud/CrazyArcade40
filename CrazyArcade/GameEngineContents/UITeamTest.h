#pragma once
#include <GameEngine/GameEngineLevel.h>
class UITeamTest : public GameEngineLevel
{
public:
	UITeamTest();
	~UITeamTest();


	UITeamTest(const UITeamTest& _Other) = delete;
	UITeamTest(UITeamTest&& _Other) noexcept = delete;
	UITeamTest& operator=(const UITeamTest& _Other) = delete;
	UITeamTest& operator=(UITeamTest&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

};