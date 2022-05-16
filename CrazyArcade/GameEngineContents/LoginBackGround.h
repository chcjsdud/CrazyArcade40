#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineBackGroundRenderer_;
class LoginBackGround : public GameEngineActor
{
public:
	//construcuter destructer
	LoginBackGround();
	~LoginBackGround();

	//delete Function
	LoginBackGround(const LoginBackGround& _Other) = delete;
	LoginBackGround(LoginBackGround&& _Other) noexcept = delete;
	LoginBackGround& operator=(const LoginBackGround& _Other) = delete;
	LoginBackGround& operator=(LoginBackGround&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;

	GameEngineRenderer* LoginBackGroundRenderer_;

};

