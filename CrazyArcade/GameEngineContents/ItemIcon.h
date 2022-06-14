#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class ItemIcon : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemIcon();
	~ItemIcon();

	// delete Function
	ItemIcon(const ItemIcon& _Other) = delete;
	ItemIcon(ItemIcon&& _Other) noexcept = delete;
	ItemIcon& operator=(const ItemIcon& _Other) = delete;
	ItemIcon& operator=(ItemIcon&& _Other) noexcept = delete;

protected:

private:
	void Start();
	void Update();
	void LevelChangeStart(GameEngineLevel* _PrevLevel);

	void ChangeImage();

	GameEngineRenderer* ItemIconBox_;
	GameEngineRenderer* ItemIcon_1P_;
	GameEngineRenderer* ItemIcon_2P_;

};

