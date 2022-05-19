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
#include "Monster1.h"
#include "Monster2.h"
#include "Boss.h"

PlayerTeamTest::PlayerTeamTest()
{

}
PlayerTeamTest::~PlayerTeamTest()
{

}
void PlayerTeamTest::Loading()
{

}
void PlayerTeamTest::Update()
{
}
void PlayerTeamTest::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	{
		MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
		MapBackGround_->GetRenderer()->SetImage("Camp_ColMap.bmp");//Actor�� �̹��� �������ְ�
		//MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�

		float4 Actor = {};
		Actor.x = (MapBackGround_->GetRenderer()->GetImage()->GetScale().Half().x);
		Actor.y = (MapBackGround_->GetRenderer()->GetImage()->GetScale().Half().y);

		MapBackGround_->GetRenderer()->SetPivot(Actor);
	}

	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
	MapBackGround_->GetRenderer()->SetImage("Camp_Back.bmp");//Actor�� �̹��� �������ְ�d
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�


	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::FRONTBACKGROUND);//Actor �����
	MapFrontBackGround_->GetRenderer()->SetImage("Camp_Front.bmp");//Actor�� �̹��� �������ְ�
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�


	// *** ������: ������ ���� �΋H���� ���� �߱淡 ��� �ּ� �ɾ����� 

	//Monster1* Mandarin1 = CreateActor<Monster1>((int)ORDER::MONSTER);
	//Mandarin1->SetPosition(float4(100.0f, 100.0f));

	//Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::MONSTER);
	//Crocodile1->SetPosition(float4(150.0f, 150.0f));

	//Boss* Seal = CreateActor<Boss>((int)ORDER::MONSTER);
	//Seal->SetPosition(float4(200.0f, 200.0f));

	Player* NewPlayer = CreateActor<Player>((int)ORDER::PLAYER);
	NewPlayer->SetCharacter(Character::BAZZI);
	NewPlayer->SetPlayerType(PlayerType::Player1);
	NewPlayer->SetPosition({ 500.f, 300.f });


	// =================== 1P 2P Ű ���� �Է� �� �̵� Ȯ�� �Ϸ� 

	//NewPlayer = CreateActor<Player>((int)ORDER::PLAYER);
	//NewPlayer->SetCharacter(Character::DAO);
	//NewPlayer->SetPlayerType(PlayerType::Player2);
	//NewPlayer->SetPosition({ 200.f, 300.f });

}