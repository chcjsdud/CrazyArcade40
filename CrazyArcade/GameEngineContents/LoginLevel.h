#pragma once
#include <GameEngine/GameEngineLevel.h>

class LoginLevel : public GameEngineLevel
{
public:
	//construcuter destructer
	LoginLevel();
	~LoginLevel();

	//delete Function
	LoginLevel(const LoginLevel& _Other) = delete;
	LoginLevel(LoginLevel&& _Other) noexcept = delete;
	LoginLevel& operator=(const LoginLevel& _Other) = delete;
	LoginLevel& operator=(LoginLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

