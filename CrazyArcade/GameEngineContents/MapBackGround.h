#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>

class GameEngineRenderer;
class MapBackGround : public GameEngineActor
{
public:
	MapBackGround();
	~MapBackGround();


	MapBackGround(const MapBackGround& _Other) = delete;
	MapBackGround(MapBackGround&& _Other) noexcept = delete;
	MapBackGround& operator=(const MapBackGround& _Other) = delete;
	MapBackGround& operator=(MapBackGround&& _Other) noexcept = delete;
protected:

private:
	void Start();
	void Render();
	void Update();
	GameEngineRenderer* MapBackGroundRender_;
public:

	GameEngineRendererTileMap MapTileMap_;

	GameEngineRenderer* GetRenderer()
	{
		return	MapBackGroundRender_;
	}
};