#pragma once
#include "Monster.h"


class GameEngineRenderer;
class Monster2 : public Monster
{
public:
	Monster2();
	~Monster2();

	Monster2(const Monster2& _Other) = delete;
	Monster2(Monster2&& _Other) noexcept = delete;
	Monster2& operator=(const Monster2& _Other) = delete;
	Monster2& operator=(Monster2&& _Other) noexcept = delete;

protected:
	void Start();
	void Render();
	void Update();
	void TakeDamage() override;
	void UpdateDirection() override;

private:
	GameEngineRenderer* MiniRenderer_;
};
