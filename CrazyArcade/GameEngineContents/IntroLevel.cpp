#include "IntroLevel.h"
#include "VideoPlayer.h"
#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

IntroLevel::IntroLevel()
	:IntroVideo_(nullptr)
{
}

IntroLevel::~IntroLevel()
{
}


void IntroLevel::Loading()
{

}

void IntroLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	IntroVideo_ = CreateActor<VideoPlayer>();
	IntroVideo_->SetInfo("intro_frame_", 0, 245, 15.0f);
	
	GameEngineSound::SoundPlayOneShot("IntroBGM.mp3");

	if (false == GameEngineInput::GetInst()->IsKey("ChangeLoginLevel"))
	{
		GameEngineInput::GetInst()->CreateKey("ChangeLoginLevel", VK_RETURN);
	}
}

void IntroLevel::Update()
{
	if (true == IntroVideo_->IsVideoFinished())
	{
		//BgmPlayer.Stop();
		GameEngine::GetInst().ChangeLevel("LoginLevel");
	}

	if (true == GameEngineInput::GetInst()->IsUp("ChangeLoginLevel"))
	{
		GameEngine::GetInst().ChangeLevel("LoginLevel");
	}
}