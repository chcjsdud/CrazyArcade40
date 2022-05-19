#include "Monster.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineImageManager.h>
#include <vector>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineContents/MapGameObject.h>

int Monster::TTL_MONSTER_COUNT = 0;

Monster::Monster()
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, ColMapImage_(nullptr)
	, MonsterClass_(MonsterClass::DEFAULT)
	, MonsterState_(MonsterState::WALK)
	, HP_(1)
	, Speed_(100)
{
	TTL_MONSTER_COUNT++;
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
		ColMapImage_ = GameEngineImageManager::GetInst()->Find("Boss_ColMap.bmp");
	}
	else
		return;
}

void Monster::Update()
{
	UpdateMove();
	TakeDamage();
	Die();
}

void Monster::UpdateMove()
{
	if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x - 20), int(GetPosition().y - 20)) &&// 왼쪽이 검정이 아니고
		true != Renderer_->IsAnimationName("MoveRight") && // 현재 오른쪽이나
		true != Renderer_->IsAnimationName("MoveDown")) // 아래로 가고 있는 상황이 아니라면 오른쪽으로 가라
	{
		Dir_ = float4::LEFT;
		Renderer_->ChangeAnimation("MoveLeft");
	}

	if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y-20)) &&// 오른쪽이 검정이 아니고
		true != Renderer_->IsAnimationName("MoveLeft") && // 현재 왼쪽이나
		true != Renderer_->IsAnimationName("MoveUp")) // 위로 가고 있는 상황이 아니라면 오른쪽으로 가라
	{
		Dir_ = float4::RIGHT;
		Renderer_->ChangeAnimation("MoveRight"); 
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y)) && // 오른쪽이 검정
		RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x - 20), int(GetPosition().y))) // 왼쪽이 검정이 아닐 때
	{
		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x), int(GetPosition().y + 20))) // 아래쪽이 검정이면 왼쪽으로 가라
		{
			Dir_ = float4::LEFT;
			Renderer_->ChangeAnimation("MoveLeft");
		}

		else // 다 아니면 내려가라
		{
			Dir_ = float4::DOWN;
			Renderer_->ChangeAnimation("MoveDown");
		}
	}

	if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y)) && // 오른쪽이 검정이 아니고,
		RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x - 20), int(GetPosition().y))) // 왼쪽이 검정일 때,
	{
		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x), int(GetPosition().y - 20))) // 위쪽이 검정이라면 오른쪽으로 가라
		{
			Dir_ = float4::RIGHT;
			Renderer_->ChangeAnimation("MoveRight");
		}

		else // 다 아니면 올라가라
		{
			Dir_ = float4::UP;
			Renderer_->ChangeAnimation("MoveUp");
		}

	}

	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
	
	
	// 1. 블럭충돌 
}
void Monster::TakeDamage()
{
	if (GetAttTime_ > 2.0) // 2초 안에 다시 맞으면 DMG를 입지 않는다. (Need to chk : TIME)
	{
		std::vector<GameEngineCollision*> BubbleCol;
		if (Collision_->CollisionResult("WaveCol", BubbleCol, CollisionType::Rect, CollisionType::Rect))
		{
			for (GameEngineCollision* Collision : BubbleCol)
			{
				GameEngineActor* ColActor = Collision->GetActor();
				MapGameObject* Bubble = dynamic_cast<MapGameObject*>(ColActor);

				if (Bubble != nullptr)
				{
					SetHP(GetHp() - 1);
					GetAttTime_ = 0.0f;
				}
			}
		}
	}
}
void Monster::Render()
{
}

void Monster::Die()
{
	if (true == IsDie()) // HP가 0이거나 0보다 작으면
	{
		if (true == Renderer_->IsAnimationName("Die")) // 죽는 애니메이션 시작
		{
			if (true == Renderer_->IsEndAnimation()) // 애니메이션이 끝나면
			{
				Collision_->Off(); // 이미지가 사라진다.
				Death();
				TTL_MONSTER_COUNT--; // total 몬스터 수가 줄어든다.
				if (TTL_MONSTER_COUNT == 1) // 만약 몬스터가 한마리 남으면
				{
					SetSpeed(120); // 속도가 빨라져라
				}
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
