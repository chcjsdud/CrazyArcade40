#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineContents/Player.h>
class Area
{
public:
    Area();
    ~Area();

    //Area(const Area& _Other) = delete;
    //Area(Area&& _Other) noexcept = delete;
   // Area& operator=(const Area& _Other) = delete;
    //Area& operator=(Area&& _Other) noexcept = delete;
public:
    float StartX_;
    float StartY_;
    float EndX_;
    float EndY_;

public:
    bool Contains(Player* _Player)
    {
        if (nullptr == _Player)
        {
            return false;
        }

        float4 _PlayerPos = _Player->GetPosition();
        if (StartX_ < _PlayerPos.x && _PlayerPos.x < EndX_ &&
            StartY_ < _PlayerPos.y && _PlayerPos.y < EndY_)
        {
            return true;
        }

        return false;
    }

    bool Contains(float4 _Pos)
    {
        if (StartX_ < _Pos.x && _Pos.x < EndX_ &&
            StartY_ < _Pos.y && _Pos.y < EndY_)
        {
            return true;
        }

        return false;
    }

};
