#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>



class MapGameObject;
class MapBackGround;
class MapFront;
class Area;
class Player;
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
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
private:
	MapBackGround* MapBackGround_;
	MapFront* MapFrontBackGround_;
	MapGameObject* bubble_;

	//GameEngineImage* MapColMap_;
	GameEngineRenderer* MapColRenderer_;
	std::vector<Area> Areas_;
	GameEngineImage* ColMapImage_;


	Player* Player1_;
	Player* Player2_;
};