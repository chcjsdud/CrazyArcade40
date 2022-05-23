#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class GameEngineCollision;
class MapChoiceUI : public GameEngineActor
{
public:
	//construcuter destructer
	MapChoiceUI();
	~MapChoiceUI();

	//delete Function
	MapChoiceUI(const MapChoiceUI& _Other) = delete;
	MapChoiceUI(MapChoiceUI&& _Other) noexcept = delete;
	MapChoiceUI& operator=(const MapChoiceUI& _Other) = delete;
	MapChoiceUI& operator=(MapChoiceUI&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* MapUIBackGround_;
	GameEngineRenderer* MapChoiceButton_;
	GameEngineCollision* MapButton_;
	void Start() override;
	void Update() override;
	void Render() override {};

	void  MapButtonClick();
};

