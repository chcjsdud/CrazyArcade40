#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class GameEngineCollision;
class RoomCharaterSelectUI : public GameEngineActor
{
public:
	//construcuter destructer
	RoomCharaterSelectUI();
	~RoomCharaterSelectUI();

	//delete Function
	RoomCharaterSelectUI(const RoomCharaterSelectUI& _Other) = delete;
	RoomCharaterSelectUI(RoomCharaterSelectUI&& _Other) noexcept = delete;
	RoomCharaterSelectUI& operator=(const RoomCharaterSelectUI& _Other) = delete;
	RoomCharaterSelectUI& operator=(RoomCharaterSelectUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	int ChoiceCharacter1P;
	int ChoiceCharacter2P;

	GameEngineRenderer* Choice2PRenderer;
	GameEngineRenderer* RoomCharacterRenderer;
	GameEngineRenderer* StatusRenderer;
	GameEngineRenderer* BannerRenderer;
	GameEngineRenderer* RandomRenderer;
	GameEngineCollision* RandomCollision;
	GameEngineRenderer* BazziRenderer;
	GameEngineCollision* BazziCollision;
	GameEngineRenderer* DaoRenderer;
	GameEngineCollision* DaoCollision;
	GameEngineRenderer* MaridRenderer;
	GameEngineCollision* MaridCollision;


	void RendererMouseCheck();
	void ChoiceCharacter();
	void ChoiceCheck();
	void PivotReset();
	void StatusUISet(); // �������ͽ� �̹����� �ٲ��ִ� �Լ�
	void BannerSet(); // ��� �̹����� �ٲ��ִ� �Լ�
};

