#include "UITeamTest.h"
#include "CreateRoomBackGround.h"
#include "LoginBackGround.h"
#include "Mouse.h"
#include "ContentsEnum.h"
#include "PlayBackGround.h"
#include "TimeUI.h"
#include "StartIntroUI.h"

UITeamTest::UITeamTest()
{

}
UITeamTest::~UITeamTest()
{

}
void UITeamTest::Loading()
{
	//로그인 + 방만들기화면
	/*CreateActor<LoginBackGround>((int)UIType::BackGround);
	CreateActor<CreateRoomBackGround>((int)UIType::PopUp);
	CreateActor<Mouse>((int)UIType::Mouse);*/

	//게임플레이화면
	CreateActor<PlayBackGround>((int)UIType::BackGround);
	CreateActor<StartIntroUI>((int)UIType::PopUp);
	CreateActor<TimeUI>((int)UIType::Time);
}
void UITeamTest::Update()
{

}
void UITeamTest::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}