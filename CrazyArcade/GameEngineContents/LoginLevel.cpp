#include "LoginLevel.h"
#include "Mouse.h"

LoginLevel::LoginLevel()
{
}

LoginLevel::~LoginLevel()
{
}

void LoginLevel::Loading()
{
	CreateActor<Mouse>(1);
}

void LoginLevel::Update()
{

}

void LoginLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}