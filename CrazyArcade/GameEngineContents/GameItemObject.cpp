#include"GameItemObject.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

GameItemObject::GameItemObject()
	:	MapTile_(nullptr)
{

}
GameItemObject::~GameItemObject()
{

}
void GameItemObject::Start()
{

}
void GameItemObject::Update()
{

}

// �÷��̾ ���ִ� ��ġ�� Ÿ���� � Ÿ���� ������ �˷��ִ� �Լ� return ���� Max�̸� - �ƹ��͵� ���� Ÿ���Դϴ�.
void GameItemObject::CreateItem(float4 _Pos, ItemType _Type)
{
	//if (ItemType::Max == CheckItem(_Pos))
	//{
	//	return;
	//};

	// ���� �������� ������ ������
	if (_Type == (ItemType::Fluid))
	{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	ItemBlockTile* Tiles_ = MapTile_->CreateTile<ItemBlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Tiles_->Renderer = CreateRenderer();
	Tiles_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y }); // ������ y�� 90�̾���Ѵ�.

	Tiles_->Renderer->CreateAnimation("Fluid.bmp", "Animation", 0, 5, 0.2f, true);
	Tiles_->Renderer->ChangeAnimation("Animation");
	}
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