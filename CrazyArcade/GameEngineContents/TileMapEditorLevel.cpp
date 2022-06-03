#include "TileMapEditorLevel.h"
#include "TileMapEditor.h"
#include "ContentsEnum.h"
#include "Mouse.h"
#include "PlayBackGround.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
TileMapEditorLevel::TileMapEditorLevel() 
{
}

TileMapEditorLevel::~TileMapEditorLevel() 
{
}

void TileMapEditorLevel::Loading()
{
    TileMapEditor::MapEditorSet = CreateActor< TileMapEditor>(static_cast<int>(ORDER::BACKGROUND));
    TileMapEditor::MapEditorSet->EditorTileMap_.TileRangeSetting(15, 13, { 40,40 });
    
    TileMapEditor::MapEditorSet->GetRenderer()->SetImage("Camp_Back.bmp");
    TileMapEditor::MapEditorSet->GetRenderer()->SetPivot({ 320,280 });
    
    MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::UI));
    MouseSet->RenderOff();
    if (false == GameEngineInput::GetInst()->IsKey("CampMapCreate"))
    {
        GameEngineInput::GetInst()->CreateKey("CampMapCreate", 'q');
        GameEngineInput::GetInst()->CreateKey("VillageMapCreate", 'w');
        GameEngineInput::GetInst()->CreateKey("CemetoryCreate", 'e');
        GameEngineInput::GetInst()->CreateKey("MosterMap1Create", 'r');
        GameEngineInput::GetInst()->CreateKey("MosterMap2Create", 't');
        GameEngineInput::GetInst()->CreateKey("BossMapCreate", 'y');
    }
    YSortOn(static_cast<int>(ORDER::PLAYER));
}
void TileMapEditorLevel::Update()
{
    TileMapEditor::MapEditorSet->SetCurPos(MouseSet->ReturnPos());

    CheckStage();
};

void TileMapEditorLevel::CheckStage()
{
    if (true == GameEngineInput::GetInst()->IsDown("CampMapCreate"))
    {
        TileMapEditor::MapEditorSet->GetRenderer()->SetImage("Camp_Back.bmp");
        TileMapEditor::MapEditorSet->GetRenderer()->SetPivot({ 320,280 });
        TileMapEditor::MapEditorSet->NextLevelName_ = "CampLevel";
    }
    if (true == GameEngineInput::GetInst()->IsDown("VillageMapCreate"))
    {
        TileMapEditor::MapEditorSet->GetRenderer()->SetImage("Village_Back.bmp");
        TileMapEditor::MapEditorSet->GetRenderer()->SetPivot({ 320,280 });
        TileMapEditor::MapEditorSet->NextLevelName_ = "VillageLevel";
    }
    if (true == GameEngineInput::GetInst()->IsDown("CemetoryCreate"))
    {
        TileMapEditor::MapEditorSet->GetRenderer()->SetImage("Cemetory_Back.bmp");
        TileMapEditor::MapEditorSet->GetRenderer()->SetPivot({ 320,280 });
        TileMapEditor::MapEditorSet->NextLevelName_ = "CemetoryLevel";
    }
    if (true == GameEngineInput::GetInst()->IsDown("MosterMap1Create"))
    {
        TileMapEditor::MapEditorSet->GetRenderer()->SetImage("MonsterStage1_Back.bmp");
        TileMapEditor::MapEditorSet->GetRenderer()->SetPivot({ 320,280 });
        TileMapEditor::MapEditorSet->NextLevelName_ = "Monster1Level";
    }
    if (true == GameEngineInput::GetInst()->IsDown("MosterMap2Create"))
    {
        TileMapEditor::MapEditorSet->GetRenderer()->SetImage("MonsterStage2_Back.bmp");
        TileMapEditor::MapEditorSet->GetRenderer()->SetPivot({ 320,280 });
        TileMapEditor::MapEditorSet->NextLevelName_ = "Monster2Level";
    }
    if (true == GameEngineInput::GetInst()->IsDown("BossMapCreate"))
    {
        TileMapEditor::MapEditorSet->GetRenderer()->SetImage("BossStage_Back.bmp");
        TileMapEditor::MapEditorSet->GetRenderer()->SetPivot({ 320,280 });
        TileMapEditor::MapEditorSet->NextLevelName_ = "BossLevel";
    }
}
void TileMapEditorLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	
}
void TileMapEditorLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}