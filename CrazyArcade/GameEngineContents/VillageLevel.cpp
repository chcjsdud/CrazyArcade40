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
#include "TimeUI.h"
#include "StartIntroUI.h"
#include "PlayResultUI.h"
#include "PlayNickName.h"
#include "TimeUI.h"
#include "PlayerFaceIconUI.h"


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
	CreateActor<StartIntroUI>((int)UIType::StartIntroUI);
	CreateActor<TimeUI>((int)UIType::Time);
	CreateActor<PlayerFaceIconUI>((int)UIType::Time);
	CreateActor<Mouse>((int)UIType::Mouse);
	CreateActor<PlayNickName>((int)UIType::PopUpButton);

	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor 만들고
	MapBackGround_->GetRenderer()->SetImage("Village_Back.bmp");//Actor에 이미지 세팅해주고
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//윈도우기준 그려줄 위치 정해주고
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// 타일맵 만들어줌
	
	CreateActor<PlayBackGround>((int)ORDER::PLAYER);
	CreateActor<StartIntroUI>((int)UIType::StartIntroUI);
	CreateActor<TimeUI>((int)UIType::Time);
	CreateActor<PlayerFaceIconUI>((int)UIType::Time);
	CreateActor<Mouse>((int)UIType::Mouse);
	CreateActor<PlayNickName>((int)UIType::PopUpButton);
	
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
}

void VillageLevel::Update()
{
}

void VillageLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	GameBgmPlayer::BgmPlay_->ChangeBgm("VillageBGM.mp3");
	if (nullptr != Player::MainPlayer_1)		// 플레이어1이 null이 아니었다 => 다른 레벨의 플레이어 초기화 후 플레이어 생성 
	{
		Player::MainPlayer_1->Death();
	}

	if (nullptr != Player::MainPlayer_2)
	{
		Player::MainPlayer_2->Death();
	}

	Player::MainPlayer_1 = CreateActor<Player>((int)ORDER::PLAYER, "Player1");
	Player::MainPlayer_1->SetCharacter(static_cast<Character>(GlobalUIName::GetInst()->Get1PChar()));
	Player::MainPlayer_1->SetPlayerType(PlayerType::Player1);
	Player::MainPlayer_1->SetPosition({ 80.0f, 450.0f });
	Player::MainPlayer_1->SetMapTile(&MapBackGround_->MapTileMap_);

	if (true == GlobalUIName::GetInst()->Is2pUpdate())
	{
		Player::MainPlayer_2 = CreateActor<Player>((int)ORDER::PLAYER, "Player2");
		Player::MainPlayer_2->SetCharacter(static_cast<Character>(GlobalUIName::GetInst()->Get2PChar()));
		Player::MainPlayer_2->SetPlayerType(PlayerType::Player2);
		Player::MainPlayer_2->SetPosition({ 590.f, 450.f });
		Player::MainPlayer_2->SetMapTile(&MapBackGround_->MapTileMap_);
	}

}

void VillageLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	GameBgmPlayer::BgmPlay_->Stop();
}
