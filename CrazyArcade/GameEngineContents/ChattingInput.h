#pragma once
#include <GameEngine/GameEngineActor.h>

#define MAX_INPUTCOUNT 20

class GameEngineRenderer;
class ChattingInput : public GameEngineActor
{
private:
	static bool caretshow_;

public:
	static void SetCurCaretState(bool _Flag);

private:
	bool ChattingInputOK_;
	std::string InputText_;
	int curcaretpos_;
	int prevcaretpos_;

private:
	GameEngineRenderer* chattingInputBoxSpriteRender_;

	GameEngineCollision* chattingInputBoxCollision_;

public:
	//construcuter destructer
	ChattingInput();
	~ChattingInput();

	//delete Function
	ChattingInput(const ChattingInput& _Other) = delete;
	ChattingInput(ChattingInput&& _Other) noexcept;
	ChattingInput& operator=(const ChattingInput& _Other) = delete;
	ChattingInput& operator=(ChattingInput&& _Other) noexcept = delete;

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

public:
	void AddText(const std::string& _Text);
};

