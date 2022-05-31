#include "TileMapEditor.h"
#include "ContentsEnum.h"
#include "MapGameObject.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>

TileMapEditor* TileMapEditor::MapEditorSet=nullptr;


TileMapEditor::TileMapEditor()
	:EditorTileMap_(this),
	LevelName_(""),
	RenderName_("Block1"),
	NextLevelName_("CampLevel"),
	MoveBox1(nullptr),
	MoveBox2(nullptr),
	MoveBox3(nullptr),
	Block1(nullptr),
	Block2(nullptr),
	Block3(nullptr),
	Block4(nullptr),
	Block5(nullptr),
	Block6(nullptr),
	Block7(nullptr),
	Block8(nullptr),
	Bush1(nullptr),
	Bush2(nullptr),
	Stone1(nullptr),
	Stone2(nullptr),
	MoveBox1Col(nullptr),
	MoveBox2Col(nullptr),
	MoveBox3Col(nullptr),
	Block1Col(nullptr),
	Block2Col(nullptr),
	Block3Col(nullptr),
	Block4Col(nullptr),
	Block5Col(nullptr),
	Block6Col(nullptr),
	Block7Col(nullptr),
	Block8Col(nullptr),
	Bush1Col(nullptr),
	Bush2Col(nullptr),
	Stone1Col(nullptr),
	Stone2Col(nullptr)
{

}

TileMapEditor::~TileMapEditor() 
{
}

void TileMapEditor::Start()
{
	SetPosition({ 0,0 });
	GameEngineRenderer* MapUIBack = CreateRenderer("PlayUI.bmp",(int)ORDER::BACKGROUND);
	MapUIBack->SetPivot({ 400,300 });
	MapBack = CreateRenderer();


	MoveBox1 = CreateRenderer("CampMoveBox1.bmp",static_cast<int>(ORDER::MAPOBJECT));
	MoveBox1->SetPivot({ 700,50 });
	MoveBox2= CreateRenderer("CampMoveBox2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	MoveBox2->SetPivot({ 700,100 });
	MoveBox2->SetIndex(0);
	MoveBox3= CreateRenderer("CampMoveBox3.bmp", static_cast<int>(ORDER::MAPOBJECT));
	MoveBox3->SetPivot({ 700,150 });
	Block1= CreateRenderer("CampBlock1.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Block1->SetPivot({ 700,200 });
	Block2= CreateRenderer("CampBlock2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Block2->SetPivot({ 700,250 });
	Block3 = CreateRenderer("CampBlock2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Block3->SetPivot({ 700,300 });
	Block4 = CreateRenderer("CampBlock2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Block4->SetPivot({ 700,350 });

	Block5 = CreateRenderer("CampBlock1.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Block5->SetPivot({ 750,200 });
	Block6 = CreateRenderer("CampBlock2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Block6->SetPivot({ 750,250 });
	Block7 = CreateRenderer("CampBlock2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Block7->SetPivot({ 750,300 });
	Block8 = CreateRenderer("CampBlock2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Block8->SetPivot({ 750,350 });

	Bush1= CreateRenderer("CampBush1.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Bush1->SetPivot({ 700,400 });
	Bush2= CreateRenderer("CampBush2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Bush2->SetPivot({ 700,450 });
	Stone1 = CreateRenderer("CampBlock2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Stone1->SetPivot({ 700,510 });
	Stone2 = CreateRenderer("CampBlock2.bmp", static_cast<int>(ORDER::MAPOBJECT));
	Stone2->SetPivot({ 700,560 });

	BlockSet = GetLevel()->CreateActor<MapGameObject>();
	BlockSet->SetMapTile(&EditorTileMap_);

	MoveBox1Col = CreateCollision("Box1",{ 40,46 }, { 700,50 });
	MoveBox2Col = CreateCollision("Box2", { 40,46 }, { 700,100 });
	MoveBox3Col = CreateCollision("Box3", { 40,46 }, { 700,150 });
	Block1Col = CreateCollision("Block1", { 40,46 }, { 700,200 });
	Block2Col = CreateCollision("Block2", { 40,46 }, { 700,250 });
	Block3Col = CreateCollision("Block3", { 40,46 }, { 700,300 });
	Block4Col = CreateCollision("Block4", { 40,46 }, { 700,350 });

	Block5Col = CreateCollision("Block5", { 40,46 }, { 750,200 });
	Block6Col = CreateCollision("Block6", { 40,46 }, { 750,250 });
	Block7Col = CreateCollision("Block7", { 40,46 }, { 750,300 });
	Block8Col = CreateCollision("Block8", { 40,46 }, { 750,350 });

	Bush1Col = CreateCollision("Bush1", { 40,46 }, { 700,400 });
	Bush2Col = CreateCollision("Bush2", { 40,46 }, { 700,460 });
	Stone1Col = CreateCollision("Stone1", { 40,46 }, { 700,510 });;
	Stone2Col = CreateCollision("Stone2", { 40,46 }, { 700,560 });;

	if (false == GameEngineInput::GetInst()->IsKey("LeftMouseEditor"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftMouseEditor", VK_LBUTTON);
		GameEngineInput::GetInst()->CreateKey("Save", 'K');
		GameEngineInput::GetInst()->CreateKey("Load", 'L');
	}
}

void TileMapEditor::LevelBlockUpdate()
{
	
	if ("CampLevel" == NextLevelName_)
	{
		TileAllOff();
		MoveBox1->On();
		MoveBox1->SetImage("CampMoveBox1.bmp");

		MoveBox2->On();
		MoveBox2->SetImage("CampMoveBox2.bmp");
		MoveBox2->SetIndex(0);

		MoveBox3->On();
		MoveBox3->SetImage("CampMoveBox3.bmp");

		Block1->On();
		Block1->SetImage("CampBlock1.bmp");

		Block2->On();
		Block2->SetImage("CampBlock2.bmp");

		Bush1->On();
		Bush1->SetImage("CampBush1.bmp");
		Bush1->SetIndex(0);
		Bush2->On();
		Bush2->SetImage("CampBush2.bmp");
		Bush2->SetIndex(0);

		MoveBox1Col->On();
		MoveBox2Col->On();
		MoveBox3Col->On();
		Block1Col->On();
		Block2Col->On();
		Bush1Col->On();
		Bush2Col->On();

	}

	else if ("VillageLevel" == NextLevelName_)
	{
		TileAllOff();

		MoveBox1->On();
		MoveBox1Col->On();
		MoveBox1->SetImage("VillageMoveBox1.bmp");

		Block1->On();
		Block1Col->On();
		Block1->SetImage("VillageBlock1.bmp");

		Block2->On();
		Block2Col->On();
		Block2->SetImage("VillageBlock2.bmp");

		Bush1->On();
		Bush1Col->On();
		Bush1->SetImage("VillageBush1.bmp");
		Bush1->SetIndex(0);
	}
	else if ("CemetoryLevel" == NextLevelName_)
	{
		TileAllOff();
		MoveBox1->On();
		MoveBox1->SetImage("CemetoryMoveBox1.bmp");

		MoveBox2->On();
		MoveBox2->SetImage("CemetoryMoveBox2.bmp");

		MoveBox3->On();
		MoveBox3->SetImage("CemetoryMoveBox3.bmp");

		Block1->On();
		Block1->SetImage("CemetoryBlock1.bmp");

		Block2->On();
		Block2->SetImage("CemetoryBlock2.bmp");

		Block3->On();
		Block3->SetImage("CemetoryBlock3.bmp");

		Block4->On();
		Block4->SetImage("CemetoryBlock4.bmp");

		Block5->On();
		Block5->SetImage("CemetoryBlock5.bmp");

		Block6->On();
		Block6->SetImage("CemetoryBlock6.bmp");

		Block7->On();
		Block7->SetImage("CemetoryBlock7.bmp");

		Block8->On();
		Block8->SetImage("CemetoryBlock8.bmp");

		Stone1->On();
		Stone1->SetImage("CemetoryStone1.bmp");
		Stone1Col->On();
		Stone2->On();
		Stone2->SetImage("CemetoryStone2.bmp");
		Stone2Col->On();



		MoveBox1Col->On();
		MoveBox2Col->On();
		MoveBox3Col->On();
		Block1Col->On();
		Block2Col->On();
		Block3Col->On();
		Block4Col->On();
		Block5Col->On();
		Block6Col->On();
		Block7Col->On();
		Block8Col->On();
	}
	else 
	{
		TileAllOff();
		MoveBox1->On();
		MoveBox1->SetImage("MonsterMoveBox1.bmp");

		Block1->On();
		Block1->SetImage("MonsterBlock1.bmp");

		Block2->On();
		Block2->SetImage("MonsterBlock2.bmp");

		Block3->On();
		Block3->SetImage("MonsterBlock3.bmp");

		Block4->On();
		Block4->SetImage("MonsterBlock4.bmp");

		Block5->On();
		Block5->SetImage("MonsterBlock5.bmp");

		Block6->On();
		Block6->SetImage("MonsterBlock6.bmp");

		Block7->On();
		Block7->SetImage("MonsterBlock7.bmp");

		Block8->On();
		Block8->SetImage("MonsterBlock8.bmp");

		MoveBox1Col->On();
		Block1Col->On();
		Block2Col->On();
		Block3Col->On();
		Block4Col->On();
		Block5Col->On();
		Block6Col->On();
		Block7Col->On();
		Block8Col->On();

	}
}
void TileMapEditor::Update()
{
	if (NextLevelName_ != LevelName_)
	{
		LevelBlockUpdate();
		LevelName_= NextLevelName_;
	}

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
		if (true == Block3Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Block3";
		}
		if (true == Block4Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Block4";
		}
		if (true == Block5Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Block5";
		}
		if (true == Block6Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Block6";
		}
		if (true == Block7Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Block7";
		}
		if (true == Block8Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Block8";
		}
		if (true == Bush1Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Bush1";
		}
		if (true == Bush2Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Bush2";
		}
		if (true == Stone1Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Stone1";
		}
		if (true == Stone2Col->CollisionCheck("MouseCol"))
		{
			RenderName_ = "Stone2";
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("LeftMouseEditor"))
	{
		//MapGameObject* Block_ = GetLevel()->CreateActor<MapGameObject>(static_cast<int>(ORDER::BlOCK), "Block");
		//블럭 찍기 함수
		// 마우스 위치 MousePos
		// bmp 이름은 LevelName_ + RenderName_ + " .bmp" 로
		//이때 타일맵이 아니거나 이미 찍혀있는 타일일떄는 그냥 return해주어 아무일도 안일어나게 하기
	
		BlockSet->CreateBlock(MousePos, LevelNameReturnToString() + RenderName_);
	}

	if (true == GameEngineInput::GetInst()->IsDown("Save"))
	{
		GameEngineDirectory Dir;

		Dir.MoveParent("CrazyArcade");
		Dir.Move("Resources");
		Dir.Move("Data");

		GameEngineFile SaveFile = (Dir.GetFullPath() + "\\"+ LevelName_ +".MapData").c_str();

		SaveFile.Open(OpenMode::Write);

		int Size = static_cast<int>(EditorTileMap_.Tiles_.size());
		SaveFile.Write(&Size, sizeof(int));

		for (size_t y = 0; y < EditorTileMap_.Tiles_.size(); y++)
		{
			int XSize = static_cast<int>(EditorTileMap_.Tiles_[y].size());
			SaveFile.Write(&XSize, sizeof(int));
			for (size_t x = 0; x < EditorTileMap_.Tiles_[y].size(); x++)
			{
				BlockTile* Tile = EditorTileMap_.GetTile<BlockTile>(x, y);

				if (nullptr == Tile)
				{
					std::string Name = "None";
					SaveFile.Write(Name);
					continue;
				}

				std::string Name = Tile->Renderer->GetImage()->GetNameConstPtr();
				Name.replace(Name.size() - 4, 4, "");

				SaveFile.Write(Name);

			}
		}
	}


	if (true == GameEngineInput::GetInst()->IsDown("Load"))
	{
		GameEngineDirectory Dir;

		Dir.MoveParent("CrazyArcade");
		Dir.Move("Resources");
		Dir.Move("Data");

		GameEngineFile LoadFile = (Dir.GetFullPath() + "\\" + LevelName_ + ".MapData").c_str();

		LoadFile.Open(OpenMode::Read);

		int Size = 0;
		LoadFile.Read(&Size, sizeof(int));

		for (size_t y = 0; y < Size; y++)
		{
			int XSize = 0;
			LoadFile.Read(&XSize, sizeof(int));
			for (size_t x = 0; x < XSize; x++)
			{
				std::string Name;
				LoadFile.Read(Name);

				if (Name == "None")
				{
					continue;
				}

				//                          5 7
				BlockSet->CreateBlock(float4(x * 40, y * 40), Name);
			}
		}
	}
}

std::string TileMapEditor::LevelNameReturnToString()
{
	if ("CampLevel" == LevelName_)
	{
		return "Camp";
	}
	else if ("VillageLevel" == LevelName_)
	{
		return "Village";
	}
	else if ("CemetoryLevel" == LevelName_)
	{
		return "Cemetory";
	}
	else
	{
		return "Monster";
	}

}

void TileMapEditor::TileAllOff()
{
	MoveBox1->Off();
	MoveBox2->Off();
	MoveBox3->Off();
	Block1->Off();
	Block2->Off();
	Block3->Off();
	Block4->Off();
	Block5->Off();
	Block6->Off();
	Block7->Off();
	Block8->Off();
	Bush1->Off();
	Bush2->Off();
	Stone1->Off();
	Stone2->Off();

	MoveBox1Col->Off();
	MoveBox2Col->Off();
	MoveBox3Col->Off();
	Block1Col->Off();
	Block2Col->Off();
	Block3Col->Off();
	Block4Col->Off();
	Block5Col->Off();
	Block6Col->Off();
	Block7Col->Off();
	Block8Col->Off();
	Bush1Col->Off();
	Bush2Col->Off();
	Stone1Col->Off();
	Stone2Col->Off();
}