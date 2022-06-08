#include"CampLevel.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include "MapFront.h"
#include "MapGameObject.h"
#include"GameItemObject.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include<GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>

#include "Area.h"

CampLevel::CampLevel()
:MapBackGround_(nullptr)
, MapFrontBackGround_(nullptr)
, Item_(nullptr)
, bubble_(nullptr)
{

}
CampLevel::~CampLevel()
{

}

void CampLevel::Loading()
{


	MapBackGround_ = CreateActor<MapBackGround>(static_cast<int>(ORDER::BACKGROUND));//Actor �����
	MapBackGround_->GetRenderer()->SetImage("Camp_Back.bmp");//Actor�� �̹��� �������ְ�
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�
	MapBackGround_->MapTileMap_.TileRangeSetting(15, 13, { 40,40 });// Ÿ�ϸ� �������
	

	{

		MapGameObject* BlockSet = CreateActor<MapGameObject>();
		BlockSet->SetMapTile(&MapBackGround_->MapTileMap_);
		GameEngineDirectory Dir;

		Dir.MoveParent("CrazyArcade");
		Dir.Move("Resources");
		Dir.Move("Data");

		GameEngineFile LoadFile = (Dir.GetFullPath() + "\\CampLevel.MapData").c_str();

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
		}
		BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(0 * 40))), "WallBlock");
		BlockSet->CreateBlock(float4(static_cast<float>(4 * 40), (static_cast<float>(0 * 40))), "WallBlock");
		BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(1 * 40))), "WallBlock");
		BlockSet->CreateBlock(float4(static_cast<float>(3 * 40), (static_cast<float>(11 * 40))), "WallBlock");
		BlockSet->CreateBlock(float4(static_cast<float>(11 * 40), (static_cast<float>(12 * 40))), "WallBlock");
		BlockSet->CreateBlock(float4(static_cast<float>(10 * 40), (static_cast<float>(12 * 40))), "WallBlock");

	}

	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor �����

	Item_ = CreateActor<GameItemObject>(static_cast<int>(ORDER::MAPOBJECT), "GameItem");
	Item_->SetMapTile(&MapBackGround_->MapTileMap_);

	bubble_ = CreateActor<MapGameObject>(static_cast<int>(ORDER::EFFECT), "Bubble");
	bubble_->SetMapTile(&MapBackGround_->MapTileMap_);
	bubble_->SetGameItem();



//	Item_->CreateItem({ 200,380 }, (ItemType::Fluid));



	if (false == GameEngineInput::GetInst()->IsKey("CreatBoom"))
	{
		GameEngineInput::GetInst()->CreateKey("CreatBoom", VK_SPACE);
	}

	//if (nullptr != Player::MainPlayer_1)		// �÷��̾�1�� null�� �ƴϾ��� => �ٸ� ������ �÷��̾� �ʱ�ȭ �� �÷��̾� ���� 
	//{
	//	Player::MainPlayer_1 = nullptr;
	//}

	//if (nullptr != Player::MainPlayer_2)
	//{
	//	Player::MainPlayer_2 = nullptr;
	//}

	//Player::MainPlayer_1 = CreateActor<Player>((int)ORDER::PLAYER, "Player1");
	//Player::MainPlayer_1->SetCharacter(Character::BAZZI);
	//Player::MainPlayer_1->SetPlayerType(PlayerType::Player1);
	//Player::MainPlayer_1->SetPosition({560.f, 500.f});
	//Player::MainPlayer_1->SetMapTile(&MapBackGround_->MapTileMap_);

	//Player::MainPlayer_2 = CreateActor<Player>((int)ORDER::PLAYER, "Player2");
	//Player::MainPlayer_2->SetCharacter(Character::LUXMARID);
	//Player::MainPlayer_2->SetPlayerType(PlayerType::Player2);
	//Player::MainPlayer_2->SetPosition({200.f, 200.f});
	//Player::MainPlayer_2->SetMapTile(&MapBackGround_->MapTileMap_);

	YSortOn(static_cast<int>(ORDER::PLAYER));
}

void CampLevel::Update()
{
}

void CampLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	if (nullptr != Player::MainPlayer_1)		// �÷��̾�1�� null�� �ƴϾ��� => �ٸ� ������ �÷��̾� �ʱ�ȭ �� �÷��̾� ���� 
	{
		Player::MainPlayer_1 = nullptr;
	}

	if (nullptr != Player::MainPlayer_2)
	{
		Player::MainPlayer_2 = nullptr;
	}

	Player::MainPlayer_1 = CreateActor<Player>((int)ORDER::PLAYER, "Player1");
	Player::MainPlayer_1->SetCharacter(Character::BAZZI);
	Player::MainPlayer_1->SetPlayerType(PlayerType::Player1);
	Player::MainPlayer_1->SetPosition({ 100.f, 340.f });
	Player::MainPlayer_1->SetMapTile(&MapBackGround_->MapTileMap_);

}

void CampLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
