#pragma once
#include "Monster.h"

class GameEngineRenderer;
class Monster1 : public Monster
{
public:
	Monster1();
	~Monster1();

	Monster1(const Monster1& _Other) = delete;
	Monster1(Monster1&& _Other) noexcept = delete;
	Monster1& operator=(const Monster1& _Other) = delete;
	Monster1& operator=(Monster1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Render() override;
	void Update() override;
	void Die() override;
private:

	float SpeechTime_;
	bool DieSoundPlay_;
	void Speech();
};
