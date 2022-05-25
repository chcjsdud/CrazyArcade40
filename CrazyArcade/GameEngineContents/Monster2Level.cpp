#include"Monster2Level.h"
#include"ContentsEnum.h"
#include "MapBackGround.h"
#include "MapFront.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Monster2.h"
#include "Area.h"
#include <GameEngine/GameEngineImageManager.h>
Monster2Level::Monster2Level()
{

}
Monster2Level::~Monster2Level()
{

}
void Monster2Level::Loading()
{
	MapBackGround_ = CreateActor<MapBackGround>((int)ORDER::BACKGROUND);//Actor �����
	MapBackGround_->GetRenderer()->SetImage("MonsterStage2_Back.bmp");//Actor�� �̹��� �������ְ�
	MapBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�

	MapFrontBackGround_ = CreateActor<MapFront>((int)ORDER::PLAYER);//Actor �����
	MapFrontBackGround_->GetRenderer()->SetImage("MonsterStage2_Front.bmp");//Actor�� �̹��� �������ְ�
	MapFrontBackGround_->GetRenderer()->SetPivot({ 320,280 });//��������� �׷��� ��ġ �����ְ�

	ColMapImage_ = GameEngineImageManager::GetInst()->Find("MonsterStage2_ColMap.bmp");

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
	
	Monster2* Crocodile1 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile1->SetPosition(Areas_[23].GetCenter());

	Monster2* Crocodile2 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile2->SetPosition(Areas_[14].GetCenter());

	Monster2* Crocodile3 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile3->SetPosition(Areas_[50].GetCenter());

	Monster2* Crocodile4 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile4->SetPosition(Areas_[89].GetCenter());

	Monster2* Crocodile5 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile5->SetPosition(Areas_[131].GetCenter());

	Monster2* Crocodile6 = CreateActor<Monster2>((int)ORDER::MONSTER);
	Crocodile6->SetPosition(Areas_[170].GetCenter());
}
void Monster2Level::Update()
{
	if (Monster::TTL_MONSTER_COUNT == 0)
	{
		// UI ������
		////if(UI ȭ�� ������)
		//{
		//	GameEngine::GetInst().ChangeLevel("BossLevel");
		//}
	}

	// else if �÷��̾� ���� 0�̵Ǹ�
	// UI ������
	// //if(UI ȭ�� ������)
	// {
	// ���Ƿ� �̵�
	//}
}
void Monster2Level::LevelChangeStart(GameEngineLevel* _NextLevel)
{


}
void Monster2Level::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{

}