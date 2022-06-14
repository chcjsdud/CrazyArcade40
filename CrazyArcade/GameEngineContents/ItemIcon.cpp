#include "ItemIcon.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "GlobalUIName.h"
#include <GameEngine/GameEngineRenderer.h>

ItemIcon::ItemIcon() 
	: ItemIconBox_(nullptr)
	, ItemIcon_1P_(nullptr)
	, ItemIcon_2P_(nullptr)
{
}

ItemIcon::~ItemIcon() 
{
}

void ItemIcon::Start()
{
	
	ItemIconBox_ = CreateRenderer(static_cast<int>(UIType::PlayResultUI));
	ItemIcon_1P_ = CreateRenderer(static_cast<int>(UIType::PlayResultUI));
	ItemIcon_2P_ = CreateRenderer(static_cast<int>(UIType::PlayResultUI));

	ItemIcon_1P_->Off();
	ItemIcon_2P_->Off();
}

void ItemIcon::Update()
{
	ChangeImage();
}

void ItemIcon::LevelChangeStart(GameEngineLevel* PrevLevel)
{
	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		SetPosition({ 719, 510 });
		ItemIconBox_->SetImage("Item_2P.bmp");
		ItemIcon_1P_->On();
		ItemIcon_2P_->On();
		ItemIcon_1P_->SetImage("EmptyIcon.bmp");
		ItemIcon_1P_->SetPivot({-36,7});
		ItemIcon_2P_->SetImage("EmptyIcon.bmp");
		ItemIcon_2P_->SetPivot({ 30,7 });

	
	}
	else
	{
		SetPosition({ 690, 510 });
		ItemIconBox_->SetImage("Item_1P.bmp");
		
		ItemIcon_1P_->On();
		ItemIcon_2P_->Off();
		ItemIcon_1P_->SetPivot({ 0,0 });
		ItemIcon_1P_->SetImage("EmptyIcon.bmp");
	}
}

void ItemIcon::ChangeImage()
{

	ItemType Player1pItem = Player::MainPlayer_1->GetCurItem();

	switch (Player1pItem)
	{
	case ItemType::Max:
		ItemIcon_1P_->SetImage("EmptyIcon.bmp");
		break;
	case ItemType::Niddle:
		ItemIcon_1P_->SetImage("NiddleIcon.bmp");
		break;
	case ItemType::Shield:
		ItemIcon_1P_->SetImage("ShieldIcon.bmp");
		break;
	case ItemType::SuperJump:
		ItemIcon_1P_->SetImage("SuperJumpIcon.bmp");
		break;
	default:
		break;
	}

	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		ItemType Player2pItem = Player::MainPlayer_2->GetCurItem();

		switch (Player2pItem)
		{
		case ItemType::Max:
			ItemIcon_1P_->SetImage("EmptyIcon.bmp");
			break;
		case ItemType::Niddle:
			ItemIcon_1P_->SetImage("NiddleIcon.bmp");
			break;
		case ItemType::Shield:
			ItemIcon_1P_->SetImage("ShieldIcon.bmp");
			break;
		case ItemType::SuperJump:
			ItemIcon_1P_->SetImage("SuperJumpIcon.bmp");
			break;
		default:
			break;
		}
	}
}