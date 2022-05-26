#include "ChattingInput.h"
#include "ChattingHistory.h"
#include "ContentsEnum.h"
#include <GameEngine/KeyboardClass.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

bool ChattingInput::caretshow_ = false;

void ChattingInput::SetCurCaretState(bool _Flag)
{
	caretshow_ = _Flag;
}


ChattingInput::ChattingInput() :
	ChattingInputOK_(false),
	curcaretpos_(0),
	prevcaretpos_(0),
	chattingInputBoxSpriteRender_(nullptr),
	chattingInputBoxCollision_(nullptr)
{

}

ChattingInput::~ChattingInput()
{
	// 소멸시 입력중인 채팅 삭제
	if (!InputText_.empty())
	{
		InputText_.clear();
	}
}

ChattingInput::ChattingInput(ChattingInput&& _other) noexcept :
	ChattingInputOK_(_other.ChattingInputOK_),
	curcaretpos_(_other.curcaretpos_),
	prevcaretpos_(_other.prevcaretpos_),
	chattingInputBoxSpriteRender_(_other.chattingInputBoxSpriteRender_),
	chattingInputBoxCollision_(_other.chattingInputBoxCollision_)
{

}

void ChattingInput::Start()
{

	chattingInputBoxCollision_ = CreateCollision("Chatting", {240.0f, 23.0f});
	chattingInputBoxCollision_->SetPivot(float4(270.0f + 10.0f, 16.0f + 518.0f));

	if (false == GameEngineInput::GetInst()->IsKey("Chatting_End"))
	{
		GameEngineInput::GetInst()->CreateKey("Chatting_End", VK_RETURN);
	}

	if (false == GameEngineInput::GetInst()->IsKey("Chatting_Del"))
	{
		GameEngineInput::GetInst()->CreateKey("Chatting_Del", VK_BACK);
	}
}


void ChattingInput::Update()
{
	SetTextColor(GameEngine::BackBufferDC(), RGB(0, 0, 0));
	SetBkMode(GameEngine::BackBufferDC(), TRANSPARENT);
	// 마우스와 채팅 입력창 충돌
	// ChattingInputOK_ On
	if (false != chattingInputBoxCollision_->CollisionCheck("MouseCol"))
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			if (false == ChattingInputOK_)
			{
				// Input On
				ChattingInputOK_ = true;

				// 선택되었으므로 이미지 변경
				//chattingInputBoxSpriteRender_->SetImage("LeftMouse");
				//float4 ImageHarfSize = chattingInputBoxSpriteRender_->GetImageSize().halffloat4();
				//chattingInputBoxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 650.f));
				//chattingInputBoxSpriteRender_->SetRenderSize(float4(1000.f, 32.f));

				// 캐럿 생성
				if (false == caretshow_)
				{
					caretshow_ = true;
					CreateCaret(GameEngineWindow::GetInst().GethWnd(), NULL, 2, 14);
					ShowCaret(GameEngineWindow::GetInst().GethWnd());
					SetCaretBlinkTime(50);
					SetCaretPos(180 + 10, 510 + 16);
				}
			}
		}
	}
	else
	{
		// 채팅 입력창과 충돌이 아닌경우 마우스 왼쪽버튼 클릭시 입력모드 해제
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			if (true == ChattingInputOK_)
			{
				// Input On
				ChattingInputOK_ = false;


				// 캐럿 생성
				if (true == caretshow_)
				{
					caretshow_ = false;

					// 캐럿 반납
					SetCaretBlinkTime(500);
					HideCaret(GameEngineWindow::GetInst().GethWnd());
					DestroyCaret();
				}
			}
		}
	}
	// 키보드 키입력 체크 및 문자열 편집
	if (true == ChattingInputOK_)
	{
		while (!KeyboardClass::GetInst().CharBufferIsEmpty())
		{
			std::string SetStr = "";
			unsigned char ReadChar = KeyboardClass::GetInst().ReadChar();
			SetStr += ReadChar;

			AddText(SetStr);
		}
	}
	else // 현재 입력상태가 아닌와중에도 키보드 입력이 있다면 charbuffer를 클리어한다.
	{
		KeyboardClass::GetInst().DeleteCharBuffer();
	}

	// 입력중인 채팅 문자열을 채팅 이력으로 보내기(채팅입력완료)
	if (true == GameEngineInput::GetInst()->IsDown("Chatting_End"))
	{
		// 채팅 입력창 활성화 시에만 아래 처리가능
		if (true == ChattingInputOK_)
		{
			// 문자열이 있을때만 이력에 남길수있다.
			if (!InputText_.empty())
			{
				// 현재 입력된 문자열을 ChattingHistory로 넘겨준다.
				ChattingHistory::ChattingHistoryAdd(InputText_);
				InputText_.clear();

				// 캐럿위치 초기화
				SetCaretPos(180 + 10, 510 + 16);
			}
		}
	}

	// 입력중인 채팅 문자열 마지막부터 삭제
	if (true == GameEngineInput::GetInst()->IsDown("Chatting_Del"))
	{
		// 채팅 입력창 활성화 시에만 아래 처리가능
		if (true == ChattingInputOK_)
		{
			if (!InputText_.empty())
			{
				InputText_.pop_back();

				curcaretpos_ = static_cast<int>(lstrlen(InputText_.c_str()));
				SIZE CurTextSize;
				GetTextExtentPoint(GameEngine::BackBufferDC(), InputText_.c_str(), lstrlen(InputText_.c_str()), &CurTextSize);
				SetCaretPos(180 + 10 + CurTextSize.cx, 510 + 16);
			}
		}
	}
	
}



void ChattingInput::Render()
{
	if (false == GetLevel()->FindActor("ChoiceMap")->IsUpdate())
	{
		if (!InputText_.empty())
		{
			TextOut(GameEngine::BackBufferDC(), 180 + 10, 16 + 510, InputText_.c_str(), lstrlen(InputText_.c_str()));

			if (true == caretshow_)
			{
				curcaretpos_ = static_cast<int>(lstrlen(InputText_.c_str()));
				SIZE CurTextSize;
				GetTextExtentPoint(GameEngine::BackBufferDC(), InputText_.c_str(), lstrlen(InputText_.c_str()), &CurTextSize);
				SetCaretPos(180 + 10 + CurTextSize.cx, 510 + 16);
			}
		}
	}
}

void ChattingInput::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (false == InputText_.empty())
	{
		InputText_.clear();
	}
}

void ChattingInput::AddText(const std::string& _Text)
{
	// 채팅 최대글자수 넘어가면 입력불가
	std::string CurText = InputText_;
	CurText += _Text;
	if (MAX_INPUTCOUNT <= lstrlen(CurText.c_str()))
	{
		// 입력불가
		return;
	}

	InputText_ += _Text;
}