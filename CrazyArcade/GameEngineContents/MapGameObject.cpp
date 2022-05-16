#include"MapGameObject.h"
#include <GameEngine/GameEngineRenderer.h>

MapGameObject::MapGameObject()
	:MapTile_(nullptr),
	AllBlock_()
{

}

MapGameObject::~MapGameObject()
{

}

void MapGameObject::Start()
{
	CreateBlockTile();
}

void MapGameObject::Update()
{

}

void MapGameObject::CreateBlockTile()
{
	if (GetLevel()->GetNameCopy() == "VillageLevel")
	{

	}
}