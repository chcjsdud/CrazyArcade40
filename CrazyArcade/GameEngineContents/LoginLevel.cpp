#include "LoginLevel.h"
#include "TextArea.h"
#include "Mouse.h"
#include "LoginBackGround.h"
#include "ContentsEnum.h"
#include "GameBgmPlayer.h"

LoginLevel::LoginLevel()
{
}

LoginLevel::~LoginLevel()
{
}

void LoginLevel::Loading()
{
	CreateActor<LoginBackGround>((int)UIType::BackGround);
	CreateActor<Mouse>((int)UIType::Mouse);
	
}

void LoginLevel::Update()
{

}

void LoginLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ShowCursor(false);
	GameBgmPlayer::BgmPlay_->ChangeBgm("LoginBGM.wav");
}

void LoginLevel::LevelChangeEnd(GameEngineLevel* NextLevel)
{
	GameBgmPlayer::BgmPlay_->Stop();
	ShowCursor(true);
}
