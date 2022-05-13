#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

class VideoPlayer;
class IntroLevel : public GameEngineLevel
{
public:
	IntroLevel();
	~IntroLevel();

	IntroLevel(const IntroLevel& _Other) = delete;
	IntroLevel(IntroLevel&& _Other) noexcept = delete;
	IntroLevel& operator=(const IntroLevel& _Other) = delete;
	IntroLevel& operator=(IntroLevel&& _Other) noexcept = delete;


protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;

private:
	float Time;
	VideoPlayer* IntroVideo_;
	GameEngineSoundPlayer BgmPlayer;
};

