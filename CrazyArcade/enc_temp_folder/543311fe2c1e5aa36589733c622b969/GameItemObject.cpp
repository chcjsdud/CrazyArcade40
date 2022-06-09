#include"GameItemObject.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

GameItemObject* GameItemObject::GameItemObject_ = nullptr;

GameItemObject::GameItemObject()
	:	MapTile_(nullptr)

{

}
GameItemObject::~GameItemObject()
{

}
void GameItemObject::Start()
{
	GameItemObject_ = this;
}
void GameItemObject::Update()
{

}


// 플레이어가 서있는 위치의 타일이 어떤 타입의 블럭인지 알려주는 함수 return 값이 Max이면 - 아무것도 없는 타일입니다.
void GameItemObject::CreateItem(float4 _Pos, ItemType _Type)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	ItemBlockTile* Tiles_ = MapTile_->CreateTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
	Tiles_->Renderer = CreateRenderer();
	Tiles_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y }); // 아이템 y는 90이어야한다.
	Tiles_->BlockType_ = BlockType::ItemBlock;
	Tiles_->Renderer->SetOrder(static_cast<int>(ORDER::PLAYER));
	if (_Type == ItemType::Roller)
	{
		Tiles_->Renderer->CreateAnimation("Roller.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
	else if(_Type == ItemType::Bubble)
	{
		Tiles_->Renderer->CreateAnimation("Bubble.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
	else if (_Type == ItemType::Fluid)
	{
		Tiles_->Renderer->CreateAnimation("Fluid.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
	else if (_Type == ItemType::UltraBubble)
	{
		Tiles_->Renderer->CreateAnimation("UltraBubble.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
	else if (_Type == ItemType::RedDevil)
	{
		Tiles_->Renderer->CreateAnimation("RedDevil.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
	else if (_Type == ItemType::Devil)
	{
		Tiles_->Renderer->CreateAnimation("Devil.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
	else if (_Type == ItemType::Shoes)
	{
		Tiles_->Renderer->CreateAnimation("Shoes.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
	else if (_Type == ItemType::Niddle)
	{
		Tiles_->Renderer->CreateAnimation("Niddle.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
	else if (_Type == ItemType::Shield)
	{
		Tiles_->Renderer->CreateAnimation("Shield.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}

	else if (_Type == ItemType::SuperJump)
	{
		Tiles_->Renderer->CreateAnimation("SuperJump.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
		else if (_Type == ItemType::Turtle)
	{
		Tiles_->Renderer->CreateAnimation("Turtle.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
		else if (_Type == ItemType::SpaceShip)
	{
		Tiles_->Renderer->CreateAnimation("SpaceShip.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
		else if (_Type == ItemType::Owl)
	{
		Tiles_->Renderer->CreateAnimation("Owl.bmp", "Animation", 0, 5, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
		else if (_Type == ItemType::Bubble_Dark)
	{
		Tiles_->Renderer->CreateAnimation("Bubble_Dark.bmp", "Animation", 0, 3, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
		else if (_Type == ItemType::Bubble_Boss)
	{
		Tiles_->Renderer->CreateAnimation("Bubble_Boss.bmp", "Animation", 0, 3, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
		else if (_Type == ItemType::Bubble_Default)
	{
		Tiles_->Renderer->CreateAnimation("Bubble_Default.bmp", "Animation", 0, 3, 0.2f, true);
		Tiles_->Renderer->ChangeAnimation("Animation");
	}
}

// 플레이어가 서있는 위치의 타일의 BlockType이 아이템블록이라면 , 아이템이 무슨아이템인지 체크하는 함수입니당. 위치넣어주면 아이템타입이 리턴됩니당. 
ItemType GameItemObject::CheckItem(float4 _Pos)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	ItemBlockTile* Tiles_ = MapTile_->GetTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y);
	if (Tiles_ == nullptr)
	{
		return ItemType::Max;
	}
	else
	{
		return Tiles_->ItemType_;
	}
}
