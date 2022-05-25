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
	// ���콺�� �ؽ�Ʈ �Է�â �浹
	if (true == TextAreaCollision_->CollisionCheck("MouseCol"))
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{

			TextInputOK_ = true;

			// ĳ�� ����
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


				// ĳ�� ����
				if (true == caretshow_)
				{
					caretshow_ = false;

					// ĳ�� �ݳ�
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
		else // ���� �Է»��°� �ƴѿ��߿��� Ű���� �Է��� �ִٸ� charbuffer�� Ŭ�����Ѵ�.
		{
			KeyboardClass::GetInst().DeleteCharBuffer();
		}
	}

	// �Է����� ä�� ���ڿ� ���������� ����
	if (true == GameEngineInput::GetInst()->IsPress("Chatting_Del"))
	{
		// ä�� �Է�â Ȱ��ȭ �ÿ��� �Ʒ� ó������
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
	// ä�� �ִ���ڼ� �Ѿ�� �ԷºҰ�
	std::string CurText = InputText_;
	CurText += _Text;
	if (MaxLen_ <= lstrlen(CurText.c_str()))
	{
		// �ԷºҰ�
		return;
	}

	InputText_ += _Text;
}