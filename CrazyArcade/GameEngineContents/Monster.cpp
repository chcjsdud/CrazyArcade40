#include "Monster.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineImageManager.h>


Monster::Monster()
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, ColMapImage_(nullptr)
	, MonsterClass_(MonsterClass::DEFAULT)
	, MonsterState_(MonsterState::WALK)
	, HP_(1)
	, Speed_(100)
{
}

Monster::~Monster()
{
}


void Monster::Start()
{
	//GameEngineLevel* Level = GetLevel();
	//ColMapImage_ = Level->GetColMapImage();
	Collision_ = CreateCollision("Monster", float4(50.0f, 50.0f), float4(0.0f, 0.0f));
	/////////////////// Test Level ///////////////////
	if (GetLevel()->GetNameCopy() == "PlayerTeamTest")
	{
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("Boss_ColMap.bmp");
	}
	/////////////////// ColMap ///////////////////
	if (GetLevel()->GetNameCopy() == "CampLevel")
	{
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("Camp_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "VillageLevel")
	{
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("Village_Col.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "CemetoryLevel")
	{
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("Cemetory_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "Monster1Level")
	{
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("MonsterStage1_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "Monster2Level")
	{
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("MonsterStage2_ColMap.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "BossLevel")
	{
		/////////////////// �������� ColMap ���� �ʿ� ///////////////////
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("Camp_ColMap.bmp");
	}
	else
		return;
}

void Monster::Update()
{
	UpdateMove();
	Die();
}

void Monster::UpdateMove()
{
	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x + 30), int(GetPosition().y)) && // �������� ����
		RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x - 30), int(GetPosition().y))) // ������ ������ �ƴ� ��
	{
		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x), int(GetPosition().y + 30))) // �ƴϰ�, �Ʒ����� �����̸� �������� ����
		{
			Dir_ = float4::LEFT;
			Renderer_->ChangeAnimation("MoveLeft");
		}

		else // �� �ƴϸ� ��������
		{
			Dir_ = float4::DOWN;
			Renderer_->ChangeAnimation("MoveDown");
		}
	}

	if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x + 30), int(GetPosition().y)) && // �������� ������ �ƴϰ�,
		RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x - 30), int(GetPosition().y))) // ������ ������ ��,
	{
		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x), int(GetPosition().y - 30))) // ������ �����̶�� ���������� ����
		{
			Dir_ = float4::RIGHT;
			Renderer_->ChangeAnimation("MoveRight");
		}

		else // �� �ƴϸ� �ö󰡶�
		{
			Dir_ = float4::UP;
			Renderer_->ChangeAnimation("MoveUp");
		}

	}

	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
	
	// 1. ���浹 
	// 2. ��ǳ���浹
}
void Monster::Render()
{
}


void Monster::Die()
{
	if (true == IsDie())
	{
		if (true == Renderer_->IsAnimationName("Die"))
		{
			if (true == Renderer_->IsEndAnimation())
			{
				Collision_->Off();
				Death();
			}
		}
	}
}

bool Monster::IsDie()
{
	if (GetHP() <= 0)
	{
		return true;
	}
	else return false;
}
