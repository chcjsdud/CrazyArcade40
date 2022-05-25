#include "ChattingHistory.h"
#include "GlobalUIName.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

std::list<std::string> ChattingHistory::historychatt_;
std::string ChattingHistory::hostname_ = "";

void ChattingHistory::ChattingHistoryAdd(const std::string& _ChattingText)
{
	// ä�� �̷º����� �Ѵ�.
	// ��, �̷� ���� �ִ�ġ�� �Ѿ�� �տ������� �����.
	size_t CurHistory = historychatt_.size();
	if (MAX_CHATTINGHISTORY <= CurHistory)
	{
		// �Ǿ��� �̷��� ����� �ڿ� ����
		historychatt_.pop_front();
		historychatt_.push_back(_ChattingText);
	}
	else
	{
		historychatt_.push_back(_ChattingText);
	}
}

void ChattingHistory::CurHostName(const std::string& _HostName)
{
	hostname_ = _HostName;
}

ChattingHistory::ChattingHistory() :
	chattingHisBoxSpriteRender_(nullptr)
{
}

ChattingHistory::~ChattingHistory()
{
	// �Ҹ�� �̷��� ��� ����
	if (!historychatt_.empty())
	{
		historychatt_.clear();
	}
}

ChattingHistory::ChattingHistory(ChattingHistory&& _other) noexcept :
	chattingHisBoxSpriteRender_(_other.chattingHisBoxSpriteRender_)
{
}

void ChattingHistory::Start()
{
	//chattingHisBoxSpriteRender_ = CreateRenderer("Lobby_ChattingHis", static_cast<int>(UIType::Time));
	//chattingHisBoxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 390.f));
	//chattingHisBoxSpriteRender_->SetRenderSize(float4(1260.f, 250.f));
	//chattingHisBoxSpriteRender_->CameraEffectOff();
}



void ChattingHistory::Update()
{
}


void ChattingHistory::Render()
{
	

	size_t HistCnt = historychatt_.size();
	if (0 < HistCnt)
	{
		std::list<std::string>::iterator StartIter = historychatt_.begin();
		std::list<std::string>::iterator EndIter = historychatt_.end();
		int Index = 0;
		for (; StartIter != EndIter; ++StartIter)
		{
			std::string CurHistoryChatt = GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str();
			if (GlobalUIName::GetInst()->GetNickName_2ConstRef() != "")
			{
				CurHistoryChatt += ", ";
				CurHistoryChatt += GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str();
			}
			CurHistoryChatt += " : ";
			CurHistoryChatt += (*StartIter);
			SetBkMode(GameEngine::BackBufferDC(), TRANSPARENT);

			TextOut(GameEngine::BackBufferDC(), 20, 404 + (Index * 18), CurHistoryChatt.c_str(), lstrlen(CurHistoryChatt.c_str()));

			++Index;
		}
	}
}

void ChattingHistory::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (!historychatt_.empty())
	{
		historychatt_.clear();
	}
}
