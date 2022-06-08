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


// �÷��̾ ���ִ� ��ġ�� Ÿ���� � Ÿ���� ������ �˷��ִ� �Լ� return ���� Max�̸� - �ƹ��͵� ���� Ÿ���Դϴ�.
void GameItemObject::CreateItem(float4 _Pos, ItemType _Type)
{

	
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	ItemBlockTile* Tiles_ = MapTile_->CreateTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
	Tiles_->Renderer = CreateRenderer();
	Tiles_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y }); // ������ y�� 90�̾���Ѵ�.
	Tiles_->BlockType_ = BlockType::ItemBlock;
	Tiles_->Renderer->CreateAnimation("Fluid.bmp", "Animation", 0, 5, 0.2f, true);
	Tiles_->Renderer->ChangeAnimation("Animation");
	Tiles_->Renderer->SetOrder(static_cast<int>(ORDER::PLAYER));
	
}

// �÷��̾ ���ִ� ��ġ�� Ÿ���� BlockType�� �����ۺ���̶�� , �������� �������������� üũ�ϴ� �Լ��Դϴ�. ��ġ�־��ָ� ������Ÿ���� ���ϵ˴ϴ�. 
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

void GameItemObject::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	LevelRegist("GameItem");
}