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
	//if (ItemType::Max == CheckItem(_Pos))
	//{
	//	return;
	//};
	
	if (ItemType::Fluid == _Type)
	{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	ItemBlockTile* Tiles_ = MapTile_->CreateTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Tiles_->Renderer = CreateRenderer();
	Tiles_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y }); // 아이템 y는 90이어야한다.
	Tiles_->BlockType_ = BlockType::ItemBlock;
	Tiles_->Renderer->CreateAnimation("Fluid.bmp", "Animation", 0, 5, 0.2f, true);
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