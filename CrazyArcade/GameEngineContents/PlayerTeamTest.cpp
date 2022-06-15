#include"PlayerTeamTest.h"
#include "GlobalUIName.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/ContentsEnum.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include "Player.h"
#include "ContentsEnum.h"
#include "MapBackGround.h."
#include "MapFront.h"
#include "MapGameObject.h"
#include "GameEngineContents/GameItemObject.h"
#include "Monster1.h"
#include "Monster2.h"
#include "Boss.h"

////////////////////UI
#include "Mouse.h"
#include "PlayBackGround.h"
#include "TimeUI.h"
#include "StartIntroUI.h"
#include "PlayResultUI.h"
#include "PlayNickName.h"
#include "TimeUI.h"
#include "PlayerFaceIconUI.h"
#include "Area.h"
#include "PlayScoreBoard.h"
#include <vector>

PlayerTeamTest::PlayerTeamTest()
	:ColMapImage_(nullptr)
	, MapBackGround_(nullptr)
	, MapColRenderer_(nullptr)
	, MapFrontBackGround_(nullptr)
	, PlayerTeamTestObject_(nullptr)
	, IsGameEnd_(false)
{

}
PlayerTeamTest::~PlayerTeamTest()
{

}
void PlayerTeamTest::Loading()
{
	CreateActor<PlayBackGround>((int)ORDER::PLAYER);
	CreateActor<Mouse>((int)UIType::Mouse);
	CreateActor<PlayNickName>((int)UIType::PopUpButton);
	
	

	{
		MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor 만들고
		MapBackGround_->GetRenderer()->SetImage("Camp_ColMap.bmp");//Actor에 이미지 세팅해주고

		float4 Actor = {};
		Actor.x = (MapBackGround_->GetRenderer()->GetImage()->GetScale().Half().x);
		Actor.y = (MapBackGround_->GetRenderer()->GetImage()->GetScale().Half().y);

		MapBackGround_->GetRenderer()->SetPivot(Actor);
	}

	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor 만들고
	MapBackGround_->GetRenderer()->SetImage("Camp_Back.bmp");//Actor에 이미지 세팅해주고d
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// 타일맵 만들어줌


	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor 만들고

	//ColMapImage_ = GameEngineImageManager::GetInst()->Find("Camp_ColMap.bmp");

	//{
	//	MapGameObject* BlockSet = CreateActor<MapGameObject>();
	//	BlockSet->SetMapTile(&MapBackGround_->MapTileMap_);
	//	GameEngineDirectory Dir;
	//
	//	Dir.MoveParent("CrazyArcade");
	//	Dir.Move("Resources");
	//	Dir.Move("Data");
	//
	//	GameEngineFile LoadFile = (Dir.GetFullPath() + "\\CampLevel.MapData").c_str();
	//
	//	LoadFile.Open(OpenMode::Read);
	//
	//	int Size = 0;
	//	LoadFile.Read(&Size, sizeof(int));
	//
	//	for (size_t y = 0; y < Size; y++)
	//	{
	//		int XSize = 0;
	//		LoadFile.Read(&XSize, sizeof(int));
	//		for (size_t x = 0; x < XSize; x++)
	//		{
	//			std::string Name;
	//			LoadFile.Read(Name);
	//
	//			if (Name == "None")
	//			{
	//				continue;
	//			}
	//
	//			//                          5 7
	//			BlockSet->CreateBlock(float4(x * 40, y * 40), Name);
	//		}
	//	}
	//
	Item_ = CreateActor<GameItemObject>((int)ORDER::MAPOBJECT);
	Item_->SetMapTile(&MapBackGround_->MapTileMap_);
	Item_->CreateItem({ 400.f, 50.f }, ItemType::Shoes);

	Item_ = CreateActor<GameItemObject>((int)ORDER::MAPOBJECT);
	Item_->SetMapTile(&MapBackGround_->MapTileMap_);
	Item_->CreateItem({ 400.f, 130.f }, ItemType::Turtle);

	Item_ = CreateActor<GameItemObject>((int)ORDER::MAPOBJECT);
	Item_->SetMapTile(&MapBackGround_->MapTileMap_);
	Item_->CreateItem({ 400.f, 210.f }, ItemType::SpaceShip);

	Item_ = CreateActor<GameItemObject>((int)ORDER::MAPOBJECT);
	Item_->SetMapTile(&MapBackGround_->MapTileMap_);
	Item_->CreateItem({ 400.f, 290.f }, ItemType::Owl);

	Item_ = CreateActor<GameItemObject>((int)ORDER::MAPOBJECT);
	Item_->SetMapTile(&MapBackGround_->MapTileMap_);
	Item_->CreateItem({ 400.f, 370.f }, ItemType::Shield);

	Item_ = CreateActor<GameItemObject>((int)ORDER::MAPOBJECT);
	Item_->SetMapTile(&MapBackGround_->MapTileMap_);
	Item_->CreateItem({ 400.f, 450.f }, ItemType::Devil);



	//Monster1* Mandarin1 = CreateActor<Monster1>((int)ORDER::MONSTER);
	//Mandarin1->SetPosition(Areas_[0].GetCenter());
	//Mandarin1->SetMapTile(&MapBackGround_->MapTileMap_);

	//Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::MONSTER);
	//Crocodile1->SetPosition(Areas_[6].GetCenter());
	//Crocodile1->SetMapTile(&MapBackGround_->MapTileMap_);
	for (int x = 0; x < 15; ++x)
	{
		for (int y = 0; y < 13; ++y)
		{
			float StartX = static_cast<float>((600 / 15 * x) + 20);
			float StartY = static_cast<float>((520 / 13 * y) + 40);
			float EndX = static_cast<float>((600 / 15 * (x + 1)) + 20);
			float EndY = static_cast<float>((520 / 13 * (y + 1)) + 40);

			Area area(ColMapImage_, StartX, StartY, EndX, EndY);
			Areas_.push_back(area);
		}
	}
}
void PlayerTeamTest::Update()
{
	if (nullptr != Player::MainPlayer_1) {
		if (Player::MainPlayer_1->GetIslive() == false)
		{
			if (IsGameEnd_ == false) {
				PlayResultUI_ = CreateActor< PlayResultUI>((int)UIType::PlayResultUI);
				PlayResultUI_->SetGameResult(GameResult::Lose);
				PlayScoreBoard_ = CreateActor<PlayScoreBoard>((int)UIType::PlayResultUI);
				PlayScoreBoard_->SetWhowin(GameResult::Win_2P);
				IsGameEnd_ = true;
			}
		}
	}

	if (nullptr != Player::MainPlayer_2)
	{
		if (Player::MainPlayer_2->GetIslive() == false)
		{
			if (IsGameEnd_ == false) {
				PlayResultUI_ = CreateActor< PlayResultUI>((int)UIType::PlayResultUI);
				PlayResultUI_->SetGameResult(GameResult::Win);
				PlayScoreBoard_ = CreateActor<PlayScoreBoard>((int)UIType::PlayResultUI);
				PlayScoreBoard_->SetWhowin(GameResult::Win_1P);
				IsGameEnd_ = true;
			}
		}
	}

	if (true == TimeUI_->GetIsTimeOver())
	{
		if (IsGameEnd_ == false) {
			PlayResultUI_ = CreateActor< PlayResultUI>((int)UIType::PlayResultUI);
			PlayResultUI_->SetGameResult(GameResult::Draw);
			PlayScoreBoard_ = CreateActor<PlayScoreBoard>((int)UIType::PlayResultUI);
			PlayScoreBoard_->SetWhowin(GameResult::Draw);
			IsGameEnd_ = true;
		}
	}
}
void PlayerTeamTest::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<PlayerFaceIconUI>((int)UIType::Time);
	CreateActor<StartIntroUI>((int)UIType::StartIntroUI);
	TimeUI_ = CreateActor<TimeUI>((int)UIType::Time);
	IsGameEnd_ = false;

	//Monster1* Mandarin1 = CreateActor<Monster1>((int)ORDER::MONSTER);
	//Mandarin1->SetPosition(float4(100.0f, 100.0f));

	////Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::MONSTER);
	////Crocodile1->SetPosition(float4(150.0f, 150.0f));

	////Boss* Seal = CreateActor<Boss>((int)ORDER::MONSTER);
	////Seal->SetPosition(float4(200.0f, 200.0f));

	// =========================================== 다른 레벨에서 플레이어 생성 시 필요한 구문
	// 플레이어 포지션 세팅 시, 단순 값이 아닌 타일 기준으로 세팅할 경우(Area사용) 레벨 내에서 ColMapImage_세팅이 필요합니다 
	


	Player::MainPlayer_1 = CreateActor<Player>((int)ORDER::PLAYER, "Player1");
	Player::MainPlayer_1->SetCharacter(static_cast<Character>(GlobalUIName::GetInst()->Get1PChar()));
	Player::MainPlayer_1->SetPlayerType(PlayerType::Player1);
	Player::MainPlayer_1->SetPosition(Areas_[170].GetCenter());		// 23
	Player::MainPlayer_1->SetMapTile(&MapBackGround_->MapTileMap_);
	Player::MainPlayer_1->Boom_ = CreateActor<MapGameObject>((int)ORDER::PLAYER);
	Player::MainPlayer_1->Boom_->SetMapTile(&MapBackGround_->MapTileMap_);


	Player::MainPlayer_2 = CreateActor<Player>((int)ORDER::PLAYER, "Player2");
	Player::MainPlayer_2->SetCharacter(static_cast<Character>(GlobalUIName::GetInst()->Get2PChar()));
	Player::MainPlayer_2->SetPlayerType(PlayerType::Player2);
	Player::MainPlayer_2->SetPosition(Areas_[36].GetCenter());	//170
	Player::MainPlayer_2->SetMapTile(&MapBackGround_->MapTileMap_);
	Player::MainPlayer_2->Boom_ = CreateActor<MapGameObject>((int)ORDER::PLAYER);
	Player::MainPlayer_2->Boom_->SetMapTile(&MapBackGround_->MapTileMap_);

	Character Char1 = Player::MainPlayer_1->GetCharacter();
	Character Char = Player::MainPlayer_2->GetCharacter();
	//윈도우 마우스 숨김

	PlayerTeamTestObject_ = CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
	PlayerTeamTestObject_->SetMapTile(&MapBackGround_->MapTileMap_);
	PlayerTeamTestObject_->SetGameItem();

	ShowCursor(false);
}

void PlayerTeamTest::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	if (nullptr != Player::MainPlayer_1)		// 플레이어1이 null이 아니었다 => 다른 레벨의 플레이어 초기화 후 플레이어 생성 
	{
		Player::MainPlayer_1->Death();
	}
	if (nullptr != Player::MainPlayer_2)
	{
		Player::MainPlayer_2->Death();
	}
	if (nullptr != PlayResultUI_)
	{
		PlayResultUI_->Death();
		PlayResultUI_ = nullptr;
	}
	if (nullptr != PlayScoreBoard_)
	{
		PlayScoreBoard_->Death();
		PlayScoreBoard_ = nullptr;
	}
	
	//윈도우 마우스 보이기
	
	ShowCursor(true);

}