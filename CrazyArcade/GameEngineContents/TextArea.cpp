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
	, MaxLen_(0)
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
	SetTextColor(GameEngine::BackBufferDC(), RGB(0, 0, 0));
	// 마우스와 텍스트 입력창 충돌
	
	if (true == GameEngineInput::GetInst()->IsDown("LeftMouse")
		&& true == TextAreaCollision_->CollisionCheck("MouseCol"))
	{
		TextInputOK_ = true;
		KeyboardClass::GetInst().DeleteCharBuffer();
			// 캐럿 생성
			if (false == caretshow_)
			{
				caretshow_ = true;
				CreateCaret(GameEngineWindow::GetInst().GethWnd(), NULL, 2, 14);
				ShowCaret(GameEngineWindow::GetInst().GethWnd());
				SetCaretBlinkTime(50);
				SetCaretPos(GetPosition().ix() - 56, GetPosition().iy() - 6);
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
					SetCaretBlinkTime(20);
					HideCaret(GameEngineWindow::GetInst().GethWnd());
					DestroyCaret();
				}
			}
		}

		if (true == TextInputOK_)
		{
			if (false == KeyboardClass::GetInst().CharBufferIsEmpty())
			{
				while (!KeyboardClass::GetInst().CharBufferIsEmpty())
				{
					std::string SetStr = "";
					unsigned char ReadChar = KeyboardClass::GetInst().ReadChar();
					SetStr += ReadChar;

					AddText(SetStr);
				}
			}		
		}
		
	}

	// 입력중인 채팅 문자열 마지막부터 삭제
	if (true == GameEngineInput::GetInst()->IsDown("Chatting_Del"))
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
				SetCaretPos(GetPosition().ix() - 56  + CurTextSize.cx, GetPosition().iy() - 6);
			}
		}
	}
	
	else
	{
		
	}
}
void TextArea::Render()
{
	if (!InputText_.empty())
	{
		SetBkMode(GameEngine::BackBufferDC(), TRANSPARENT);
		TextOut(GameEngine::BackBufferDC(), GetPosition().ix() - 56, GetPosition().iy() - 6, InputText_.c_str(), lstrlen(InputText_.c_str()));

		if (true == caretshow_)
		{
			curcaretpos_ = static_cast<int>(lstrlen(InputText_.c_str()));
			SIZE CurTextSize;
			GetTextExtentPoint(GameEngine::BackBufferDC(), InputText_.c_str(), lstrlen(InputText_.c_str()), &CurTextSize);
			SetCaretPos(GetPosition().ix() - 56 + CurTextSize.cx, GetPosition().iy() - 6);
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