#include"MapFront.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>

MapFront::MapFront()
{

}
MapFront::~MapFront()
{

}
void MapFront::Start()
{
	SetPosition({ 320,280 });
	if ("CampLevel" == GetLevel()->GetNameCopy())
	{
		GameEngineRenderer* Y1 = CreateRenderer("CampY1.bmp",static_cast<int>(ORDER::PLAYER));
		Y1->SetPivot({ 0,-240 });
		GameEngineRenderer* Y2 = CreateRenderer("CampY2.bmp", static_cast<int>(ORDER::PLAYER));
		Y2->SetPivot({ 0,-200 });
		GameEngineRenderer* Y12 = CreateRenderer("CampY12.bmp", static_cast<int>(ORDER::PLAYER));
		Y12->SetPivot({ 0,200 });
		GameEngineRenderer* Y13 = CreateRenderer("CampY13.bmp", static_cast<int>(ORDER::PLAYER));
		Y13->SetPivot({ 0,240 });
		MapFrontImg_ = CreateRenderer("Camp_FrontCenter.bmp", static_cast<int>(ORDER::PLAYER));
	}	
	else if ("CemetoryLevel" == GetLevel()->GetNameCopy())
	{
		GameEngineRenderer* Y1 = CreateRenderer("CemetoryY1.bmp", static_cast<int>(ORDER::PLAYER));
		Y1->SetPivot({ 0,-240 });
		GameEngineRenderer* Y2 = CreateRenderer("CemetoryY2.bmp", static_cast<int>(ORDER::PLAYER));
		Y2->SetPivot({ 0,-200 });
		GameEngineRenderer* Y3 = CreateRenderer("CemetoryY3.bmp", static_cast<int>(ORDER::PLAYER));
		Y3->SetPivot({ 0,-160 });
		GameEngineRenderer* Y5 = CreateRenderer("CemetoryY5.bmp", static_cast<int>(ORDER::PLAYER));
		Y5->SetPivot({ 0,-100 });
		GameEngineRenderer* Y6 = CreateRenderer("CemetoryY6.bmp", static_cast<int>(ORDER::PLAYER));
		Y6->SetPivot({ 0,-40 });
		GameEngineRenderer* Y7 = CreateRenderer("CemetoryY7.bmp", static_cast<int>(ORDER::PLAYER));
		Y7->SetPivot({ 0,-20 });
		GameEngineRenderer* Y9 = CreateRenderer("CemetoryY9.bmp", static_cast<int>(ORDER::PLAYER));
		Y9->SetPivot({ 0,80 });
		GameEngineRenderer* Y10 = CreateRenderer("CemetoryY10.bmp", static_cast<int>(ORDER::PLAYER));
		Y10->SetPivot({ 0,100 });
		GameEngineRenderer* Y12 = CreateRenderer("CemetoryY12.bmp", static_cast<int>(ORDER::PLAYER));
		Y12->SetPivot({ 0,180 });
		GameEngineRenderer* Y13 = CreateRenderer("CemetoryY13.bmp", static_cast<int>(ORDER::PLAYER));
		Y13->SetPivot({ 0,240 });
	}
	else if ("VillageLevel" == GetLevel()->GetNameCopy())
	{
		GameEngineRenderer* Y1 = CreateRenderer("VillageY1.bmp", static_cast<int>(ORDER::PLAYER));
		Y1->SetPivot({ 0,-240 });
		GameEngineRenderer* Y2 = CreateRenderer("VillageY2.bmp", static_cast<int>(ORDER::PLAYER));
		Y2->SetPivot({ 0,-200 });
		GameEngineRenderer* Y3 = CreateRenderer("VillageY3.bmp", static_cast<int>(ORDER::PLAYER));
		Y3->SetPivot({ 0,-160 });
		GameEngineRenderer* Y4 = CreateRenderer("VillageY4.bmp", static_cast<int>(ORDER::PLAYER));
		Y4->SetPivot({ 0,-120 });
		GameEngineRenderer* Y5 = CreateRenderer("VillageY5.bmp", static_cast<int>(ORDER::PLAYER));
		Y5->SetPivot({ 0,-80 });
		GameEngineRenderer* Y6 = CreateRenderer("VillageY6.bmp", static_cast<int>(ORDER::PLAYER));
		Y6->SetPivot({ 0,-40 });
		GameEngineRenderer* Y7 = CreateRenderer("VillageY7.bmp", static_cast<int>(ORDER::PLAYER));
		Y7->SetPivot({ 0,0 });;
		GameEngineRenderer* Y8 = CreateRenderer("VillageY8.bmp", static_cast<int>(ORDER::PLAYER));
		Y8->SetPivot({ 0,40 });
		GameEngineRenderer* Y9 = CreateRenderer("VillageY9.bmp", static_cast<int>(ORDER::PLAYER));
		Y9->SetPivot({ 0,80 });
		GameEngineRenderer* Y10 = CreateRenderer("VillageY10.bmp", static_cast<int>(ORDER::PLAYER));
		Y10->SetPivot({ 0,120 });
		GameEngineRenderer* Y11 = CreateRenderer("VillageY11.bmp", static_cast<int>(ORDER::PLAYER));
		Y11->SetPivot({ 0,160 });
		GameEngineRenderer* Y12 = CreateRenderer("VillageY12.bmp", static_cast<int>(ORDER::PLAYER));
		Y12->SetPivot({ 0,200 });
		GameEngineRenderer* Y13 = CreateRenderer("VillageY13.bmp", static_cast<int>(ORDER::PLAYER));
		Y13->SetPivot({ 0,240 });
	}
	else if("Monster1Level"== GetLevel()->GetNameCopy())
	{
		GameEngineRenderer* Y1 = CreateRenderer("Monster1Y1.bmp", static_cast<int>(ORDER::PLAYER));
		Y1->SetPivot({ 0,-240 });
		GameEngineRenderer* Y5 = CreateRenderer("Monster1Y5.bmp", static_cast<int>(ORDER::PLAYER));
		Y5->SetPivot({ 0,-80 });
		GameEngineRenderer* Y4 = CreateRenderer("Monster1Y4.bmp", static_cast<int>(ORDER::PLAYER));
		Y4->SetPivot({ 0,-120 });
		GameEngineRenderer* Y6 = CreateRenderer("Monster1Y6.bmp", static_cast<int>(ORDER::PLAYER));
		Y6->SetPivot({ 0,-40 });
		GameEngineRenderer* Y8 = CreateRenderer("Monster1Y8.bmp", static_cast<int>(ORDER::PLAYER));
		Y8->SetPivot({ 0,40 });
		GameEngineRenderer* Y9 = CreateRenderer("Monster1Y9.bmp", static_cast<int>(ORDER::PLAYER));
		Y9->SetPivot({ 0,80 });
		GameEngineRenderer* Y10 = CreateRenderer("Monster1Y10.bmp", static_cast<int>(ORDER::PLAYER));
		Y10->SetPivot({ 0,120 });
		
		GameEngineRenderer* Y13 = CreateRenderer("Monster1Y13.bmp", static_cast<int>(ORDER::PLAYER));
		Y13->SetPivot({ 0,240 });
	}
	else if ("Monster2Level" == GetLevel()->GetNameCopy())
	{
		GameEngineRenderer* Y1 = CreateRenderer("Monster2Y1.bmp", static_cast<int>(ORDER::PLAYER));
		Y1->SetPivot({ 0,-240 });
		GameEngineRenderer* Y2 = CreateRenderer("Monster2Y2.bmp", static_cast<int>(ORDER::PLAYER));
		Y2->SetPivot({ 0,-200 });
		GameEngineRenderer* Y3 = CreateRenderer("Monster2Y3.bmp", static_cast<int>(ORDER::PLAYER));
		Y3->SetPivot({ 0,-160 });
		GameEngineRenderer* Y4 = CreateRenderer("Monster2Y4.bmp", static_cast<int>(ORDER::PLAYER));
		Y4->SetPivot({ 0,-120 });
		GameEngineRenderer* Y5 = CreateRenderer("Monster2Y5.bmp", static_cast<int>(ORDER::PLAYER));
		Y5->SetPivot({ 0,-80 });
		GameEngineRenderer* Y6 = CreateRenderer("Monster2Y6.bmp", static_cast<int>(ORDER::PLAYER));
		Y6->SetPivot({ 0,-40 });
		GameEngineRenderer* Y7 = CreateRenderer("Monster2Y7.bmp", static_cast<int>(ORDER::PLAYER));
		Y7->SetPivot({ 0,0 });;
		GameEngineRenderer* Y8 = CreateRenderer("Monster2Y8.bmp", static_cast<int>(ORDER::PLAYER));
		Y8->SetPivot({ 0,40 });
		GameEngineRenderer* Y9 = CreateRenderer("Monster2Y9.bmp", static_cast<int>(ORDER::PLAYER));
		Y9->SetPivot({ 0,80 });
		GameEngineRenderer* Y10 = CreateRenderer("Monster2Y10.bmp", static_cast<int>(ORDER::PLAYER));
		Y10->SetPivot({ 0,120 });
		GameEngineRenderer* Y11 = CreateRenderer("Monster2Y11.bmp", static_cast<int>(ORDER::PLAYER));
		Y11->SetPivot({ 0,160 });
		GameEngineRenderer* Y12 = CreateRenderer("Monster2Y12.bmp", static_cast<int>(ORDER::PLAYER));
		Y12->SetPivot({ 0,200 });
		GameEngineRenderer* Y13 = CreateRenderer("Monster2Y13.bmp", static_cast<int>(ORDER::PLAYER));
		Y13->SetPivot({ 0,240 });
	}
	else if ("PlayerTeamTest" == GetLevel()->GetNameCopy())
	{
		GameEngineRenderer* Y1 = CreateRenderer("CampY1.bmp", static_cast<int>(ORDER::PLAYER));
		Y1->SetPivot({ 0,-240 });
		GameEngineRenderer* Y2 = CreateRenderer("CampY2.bmp", static_cast<int>(ORDER::PLAYER));
		Y2->SetPivot({ 0,-200 });
		GameEngineRenderer* Y12 = CreateRenderer("CampY12.bmp", static_cast<int>(ORDER::PLAYER));
		Y12->SetPivot({ 0,200 });
		GameEngineRenderer* Y13 = CreateRenderer("CampY13.bmp", static_cast<int>(ORDER::PLAYER));
		Y13->SetPivot({ 0,240 });
	}
}
void MapFront::Render()
{

}
void MapFront::Update()
{

}

