#include "Area.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>
#include "Monster.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineContents/MapGameObject.h>

Area::Area(GameEngineImage* _ColMapImage, float _StartX, float _StartY, float _EndX, float _EndY)
    : StartX_(_StartX)
    , StartY_(_StartY)
    , EndX_(_EndX)
    , EndY_(_EndY)
    , ColMapImage_(_ColMapImage)
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
    if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(float4(CenterX_, CenterY_)))
    {
        return true;
    }

    return false;
}

bool Area::HasBlock(float4 _Pos)
{
    return GetTile(_Pos) != nullptr;
}

bool Area::InCenter(float4 _Pos)
{
    if (CenterX_ - 1 < _Pos.x && _Pos.x < CenterX_ + 1 &&
        CenterY_ - 1 < _Pos.y && _Pos.y < CenterY_ + 1)
    {
        return true;
    }

    return false;
}

bool Area::HasWaveTile(float4 _Pos)
{
    BlockTile* Tile_ = GetTile(_Pos);

    return Tile_ != nullptr ?
        Tile_->BlockType_ == BlockType::WaveBlock :
        false;
}

BlockTile* Area::GetTile(float4 _Pos)
{
    if (MapTile_ == nullptr)
    {
        return nullptr;
    }

    TileIndex_ = MapTile_->GetTileIndex(_Pos);
    return MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
}
