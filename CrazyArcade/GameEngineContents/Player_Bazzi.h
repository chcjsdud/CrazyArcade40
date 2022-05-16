#pragma once
#include "Player.h"

class Player_Bazzi : public Player
{
public:
	// constrcuter destructer
	Player_Bazzi();
	~Player_Bazzi();

	// delete Function
	Player_Bazzi(const Player_Bazzi& _Other) = delete;
	Player_Bazzi(Player_Bazzi&& _Other) noexcept = delete;
	Player_Bazzi& operator=(const Player_Bazzi& _Other) = delete;
	Player_Bazzi& operator=(Player_Bazzi&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void Render() override;

private:

};
