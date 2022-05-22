#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineContents/Player.h>

class GameEngineImage;
class Area
{
    friend GameEngineLevel;
public:
    Area(GameEngineImage* _ColMapImage, float _StartX, float _StartY, float _EndX, float _EndY);
    ~Area();

    //Area(const Area& _Other) = delete;
    //Area(Area&& _Other) noexcept = delete;
   // Area& operator=(const Area& _Other) = delete;
    //Area& operator=(Area&& _Other) noexcept = delete;
private:
    float StartX_;
    float StartY_;
    float EndX_;
    float EndY_;
    float CenterX_;
    float CenterY_;
    GameEngineImage* ColMapImage_;

public:
    float4 GetCenter() { return float4(CenterX_, CenterY_); }

    // 해당위치가 Area 안에 있는지
    bool Contains(float4 _Pos);

    // ColMap이 검은색
    bool HasWall();


    bool InCenter(float4 _Pos);

};
