#pragma once
#include <GameEngine/GameEngineActor.h>

class TitleBackGround : public GameEngineActor
{
public:
	TitleBackGround();
	~TitleBackGround();


	TitleBackGround(const TitleBackGround& _Other) = delete;
	TitleBackGround(TitleBackGround&& _Other) noexcept = delete;
	TitleBackGround& operator=(const TitleBackGround& _Other) = delete;
	TitleBackGround& operator=(TitleBackGround&& _Other) noexcept = delete;
protected:
	void Start();
	void Render();
	void Update();
private:
	GameEngineRenderer* TitleBackGroundRender_;
};