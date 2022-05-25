#pragma once
#include <GameEngine/GameEngineActor.h>

#define MAX_CHATTINGHISTORY 13


class GameEngineRenderer;
class ChattingHistory : public GameEngineActor
{
private:
	static std::list<std::string> historychatt_;
	static std::string hostname_;

public:
	static void ChattingHistoryAdd(const std::string& _ChattingText);
	static void CurHostName(const std::string& _HostName);

private:
	GameEngineRenderer* chattingHisBoxSpriteRender_;

public:
	ChattingHistory(); // default constructer ����Ʈ ������
	~ChattingHistory(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	ChattingHistory(const ChattingHistory& _other) = delete; // default Copy constructer ����Ʈ ���������
	ChattingHistory(ChattingHistory&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	ChattingHistory& operator=(const ChattingHistory& _other) = delete; // default Copy operator ����Ʈ ���� ������
	ChattingHistory& operator=(const ChattingHistory&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel);
};