#include"VillageLevel.h"
#include "GameBgmPlayer.h"
#include"ContentsEnum.h"
#include "GlobalUIName.h"
#include "MapBackGround.h"
#include "MapFront.h"
#include "MapGameObject.h"
#include"GameItemObject.h"
#include "PlayBackGround.h"
#include "StartIntroUI.h"
#include "TimeUI.h"
#include "PlayerFaceIconUI.h"
#include "Mouse.h"
#include "PlayNickName.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include<GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>

//UI 부분
#include "Mouse.h"
#include "PlayBackGround.h"
#include "ItemIcon.h"
#include "TimeUI.h"
#include "StartIntroUI.h"
#include "PlayResultUI.h"
#include "PlayNickName.h"
#include "TimeUI.h"
#include "PlayerFaceIconUI.h"
#include "PlayResultUI.h"
#include "PlayScoreBoard.h"


#include "Area.h"
VillageLevel::VillageLevel()
	: MapBackGround_(nullptr)
	, MapFrontBackGround_(nullptr)
{

}
VillageLevel::~VillageLevel()
{

}

void VillageLevel::Loading()
{
	CreateActor<PlayBackGround>((int)ORDER::PLAYER);
	CreateActor<ItemIcon>((int)UIType::PopUpButton);
	CreateActor<Mouse>((int)UIType::Mouse);
	CreateActor<PlayNickName>((int)UIType::PopUpButton);

	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor 만들고
	MapBackGround_->GetRenderer()->SetImage("Village_Back.bmp");//Actor에 이미지 세팅해주고
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// 타일맵 만들어줌
	

	
	{
		MapGameObject* BlockSet = CreateActor<MapGameObject>();
		BlockSet->SetMapTile(&MapBackGround_->MapTileMap_);
		GameEngineDirectory Dir;

		Dir.MoveParent("CrazyArcade");
		Dir.Move("Resources");
		Dir.Move("Data");

		GameEngineFile LoadFile = (Dir.GetFullPath() + "\\VillageLevel.MapData").c_str();

		LoadFile.Open(OpenMode::Read);

		int Size = 0;
		LoadFile.Read(&Size, sizeof(int));

		for (size_t y = 0; y < Size; y++)
		{
			int XSize = 0;
			LoadFile.Read(&XSize, sizeof(int));
			for (size_t x = 0; x < XSize; x++)
			{
				std::string Name;
				LoadFile.Read(Name);

				if (Name == "None")
				{
					continue;
				}

				//                          5 7
				BlockSet->CreateBlock(float4(static_cast<float>(x * 40), static_cast<float>(y * 40)), Name);
			}
			BlockSet->CreateBlock(float4(static_cast<float>(10 * 40), (static_cast<float>(0 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(12 * 40), (static_cast<float>(0 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(14 * 40), (static_cast<float>(0 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(1 * 40), (static_cast<float>(1 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(1 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(5 * 40), (static_cast<float>(1 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(9 * 40), (static_cast<float>(1 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(10 * 40), (static_cast<float>(2 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(12 * 40), (static_cast<float>(2 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(14 * 40), (static_cast<float>(2 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(1 * 40), (static_cast<float>(3 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(3 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(5 * 40), (static_cast<float>(3 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(9 * 40), (static_cast<float>(3 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(10 * 40), (static_cast<float>(4 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(12 * 40), (static_cast<float>(4 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(14 * 40), (static_cast<float>(4 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(1 * 40), (static_cast<float>(5 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(5 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(5 * 40), (static_cast<float>(5 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(0 * 40), (static_cast<float>(6 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(2 * 40), (static_cast<float>(6 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(4 * 40), (static_cast<float>(6 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(10 * 40), (static_cast<float>(6 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(12 * 40), (static_cast<float>(6 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(14 * 40), (static_cast<float>(6 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(9 * 40), (static_cast<float>(7 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(7 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(13* 40), (static_cast<float>(7 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(0* 40), (static_cast<float>(8 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(2 * 40), (static_cast<float>(8 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(4 * 40), (static_cast<float>(8 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(5 * 40), (static_cast<float>(9 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(9 * 40), (static_cast<float>(9 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(9 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(13 * 40), (static_cast<float>(9 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(0 * 40), (static_cast<float>(10 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(2 * 40), (static_cast<float>(10 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(4 * 40), (static_cast<float>(10 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(5 * 40), (static_cast<float>(11 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(9 * 40), (static_cast<float>(11 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(11 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(13 * 40), (static_cast<float>(11 * 40))), "WallBlock");

			BlockSet->CreateBlock(float4(static_cast<float>(0 * 40), (static_cast<float>(12 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(2 * 40), (static_cast<float>(12 * 40))), "WallBlock");
			BlockSet->CreateBlock(float4(static_cast<float>(4 * 40), (static_cast<float>(12 * 40))), "WallBlock");

		}
	}

	VillageObject_ = CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
	VillageObject_->SetMapTile(&MapBackGround_->MapTileMap_);
	VillageObject_->SetGameItem();


	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor 만들고

	YSortOn(static_cast<int>(ORDER::PLAYER));

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

void VillageLevel::Update()
{
	if (nullptr != Player::MainPlayer_1) {
		if (Player::MainPlayer_1->GetIslive() == false)
		{
			if (IsGameEnd_ == false) {
				PlayResultUI_ = CreateActor< PlayResultUI>((int)UIType::PlayResultUI);
				PlayResultUI_->SetGameResult(GameResult::Lose);
				PlayResultUI_->SetChangeLevel("RoomLevel");
				PlayScoreBoard_ = CreateActor<PlayScoreBoard>((int)UIType::PlayResultUI);
				PlayScoreBoard_->SetWhowin(GameResult::Win_2P);
				IsGameEnd_ = true;
				GameBgmPlayer::BgmPlay_->Stop();
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
				PlayResultUI_->SetChangeLevel("RoomLevel");
				PlayScoreBoard_ = CreateActor<PlayScoreBoard>((int)UIType::PlayResultUI);
				PlayScoreBoard_->SetWhowin(GameResult::Win_1P);
				IsGameEnd_ = true;
				GameBgmPlayer::BgmPlay_->Stop();
			}
		}
	}

	if (true == TimeUI_->GetIsTimeOver())
	{
		if (IsGameEnd_ == false) {
			PlayResultUI_ = CreateActor< PlayResultUI>((int)UIType::PlayResultUI);
			PlayResultUI_->SetGameResult(GameResult::Draw);
			PlayResultUI_->SetChangeLevel("RoomLevel");
			PlayScoreBoard_ = CreateActor<PlayScoreBoard>((int)UIType::PlayResultUI);
			PlayScoreBoard_->SetWhowin(GameResult::Draw);
			IsGameEnd_ = true;
			GameBgmPlayer::BgmPlay_->Stop();
		}
	}
}

void VillageLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	TimeUI_ = CreateActor<TimeUI>((int)UIType::Time);
	CreateActor<PlayerFaceIconUI>((int)UIType::Time);
	CreateActor<StartIntroUI>((int)UIType::StartIntroUI);
	IsGameEnd_ = false;
	GameBgmPlayer::BgmPlay_->ChangeBgm("VillageBGM.mp3");
	if (nullptr != Player::MainPlayer_1)		// 플레이어1이 null이 아니었다 => 다른 레벨의 플레이어 초기화 후 플레이어 생성 
	{
		Player::MainPlayer_1 = nullptr;
	}

	if (nullptr != Player::MainPlayer_2)
	{
		Player::MainPlayer_2 = nullptr;
	}

	Player::MainPlayer_1 = CreateActor<Player>((int)ORDER::PLAYER, "Player1");
	Player::MainPlayer_1->SetCharacter(static_cast<Character>(GlobalUIName::GetInst()->Get1PChar()));
	Player::MainPlayer_1->SetPlayerType(PlayerType::Player1);
	Player::MainPlayer_1->SetPosition(Areas_[23].GetCenter());
	Player::MainPlayer_1->SetMapTile(&MapBackGround_->MapTileMap_);
	Player::MainPlayer_1->Boom_ = CreateActor<MapGameObject>((int)ORDER::PLAYER);
	Player::MainPlayer_1->Boom_->SetMapTile(&MapBackGround_->MapTileMap_);

	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		Player::MainPlayer_2 = CreateActor<Player>((int)ORDER::PLAYER, "Player2");
		Player::MainPlayer_2->SetCharacter(static_cast<Character>(GlobalUIName::GetInst()->Get2PChar()));
		Player::MainPlayer_2->SetPlayerType(PlayerType::Player2);
		Player::MainPlayer_2->SetPosition(Areas_[192].GetCenter());
		Player::MainPlayer_2->SetMapTile(&MapBackGround_->MapTileMap_);
		Player::MainPlayer_2->Boom_ = CreateActor<MapGameObject>((int)ORDER::PLAYER);
		Player::MainPlayer_2->Boom_->SetMapTile(&MapBackGround_->MapTileMap_);
	}

	ShowCursor(false);
}

void VillageLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	GameBgmPlayer::BgmPlay_->Stop();

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

	ShowCursor(true);
}
