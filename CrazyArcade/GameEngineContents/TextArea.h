#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineCollision;
class TextArea : public GameEngineActor
{
private:
	static bool caretshow_;

public:
	static void SetCurCaretState(bool _Flag);
	void TextAreaInit(const float4& _Value, int _Len);
private:
	bool TextInputOK_;
	std::string InputText_;
	int MaxLen_;
	int curcaretpos_;
	int prevcaretpos_;

private:
	GameEngineCollision* TextAreaCollision_;

public:
	//construcuter destructer
	TextArea();
	~TextArea();

	//delete Function
	TextArea(const TextArea& _Other) = delete;
	TextArea(TextArea&& _Other) noexcept = delete;
	TextArea& operator=(const TextArea& _Other) = delete;
	TextArea& operator=(TextArea&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;


	std::string GetText()
	{
		return InputText_;
	}
public:
	void AddText(const std::string& _Text);
};

