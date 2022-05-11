#include"TitleBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
TitleBackGround::TitleBackGround()
: TitleBackGroundRender_(nullptr)
{

}
TitleBackGround::~TitleBackGround()
{

}
void TitleBackGround::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half() });
}
void TitleBackGround::Render()
{

}
void TitleBackGround::Update()
{

}