#pragma once
#include <GameEngine/GameEngineLevel.h>


class MapBackGround;
class Player;
class CampLevel : public GameEngineLevel
{
private:
	MapBackGround* MapBackGround_;
	MapBackGround* MapFrontBackGround_;

public:
	CampLevel();
	~CampLevel();


	CampLevel(const CampLevel& _Other) = delete;
	CampLevel(CampLevel&& _Other) noexcept = delete;
	CampLevel& operator=(const CampLevel& _Other) = delete;
	CampLevel& operator=(CampLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


};
