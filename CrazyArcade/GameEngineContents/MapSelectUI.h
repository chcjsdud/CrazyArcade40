#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class GameEngineCollision;
class MapSelectUI : public GameEngineActor
{
public:
	//construcuter destructer
	MapSelectUI();
	~MapSelectUI();

	//delete Function
	MapSelectUI(const MapSelectUI& _Other) = delete;
	MapSelectUI(MapSelectUI&& _Other) noexcept = delete;
	MapSelectUI& operator=(const MapSelectUI& _Other) = delete;
	MapSelectUI& operator=(MapSelectUI&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* MapUIBackGround_;
	GameEngineRenderer* MapSelectButton_;
	GameEngineCollision* MapButton_;
	void Start() override;
	void Update() override;
	void Render() override {};

	void  MapButtonClick();
};

