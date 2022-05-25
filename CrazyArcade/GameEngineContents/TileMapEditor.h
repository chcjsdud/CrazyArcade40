#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRendererTileMap.h>
// Ό³Έν :
class GameEngineRenderer;
class GameEngineCollision;
class MapGameObject;
class TileMapEditor : public GameEngineActor
{
public:
	static TileMapEditor* MapEditorSet;
	// constrcuter destructer
	TileMapEditor();
	~TileMapEditor();

	// delete Function
	TileMapEditor(const TileMapEditor& _Other) = delete;
	TileMapEditor(TileMapEditor&& _Other) noexcept = delete;
	TileMapEditor& operator=(const TileMapEditor& _Other) = delete;
	TileMapEditor& operator=(TileMapEditor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

public:
	inline GameEngineRenderer* GetRenderer()
	{
		return MapBack;
	}

	inline void SetCurPos(float4 _Pos)
	{
		MousePos = _Pos - float4{20.0f, 40.0f};
	}
	GameEngineRendererTileMap EditorTileMap_;

private:
	std::string LevelNameReturnToString();
	std::string TileNameReturnToString();
	MapGameObject* BlockSet;
	GameEngineRenderer* MapBack;
	float4 MousePos;
	std::string RenderName_;
	std::string LevelName_;
	GameEngineRenderer* MoveBox1;
	GameEngineRenderer* MoveBox2;
	GameEngineRenderer* MoveBox3;
	GameEngineRenderer* Block1;
	GameEngineRenderer* Block2;
	GameEngineRenderer* Bush1;
	GameEngineRenderer* Bush2;
	GameEngineRenderer* Stone;
	GameEngineRenderer* Stone2;

	GameEngineCollision* MoveBox1Col;
	GameEngineCollision* MoveBox2Col;
	GameEngineCollision* MoveBox3Col;
	GameEngineCollision* Block1Col;
	GameEngineCollision* Block2Col;
	GameEngineCollision* Bush1Col;
	GameEngineCollision* Bush2Col;
	GameEngineCollision* StoneCol;
	GameEngineCollision* Stone2Col;
};

