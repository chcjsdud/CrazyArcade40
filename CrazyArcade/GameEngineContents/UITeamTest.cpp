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
	//�α��� + �游���ȭ��
	/*CreateActor<LoginBackGround>((int)UIType::BackGround);
	CreateActor<CreateRoomBackGround>((int)UIType::PopUp);
	CreateActor<Mouse>((int)UIType::Mouse);*/

	//�����÷���ȭ��
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