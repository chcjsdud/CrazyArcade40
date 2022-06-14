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
	if (GetLevel()->GetNameConstRef() == "RoomLevel")
	{
		if (false == GetLevel()->FindActor("ChoiceMap")->IsUpdate() && false == GetLevel()->FindActor("Mypage")->IsUpdate())
		{
			SetTextColor(GameEngine::BackBufferDC(), RGB(255, 255, 255));
			TextOut(GameEngine::BackBufferDC(), 75, 197, GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str()));
			if (true == GlobalUIName::GetInst()->Is2pUpdate())
			{
				TextOut(GameEngine::BackBufferDC(), 180, 197, GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str()));
			}
		}
		else
		{
			SetTextColor(GameEngine::BackBufferDC(), RGB(255, 255, 255));
			TextOut(GameEngine::BackBufferDC(), 75, 197, GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str()));
		}
	}
	else if (GetLevel()->GetNameConstRef() == "MonsterRoomLevel")
	{
		if (false == GetLevel()->FindActor("Mypage")->IsUpdate())
		{
			SetTextColor(GameEngine::BackBufferDC(), RGB(255, 255, 255));
			TextOut(GameEngine::BackBufferDC(), 75, 217, GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str()));
			if (true == GlobalUIName::GetInst()->Is2pUpdate())
			{
				TextOut(GameEngine::BackBufferDC(), 180, 217, GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str()));
			}
		}
		else
		{
			TextOut(GameEngine::BackBufferDC(), 75, 217, GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str()));
		}
	}
	SetTextAlign(GameEngine::BackBufferDC(), TA_TOP | TA_LEFT);
}