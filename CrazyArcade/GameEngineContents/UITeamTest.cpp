#include "UITeamTest.h"
#include "StartButton.h"
#include "CreateRoomBackGround.h"
#include "RoomBackGround.h"
#include "RoomCharaterSelectUI.h"
#include "LoginBackGround.h"
#include "Mouse.h"
#include "ContentsEnum.h"
#include "PlayBackGround.h"
#include "TimeUI.h"
#include "StartIntroUI.h"
#include "ChoiceMap.h"

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
	/*CreateActor<PlayBackGround>((int)UIType::BackGround);
	CreateActor<StartIntroUI>((int)UIType::PopUp);
	CreateActor<TimeUI>((int)UIType::Time);*/

	// �� ȭ��
	/*CreateActor<RoomBackGround>((int)UIType::PopUp);
	CreateActor<StartButton>((int)UIType::PopUpButton);
	CreateActor<RoomCharaterSelectUI>((int)UIType::PopUpButton);
	CreateActor<Mouse>((int)UIType::Mouse);*/

	CreateActor<ChoiceMap>((int)UIType::PopUp);
	CreateActor<Mouse>((int)UIType::Mouse);
}
void UITeamTest::Update()
{

}
void UITeamTest::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}