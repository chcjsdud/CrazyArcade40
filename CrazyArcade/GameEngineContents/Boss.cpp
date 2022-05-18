#include "Boss.h"
#include "Monster.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>
#include <vector>

Boss::Boss()
    : Monster()
    , StartMove_(false)
    , MoveTime_(0.0f)
    , BossState_(BossState::IDLE)
    , Player_(nullptr)
    , WaterTime_(0.0f)
    , BossIndex_(2)
    , PlayerIndex_(5)
    , SettingTime_(5.0f)
{
}

Boss::~Boss()
{
}

void Boss::Start()
{
    Monster::Start();
    SetMonsterClass(MonsterClass::BOSS);
    SetHP(15);
    SetSpeed(50);
    Renderer_ = CreateRenderer("Monster.bmp");
    GameEngineImage* Image = Renderer_->GetImage();
    Image->CutCount(10, 7);
    Renderer_->CreateAnimation("Monster.bmp", "Idle", 24, 25, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "WalkRight", 26, 27, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "WalkLeft", 40, 41, 0.2f, true);
    // Need to chk : MoveUp �̹���
    Renderer_->CreateAnimation("Monster.bmp", "WalkUp", 0, 1, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "WalkDown", 24, 25, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "Die1", 35, 36, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "Die2", 37, 38, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "TakeDamage", 28, 28, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "BubbleAttack", 29, 30, 0.2f, true); // ���ֱ�
    Renderer_->CreateAnimation("Monster.bmp", "RollAttack", 31, 34, 0.2f, true); // ������
    Renderer_->ChangeAnimation("Idle");
    Renderer_->SetPivot(float4(0, 0));
    Dir_ = float4::ZERO;

    Collision_->SetScale(float4(130.0, 150.0f));
    Collision_->SetPivot(float4(0.0f, 0.0f));

    const float MapSizeX = 603;
    const float MapSizeY = 522;
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            Area area;
            area.StartX_ = (MapSizeX / 3 * x) + 19;
            area.StartY_ = (MapSizeY / 3 * y) + 40;
            area.EndX_ = (MapSizeX / 3 * (x + 1)) + 19;
            area.EndY_ = (MapSizeY / 3 * (y + 1)) + 40;
            Areas_.push_back(area);
        }
    }

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

void Boss::Render()
{
}

void Boss::Update()
{
    WaterTime_ += GameEngineTime::GetDeltaTime();
    MoveTime_ += GameEngineTime::GetDeltaTime();
    RollTime_ += GameEngineTime::GetDeltaTime();
    UpdateState();
    UpdateMove();
    Die();
    StateUpdate();
}

void Boss::UpdateMove()
{
    SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_); // ������ �������� �����δ�.
}

void Boss::UpdateState()
{
    //if (GetHP() > 5)
    //{
		SettingTime_ = 5.0f;
        
        if (WaterTime_ > 2.0f &&
            BossState_ == BossState::BUBBLEATTACK)
        {
            SetState(BossState::IDLE);
        }

        if (RollTime_ > 10.0f &&
            BossState_ == BossState::ROLLATTACK)
        {
            Dir_ = float4::ZERO;
            SetState(BossState::IDLE);
        }
        
        if (MoveTime_ > 5.0f &&
            (BossState_ != BossState::ROLLATTACK &&
            BossState_ != BossState::BUBBLEATTACK)) // 5�ʸ��� ���Ϳ� �� ��ġ�� ���Ѵ�.
        {
            for (int i = 0; i < Areas_.size(); ++i)
            {
                Area& NewArea = Areas_[i];
                if (true == NewArea.Contains(Player_->GetPosition()))
                {
                    PlayerIndex_ = i;
                }
                if (true == NewArea.Contains(GetPosition()))
                {
                    BossIndex_ = i;
                }
            }
        }

        //// ���� ����� ��
        std::vector<GameEngineCollision*> WallCollision;
        if ((RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(-25.0f, 0.0f)) ||
            RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(25.0f, 0.0f))) &&
            GetState() != BossState::IDLE)
        {
            if (true == SameYLine())
            {
                PlayerPos_ = Player_->GetPosition(); // Player�� ��ġ�� �ľ��Ѵ�.
                if (PlayerPos_.x - GetPosition().x > 0) // �÷��̾ ������ �����ʿ� ������
                {
                    Dir_ = float4::RIGHT;
                    Direction_ = "Right";
                }
                else // �÷��̾ ������ ���ʿ� ������
                {
                    Dir_ = float4::LEFT;
                    Direction_ = "Left";
                }
                SetState(BossState::ROLLATTACK);
                RollTime_ = 0.0f;
            }
        }

        if (PlayerIndex_ != BossIndex_)
        {
            if (MoveTime_ > SettingTime_)
            {
                if (true == SameXLine()) // ���� �����ٿ� ������
                {
                    PlayerPos_ = Player_->GetPosition(); // Player�� ��ġ�� �ľ�
                    if (PlayerPos_.y - GetPosition().y > 0) // �÷��̾ ������ �Ʒ��� ������
                    {
                        Dir_ = float4::DOWN;
                        Direction_ = "Down";
                    }
                    else // �÷��̾ ������ ���� ������
                    {
                        Dir_ = float4::UP;
                        Direction_ = "Up";
                    }
                    SetState(BossState::WALK);
                }
                else if (true == SameYLine()) // ���� �����ٿ� ������
                {
                    PlayerPos_ = Player_->GetPosition(); // Player�� ��ġ�� �ľ��Ѵ�.
                    if (PlayerPos_.x - GetPosition().x > 0) // �÷��̾ ������ �����ʿ� ������
                    {
                        Dir_ = float4::RIGHT;
                        Direction_ = "Right";
                    }
                    else // �÷��̾ ������ ���ʿ� ������
                    {
                        Dir_ = float4::LEFT;
                        Direction_ = "Left";
                    }
                    SetState(BossState::WALK);
                }
                else // ���� �����ٵ� �����ٵ� �ƴϸ� ��ǳ�� ����
                {
					Dir_ = float4::ZERO;
                    WaterTime_ = 0.0f;
					SetState(BossState::BUBBLEATTACK); // ��ǳ�� ����
                }
            }
        }

        //if (PlayerIndex_ == BossIndex_)
        //{
        //    Dir_ = float4::ZERO;
        //    WaterTime_ = 0.0f;
        //    SetState(BossState::BUBBLEATTACK); // ��ǳ�� ����
        //}

    if (MoveTime_ > SettingTime_)
    {
        MoveTime_ = 0.0f;
    }
}


void Boss::SetState(BossState _BossState)
{
    BossState_ = _BossState;
    switch (BossState_)
    {
    case BossState::IDLE:
        Renderer_->ChangeAnimation("Idle");
        break;
    case BossState::WALK:
        Renderer_->ChangeAnimation("Walk" + Direction_);
        break;
    case BossState::BUBBLEATTACK:
        Renderer_->ChangeAnimation("BubbleAttack");
        break;
    case BossState::ROLLATTACK:
        Renderer_->ChangeAnimation("RollAttack");
        break;
    case BossState::TAKEDAMAGE:
        Renderer_->ChangeAnimation("TakeDamage");
        break;
    }
}

void Boss::StateUpdate()
{
    switch (BossState_)
    {
    case BossState::IDLE:
        UpdateIdle();
        break;
    case BossState::WALK:
        UpdateWalk();
        break;
    case BossState::BUBBLEATTACK:
        UpdateBubbleAttack();
        break;
    case BossState::ROLLATTACK:
        UpdateRollAttack();
        break;
    case BossState::TAKEDAMAGE:
        UpdateTakeDamage();
        break;
    case BossState::DIE:
        UpdateDie();
        break;
    }
}

void Boss::UpdateIdle()
{
}

void Boss::UpdateWalk()
{
}

void Boss::UpdateBubbleAttack()
{
}

void Boss::UpdateRollAttack()
{
}

void Boss::UpdateTakeDamage()
{
   // Monster::TakeDamage();
}

void Boss::UpdateDie()
{
}

bool Boss::SameXLine() // ������

{
    if (PlayerIndex_ < 3 && BossIndex_ < 3) 
    {
        return true;
    }

    else if (PlayerIndex_ >= 3 && BossIndex_ >= 3 &&
        PlayerIndex_ < 6 && BossIndex_ < 6)
    {
        return true;
    }

    else if (PlayerIndex_ >= 6 && BossIndex_ >= 6 &&
        PlayerIndex_ < 9 && BossIndex_ < 9)
    {
        return true;
    }

    return false;
}

bool Boss::SameYLine() // ������
{
    int Offset = PlayerIndex_ - BossIndex_;
    if (Offset < 0)
    {
        Offset = Offset * -1;
    }
    // ���� ���ο� �ִ�.
    return Offset % 3 == 0;
}