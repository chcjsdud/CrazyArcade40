#include "StartButton.h"
#include "GlobalUIName.h"
#include "RoomCharaterSelectUI.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEngine/GameEngine.h>


StartButton::StartButton()
	: StartRenderer_(nullptr)
	, StartCollision_(nullptr)
{
}

StartButton::~StartButton()
{
	
}

void StartButton::Start()
{
	SetPosition({625, 509});
	StartRenderer_ = CreateRenderer((int)UIType::PopUpButton);
	StartRenderer_->SetImage("StartButton.bmp");

	StartRenderer_->CreateAnimation("StartButton.bmp", "StartButton_Idle", 0, 0, 0.1f, false);
	StartRenderer_->CreateAnimation("StartButton.bmp", "StartButton_Approach", 10, 14, 0.1f, true);
	StartRenderer_->CreateAnimation("StartButton.bmp", "StartButton_Cilck", 19, 19, 0.1f, false);

	StartRenderer_->ChangeAnimation("StartButton_Idle");

	StartCollision_ = CreateCollision("StartButton", { 200.0f, 66.0f });
	StartCollision_->SetPivot(float4{0.0f,20.0f});

}

void StartButton::Update()
{
	if (true == StartCollision_->CollisionCheck("MouseCol"))
	{
		StartRenderer_->ChangeAnimation("StartButton_Approach");
	}


	else if (false == StartCollision_->CollisionCheck("MouseCol"))
	{
		StartRenderer_->ChangeAnimation("StartButton_Idle");
	}



	if (true == StartCollision_->CollisionCheck("MouseCol"))
	{
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			StartRenderer_->ChangeAnimation("StartButton_Cilck");
		}
		if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			StartButtonClick();
		}
	}
	else {
	}


}

void StartButton::StartButtonClick()
{
	if (4 == GlobalUIName::GetInst()->Get1PChar())
	{
		GlobalUIName::GetInst()->Set1P(Random_.RandomInt(0, 2));
	}
	if (4 == GlobalUIName::GetInst()->Get2PChar())
	{
		GlobalUIName::GetInst()->Set2P(Random_.RandomInt(0, 2));
	}

	if (GlobalUIName::GetInst()->GetChoiceMap() == 1)
	{
		GameEngine::GetInst().ChangeLevel("VillageLevel");
	}

	if (GlobalUIName::GetInst()->GetChoiceMap() == 2)
	{
		GameEngine::GetInst().ChangeLevel("CemetoryLevel");
	}

	if (GlobalUIName::GetInst()->GetChoiceMap() == 3)
	{
		GameEngine::GetInst().ChangeLevel("CampLevel");
	}
	
	if (GlobalUIName::GetInst()->GetChoiceMap() == 4)
	{
		GameEngine::GetInst().ChangeLevel("Monster1Level");
	}
}