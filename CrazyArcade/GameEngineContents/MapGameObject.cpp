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

// �÷��̾ ���ִ� ��ġ�� Ÿ���� � Ÿ���� ������ �˷��ִ� �Լ� return ���� Max�̸� - �ƹ��͵� ���� Ÿ���Դϴ�.
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
// �÷��̾ ���ִ� ��ġ�� Ÿ���� BlockType�� �����ۺ���̶�� , �������� �������������� üũ�ϴ� �Լ��Դϴ�. ��ġ�־��ָ� ������Ÿ���� ���ϵ˴ϴ�. 
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

void MapGameObject::DestroyBoom()//��ź���� ���� Ÿ�̸� ����
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
			BubblePop(_Poss, _Power);//��ź ������ �ڸ��� ���̺� �������
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
			//������ �߾����� �ٸ� wave���� �����������

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
	int IndexCount_ = static_cast<int>(_Power);//�ĵ� ������� �Ÿ�
	int PowerCount_ = static_cast<int>(_Power);//üũ������� ĭ
	for (int i = 1; i <= PowerCount_; i++)//�Ŀ��� 0�̵ɶ����� üũ
	{

		TileIndex TilePos = _Pos;

		if (TilePos.X - i < 0)//���� �ε����ٸ�
		{
			IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
			i = PowerCount_ + 1;//���⼭ for�� ����
		}
		else//���� �� �ε����ٸ�
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X - i, TilePos.Y);//���� �˻����� Ÿ����ġ
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X - i, TilePos.Y);//���� �˻����� Ÿ�� ����

			if (Tiles_ != nullptr &&Tiles_->BlockType_ == BlockType::WallBlock) //�Ⱥμ����� ���� ���� ��
		
			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)// ��ź�� ���� ��
			{
				PowerCount_ += static_cast<int>(Tiles_->Power_);
				{
		
				MapTile_->DeleteTile(TileCenterPos_.x, TileCenterPos_.y);
				for (int i = 0; i < BoomBlockTiles_.size(); i++){
					if(BoomBlockTiles_[i] == Tiles_){
					BoomBlockTiles_.erase(BoomBlockTiles_.begin()+i);////���Ϳ��� ���������
					}
				}
				BubblePop(TileCenterPos_, Tiles_->Power_);//��ź ������ �ڸ��� ���̺� �������
				}
			}
			else if (Tiles_ != nullptr && 
				Tiles_->BlockType_ == BlockType::FixBlock&& //�μ����º�
				Tiles_->BlockType_ == BlockType::PullBlock)//�и��»���
			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = static_cast<int>(_Power) + 1;//���⼭ for�� ����
				//���⼭ �ش� ������Ʈ�ν��ָ��
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//�̹� ������ ������
			{
				//���߿� ������ ģ���� ��������ؼ� ���������
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock)//�������� ������
			{
				//������ �����ִ� �Լ�
			}
		}



	}

	for (int i = 1; i <= IndexCount_; i++)//����Ǵ°����� �ݺ�, 0�� ���� �ѷ��ٰ���
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X - i, TilePos.Y);

		if (i == IndexCount_) //������������ �Ǹ�
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
		else//���������� �ƴϸ�
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
