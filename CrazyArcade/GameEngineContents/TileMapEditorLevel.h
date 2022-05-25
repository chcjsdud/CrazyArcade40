#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class TileMapEditor;
class TileMapEditorLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TileMapEditorLevel();
	~TileMapEditorLevel();

	// delete Function
	TileMapEditorLevel(const TileMapEditorLevel& _Other) = delete;
	TileMapEditorLevel(TileMapEditorLevel&& _Other) noexcept = delete;
	TileMapEditorLevel& operator=(const TileMapEditorLevel& _Other) = delete;
	TileMapEditorLevel& operator=(TileMapEditorLevel&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
private:
	void CheckStage();
};

