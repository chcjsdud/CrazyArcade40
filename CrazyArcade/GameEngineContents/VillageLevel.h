#pragma once
#include <GameEngine/GameEngineLevel.h>

class VillageLevel : public GameEngineLevel
{
public:
	VillageLevel();
	~VillageLevel();


	VillageLevel(const VillageLevel& _Other) = delete;
	VillageLevel(VillageLevel&& _Other) noexcept = delete;
	VillageLevel& operator=(const VillageLevel& _Other) = delete;
	VillageLevel& operator=(VillageLevel&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:

};