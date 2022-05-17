#include"MapBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

MapBackGround::MapBackGround()
	:MapBackGroundRender_(nullptr)
	, MapTileMap_(nullptr)
{

}
MapBackGround::~MapBackGround()
{

}
void MapBackGround::Start()
{
	SetPosition({ 0,0 });
	MapBackGroundRender_ = CreateRenderer();
}
void MapBackGround::Render()
{

}
void MapBackGround::Update()
{

}