#include"MapFront.h"

MapFront::MapFront()
	:MapFrontRender_(nullptr)
{

}
MapFront::~MapFront()
{

}
void MapFront::Start()
{
	SetPosition({ 0,0 });
	MapFrontRender_ = CreateRenderer();
}
void MapFront::Render()
{

}
void MapFront::Update()
{

}