#pragma once
#include "Player.h"

class Player_2P : public Player
{
public:
	// constrcuter destructer
	Player_2P();
	~Player_2P();

	// delete Function
	Player_2P(const Player_2P& _Other) = delete;
	Player_2P(Player_2P&& _Other) noexcept = delete;
	Player_2P& operator=(const Player_2P& _Other) = delete;
	Player_2P& operator=(Player_2P&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

protected:
	//bool IsMoveKey() override;

private:

};
