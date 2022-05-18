#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>

class MapBackGround;
class MapFront;
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
private:
	MapBackGround* MapBackGround_;
	MapFront* MapFrontBackGround_;

	//GameEngineImage* MapColMap_;
	GameEngineRenderer* MapColRenderer_;

};