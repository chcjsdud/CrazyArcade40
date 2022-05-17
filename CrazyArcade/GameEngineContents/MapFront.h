#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class MapFront : public GameEngineActor
{
public:
	MapFront();
	~MapFront();


	MapFront(const MapFront& _Other) = delete;
	MapFront(MapFront&& _Other) noexcept = delete;
	MapFront& operator=(const MapFront& _Other) = delete;
	MapFront& operator=(MapFront&& _Other) noexcept = delete;
protected:

private:
	void Start();
	void Render();
	void Update();
	GameEngineRenderer* MapFrontRender_;
public:
	GameEngineRenderer* GetRenderer()
	{
		return	MapFrontRender_;
	}
};