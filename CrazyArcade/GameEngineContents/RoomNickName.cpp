#include "RoomNickName.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include "GlobalUIName.h"

RoomNickName::RoomNickName()
{
}

RoomNickName::~RoomNickName()
{
}

void RoomNickName::Render()
{
	SetTextAlign(GameEngine::BackBufferDC(), TA_CENTER);
	if (false == GetLevel()->FindActor("ChoiceMap")->IsUpdate())
	{
		SetTextColor(GameEngine::BackBufferDC(), RGB(255, 255, 255));
		TextOut(GameEngine::BackBufferDC(), 75,197, GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str()));
		TextOut(GameEngine::BackBufferDC(), 180, 197, GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str()));
	}
	else
	{
		SetTextColor(GameEngine::BackBufferDC(), RGB(255, 255, 255));
		TextOut(GameEngine::BackBufferDC(), 75, 197, GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str()));
	}
	SetTextAlign(GameEngine::BackBufferDC(), TA_TOP | TA_LEFT);
}