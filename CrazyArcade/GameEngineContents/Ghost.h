#pragma once
#include "Monster.h"

class Ghost : public Monster
{
public:
	Ghost();
	~Ghost();

	Ghost(const Ghost& _Other) = delete;
	Ghost(Ghost&& _Other) noexcept = delete;
	Ghost& operator=(const Ghost& _Other) = delete;
	Ghost& operator=(Ghost&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Render() override;
	void Update() override;
	void UpdateDirection() override;
	void UpdateMove() override;
	void Die() override;

private:
	void UpdateAttack();

private:
	float AttTime_;

};
