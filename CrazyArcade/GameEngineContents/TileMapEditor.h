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
	std::string NextLevelName_;
private:
	void LevelBlockUpdate();
	void TileAllOff();

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
	GameEngineRenderer* Block3;
	GameEngineRenderer* Block4;
	GameEngineRenderer* Block5;
	GameEngineRenderer* Block6;
	GameEngineRenderer* Block7;
	GameEngineRenderer* Block8;
	GameEngineRenderer* Bush1;
	GameEngineRenderer* Bush2;
	GameEngineRenderer* Stone1;
	GameEngineRenderer* Stone2;

	GameEngineCollision* MoveBox1Col;
	GameEngineCollision* MoveBox2Col;
	GameEngineCollision* MoveBox3Col;
	GameEngineCollision* Block1Col;
	GameEngineCollision* Block2Col;
	GameEngineCollision* Block3Col;
	GameEngineCollision* Block4Col;
	GameEngineCollision* Block5Col;
	GameEngineCollision* Block6Col;
	GameEngineCollision* Block7Col;
	GameEngineCollision* Block8Col;
	GameEngineCollision* Bush1Col;
	GameEngineCollision* Bush2Col;
	GameEngineCollision* Stone1Col;
	GameEngineCollision* Stone2Col;
};

