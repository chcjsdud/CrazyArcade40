#include "Area.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>
#include "Monster.h"
#include "GameItemObject.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineContents/MapGameObject.h>

Area::Area(GameEngineImage* _ColMapImage, float _StartX, float _StartY, float _EndX, float _EndY)
    : StartX_(_StartX)
    , StartY_(_StartY)
    , EndX_(_EndX)
    , EndY_(_EndY)
    , ColMapImage_(_ColMapImage)
    , Monster_(nullptr)
    , MapTile_(nullptr)
    , BlockType_(nullptr)
{
    CenterX_ = StartX_ + (EndX_ - StartX_) * float(0.5);
    //CenterY_ = StartY_ + (EndY_ - StartY_) * 0.5;
    CenterY_ = EndY_ - 1;
}

Area::~Area()
{
}

bool Area::Contains(float4 _Pos)
{
    if (StartX_ < _Pos.x && _Pos.x < EndX_ &&
        StartY_ < _Pos.y && _Pos.y < EndY_)
    {
        return true;
    }

    return false;
}

bool Area::HasWall()
{
    if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(float4(CenterX_, CenterY_)) ||
        RGB(16, 184, 152) == ColMapImage_->GetImagePixel(float4(CenterX_, CenterY_)))
    {
        return true;
    }

    return false;
}

bool Area::BossHasWall()
{
    if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(float4(CenterX_, CenterY_)))
    {
        return true;
    }

    return false;
}

bool Area::HasBlock()
{
    return GetTile(float4(CenterX_, CenterY_)) != nullptr;
}

int Area::ChooseWaterAttackAni()
{
    BlockTile* Tile_ = GetTile(float4(CenterX_, CenterY_));
    TileIndex Pos_ = MapTile_->GetTileIndex(float4(CenterX_, CenterY_));
    ItemBlockTile* ItemTile_ = MapTile_->GetTile<ItemBlockTile>(Pos_.X, Pos_.Y);

    if (Tile_ != nullptr)
    {
        if(Tile_->BlockType_ == BlockType::BubbleBlock|| Tile_->BlockType_ == BlockType::WaveBlock)
        {
            return 2;
        }
        if (Tile_->BlockType_ == BlockType::FixBlock || Tile_->BlockType_ == BlockType::PullBlock)
        {
            return 0; // 1번 애니메이션
        }
        else
        {
            return 1; // 0번 애니메이션
        }
    }
    else
    {
        return 1;
    }
}

bool Area::InCenter(float4 _Pos)
{
    if (CenterX_ - 5 < _Pos.x && _Pos.x < CenterX_ + 5 &&
        CenterY_ - 5 < _Pos.y && _Pos.y < CenterY_ + 5)
    {
        return true;
    }

    return false;
}

bool Area::GhostCanMoveTile()
{
    BlockTile* Tile_ = GetTile(float4(CenterX_, CenterY_));

    return Tile_ != nullptr ?
        Tile_->BlockType_ != BlockType::WallBlock :
        false;
}

bool Area::HasWaveTile()
{
    BlockTile* Tile_ = GetTile(float4(CenterX_, CenterY_));

    return Tile_ != nullptr ?
        Tile_->BlockType_ == BlockType::WaveBlock :
        false;
}

bool Area::HasBubble()
{
    BlockTile* Tile_ = GetTile(float4(CenterX_, CenterY_));

    return Tile_ != nullptr ?
        Tile_->BlockType_ == BlockType::BoomBlock :
        false;
}

BlockTile* Area::GetTile(float4 _Pos)
{
    if (MapTile_ == nullptr)
    {
        return nullptr;
    }

    TileIndex_ = MapTile_->GetTileIndex(_Pos - float4(20.0f, 40.0f));
    if (TileIndex_.Y >= 13 || TileIndex_.X >= 15)
    {
        return nullptr;
    }
    return MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
}
