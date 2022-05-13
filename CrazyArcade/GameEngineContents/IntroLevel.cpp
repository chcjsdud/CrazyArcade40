#include "IntroLevel.h"
#include "VideoPlayer.h"
#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineWindow.h>

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
	IntroVideo_->SetInfo("intro_frame_", 0, 245, 10.0f);
	
	//BgmPlayer = GameEngineSound::SoundPlayControl("00.mp3");
}

void IntroLevel::Update()
{
	if (true == IntroVideo_->IsVideoFinished())
	{
		//BgmPlayer.Stop();
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}
}