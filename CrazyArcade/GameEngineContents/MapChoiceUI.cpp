#include "MapChoiceUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "ContentsEnum.h"



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
	SetPosition({ 625, 410 });
	MapUIBackGround_ = CreateRenderer("CampMapChoice.bmp");

	MapChoiceButton_ = CreateRenderer((int)UIType::PopUpButton, RenderPivot::CENTER, {77.0f,14.0f});
	MapChoiceButton_->SetImage("MapChoiceButton.bmp");

	MapChoiceButton_->CreateAnimation("MapChoiceButton.bmp", "MapChoiceButton_Idle", 0, 0, 0.1f, false);
	MapChoiceButton_->CreateAnimation("MapChoiceButton.bmp", "MapChoiceButton_Approach", 1, 6, 0.1f, true);
	MapChoiceButton_->CreateAnimation("MapChoiceButton.bmp", "MapChoiceButton_Cilck", 7, 7, 0.1f, false);
	MapChoiceButton_->ChangeAnimation("MapChoiceButton_Idle");

	MapButton_ = CreateCollision("MapButton", { 120, 50 }, {78, 40});
}


void MapChoiceUI::Update()
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
		true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		MapButtonClick();
	}
}

void MapChoiceUI::MapButtonClick()
{

}