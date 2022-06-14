#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineBackGroundRenderer_;
class Mypage : public GameEngineActor
{
public:
	//construcuter destructer
	Mypage();
	~Mypage();

	//delete Function
	Mypage(const Mypage& _Other) = delete;
	Mypage(Mypage&& _Other) noexcept = delete;
	Mypage& operator=(const Mypage& _Other) = delete;
	Mypage& operator=(Mypage&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;
	void Render() override;


	GameEngineRenderer* MypageRenderer_;

	GameEngineRenderer* BubbleSelectRenderer_1;
	GameEngineRenderer* BubbleSelectRenderer_2;
	GameEngineRenderer* BubbleSelectRenderer_3;
	GameEngineRenderer* BubbleSelectRenderer_4;
	GameEngineRenderer* BubbleSelectRenderer_5;
	GameEngineRenderer* BubbleSelectRenderer_6;
	GameEngineRenderer* BubbleSelectRenderer_7;
	GameEngineRenderer* BubbleSelectRenderer_8;


	GameEngineRenderer* BubbleRenderer_1;
	GameEngineRenderer* BubbleRenderer_2;
	GameEngineRenderer* BubbleRenderer_3;
	GameEngineRenderer* BubbleRenderer_4;
	GameEngineRenderer* BubbleRenderer_5;
	GameEngineRenderer* BubbleRenderer_6;
	GameEngineRenderer* BubbleRenderer_7;
	GameEngineRenderer* BubbleRenderer_8;

	GameEngineRenderer* BubbleCheckRenderer_1P;
	GameEngineRenderer* BubbleCheckRenderer_2P;

	GameEngineCollision* BubbleSelectCollision_1;
	GameEngineCollision* BubbleSelectCollision_2;
	GameEngineCollision* BubbleSelectCollision_3;
	GameEngineCollision* BubbleSelectCollision_4;
	GameEngineCollision* BubbleSelectCollision_5;
	GameEngineCollision* BubbleSelectCollision_6;
	GameEngineCollision* BubbleSelectCollision_7;
	GameEngineCollision* BubbleSelectCollision_8;


	GameEngineRenderer* BubbleNameRenderer_1;
	GameEngineRenderer* BubbleNameRenderer_2;
	GameEngineRenderer* BubbleNameRenderer_3;
	GameEngineRenderer* BubbleNameRenderer_4;
	GameEngineRenderer* BubbleNameRenderer_5;
	GameEngineRenderer* BubbleNameRenderer_6;
	GameEngineRenderer* BubbleNameRenderer_7;
	GameEngineRenderer* BubbleNameRenderer_8;


	GameEngineRenderer* MyPageCloseBtnRenderer_;
	GameEngineCollision* MyPageCloseBtnCollision_;


private:

public:

};

