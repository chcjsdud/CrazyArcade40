#include"MapGameObject.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

MapGameObject::MapGameObject()
	:MapTile_(nullptr),
	AllBlockTiles_(),
	BoomDeathTime(0.0f),
	IsBoomDeath(false),
	WaveDeathTime(0.0f),
	IsWaveDeath(false),
	IsWaveDeathAni(false)

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
	if (IsWaveDeath == true)
	{
		WaveDeathTime -= 1.0f * GameEngineTime::GetDeltaTime();
		if (WaveDeathTime < 0.0f)
		{
			WaveDeathAni();
			DestroyWave();
		}
	}
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
	BoomDeathTime = 3.0f;
	IsBoomDeath = true;
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
	WaveBlockTiles_.push_back(Wave_);

	MakeLeftWave(TileIndex_, Power);
	MakeRightWave(TileIndex_, Power);
	MakeDownWave(TileIndex_, Power);
	MakeUpWave(TileIndex_, Power);
	WaveDeathTime = 1.5f;
	IsWaveDeath = true;
	IsWaveDeathAni = true;

}
void MapGameObject::WaveDeathAni()
{
	if (IsWaveDeathAni == true)
	{
		MapTile_->DeleteTile(WaveBlockTiles_[0]->TileIndex_.X, WaveBlockTiles_[0]->TileIndex_.Y);

		for (int i = 1; i < WaveBlockTiles_.size(); i++)
		{
			WaveBlockTiles_[i]->Renderer->ChangeAnimation("Death");
			//터지는 중앙지점 다른 wave오면 덮어씌워져야함

		}
		IsWaveDeathAni = false;
	}
}
void MapGameObject::DestroyWave()
{
	if (WaveBlockTiles_[1]->Renderer->IsEndAnimation() == true)
	{
		for (int i = 1; i < WaveBlockTiles_.size(); i++)
		{
			MapTile_->DeleteTile(WaveBlockTiles_[i]->TileIndex_.X, WaveBlockTiles_[i]->TileIndex_.Y);
		}
		IsWaveDeath = false;
		WaveBlockTiles_.clear();
	}

}
void MapGameObject::MakeLeftWave(TileIndex _Pos, float _Power)
{
	int IndexCount_ = static_cast<int>(_Power);//파도 만들어줄 거리
	int PowerCount_ = static_cast<int>(_Power);//체크해줘야할 칸
	for (int i = 1; i <= PowerCount_; i++)//파워가 0이될때까지 체크
	{

		TileIndex TilePos = _Pos;

		if (TilePos.X - i < 0)//벽에 부딪혔다면
		{
			IndexCount_ = i - 1;//이만큼 가면된다.
			i = PowerCount_ + 1;//여기서 for문 종료
		}
		else//벽에 안 부딪혔다면
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X - i, TilePos.Y);//현재 검사중인 타일위치
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X - i, TilePos.Y);//현재 검사중인 타일 정보

			if (Tiles_ != nullptr &&Tiles_->BlockType_ == BlockType::WallBlock) //안부서지는 벽이 있을 때
		
			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = PowerCount_ + 1;//여기서 for문 종료
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)// 폭탄이 있을 때
			{
				PowerCount_ += static_cast<int>(Tiles_->Power_);
				{
		
				MapTile_->DeleteTile(TileCenterPos_.x, TileCenterPos_.y);
				for (int i = 0; i < BoomBlockTiles_.size(); i++){
					if(BoomBlockTiles_[i] == Tiles_){
					BoomBlockTiles_.erase(BoomBlockTiles_.begin()+i);////벡터에서 지워줘야함
					}
				}
				BubblePop(TileCenterPos_, Tiles_->Power_);//폭탄 지워진 자리에 웨이브 만들어줌
				}
			}
			else if (Tiles_ != nullptr && 
				Tiles_->BlockType_ == BlockType::FixBlock&& //부서지는벽
				Tiles_->BlockType_ == BlockType::PullBlock)//밀리는상자
			{
				IndexCount_ = i - 1;//이만큼 가면된다.
				i = static_cast<int>(_Power) + 1;//여기서 for문 종료
				//여기서 해당 오브젝트부숴주면됨
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//이미 터지고 있을때
			{
				//나중에 터지는 친구가 덮어씌워야해서 지워줘야함
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock)//아이템이 있을때
			{
				//아이템 없애주는 함수
			}
		}



	}

	for (int i = 1; i <= IndexCount_; i++)//가면되는곳까지 반복, 0은 따로 뿌려줄것임
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X - i, TilePos.Y);

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

			WaveBlockTiles_.push_back(Wave_);
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
			WaveBlockTiles_.push_back(Wave_);

		}

	}
}
void MapGameObject::MakeDownWave(TileIndex _Pos, float _Power)
{
	int IndexCount_ = static_cast<int>(_Power);
	for (int i = 1; i <= _Power; i++)
	{

		TileIndex TilePos = _Pos;

		if (TilePos.Y + i > 13)
		{
			IndexCount_ = i - 1;
			i = static_cast<int>(_Power) + 1;
		}
		else
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y + i);
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y + i);

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::FixBlock)
			{
				IndexCount_ = i - 1;
			}

		}

	}

	for (int i = 1; i <= IndexCount_; i++)
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y + i);

		if (i == IndexCount_)
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y + i, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			Wave_->TileIndex_.X = TilePos.X;
			Wave_->TileIndex_.Y = TilePos.Y + i;

			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Down1.bmp", "Down1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Down1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Down1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);
		}
		else
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y + i, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			Wave_->TileIndex_.X = TilePos.X;
			Wave_->TileIndex_.Y = TilePos.Y + i;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Down2.bmp", "Down2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Down2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Down2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);

		}

	}
}
void MapGameObject::MakeUpWave(TileIndex _Pos, float _Power)
{
	int IndexCount_ = static_cast<int>(_Power);
	for (int i = 1; i <= _Power; i++)
	{
		TileIndex TilePos = _Pos;

		if (TilePos.Y - i < 0)
		{
			IndexCount_ = i - 1;
			i = static_cast<int>(_Power) + 1;
		}
		else
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y - i);
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y - i);

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::FixBlock)
			{
				IndexCount_ = i - 1;
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y - i);

		if (i == IndexCount_)
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y - i, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			Wave_->TileIndex_.X = TilePos.X;
			Wave_->TileIndex_.Y = TilePos.Y - i;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Up1.bmp", "Up1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Up1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Up1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);
		}
		else
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X, TilePos.Y - i, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			Wave_->TileIndex_.X = TilePos.X;
			Wave_->TileIndex_.Y = TilePos.Y - i;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Up2.bmp", "Up2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Up2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Up2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);

		}

	}
}

void MapGameObject::MakeRightWave(TileIndex _Pos, float _Power)
{
	int IndexCount_ = static_cast<int>(_Power);
	for (int i = 1; i <= _Power; i++)
	{
		TileIndex TilePos = _Pos;

		if (TilePos.X + i > 15)
		{
			IndexCount_ = i - 1;
			i = static_cast<int>(_Power) + 1;
		}
		else
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y);
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X + i, TilePos.Y);

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::FixBlock)
			{
				IndexCount_ = i - 1;
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X + i, TilePos.Y);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X + i, TilePos.Y);

		if (i == IndexCount_)
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X + i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			Wave_->TileIndex_.X = TilePos.X + i;
			Wave_->TileIndex_.Y = TilePos.Y;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Right1.bmp", "Right1", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Right1.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Right1");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);
		}
		else
		{
			BlockTile* Wave_ = MapTile_->CreateTile<BlockTile>(TilePos.X + i, TilePos.Y, "Empty.bmp", static_cast<int>(ORDER::MAPOBJECT));
			Wave_->TileIndex_.X = TilePos.X + i;
			Wave_->TileIndex_.Y = TilePos.Y;
			Wave_->BlockCol = CreateCollision("WaveCol", { 40,40 });
			Wave_->BlockType_ = BlockType::WaveBlock;
			Wave_->Renderer = CreateRenderer();
			Wave_->Renderer->CreateAnimation("Right2.bmp", "Right2", 0, 1, 0.1f, true);
			Wave_->Renderer->CreateAnimation("Right2.bmp", "Death", 2, 10, 0.05f, false);
			Wave_->Renderer->ChangeAnimation("Right2");
			Wave_->Renderer->SetPivot(TileCenterPos_);
			WaveBlockTiles_.push_back(Wave_);

		}

	}

}
