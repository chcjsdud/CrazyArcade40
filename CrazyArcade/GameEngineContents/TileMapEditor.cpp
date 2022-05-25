#include "TileMapEditor.h"
#include "ContentsEnum.h"
#include "MapGameObject.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

TileMapEditor* TileMapEditor::MapEditorSet=nullptr;


TileMapEditor::TileMapEditor()
	:EditorTileMap_(this),
	LevelName_("Camp"),
	RenderName_("Block1")
{

}

TileMapEditor::~TileMapEditor() 
{
}

void TileMapEditor::Start()
{
	SetPosition({ 0,0 });
	MapBack = CreateRenderer();

	MoveBox1 = CreateRenderer("CampMoveBox.bmp",static_cast<int>(ORDER::MAPOBJECT));
	MoveBox1->SetPivot({ 700,100 });
	MoveBox2= CreateRenderer("CampMoveBox2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	MoveBox2->SetPivot({ 700,150 });
	MoveBox2->SetIndex(0);
	MoveBox3= CreateRenderer("CampMoveBox3.bmp", static_cast<int>(ORDER::MAPOBJECT));
	MoveBox3->SetPivot({ 700,200 });
	Block1= CreateRenderer("CampBlock1.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Block1->SetPivot({ 700,250 });
	Block2= CreateRenderer("CampBlock2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Block2->SetPivot({ 700,300 });
	Bush1= CreateRenderer("CampBush1.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Bush1->SetPivot({ 700,350 });
	Bush2= CreateRenderer("CampBush2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Bush2->SetPivot({ 700,400 });

	BlockSet = GetLevel()->CreateActor<MapGameObject>();
	BlockSet->SetMapTile(&EditorTileMap_);
	//Stone= CreateRenderer("CampBox01.bmp", static_cast<int>(ORDER::MAPOBJECT));
	//Stone= CreateRenderer("CampBox01.bmp", static_cast<int>(ORDER::MAPOBJECT));

	MoveBox1Col = CreateCollision("Box1",{ 40,46 }, { 700,100 });
	MoveBox2Col = CreateCollision("Box2", { 40,46 }, { 700,150 });
	MoveBox3Col = CreateCollision("Box3", { 40,46 }, { 700,200 });
	Block1Col = CreateCollision("Block1", { 40,46 }, { 700,250 });
	Block2Col = CreateCollision("Block2", { 40,46 }, { 700,300 });
	Bush1Col = CreateCollision("Bush1", { 40,46 }, { 700,360 });
	Bush2Col = CreateCollision("Bush2", { 40,46 }, { 700,410 });
	//StoneCol;
	//Stone2Col;

	if (false == GameEngineInput::GetInst()->IsKey("LeftMouseEditor"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftMouseEditor", VK_LBUTTON);
	}
}

void TileMapEditor::Update()
{


	if (true == GameEngineInput::GetInst()->IsDown("LeftMouseEditor"))
	{
		
		if (true == MoveBox1Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "MoveBox1";
		}
		if (true == MoveBox2Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "MoveBox2_1";
		}
		if (true == MoveBox3Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "MoveBox2_3";
		}
		if (true == Block1Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Block1";
		}
		if (true == Block2Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Block2";
		}
		if (true == Bush1Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Bush1";
		}
		if (true == Bush2Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Bush2";
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("LeftMouseEditor"))
	{
		//MapGameObject* Block_ = GetLevel()->CreateActor<MapGameObject>(static_cast<int>(ORDER::BlOCK), "Block");
		//블럭 찍기 함수
		// 마우스 위치 MousePos
		// bmp 이름은 LevelName_ + RenderName_ + " .bmp" 로
		//이때 타일맵이 아니거나 이미 찍혀있는 타일일떄는 그냥 return해주어 아무일도 안일어나게 하기
		
		BlockSet->CreateBlock(MousePos, LevelName_ + RenderName_);
	}
}

std::string TileMapEditor::LevelNameReturnToString()
{
	if ("CampLevel" == LevelName_)
	{
		return "Camp";
	}
	if ("VillageLevel" == LevelName_)
	{
		return "Village";
	}
	if ("CemetoryLevel" == LevelName_)
	{
		return "Cemetory";
	}
	if ("Monster1Level" == LevelName_)
	{
		return "Monster1";
	}
	if ("Monster2Level" == LevelName_)
	{
		return "Monster2";
	}
	if ("BossLevel" == LevelName_)
	{
		return "Boss";
	}

}