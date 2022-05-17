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

}

void MapGameObject::Update()
{

}

void MapGameObject::CreateBlockTile(int x_ ,int y_)
{
	if (GetLevel()->GetNameCopy() == "VillageLevel")
	{
		
	}
}