#include"UITeamTest.h"
#include"CreateRoomBackGround.h"
#include"LoginBackGround.h"
#include"Mouse.h"
#include"ContentsEnum.h"

UITeamTest::UITeamTest()
{

}
UITeamTest::~UITeamTest()
{

}
void UITeamTest::Loading()
{
	CreateActor<LoginBackGround>((int)UIType::BackGround);
	CreateActor<CreateRoomBackGround>((int)UIType::PopUp);
	CreateActor<Mouse>((int)UIType::Mouse);

}
void UITeamTest::Update()
{

}
void UITeamTest::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}