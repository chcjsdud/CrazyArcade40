#pragma once
#include <GameEngine/GameEngineActor.h>

class LoginButton  : public GameEngineActor
{
public:
	//construcuter destructer
	LoginButton();
	~LoginButton();

	//delete Function
	LoginButton(const LoginButton& _Other) = delete;
	LoginButton(LoginButton&& _Other) noexcept = delete;
	LoginButton& operator=(const LoginButton& _Other) = delete;
	LoginButton& operator=(LoginButton&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PreLevel) override;
};

