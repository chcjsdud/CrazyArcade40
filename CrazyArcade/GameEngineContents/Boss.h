#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineRenderer;
class Boss : public Monster
{
public:
	Boss();
	~Boss();

	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;

protected:
	void Start();
	void Render();
	void Update();
	void UpdateMove() override;
};