#pragma once
#include <GameEngine/GameEngineActor.h>
// �濡�� �г����� ���̰� �ϴ� ����
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

