#include "MapChoiceUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "ChoiceMap.h"



MapChoiceUI::MapChoiceUI()
	: MapUIBackGround_(nullptr)
	, MapChoiceButton_(nullptr)
	, MapButton_(nullptr)
{
}

MapChoiceUI::~MapChoiceUI()
{
}

void MapChoiceUI::Start()
{
	SetPosition({ 625, 420 });
	if (GetLevel()->GetNameConstRef() == "RoomLevel")
	{
		MapUIBackGround_ = CreateRenderer((int)UIType::PopUp, RenderPivot::CENTER);
		MapUIBackGround_->SetImage("VillageMapChoice.bmp");

		MapChoiceButton_ = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, { 77.0f,14.0f });
		MapChoiceButton_->SetImage("MapChoiceButton.bmp");

		MapChoiceButton_->CreateAnimation("MapChoiceButton.bmp", "MapChoiceButton_Idle", 0, 0, 0.1f, false);
		MapChoiceButton_->CreateAnimation("MapChoiceButton.bmp", "MapChoiceButton_Approach", 1, 6, 0.1f, true);
		MapChoiceButton_->CreateAnimation("MapChoiceButton.bmp", "MapChoiceButton_Cilck", 7, 7, 0.1f, false);
		MapChoiceButton_->ChangeAnimation("MapChoiceButton_Idle");

		MapButton_ = CreateCollision("MapButton", { 120, 50 }, { 78, 40 });

		choicemap = GetLevel()->CreateActor<ChoiceMap>((int)UIType::PopUp);
		choicemap->Off();
	}
	else
	{
		MapUIBackGround_ = CreateRenderer((int)UIType::PopUp, RenderPivot::CENTER);
		MapUIBackGround_->SetImage("MonsterMapChoice.bmp");
		MapChoiceButton_ = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, { 77.0f,14.0f });
		MapChoiceButton_->SetImage("MapChoiceButton.bmp");
		MapChoiceButton_->CreateAnimation("MapChoiceButton.bmp", "MapChoiceButton_Idle", 0, 0, 0.1f, false);
		MapChoiceButton_->ChangeAnimation("MapChoiceButton_Idle");
	}
}


void MapChoiceUI::Update()
{

	if (GetLevel()->GetNameConstRef() == "RoomLevel")
	{
		if (true == MapButton_->CollisionCheck("MouseCol"))
		{
			MapChoiceButton_->ChangeAnimation("MapChoiceButton_Approach");
		}


		else if (false == MapButton_->CollisionCheck("MouseCol"))
		{
			MapChoiceButton_->ChangeAnimation("MapChoiceButton_Idle");
		}

		if (true == MapButton_->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			MapChoiceButton_->ChangeAnimation("MapChoiceButton_Cilck");
		}

		if (true == MapButton_->CollisionCheck("MouseCol") &&
			true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			MapButtonClick();
		}

		if (choicemap->GetChoiceMap() == 1)
		{
			MapUIBackGround_->SetImage("VillageMapChoice.bmp");
		}
		else if (choicemap->GetChoiceMap() == 2)
		{
			MapUIBackGround_->SetImage("CemetoryMapChoice.bmp");
		}
		else if (choicemap->GetChoiceMap() == 3)
		{
			MapUIBackGround_->SetImage("CampMapChoice.bmp");
		}
	}
}

void MapChoiceUI::MapButtonClick()
{
	choicemap->On();

}