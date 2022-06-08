#pragma once
#include <GameEngine/GameEngineActor.h>
// 방에서 닉네임이 보이게 하는 액터
class PlayNickName : public GameEngineActor
{
public:
	//construcuter destructer
	PlayNickName();
	~PlayNickName();

	//delete Function
	PlayNickName(const PlayNickName& _Other) = delete;
	PlayNickName(PlayNickName&& _Other) noexcept = delete;
	PlayNickName& operator=(const PlayNickName& _Other) = delete;
	PlayNickName& operator=(PlayNickName&& _Other) noexcept = delete;

protected:

private:
	void Start() override {};
	void Update() override {};
	void Render() override;
};

