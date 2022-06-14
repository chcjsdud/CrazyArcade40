#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineBackGroundRenderer_;
class Mypage;
class MyPageButton : public GameEngineActor
{
public:
	//construcuter destructer
	MyPageButton();
	~MyPageButton();

	//delete Function
	MyPageButton(const MyPageButton& _Other) = delete;
	MyPageButton(MyPageButton&& _Other) noexcept = delete;
	MyPageButton& operator=(const MyPageButton& _Other) = delete;
	MyPageButton& operator=(MyPageButton&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;

	GameEngineRenderer* MyPageBtnRenderer_;
	GameEngineCollision* MyPageBtnCollision_;

private:
	Mypage* mypage;

public:
};

