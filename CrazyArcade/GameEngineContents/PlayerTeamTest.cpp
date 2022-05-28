#include"PlayerTeamTest.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/ContentsEnum.h>
#include "Player.h"
#include"ContentsEnum.h"
#include"MapBackGround.h."
#include "MapFront.h"
#include "MapGameObject.h"
#include "Monster1.h"
#include "Monster2.h"
#include "Boss.h"

////////////////////UI
#include "Mouse.h"
#include "PlayBackGround.h"
#include "TimeUI.h"
#include "StartIntroUI.h"
#include "PlayResultUI.h"
#include "Area.h"
#include <vector>

PlayerTeamTest::PlayerTeamTest()
{

}
PlayerTeamTest::~PlayerTeamTest()
{

}
void PlayerTeamTest::Loading()
{
	if (nullptr == Player::MainPlayer_1)
	{
		Player::MainPlayer_1 = CreateActor<Player>((int)ORDER::PLAYER, "Player1");
		Player::MainPlayer_2 = CreateActor<Player>((int)ORDER::PLAYER, "Player2");
	}
	
	Player::MainPlayer_1->Off();
	Player::MainPlayer_2->Off();
	CreateActor<PlayBackGround>((int)ORDER::PLAYER);
	CreateActor<StartIntroUI>((int)UIType::StartIntroUI);
	CreateActor<TimeUI>((int)UIType::Time);
	CreateActor<Mouse>((int)UIType::Mouse);
	//CreateActor< PlayResultUI>((int)UIType::PlayResultUI);

	{
		MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
		MapBackGround_->GetRenderer()->SetImage("Camp_ColMap.bmp");//Actor�� �̹��� �������ְ�

		float4 Actor = {};
		Actor.x = (MapBackGround_->GetRenderer()->GetImage()->GetScale().Half().x);
		Actor.y = (MapBackGround_->GetRenderer()->GetImage()->GetScale().Half().y);

		MapBackGround_->GetRenderer()->SetPivot(Actor);
	}

	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
	MapBackGround_->GetRenderer()->SetImage("Camp_Back.bmp");//Actor�� �̹��� �������ְ�d
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// Ÿ�ϸ� �������


	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::FRONTBACKGROUND);//Actor �����
	MapFrontBackGround_->GetRenderer()->SetImage("Camp_Front.bmp");//Actor�� �̹��� �������ְ�
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�

	//ColMapImage_ = GameEngineImageManager::GetInst()->Find("Camp_ColMap.bmp");

	for (int x = 0; x < 15; ++x)
	{
		for (int y = 0; y < 13; ++y)
		{
			float StartX = (600 / 15 * x) + 20;
			float StartY = (520 / 13 * y) + 40;
			float EndX = (600 / 15 * (x + 1)) + 20;
			float EndY = (520 / 13 * (y + 1)) + 40;

			Area area(ColMapImage_, StartX, StartY, EndX, EndY);
			Areas_.push_back(area);
		}
	}

	Monster1* Mandarin1 = CreateActor<Monster1>((int)ORDER::MONSTER);
	Mandarin1->SetPosition(Areas_[0].GetCenter());
	Mandarin1->SetMapTile(&MapBackGround_->MapTileMap_);

	Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile1->SetPosition(Areas_[6].GetCenter());
	Crocodile1->SetMapTile(&MapBackGround_->MapTileMap_);

}
void PlayerTeamTest::Update()
{

}
void PlayerTeamTest::LevelChangeStart(GameEngineLevel* _PrevLevel)
{



	//Monster1* Mandarin1 = CreateActor<Monster1>((int)ORDER::MONSTER);
	//Mandarin1->SetPosition(float4(100.0f, 100.0f));

	//Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::MONSTER);
	//Crocodile1->SetPosition(float4(150.0f, 150.0f));

	//Boss* Seal = CreateActor<Boss>((int)ORDER::MONSTER);
	//Seal->SetPosition(float4(200.0f, 200.0f));


	//Player* NewPlayer = CreateActor<Player>((int)ORDER::PLAYER, "Player1");
	//NewPlayer->SetCharacter(Character::BAZZI);
	//NewPlayer->SetPlayerType(PlayerType::Player1);
	//NewPlayer->SetPosition({ 500.f, 300.f });
	Player::MainPlayer_1->On();
	Player::MainPlayer_1->SetCharacter(Character::BAZZI);
	Player::MainPlayer_1->SetPlayerType(PlayerType::Player1);
	Player::MainPlayer_1->SetPosition({ 100.f, 300.f });
	Player::MainPlayer_1->SetMapTile(&MapBackGround_->MapTileMap_);

	Player::MainPlayer_2->On();
	//Player::MainPlayer_2 = CreateActor<Player>((int)ORDER::PLAYER);
	Player::MainPlayer_2->SetCharacter(Character::BAZZI);
	Player::MainPlayer_2->SetPlayerType(PlayerType::Player2);
	Player::MainPlayer_2->SetPosition({ 400.f, 300.f });
	Player::MainPlayer_2->SetMapTile(&MapBackGround_->MapTileMap_);


	// =================== 1P 2P Ű ���� �Է� �� �̵� Ȯ�� �Ϸ� 


	//������ ���콺 ����
	ShowCursor(false);
}

void PlayerTeamTest::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	//������ ���콺 ���̱�
	ShowCursor(true);
}