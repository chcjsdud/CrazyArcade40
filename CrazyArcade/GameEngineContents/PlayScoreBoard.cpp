#include "PlayScoreBoard.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"
#include "PlayerFaceIconUI.h"
#include "GlobalUIName.h"

PlayScoreBoard::PlayScoreBoard()
	: PlayScoreBoardRenderer_(nullptr)
{
}

PlayScoreBoard::~PlayScoreBoard()
{
}

void PlayScoreBoard::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	PlayScoreBoardRenderer_ = CreateRenderer((int)ORDER::UI);
	PlayScoreBoardRenderer_->SetImage("ScoreBoard.bmp");
	PlayScoreBoardRenderer_->SetAlpha(150);
	PlayScoreBoardRenderer_->SetPivot(float4{ -80.0f,-10.0f });

	PlayScoreTableRenderer_ = CreateRenderer((int)ORDER::UI);
	PlayScoreTableRenderer_->SetImage("ScoreTable.bmp");
	PlayScoreTableRenderer_->SetPivot(float4{ -40.0f,-135.0f });
	 
	WinLoseRenderer_1P = CreateRenderer((int)ORDER::UI);
	WinLoseRenderer_1P->SetImage("ScoreWin.bmp");
	WinLoseRenderer_1P->SetPivot(float4{ -255.0f,-105.0f });

	WinLoseRenderer_2P = CreateRenderer((int)ORDER::UI);
	WinLoseRenderer_2P->SetImage("ScoreLose.bmp");
	WinLoseRenderer_2P->SetPivot(float4{ -255.0f,-75.0f });


	NumRenderer_1P = CreateRenderer((int)ORDER::UI);
	NumRenderer_1P->SetImage("ScoreNum1.bmp");
	NumRenderer_1P->SetPivot(float4{ -300.0f,-105.0f });

	NumRenderer_2P = CreateRenderer((int)ORDER::UI);
	NumRenderer_2P->SetImage("ScoreNum2.bmp");
	NumRenderer_2P->SetPivot(float4{ -300.0f,-75.0f });

	Rank_1P = CreateRenderer((int)ORDER::UI);
	Rank_1P->SetImage("Rank_High.bmp");
	Rank_1P->SetPivot(float4{ -210.0f,-105.0f });
	Rank_1P->SetScale(float4{ 20.0f,20.0f });

	Rank_2P = CreateRenderer((int)ORDER::UI);
	Rank_2P->SetImage("Rank_low.bmp");
	Rank_2P->SetPivot(float4{ -210.0f,-75.0f });
	Rank_2P->SetScale(float4{20.0f,20.0f});
	//Death(10.0f);

	WinLoseRenderer_2P->Off();
	NumRenderer_2P->Off();
	Rank_2P->Off();
}

void PlayScoreBoard::Update()
{
	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		WinLoseRenderer_2P->On();
		NumRenderer_2P->On();
		Rank_2P->On();
	}
	

	if (Whowin_ != GameResult::Max) {

		if (Whowin_ == GameResult::Win)
		{
			WinLoseRenderer_1P->SetImage("ScoreWin.bmp");
			WinLoseRenderer_2P->SetImage("ScoreWin.bmp");
		}else if (Whowin_ == GameResult::Lose)
		{
			WinLoseRenderer_1P->SetImage("ScoreLose.bmp");
			WinLoseRenderer_2P->SetImage("ScoreLose.bmp");
		}
		else if (Whowin_ == GameResult::Draw)
		{
			WinLoseRenderer_1P->SetImage("ScoreDraw.bmp");
			WinLoseRenderer_2P->SetImage("ScoreDraw.bmp");
		}
		else if (Whowin_ == GameResult::Win_1P)
		{
			WinLoseRenderer_1P->SetImage("ScoreWin.bmp");
			WinLoseRenderer_2P->SetImage("ScoreLose.bmp");
		}
		else if (Whowin_ == GameResult::Win_2P)
		{
			WinLoseRenderer_1P->SetImage("ScoreLose.bmp");
			WinLoseRenderer_2P->SetImage("ScoreWin.bmp");
		}
		
	}
} 

void PlayScoreBoard::Render()
{
	SetTextAlign(GameEngine::BackBufferDC(), TA_LEFT);

	SetTextColor(GameEngine::BackBufferDC(), RGB(255, 255, 255));
	TextOut(GameEngine::BackBufferDC(), 205, 185, GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str()));
	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		TextOut(GameEngine::BackBufferDC(), 205, 215, GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str()));
	}
	SetTextAlign(GameEngine::BackBufferDC(), TA_TOP | TA_LEFT);

}
