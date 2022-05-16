#include "LoginLevel.h"
#include "Mouse.h"
#include "LoginBackGround.h"

LoginLevel::LoginLevel()
{
}

LoginLevel::~LoginLevel()
{
}

void LoginLevel::Loading()
{
	CreateActor<LoginBackGround>(0);
	CreateActor<Mouse>(1);
}

void LoginLevel::Update()
{

}

void LoginLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}