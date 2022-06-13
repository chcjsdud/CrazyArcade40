#include "Monster1.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include "Area.h"
#include "GameEngine/GameEngineCollision.h"

Monster1::Monster1()
	:Monster()
{
}

Monster1::~Monster1()
{
}

void Monster1::Start()
{
	//°¨±ÖÀÌ
	Monster::Start();
	Renderer_ = CreateRenderer("BasicMonster.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 6);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveRight", 25, 26, 0.3f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveLeft", 23, 24, 0.3f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveUp", 19, 20, 0.3f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "MoveDown", 21, 22, 0.3f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "Die", 27, 29, 0.2f, true);
	Renderer_->CreateAnimation("BasicMonster.bmp", "Start", 30, 33, 0.1f, true);
	Renderer_->ChangeAnimation("Start");
	SetSpeed(70);
	Dir_ = float4::ZERO;
	SetHP(1);

	CenterCol_->SetPivot(float4(0.0f, -18.0f));

	SpeechBubble_ = CreateRenderer("SpeechBubble1.bmp");
	GameEngineImage* SpeechBubbleImage = SpeechBubble_->GetImage();
	SpeechBubbleImage->CutCount(12, 1);
	SpeechBubble_->CreateAnimation("SpeechBubble1.bmp", "Bubble0", 0, 0, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble1.bmp", "Bubble1", 1, 1, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble1.bmp", "Bubble2", 2, 2, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble1.bmp", "Bubble3", 3, 3, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble1.bmp", "Bubble4", 4, 4, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble1.bmp", "Bubble5", 5, 5, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble1.bmp", "Bubble6", 6, 6, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble1.bmp", "Bubble7", 7, 7, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble1.bmp", "Bubble8", 8, 8, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble1.bmp", "Bubble9", 9, 9, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble1.bmp", "Bubble10", 10, 10, 0.5f, true);
	SpeechBubble_->CreateAnimation("SpeechBubble1.bmp", "Bubble11", 11, 11, 0.5f, true);
	SpeechBubble_->ChangeAnimation("Bubble11");
	SpeechBubble_->SetOrder((int)ORDER::UI);
	SpeechBubble_->SetPivot(float4(0.0f, -40.0f));
}

void Monster1::Render()
{
	if (true == GetLevel()->GetIsDebug())
	{
		Monster::Render();
	}
}

void Monster1::Update()
{
	if (true == Renderer_->IsAnimationName("Start") &&
		true == Renderer_->IsEndAnimation())
	{
		Renderer_->ChangeAnimation("MoveRight");
		Direction_ = "Right";
		Dir_ = float4::RIGHT;
	}
	else
	{
		Monster::Update();
		Speech();
	}

	SpeechTime_ += GameEngineTime::GetInst()->GetDeltaTime();
}

void Monster1::Speech()
{
	if (SpeechTime_ > 2.0f)
	{
		int RandomSpeech = (rand() % 12);
		std::string SpeechNum = std::to_string(RandomSpeech);
		SpeechBubble_->ChangeAnimation("Bubble" + SpeechNum);
		SpeechTime_ = 0.0f;
	}
}
