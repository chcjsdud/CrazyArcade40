#pragma once
#include "Player.h"

class Player_1P : public Player
{
public:
	// constrcuter destructer
	Player_1P();
	~Player_1P();

	// delete Function
	Player_1P(const Player_1P& _Other) = delete;
	Player_1P(Player_1P&& _Other) noexcept = delete;
	Player_1P& operator=(const Player_1P& _Other) = delete;
	Player_1P& operator=(Player_1P&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

protected:
	bool IsMoveKey() override;

private:

};
