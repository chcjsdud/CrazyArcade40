#include "LoginLevel.h"
#include "Mouse.h"
#include "LoginBackGround.h"
#include "ContentsEnum.h"

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
}

void LoginLevel::LevelChangeEnd(GameEngineLevel* NextLevel)
{
	ShowCursor(true);
}
