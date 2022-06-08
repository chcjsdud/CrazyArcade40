#include "PlayNickName.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include "GlobalUIName.h"

PlayNickName::PlayNickName()
{
}

PlayNickName::~PlayNickName()
{
}

void PlayNickName::Render()
{
	SetTextAlign(GameEngine::BackBufferDC(), TA_LEFT);
	
	TextOut(GameEngine::BackBufferDC(), 708, 120, GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_1ConstRef().c_str()));
	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		TextOut(GameEngine::BackBufferDC(), 708, 165, GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str(), lstrlen(GlobalUIName::GetInst()->GetNickName_2ConstRef().c_str()));
	}
	SetTextAlign(GameEngine::BackBufferDC(), TA_TOP | TA_LEFT);
}