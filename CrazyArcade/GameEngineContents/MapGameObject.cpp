#include"MapGameObject.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

MapGameObject::MapGameObject()
	:MapTile_(nullptr),
	AllBlockTiles_()

{

}

MapGameObject::~MapGameObject()
{

}

void MapGameObject::Start()
{
	SetPosition({ 0.0f, 0.0f });

}

void MapGameObject::Update()
{

	WaveDeathAni();
	DestroyWave();
	DestroyBoom();
}

// 플레이어가 서있는 위치의 타일이 어떤 타입의 블럭인지 알려주는 함수 return 값이 Max이면 - 아무것도 없는 타일입니다.
BlockType MapGameObject::CheckTile(float4 _Pos) {
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	if (Tiles_ == nullptr)
	{
		return BlockType::Max;
	}
	else
	{
		return Tiles_->BlockType_;
	}
}
// 플레이어가 서있는 위치의 타일의 BlockType이 아이템블록이라면 , 아이템이 무슨아이템인지 체크하는 함수입니당. 위치넣어주면 아이템타입이 리턴됩니당. 
ItemType MapGameObject::CheckItem(float4 _Pos)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	if (Tiles_ == nullptr)
	{
		return ItemType::Max;
	}
	else
	{
		return Tiles_->ItemType_;
	}
}

// 블럭이 사라질때 위치를 넣어주고 ItemType 이 max가 아니라면 createItem을 해준다.
void MapGameObject::CreateItem(float4 _Pos)
{
	//if (ItemType::Max == CheckItem(_Pos))
	//{
	//	return;
	//};

	// 블럭이 아이템을 가지고 있을때
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	BlockTile* Tiles_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::EFFECT));
	Tiles_->Renderer = CreateRenderer();
	Tiles_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y}); // 아이템 y는 90이어야한다.

	Tiles_->Renderer->CreateAnimation("Fluid.bmp", "Animation", 0, 5, 0.2f, true);
	Tiles_->Renderer->ChangeAnimation("Animation");


}

void MapGameObject::CreateBoom(float4 _Pos, float _Power)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	BlockTile* Boom_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::EFFECT));
	Boom_->BlockType_ = BlockType::BubbleBlock;
	Boom_->Renderer = CreateRenderer();
	Boom_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y + 20 });
	Boom_->Renderer->CreateAnimation("Bubble_Dark.bmp", "BubbleDark", 0, 3, 0.2f, true);
	Boom_->Renderer->CreateAnimation("Bubble_Default.bmp", "BubbleDefault", 0, 3, 0.2f, true);
	Boom_->Renderer->CreateAnimation("Bubble_Boss.bmp", "BubbleBoss", 0, 3, 0.2f, true);
	Boom_->Renderer->ChangeAnimation("BubbleDefault");
	Boom_->TileIndex_ = TileIndex_;
	Boom_->TilePos_ = _Pos;
	Boom_->DeathTime_ = 3.0f;
	Boom_->Power_ = _Power;
	BoomBlockTiles_.push_back(Boom_);

}



void MapGameObject::BubblePop(float4 _Pos, float Power)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);

	BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
	Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
	Wave_->BlockType_ = BlockType::WaveBlock;
	Wave_->TileIndex_ = TileIndex_;
	Wave_->Renderer = CreateRenderer();
	Wave_->Renderer->SetPivot({ TileCenterPos_.x,TileCenterPos_.y });
	Wave_->Renderer->CreateAnimation("Center.bmp", "Center", 0, 5, 0.1f, true);
	Wave_->Renderer->CreateAnimation("Center.bmp", "Death", 0, 5, 0.1f, false);
	Wave_->Renderer->ChangeAnimation("Center");
	Wave_->DeathTime_ = 1.5f;
	Wave_->IsWaveDeath;
	Wave_->IsWaveDeathAni;
	Wave_->DeathAniTime_ = 1.5f;

	WaveBlockTiles_.push_back(Wave_);

	MakeLeftWave(TileIndex_, Power);
	MakeRightWave(TileIndex_, Power);
	MakeDownWave(TileIndex_, Power);
	MakeUpWave(TileIndex_, Power);

}
void MapGameObject::DestroyBoom()//폭탄마다 각자 타이머 돌림
{

	for (int i = 0; i < BoomBlockTiles_.size(); i++)
	{
		BoomBlockTiles_[i]->DeathTime_ -= 1.0f * GameEngineTime::GetDeltaTime();
		if (BoomBlockTiles_[i]->DeathTime_ < 0.0f)
		{
			float4 _Poss = BoomBlockTiles_[i]->TilePos_;
			float _Power = BoomBlockTiles_[i]->Power_;
			MapTile_->DeleteTile(BoomBlockTiles_[i]->TileIndex_.X, BoomBlockTiles_[i]->TileIndex_.Y);
			BoomBlockTiles_.erase(BoomBlockTiles_.begin() + i);
			BubblePop(_Poss, _Power);//폭탄 지워진 자리에 웨이브 만들어줌
		}
	}

}
void MapGameObject::WaveDeathAni()
{
	for (int i = 0; i < WaveBlockTiles_.size(); i++) // 물풍선 중앙 탐색
	{
		if (WaveBlockTiles_[i]->IsWaveDeath == true) // 물풍선 파도가 다 만들어졌으면
		{
			for (int j = 0; j < WaveBlockTiles_[i]->MyWave_.size(); j++)//물풍선 중앙에서 보관하던 물줄기 백터돌면서
			{
				if (nullptr != WaveBlockTiles_[i]->MyWave_[j]->Renderer)
				{

					WaveBlockTiles_[i]->MyWave_[j]->Renderer->ChangeAnimation("Death");
					WaveBlockTiles_[i]->MyWave_[j]->IsWaveDeathAni = true;
				}

			}
			WaveBlockTiles_[i]->Renderer->ChangeAnimation("Death");
			WaveBlockTiles_[i]->IsWaveDeath = false;
		}
		if (WaveBlockTiles_[i]->MyWave_[0]->Renderer->IsEndAnimation() == true)//시간이 다줄었으면
		{
			WaveBlockTiles_[i]->IsWaveDeathAni = true;
		}
	}
}
void MapGameObject::DestroyWave()
{

	for (int i = 0; i < WaveBlockTiles_.size(); i++)//물풍선 백터 돌다가
	{
		if (WaveBlockTiles_[i]->IsWaveDeathAni == true)//죽는 애니재생이면
		{
			{
				for (int j = 0; j < WaveBlockTiles_[i]->MyWave_.size(); j++)
				{

					MapTile_->DeleteTile(WaveBlockTiles_[i]->MyWave_[j]->TileIndex_.X, WaveBlockTiles_[i]->MyWave_[j]->TileIndex_.Y);//물줄기 지워라
				}
				WaveBlockTiles_[i]->MyWave_.clear(); //물줄기 백터 클리어
				MapTile_->DeleteTile(WaveBlockTiles_[i]->TileIndex_.X, WaveBlockTiles_[i]->TileIndex_.Y);//중앙부분지우기
				WaveBlockTiles_.erase(WaveBlockTiles_.begin() + i);//중앙벡터 지우기
			}
		}

	}
}

void MapGameObject::MakeLeftWave(TileIndex _Pos, float _Power)
{

	int IndexCount_ = static_cast<int>(_Power);//파도 만들어줄 거리
	int PowerCount_ = static_cast<int>(_Power);//체크해줘야할 칸


	for (int i = 1; i <= PowerCount_; i++)//파워가 0이될때까지 체크
	{

		TileIndex TilePos = _Pos;

		if (TilePos.X - i < 0)//--------------------------------------------맵에 부딪혔다면
		{
			IndexCount_ = i - 1;//이만큼 가면된다.
			i = PowerCount_ + 1;//여기서 for문 종료
		}
		else//맵에 안 부딪혔다면
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X - i, TilePos.Y);//현재 검사중인 타일위치
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X - i, TilePos.Y);//현재 검사중인 타일 정보

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WallBlock) //-----------------------------------------안부서지는 벽이 있을 때

			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//----------------------------- 폭탄이 있을 때
			{
				PowerCount_ += static_cast<int>(Tiles_->Power_);//파워 전달해주기
				IndexCount_ += static_cast<int>(Tiles_->Power_);
				{

					//MakeDownWave(TilePos, Tiles_->Power_);	//왼쪽으로 가다가 터졌으니까 위 아래로 물줄기 만들어줌
					//MakeUpWave(TilePos, Tiles_->Power_);
					MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);//폭탄지워주고
					for (int i = 0; i < BoomBlockTiles_.size(); i++) //벡터에서 찾아서 지워주고
					{
						if (BoomBlockTiles_[i] == Tiles_)
						{
							BoomBlockTiles_.erase(BoomBlockTiles_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr &&
				Tiles_->BlockType_ == BlockType::FixBlock && //------------------------------------------------부서지는벽
				Tiles_->BlockType_ == BlockType::PullBlock)//밀리는상자
			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = static_cast<int>(_Power) + 1;//여기서 for문 종료
				//여기서 해당 오브젝트부숴주면됨
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------이미 터지고 있을때
			{
				{
			
					BlockTile*CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_,Tiles_->CenterWaveY_ );//검사하고 있는 웨이브의 시작점
					MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);//웨이브 지워주고
					for (int i = 0; i < CenterPos_->MyWave_.size(); i++) 
					{
						if (CenterPos_->MyWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyWave_.erase(CenterPos_->MyWave_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock &&//-----------------------------아이템이 있을때
				Tiles_->BlockType_ == BlockType::BushBlock)//부쉬있을때
			{
				//아이템 없애주는 함수
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)//가면되는곳까지 반복, 0은 따로 뿌려줄것임
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X - i, TilePos.Y);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y);//시작 타일
		if (i == IndexCount_) //마지막지점이 되면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X - i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X - i;
			Wave_->TileIndex_.Y = TilePos.Y;

			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Left1.bmp", "Left1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Left1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Left1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 
			Tiles_->IsWaveDeath = true;
		}
		else//마지막지점 아니면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X - i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X - i;
			Wave_->TileIndex_.Y = TilePos.Y;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Left2.bmp", "Left2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Left2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Left2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 

		}

	}
}
void MapGameObject::MakeDownWave(TileIndex _Pos, float _Power)
{

	int IndexCount_ = static_cast<int>(_Power);
	int PowerCount_ = static_cast<int>(_Power);

	for (int i = 1; i <= PowerCount_; i++)
	{

		TileIndex TilePos = _Pos;

		if (TilePos.Y + i > 12)
		{
			IndexCount_ = i - 1;
			i = PowerCount_ + 1;
		}
		else
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y+i);
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X , TilePos.Y+i);

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WallBlock)

			{
				IndexCount_ = i - 1;
				i = PowerCount_ + 1;
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)
			{
				PowerCount_ += static_cast<int>(Tiles_->Power_);
				IndexCount_ += static_cast<int>(Tiles_->Power_);
				{

					//MakeLeftWave(TilePos, Tiles_->Power_);
					//MakeRightWave(TilePos, Tiles_->Power_);
					MapTile_->DeleteTile(TilePos.X , TilePos.Y+i);
					for (int i = 0; i < BoomBlockTiles_.size(); i++) 
					{
						if (BoomBlockTiles_[i] == Tiles_)
						{
							BoomBlockTiles_.erase(BoomBlockTiles_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr &&
				Tiles_->BlockType_ == BlockType::FixBlock && //------------------------------------------------부서지는벽
				Tiles_->BlockType_ == BlockType::PullBlock)//밀리는상자
			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = static_cast<int>(_Power) + 1;//여기서 for문 종료
				//여기서 해당 오브젝트부숴주면됨
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------이미 터지고 있을때
			{
				{

					BlockTile* CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_, Tiles_->CenterWaveY_);//검사하고 있는 웨이브의 시작점
					MapTile_->DeleteTile(TilePos.X, TilePos.Y + i);//웨이브 지워주고
					for (int i = 0; i < CenterPos_->MyWave_.size(); i++)
					{
						if (CenterPos_->MyWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyWave_.erase(CenterPos_->MyWave_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock &&//-----------------------------아이템이 있을때
				Tiles_->BlockType_ == BlockType::BushBlock)//부쉬있을때
			{
				//아이템 없애주는 함수
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)//가면되는곳까지 반복, 0은 따로 뿌려줄것임
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y+i);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y);//시작 타일
		if (i == IndexCount_) //마지막지점이 되면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y + i, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X ;
			Wave_->TileIndex_.Y = TilePos.Y+i;

			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Down1.bmp", "Down1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Down1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Down1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 
			Tiles_->IsWaveDeath = true;
		}
		else//마지막지점 아니면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y + i, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X ;
			Wave_->TileIndex_.Y = TilePos.Y + i;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Down2.bmp", "Down2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Down2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Down2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 

		}

	}
}
void MapGameObject::MakeRightWave(TileIndex _Pos, float _Power)
{

	int IndexCount_ = static_cast<int>(_Power);//파도 만들어줄 거리
	int PowerCount_ = static_cast<int>(_Power);//체크해줘야할 칸


	for (int i = 1; i <= PowerCount_; i++)//파워가 0이될때까지 체크
	{

		TileIndex TilePos = _Pos;

		if (TilePos.X + i > 14)//--------------------------------------------벽에 부딪혔다면
		{
			IndexCount_ = i - 1;//이만큼 가면된다.
			i = PowerCount_ + 1;//여기서 for문 종료
		}
		else//벽에 안 부딪혔다면
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X + i, TilePos.Y);//현재 검사중인 타일위치
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X + i, TilePos.Y);//현재 검사중인 타일 정보

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WallBlock) //-----------------------------------------안부서지는 벽이 있을 때

			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//----------------------------- 폭탄이 있을 때
			{
				PowerCount_ += static_cast<int>(Tiles_->Power_);//파워 전달해주기
				IndexCount_ += static_cast<int>(Tiles_->Power_);
				{

					//MakeDownWave(TilePos, Tiles_->Power_);	
					//MakeUpWave(TilePos, Tiles_->Power_);
					MapTile_->DeleteTile(TilePos.X + i, TilePos.Y);//폭탄지워주고
					for (int i = 0; i < BoomBlockTiles_.size(); i++) //벡터에서 찾아서 지워주고
					{
						if (BoomBlockTiles_[i] == Tiles_)
						{
							BoomBlockTiles_.erase(BoomBlockTiles_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr &&
				Tiles_->BlockType_ == BlockType::FixBlock && //------------------------------------------------부서지는벽
				Tiles_->BlockType_ == BlockType::PullBlock)//밀리는상자
			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = static_cast<int>(_Power) + 1;//여기서 for문 종료
				//여기서 해당 오브젝트부숴주면됨
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------이미 터지고 있을때
			{
				{

					BlockTile* CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_, Tiles_->CenterWaveY_);//검사하고 있는 웨이브의 시작점
					MapTile_->DeleteTile(TilePos.X + i, TilePos.Y);//웨이브 지워주고
					for (int i = 0; i < CenterPos_->MyWave_.size(); i++)
					{
						if (CenterPos_->MyWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyWave_.erase(CenterPos_->MyWave_.begin() + i);
						}
					}
				}
			
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock &&//-----------------------------아이템이 있을때
				Tiles_->BlockType_ == BlockType::BushBlock)//부쉬있을때
			{
				//아이템 없애주는 함수
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)//가면되는곳까지 반복, 0은 따로 뿌려줄것임
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X + i, TilePos.Y);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y);//시작 타일
		if (i == IndexCount_) //마지막지점이 되면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X + i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X + i;
			Wave_->TileIndex_.Y = TilePos.Y;

			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Right1.bmp", "Right1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Right1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Right1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 
			Tiles_->IsWaveDeath = true;
		}
		else//마지막지점 아니면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X + i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X + i;
			Wave_->TileIndex_.Y = TilePos.Y;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Right2.bmp", "Right2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Right2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Right2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 

		}

	}
}
void MapGameObject::MakeUpWave(TileIndex _Pos, float _Power)
{

	int IndexCount_ = static_cast<int>(_Power);//파도 만들어줄 거리
	int PowerCount_ = static_cast<int>(_Power);//체크해줘야할 칸


	for (int i = 1; i <= PowerCount_; i++)//파워가 0이될때까지 체크
	{

		TileIndex TilePos = _Pos;

		if (TilePos.Y - i < 0)//--------------------------------------------벽에 부딪혔다면
		{
			IndexCount_ = i - 1;//이만큼 가면된다.
			i = PowerCount_ + 1;//여기서 for문 종료
		}
		else//벽에 안 부딪혔다면
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y - i);//현재 검사중인 타일위치
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y - i);//현재 검사중인 타일 정보

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WallBlock) //-----------------------------------------안부서지는 벽이 있을 때

			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//----------------------------- 폭탄이 있을 때
			{
				PowerCount_ += static_cast<int>(Tiles_->Power_);//파워 전달해주기
				IndexCount_ += static_cast<int>(Tiles_->Power_);
				{

					//MakeLeftWave(TilePos, Tiles_->Power_);
					//MakeRightWave(TilePos, Tiles_->Power_);
					MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);//폭탄지워주고
					for (int i = 0; i < BoomBlockTiles_.size(); i++) //벡터에서 찾아서 지워주고
					{
						if (BoomBlockTiles_[i] == Tiles_)
						{
							BoomBlockTiles_.erase(BoomBlockTiles_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr &&
				Tiles_->BlockType_ == BlockType::FixBlock && //------------------------------------------------부서지는벽
				Tiles_->BlockType_ == BlockType::PullBlock)//밀리는상자
			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = static_cast<int>(_Power) + 1;//여기서 for문 종료
				//여기서 해당 오브젝트부숴주면됨
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------이미 터지고 있을때
			{
				{

					BlockTile* CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_, Tiles_->CenterWaveY_);//검사하고 있는 웨이브의 시작점
					MapTile_->DeleteTile(TilePos.X, TilePos.Y - i);//웨이브 지워주고
					for (int i = 0; i < CenterPos_->MyWave_.size(); i++)
					{
						if (CenterPos_->MyWave_[i] == Tiles_)//웨이브 만든 시작점 찾고 거기서 벡터 지워줘야함 벡터에서 찾아서 지워주고
						{
							CenterPos_->MyWave_.erase(CenterPos_->MyWave_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock &&//-----------------------------아이템이 있을때
				Tiles_->BlockType_ == BlockType::BushBlock)//부쉬있을때
			{
				//아이템 없애주는 함수
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)//가면되는곳까지 반복, 0은 따로 뿌려줄것임
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y - i);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y);//시작 타일
		if (i == IndexCount_) //마지막지점이 되면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y - i, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X;
			Wave_->TileIndex_.Y = TilePos.Y - i;

			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Up1.bmp", "Up1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Up1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Up1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 
	
		}
		else//마지막지점 아니면
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y - i, "Empty.bmp", static_cast<int>(ORDER::EFFECT));
			Wave_->TileIndex_.X = TilePos.X;
			Wave_->TileIndex_.Y = TilePos.Y - i;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Up2.bmp", "Up2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Up2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Up2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyWave_.push_back(Wave_);//중앙타일에 벡터만들고 저장 

		}

	}
}