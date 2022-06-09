#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class TextArea;
class CreateRoomBackGround;
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
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	TextArea* NickName_One_;
	TextArea* NickName_Two_;
	PlayerMode Mode_;

	GameEngineRenderer* LoginBackGroundRenderer_;

	GameEngineRenderer* Change1PRenderer_;
	GameEngineRenderer* Change2PRenderer_;
	GameEngineRenderer* LoginBtnRenderer_;
	GameEngineRenderer* ExitBtnRenderer_;

	GameEngineCollision* Change1PCollision_;
	GameEngineCollision* Change2PCollision_;
	GameEngineCollision* LoginBtnCollision_;
	GameEngineCollision* ExitBtnCollision_;

	CreateRoomBackGround* createRoomBackGround_;
};

