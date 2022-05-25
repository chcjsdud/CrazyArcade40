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
	ChattingHistory(); // default constructer 디폴트 생성자
	~ChattingHistory(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	ChattingHistory(const ChattingHistory& _other) = delete; // default Copy constructer 디폴트 복사생성자
	ChattingHistory(ChattingHistory&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	ChattingHistory& operator=(const ChattingHistory& _other) = delete; // default Copy operator 디폴트 대입 연산자
	ChattingHistory& operator=(const ChattingHistory&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel);
};