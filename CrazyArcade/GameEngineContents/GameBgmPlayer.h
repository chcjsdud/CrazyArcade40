#pragma once
#include <GameEngineBase/GameEngineSound.h>

// Ό³Έν :
class GameBgmPlayer
{
public:
	static GameBgmPlayer* BgmPlay_;
	// constrcuter destructer
	GameBgmPlayer();
	~GameBgmPlayer();

	// delete Function*
	GameBgmPlayer(const GameBgmPlayer& _Other) = delete;
	GameBgmPlayer(GameBgmPlayer&& _Other) noexcept = delete;
	GameBgmPlayer& operator=(const GameBgmPlayer& _Other) = delete;
	GameBgmPlayer& operator=(GameBgmPlayer&& _Other) noexcept = delete;

	GameEngineSoundPlayer BgmPlayer_;

protected:

private:
	
public:

	void Stop()
	{
		BgmPlayer_.Stop();
	}

	void ChangeBgm(std::string _BgmName, float _volume = 1.0f)
	{
		BgmPlayer_.Stop();
		BgmPlayer_ = GameEngineSound::SoundPlayControl(_BgmName);
	}
	
	void Destory()
	{
		if (BgmPlay_ != nullptr)
		{
			delete BgmPlay_;
		}
	}
};

