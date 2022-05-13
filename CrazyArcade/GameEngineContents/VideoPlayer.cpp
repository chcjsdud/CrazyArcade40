#include "VideoPlayer.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

VideoPlayer::VideoPlayer()
	: Name_("")
	, StartFrame_(0)
	, EndFrame_(0)
	, Interval_(0)
	, Time_(0)
	, ElapsedTime_(0)
	, VideoFinished_(0)
{
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::SetInfo(std::string _Name, int _StartFrame, int _EndFrame, float _Time)
{
	Name_ = _Name;
	StartFrame_ = _StartFrame;
	EndFrame_ = _EndFrame;
	Time_ = _Time;
	Interval_ = Time_ / (EndFrame_ - StartFrame_ + 1);
	ElapsedTime_ = 0;
	VideoFinished_ = false;

	for (int Frame = StartFrame_; Frame <= EndFrame_; Frame++)
	{
		std::string ImageName = Name_ + std::to_string(Frame) + ".bmp";
		GameEngineRenderer* VideoFrameRenderer = CreateRenderer(ImageName);
		VideoFrameRenderer->SetScale(float4(0, 0));
		VideoFrameRenderers_.push_back(VideoFrameRenderer);
	}
}

void VideoPlayer::Start()
{
	//
	SetPosition(GameEngineWindow::GetScale().Half());
}

void VideoPlayer::Update()
{
	ElapsedTime_ += GameEngineTime::GetDeltaTime();
	int CurrentFrame = static_cast<int>(ElapsedTime_ / Interval_);

	if (CurrentFrame < VideoFrameRenderers_.size())
	{
		for (GameEngineRenderer* VideoFrameRenderer : VideoFrameRenderers_) 
		{
			VideoFrameRenderer->SetScale(float4(0, 0));
		}
		VideoFrameRenderers_[CurrentFrame]->SetImageScale();
	}
	else
	{
		VideoFinished_ = true;
	}
}

void VideoPlayer::Render()
{
}