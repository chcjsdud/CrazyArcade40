#include "TextArea.h"
#include <GameEngine/KeyboardClass.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>


bool TextArea::caretshow_ = false;

void TextArea::SetCurCaretState(bool _Flag)
{
	caretshow_ = _Flag;
}

void TextArea::TextAreaInit(const float4& _Value, int _Len)
{
	TextAreaCollision_ = CreateCollision("TextArea", _Value);
	MaxLen_ = _Len;
}

TextArea::TextArea()
	: TextInputOK_(false)
	, curcaretpos_(0)
	, prevcaretpos_(0)
	, TextAreaCollision_(nullptr)
{
}


TextArea::~TextArea()
{
}

void TextArea::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("Chatting_Del"))
	{
		GameEngineInput::GetInst()->CreateKey("Chatting_Del", VK_BACK);
	}
}

void TextArea::Update()
{
	// 마우스와 텍스트 입력창 충돌
	if (true == TextAreaCollision_->CollisionCheck("MouseCol"))
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{

			TextInputOK_ = true;

			// 캐럿 생성
			if (false == caretshow_)
			{
				caretshow_ = true;
				CreateCaret(GameEngineWindow::GetInst().GethWnd(), NULL, 2, 14);
				ShowCaret(GameEngineWindow::GetInst().GethWnd());
				SetCaretBlinkTime(50);
				SetCaretPos(GetPosition().ix(), GetPosition().iy());
			}
		}
	}

	else
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			if (true == TextInputOK_)
			{
				// Input On
				TextInputOK_ = false;


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

		if (true == TextInputOK_)
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
	}

	// 입력중인 채팅 문자열 마지막부터 삭제
	if (true == GameEngineInput::GetInst()->IsPress("Chatting_Del"))
	{
		// 채팅 입력창 활성화 시에만 아래 처리가능
		if (true == TextInputOK_)
		{
			if (!InputText_.empty())
			{
				InputText_.pop_back();

				curcaretpos_ = static_cast<int>(lstrlen(InputText_.c_str()));
				SIZE CurTextSize;
				GetTextExtentPoint(GameEngine::BackBufferDC(), InputText_.c_str(), lstrlen(InputText_.c_str()), &CurTextSize);
				SetCaretPos(GetPosition().ix(), GetPosition().iy());
			}
		}
	}
}
void TextArea::Render()
{
	if (!InputText_.empty())
	{
		TextOut(GameEngine::BackBufferDC(), 380.0f + 10.0f, 16.0f + 475.0f, InputText_.c_str(), lstrlen(InputText_.c_str()));

		if (true == caretshow_)
		{
			curcaretpos_ = static_cast<int>(lstrlen(InputText_.c_str()));
			SIZE CurTextSize;
			GetTextExtentPoint(GameEngine::BackBufferDC(), InputText_.c_str(), lstrlen(InputText_.c_str()), &CurTextSize);
			SetCaretPos(GetPosition().ix(), GetPosition().iy());
		}
	}
}

	
void TextArea::AddText(const std::string& _Text)
{
	// 채팅 최대글자수 넘어가면 입력불가
	std::string CurText = InputText_;
	CurText += _Text;
	if (MaxLen_ <= lstrlen(CurText.c_str()))
	{
		// 입력불가
		return;
	}

	InputText_ += _Text;
}