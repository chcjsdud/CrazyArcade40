#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineContents/ContentsEnum.h>

class GameEngineBackGroundRenderer_;
class PlayerFaceIconUI : public GameEngineActor
{
public:
	//construcuter destructer
	PlayerFaceIconUI();
	~PlayerFaceIconUI();

	//delete Function
	PlayerFaceIconUI(const PlayerFaceIconUI& _Other) = delete;
	PlayerFaceIconUI(PlayerFaceIconUI&& _Other) noexcept = delete;
	PlayerFaceIconUI& operator=(const PlayerFaceIconUI& _Other) = delete;
	PlayerFaceIconUI& operator=(PlayerFaceIconUI&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	GameEngineRenderer* PlayerFaceIconUIRenderer_1P;
	GameEngineRenderer* PlayerFaceIconUIRenderer_2P;

	float BlinkTime_1P;
	float CryTime_1P;
	bool Islive_1P;

	float BlinkTime_2P;
	float CryTime_2P;
	bool Islive_2P;

	bool onetime;

	Character CharacterType_1P;
	Character CharacterType_2P;

};

