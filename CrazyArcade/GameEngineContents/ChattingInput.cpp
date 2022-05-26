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
	// �Ҹ�� �Է����� ä�� ����
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
	// ���콺�� ä�� �Է�â �浹
	// ChattingInputOK_ On
	if (false != chattingInputBoxCollision_->CollisionCheck("MouseCol"))
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			if (false == ChattingInputOK_)
			{
				// Input On
				ChattingInputOK_ = true;

				// ���õǾ����Ƿ� �̹��� ����
				//chattingInputBoxSpriteRender_->SetImage("LeftMouse");
				//float4 ImageHarfSize = chattingInputBoxSpriteRender_->GetImageSize().halffloat4();
				//chattingInputBoxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 650.f));
				//chattingInputBoxSpriteRender_->SetRenderSize(float4(1000.f, 32.f));

				// ĳ�� ����
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
		// ä�� �Է�â�� �浹�� �ƴѰ�� ���콺 ���ʹ�ư Ŭ���� �Է¸�� ����
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			if (true == ChattingInputOK_)
			{
				// Input On
				ChattingInputOK_ = false;


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
	}
	// Ű���� Ű�Է� üũ �� ���ڿ� ����
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
	else // ���� �Է»��°� �ƴѿ��߿��� Ű���� �Է��� �ִٸ� charbuffer�� Ŭ�����Ѵ�.
	{
		KeyboardClass::GetInst().DeleteCharBuffer();
	}

	// �Է����� ä�� ���ڿ��� ä�� �̷����� ������(ä���Է¿Ϸ�)
	if (true == GameEngineInput::GetInst()->IsDown("Chatting_End"))
	{
		// ä�� �Է�â Ȱ��ȭ �ÿ��� �Ʒ� ó������
		if (true == ChattingInputOK_)
		{
			// ���ڿ��� �������� �̷¿� ������ִ�.
			if (!InputText_.empty())
			{
				// ���� �Էµ� ���ڿ��� ChattingHistory�� �Ѱ��ش�.
				ChattingHistory::ChattingHistoryAdd(InputText_);
				InputText_.clear();

				// ĳ����ġ �ʱ�ȭ
				SetCaretPos(180 + 10, 510 + 16);
			}
		}
	}

	// �Է����� ä�� ���ڿ� ���������� ����
	if (true == GameEngineInput::GetInst()->IsDown("Chatting_Del"))
	{
		// ä�� �Է�â Ȱ��ȭ �ÿ��� �Ʒ� ó������
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
	// ä�� �ִ���ڼ� �Ѿ�� �ԷºҰ�
	std::string CurText = InputText_;
	CurText += _Text;
	if (MAX_INPUTCOUNT <= lstrlen(CurText.c_str()))
	{
		// �ԷºҰ�
		return;
	}

	InputText_ += _Text;
}