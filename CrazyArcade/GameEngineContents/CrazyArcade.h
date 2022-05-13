#pragma once
#include <GameEngine/GameEngine.h>

class CrazyArcade : public GameEngine
{
public:
	CrazyArcade();
	~CrazyArcade();

	CrazyArcade(const CrazyArcade& _Other) = delete;
	CrazyArcade(CrazyArcade&& _Other) noexcept = delete;
	CrazyArcade& operator=(const CrazyArcade& _Other) = delete;
	CrazyArcade& operator=(CrazyArcade&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

protected:

private:

};

