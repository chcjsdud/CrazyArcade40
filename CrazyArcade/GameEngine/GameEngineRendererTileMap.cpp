#include "GameEngineRendererTileMap.h"
//20,40
float4 GameEngineRendererTileMap::GetWorldPostion(int _X, int _Y)
{
	float4 ReturnPos = TileSize_;

	ReturnPos.x *= _X;
	ReturnPos.y *= _Y;

	//크레이지 아케이드 버전 맵 위치로 수정
	ReturnPos.x += 20;
	ReturnPos.y += 40;

	ReturnPos += TileSizeHalf_;

	return ReturnPos;
}

TileIndex GameEngineRendererTileMap::GetTileIndex(const float4& _Pos)
{
	return { static_cast<int>(_Pos.x / TileSize_.x), static_cast<int>(_Pos.y / TileSize_.y)};
}

void GameEngineRendererTileMap::DeleteTile(int _X, int _Y)
{

	if (nullptr != Tiles_[_Y][_X])
	{
		Tiles_[_Y][_X]->Renderer->Death();
		delete Tiles_[_Y][_X];
		Tiles_[_Y][_X] = nullptr;
	}

}