#include"MapBackGround.h"

MapBackGround::MapBackGround()
	:MapBackGroundRender_(nullptr)
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