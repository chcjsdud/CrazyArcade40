#pragma once
#include <GameEngine/GameEngineLevel.h>
class CemeteryLevel : public GameEngineLevel
{
public:
	CemeteryLevel();
	~CemeteryLevel();


	CemeteryLevel(const CemeteryLevel& _Other) = delete;
	CemeteryLevel(CemeteryLevel&& _Other) noexcept = delete;
	CemeteryLevel& operator=(const CemeteryLevel& _Other) = delete;
	CemeteryLevel& operator=(CemeteryLevel&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;
private:

};