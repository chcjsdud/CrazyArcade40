#include "Mouse.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineCollision.h>

Mouse::Mouse()
	:MouseCol_(nullptr),
	MouseRenderer_(nullptr)
	, SoundPlay_(true)
{
}

Mouse::~Mouse()
{
}

void Mouse::Start()
{


	GetCurPos();
	SetPosition({ CurPos_.x,CurPos_.y });
    MouseRenderer_ = CreateRenderer("Mouse_1.bmp");
	MouseCol_ = CreateCollision("MouseCol", { 16,20 }, { -8,-10 });
	MouseCol_->CameraEffectOff();
	if (false == GameEngineInput::GetInst()->IsKey("LeftMouse"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftMouse", VK_LBUTTON);
		GameEngineInput::GetInst()->CreateKey("RightMouse", VK_RBUTTON);
	}
}

void Mouse::Update()
{
	GetCurPos();
	SetPosition({ CurPos_.x,CurPos_.y });
	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		MouseRenderer_->SetImage("Mouse_2.bmp");
	}
	else
	{
		MouseRenderer_->SetImage("Mouse_1.bmp");
	}

	if (MouseCol_->CollisionCheck("StartButton")
		&& SoundPlay_ == true)
	{
		GameEngineSound::SoundPlayOneShot("pt_in_rect.mp3");
		SoundPlay_ = false;
	}
	else if (MouseCol_->CollisionCheck("MapButton")
		&& SoundPlay_ == true)
	{
		GameEngineSound::SoundPlayOneShot("pt_in_rect.mp3");
		SoundPlay_ = false;
	}
	else if (MouseCol_->CollisionCheck("CharSelecter")
		&& SoundPlay_ == true)
	{
		GameEngineSound::SoundPlayOneShot("pt_in_rect.mp3");
		SoundPlay_ = false;
	}
	else if (MouseCol_->CollisionCheck("NormalModeBtn")
		&& SoundPlay_ == true)
	{
		GameEngineSound::SoundPlayOneShot("pt_in_rect.mp3");
		SoundPlay_ = false;
	}
	else if (MouseCol_->CollisionCheck("MonsterModeBtn")
		&& SoundPlay_ == true)
	{
		GameEngineSound::SoundPlayOneShot("pt_in_rect.mp3");
		SoundPlay_ = false;
	}
	else if (MouseCol_->CollisionCheck("ConfirmBtn")
		&& SoundPlay_ == true)
	{
		GameEngineSound::SoundPlayOneShot("pt_in_rect.mp3");
		SoundPlay_ = false;
	}
	else if (MouseCol_->CollisionCheck("CancelBtn")
		&& SoundPlay_ == true)
	{
		GameEngineSound::SoundPlayOneShot("pt_in_rect.mp3");
		SoundPlay_ = false;
	}
	else if (MouseCol_->CollisionCheck("Back")
		&& SoundPlay_ == true)
	{
		GameEngineSound::SoundPlayOneShot("pt_in_rect.mp3");
		SoundPlay_ = false;
	}
	else if (MouseCol_->CollisionCheck("Exit")
		&& SoundPlay_ == true)
	{
		GameEngineSound::SoundPlayOneShot("pt_in_rect.mp3");
		SoundPlay_ = false;
	}

	else if (false == MouseCol_->CollisionCheck("StartButton")
	&& false == MouseCol_->CollisionCheck("MapButton")
	&& false == MouseCol_->CollisionCheck("CharSelecter")
	&& false == MouseCol_->CollisionCheck("NormalModeBtn")
	&& false == MouseCol_->CollisionCheck("MonsterModeBtn")
	&& false == MouseCol_->CollisionCheck("ConfirmBtn")
	&& false == MouseCol_->CollisionCheck("CancelBtn")
	&& false == MouseCol_->CollisionCheck("Back")
	&& false == MouseCol_->CollisionCheck("Exit"))
	{
		SoundPlay_ = true;
	}
}