#pragma once
class PlayerTeamTest
{
public:
	PlayerTeamTest();
	~PlayerTeamTest();


	PlayerTeamTest(const PlayerTeamTest& _Other) = delete;
	PlayerTeamTest(PlayerTeamTest&& _Other) noexcept = delete;
	PlayerTeamTest& operator=(const PlayerTeamTest& _Other) = delete;
	PlayerTeamTest& operator=(PlayerTeamTest&& _Other) noexcept = delete;
protected:

private:

};