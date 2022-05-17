#include"MapGameObject.h"
#include <GameEngine/GameEngineRenderer.h>

MapGameObject::MapGameObject()
	:MapTile_(nullptr),
	AllBlockTiles_()
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