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
    , PlayerIndex_(5)
    , SettingTime_(5.0f)
    , RollTime_(0.0f)
{
}

Boss::~Boss()
{
}

void Boss::Start()
{
    AreaHeight_ = 3;
    AreaWidth_ = 3;
    Monster::Start();

    Renderer_ = CreateRenderer("Monster.bmp");
    GameEngineImage* Image = Renderer_->GetImage();
    Image->CutCount(10, 7);
    Renderer_->CreateAnimation("Monster.bmp", "Idle", 24, 25, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "WalkRight", 26, 27, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "WalkLeft", 40, 41, 0.2f, true);
    // Need to chk : MoveUp 이미지
    Renderer_->CreateAnimation("Monster.bmp", "WalkUp", 0, 1, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "WalkDown", 24, 25, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "Die1", 35, 36, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "Die2", 37, 38, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "TakeDamage", 28, 28, 0.2f, true);
    Renderer_->CreateAnimation("Monster.bmp", "BubbleAttack", 29, 30, 0.2f, true); // 물주기
    Renderer_->CreateAnimation("Monster.bmp", "RollAttack", 31, 34, 0.2f, true); // 구르기
    Renderer_->ChangeAnimation("Idle");
    Dir_ = float4::ZERO;
    CenterCol_->SetScale(float4(130.0, 150.0f));
    CenterCol_->SetPivot(float4(0.0f, -50.0f));

    Index_ = 3;
    SetMonsterClass(MonsterClass::BOSS);
    SetHP(150);
    SetSpeed(50); // Need to chk : Speed
}

void Boss::Render()
{
}

void Boss::Update()
{
    //UpdateDirection();
    //SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);

    /// 연습코드

    WaterTime_ += GameEngineTime::GetDeltaTime();
    MoveTime_ += GameEngineTime::GetDeltaTime();
    RollTime_ += GameEngineTime::GetDeltaTime();

    // TODO  주석 풀기
    UpdateState();
    UpdateMove();
    Die();
    StateUpdate();
}

void Boss::UpdateMove()
{
    SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_); // 지정한 방향으로 움직인다.
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
            BossState_ != BossState::BUBBLEATTACK)) // 5초마다 몬스터와 내 위치를 비교한다.
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
                    Index_ = i;
                }
            }
        }

        //// 벽에 닿았을 때
        std::vector<GameEngineCollision*> WallCollision;
        if ((RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(-25.0f, 0.0f)) ||
            RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(25.0f, 0.0f))) &&
            GetState() != BossState::IDLE)
        {
            if (true == SameYLine())
            {
                PlayerPos_ = Player_->GetPosition(); // Player의 위치를 파악한다.
                if (PlayerPos_.x - GetPosition().x > 0) // 플레이어가 나보다 오른쪽에 있으면
                {
                    Dir_ = float4::RIGHT;
                    Direction_ = "Right";
                }
                else // 플레이어가 나보다 왼쪽에 있으면
                {
                    Dir_ = float4::LEFT;
                    Direction_ = "Left";
                }
                SetState(BossState::ROLLATTACK);
                RollTime_ = 0.0f;
            }
        }

        if (PlayerIndex_ != Index_)
        {
            if (MoveTime_ > SettingTime_)
            {
                if (true == SameXLine()) // 같은 세로줄에 있으면
                {
                    PlayerPos_ = Player_->GetPosition(); // Player의 위치를 파악
                    if (PlayerPos_.y - GetPosition().y > 0) // 플레이어가 나보다 아래에 있으면
                    {
                        Dir_ = float4::DOWN;
                        Direction_ = "Down";
                    }
                    else // 플레이어가 나보다 위에 있으면
                    {
                        Dir_ = float4::UP;
                        Direction_ = "Up";
                    }
                    SetState(BossState::WALK);
                }
                else if (true == SameYLine()) // 같은 가로줄에 있으면
                {
                    PlayerPos_ = Player_->GetPosition(); // Player의 위치를 파악한다.
                    if (PlayerPos_.x - GetPosition().x > 0) // 플레이어가 나보다 오른쪽에 있으면
                    {
                        Dir_ = float4::RIGHT;
                        Direction_ = "Right";
                    }
                    else // 플레이어가 나보다 왼쪽에 있으면
                    {
                        Dir_ = float4::LEFT;
                        Direction_ = "Left";
                    }
                    SetState(BossState::WALK);
                }
                else // 같은 세로줄도 가로줄도 아니면 물풍선 공격
                {
					Dir_ = float4::ZERO;
                    WaterTime_ = 0.0f;
					SetState(BossState::BUBBLEATTACK); // 물풍선 공격
                }
            }
        }

        //if (PlayerIndex_ == BossIndex_)
        //{
        //    Dir_ = float4::ZERO;
        //    WaterTime_ = 0.0f;
        //    SetState(BossState::BUBBLEATTACK); // 물풍선 공격
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

bool Boss::SameXLine() // 세로줄

{
    if (PlayerIndex_ < 3 && Index_ < 3) 
    {
        return true;
    }

    else if (PlayerIndex_ >= 3 && Index_ >= 3 &&
        PlayerIndex_ < 6 && Index_ < 6)
    {
        return true;
    }

    else if (PlayerIndex_ >= 6 && Index_ >= 6 &&
        PlayerIndex_ < 9 && Index_ < 9)
    {
        return true;
    }

    return false;
}

bool Boss::SameYLine() // 가로줄
{
    int Offset = PlayerIndex_ - Index_;
    if (Offset < 0)
    {
        Offset = Offset * -1;
    }
    // 같은 라인에 있다.
    return Offset % 3 == 0;
}