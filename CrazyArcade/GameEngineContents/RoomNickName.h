#pragma once
#include <GameEngine/GameEngineActor.h>
// �濡�� �г����� ���̰� �ϴ� ����
class RoomNickName : public GameEngineActor
{
public:
	//construcuter destructer
	RoomNickName();
	~RoomNickName();

	//delete Function
	RoomNickName(const RoomNickName& _Other) = delete;
	RoomNickName(RoomNickName&& _Other) noexcept = delete;
	RoomNickName& operator=(const RoomNickName& _Other) = delete;
	RoomNickName& operator=(RoomNickName&& _Other) noexcept = delete;

protected:

private:
	void Start() override {};
	void Update() override {};
	void Render() override;
};

