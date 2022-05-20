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

// ���� ������� ��ġ�� �־��ְ� ItemType �� max�� �ƴ϶�� createItem�� ���ش�.
void MapGameObject::CreateItem(float4 _Pos)
{
	//if (ItemType::Max == CheckItem(_Pos))
	//{
	//	return;
	//};

	// ���� �������� ������ ������
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	BlockTile* Tiles_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::EFFECT));
	Tiles_->Renderer = CreateRenderer();
	Tiles_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y}); // ������ y�� 90�̾���Ѵ�.

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
void MapGameObject::WaveDeathAni()
{
	for (int i = 0; i < WaveBlockTiles_.size(); i++) // ��ǳ�� �߾� Ž��
	{
		if (WaveBlockTiles_[i]->IsWaveDeath == true) // ��ǳ�� �ĵ��� �� �����������
		{
			for (int j = 0; j < WaveBlockTiles_[i]->MyWave_.size(); j++)//��ǳ�� �߾ӿ��� �����ϴ� ���ٱ� ���͵��鼭
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
		if (WaveBlockTiles_[i]->MyWave_[0]->Renderer->IsEndAnimation() == true)//�ð��� ���پ�����
		{
			WaveBlockTiles_[i]->IsWaveDeathAni = true;
		}
	}
}
void MapGameObject::DestroyWave()
{

	for (int i = 0; i < WaveBlockTiles_.size(); i++)//��ǳ�� ���� ���ٰ�
	{
		if (WaveBlockTiles_[i]->IsWaveDeathAni == true)//�״� �ִ�����̸�
		{
			{
				for (int j = 0; j < WaveBlockTiles_[i]->MyWave_.size(); j++)
				{

					MapTile_->DeleteTile(WaveBlockTiles_[i]->MyWave_[j]->TileIndex_.X, WaveBlockTiles_[i]->MyWave_[j]->TileIndex_.Y);//���ٱ� ������
				}
				WaveBlockTiles_[i]->MyWave_.clear(); //���ٱ� ���� Ŭ����
				MapTile_->DeleteTile(WaveBlockTiles_[i]->TileIndex_.X, WaveBlockTiles_[i]->TileIndex_.Y);//�߾Ӻκ������
				WaveBlockTiles_.erase(WaveBlockTiles_.begin() + i);//�߾Ӻ��� �����
			}
		}

	}
}

void MapGameObject::MakeLeftWave(TileIndex _Pos, float _Power)
{

	int IndexCount_ = static_cast<int>(_Power);//�ĵ� ������� �Ÿ�
	int PowerCount_ = static_cast<int>(_Power);//üũ������� ĭ


	for (int i = 1; i <= PowerCount_; i++)//�Ŀ��� 0�̵ɶ����� üũ
	{

		TileIndex TilePos = _Pos;

		if (TilePos.X - i < 0)//--------------------------------------------�ʿ� �ε����ٸ�
		{
			IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
			i = PowerCount_ + 1;//���⼭ for�� ����
		}
		else//�ʿ� �� �ε����ٸ�
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X - i, TilePos.Y);//���� �˻����� Ÿ����ġ
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X - i, TilePos.Y);//���� �˻����� Ÿ�� ����

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WallBlock) //-----------------------------------------�Ⱥμ����� ���� ���� ��

			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//----------------------------- ��ź�� ���� ��
			{
				PowerCount_ += static_cast<int>(Tiles_->Power_);//�Ŀ� �������ֱ�
				IndexCount_ += static_cast<int>(Tiles_->Power_);
				{

					//MakeDownWave(TilePos, Tiles_->Power_);	//�������� ���ٰ� �������ϱ� �� �Ʒ��� ���ٱ� �������
					//MakeUpWave(TilePos, Tiles_->Power_);
					MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);//��ź�����ְ�
					for (int i = 0; i < BoomBlockTiles_.size(); i++) //���Ϳ��� ã�Ƽ� �����ְ�
					{
						if (BoomBlockTiles_[i] == Tiles_)
						{
							BoomBlockTiles_.erase(BoomBlockTiles_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr &&
				Tiles_->BlockType_ == BlockType::FixBlock && //------------------------------------------------�μ����º�
				Tiles_->BlockType_ == BlockType::PullBlock)//�и��»���
			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = static_cast<int>(_Power) + 1;//���⼭ for�� ����
				//���⼭ �ش� ������Ʈ�ν��ָ��
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------�̹� ������ ������
			{
				{
			
					BlockTile*CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_,Tiles_->CenterWaveY_ );//�˻��ϰ� �ִ� ���̺��� ������
					MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);//���̺� �����ְ�
					for (int i = 0; i < CenterPos_->MyWave_.size(); i++) 
					{
						if (CenterPos_->MyWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyWave_.erase(CenterPos_->MyWave_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock &&//-----------------------------�������� ������
				Tiles_->BlockType_ == BlockType::BushBlock)//�ν�������
			{
				//������ �����ִ� �Լ�
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)//����Ǵ°����� �ݺ�, 0�� ���� �ѷ��ٰ���
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X - i, TilePos.Y);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y);//���� Ÿ��
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
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 
			Tiles_->IsWaveDeath = true;
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
			Wave_->CenterWaveX_ = TilePos.X;
			Wave_->CenterWaveY_ = TilePos.Y;
			Tiles_->MyWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 

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
				Tiles_->BlockType_ == BlockType::FixBlock && //------------------------------------------------�μ����º�
				Tiles_->BlockType_ == BlockType::PullBlock)//�и��»���
			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = static_cast<int>(_Power) + 1;//���⼭ for�� ����
				//���⼭ �ش� ������Ʈ�ν��ָ��
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------�̹� ������ ������
			{
				{

					BlockTile* CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_, Tiles_->CenterWaveY_);//�˻��ϰ� �ִ� ���̺��� ������
					MapTile_->DeleteTile(TilePos.X, TilePos.Y + i);//���̺� �����ְ�
					for (int i = 0; i < CenterPos_->MyWave_.size(); i++)
					{
						if (CenterPos_->MyWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyWave_.erase(CenterPos_->MyWave_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock &&//-----------------------------�������� ������
				Tiles_->BlockType_ == BlockType::BushBlock)//�ν�������
			{
				//������ �����ִ� �Լ�
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)//����Ǵ°����� �ݺ�, 0�� ���� �ѷ��ٰ���
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y+i);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y);//���� Ÿ��
		if (i == IndexCount_) //������������ �Ǹ�
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
			Tiles_->MyWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 
			Tiles_->IsWaveDeath = true;
		}
		else//���������� �ƴϸ�
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
			Tiles_->MyWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 

		}

	}
}
void MapGameObject::MakeRightWave(TileIndex _Pos, float _Power)
{

	int IndexCount_ = static_cast<int>(_Power);//�ĵ� ������� �Ÿ�
	int PowerCount_ = static_cast<int>(_Power);//üũ������� ĭ


	for (int i = 1; i <= PowerCount_; i++)//�Ŀ��� 0�̵ɶ����� üũ
	{

		TileIndex TilePos = _Pos;

		if (TilePos.X + i > 14)//--------------------------------------------���� �ε����ٸ�
		{
			IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
			i = PowerCount_ + 1;//���⼭ for�� ����
		}
		else//���� �� �ε����ٸ�
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X + i, TilePos.Y);//���� �˻����� Ÿ����ġ
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X + i, TilePos.Y);//���� �˻����� Ÿ�� ����

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WallBlock) //-----------------------------------------�Ⱥμ����� ���� ���� ��

			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//----------------------------- ��ź�� ���� ��
			{
				PowerCount_ += static_cast<int>(Tiles_->Power_);//�Ŀ� �������ֱ�
				IndexCount_ += static_cast<int>(Tiles_->Power_);
				{

					//MakeDownWave(TilePos, Tiles_->Power_);	
					//MakeUpWave(TilePos, Tiles_->Power_);
					MapTile_->DeleteTile(TilePos.X + i, TilePos.Y);//��ź�����ְ�
					for (int i = 0; i < BoomBlockTiles_.size(); i++) //���Ϳ��� ã�Ƽ� �����ְ�
					{
						if (BoomBlockTiles_[i] == Tiles_)
						{
							BoomBlockTiles_.erase(BoomBlockTiles_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr &&
				Tiles_->BlockType_ == BlockType::FixBlock && //------------------------------------------------�μ����º�
				Tiles_->BlockType_ == BlockType::PullBlock)//�и��»���
			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = static_cast<int>(_Power) + 1;//���⼭ for�� ����
				//���⼭ �ش� ������Ʈ�ν��ָ��
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------�̹� ������ ������
			{
				{

					BlockTile* CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_, Tiles_->CenterWaveY_);//�˻��ϰ� �ִ� ���̺��� ������
					MapTile_->DeleteTile(TilePos.X + i, TilePos.Y);//���̺� �����ְ�
					for (int i = 0; i < CenterPos_->MyWave_.size(); i++)
					{
						if (CenterPos_->MyWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyWave_.erase(CenterPos_->MyWave_.begin() + i);
						}
					}
				}
			
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock &&//-----------------------------�������� ������
				Tiles_->BlockType_ == BlockType::BushBlock)//�ν�������
			{
				//������ �����ִ� �Լ�
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)//����Ǵ°����� �ݺ�, 0�� ���� �ѷ��ٰ���
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X + i, TilePos.Y);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y);//���� Ÿ��
		if (i == IndexCount_) //������������ �Ǹ�
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
			Tiles_->MyWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 
			Tiles_->IsWaveDeath = true;
		}
		else//���������� �ƴϸ�
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
			Tiles_->MyWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 

		}

	}
}
void MapGameObject::MakeUpWave(TileIndex _Pos, float _Power)
{

	int IndexCount_ = static_cast<int>(_Power);//�ĵ� ������� �Ÿ�
	int PowerCount_ = static_cast<int>(_Power);//üũ������� ĭ


	for (int i = 1; i <= PowerCount_; i++)//�Ŀ��� 0�̵ɶ����� üũ
	{

		TileIndex TilePos = _Pos;

		if (TilePos.Y - i < 0)//--------------------------------------------���� �ε����ٸ�
		{
			IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
			i = PowerCount_ + 1;//���⼭ for�� ����
		}
		else//���� �� �ε����ٸ�
		{
			float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y - i);//���� �˻����� Ÿ����ġ
			BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y - i);//���� �˻����� Ÿ�� ����

			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WallBlock) //-----------------------------------------�Ⱥμ����� ���� ���� ��

			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//----------------------------- ��ź�� ���� ��
			{
				PowerCount_ += static_cast<int>(Tiles_->Power_);//�Ŀ� �������ֱ�
				IndexCount_ += static_cast<int>(Tiles_->Power_);
				{

					//MakeLeftWave(TilePos, Tiles_->Power_);
					//MakeRightWave(TilePos, Tiles_->Power_);
					MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);//��ź�����ְ�
					for (int i = 0; i < BoomBlockTiles_.size(); i++) //���Ϳ��� ã�Ƽ� �����ְ�
					{
						if (BoomBlockTiles_[i] == Tiles_)
						{
							BoomBlockTiles_.erase(BoomBlockTiles_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr &&
				Tiles_->BlockType_ == BlockType::FixBlock && //------------------------------------------------�μ����º�
				Tiles_->BlockType_ == BlockType::PullBlock)//�и��»���
			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = static_cast<int>(_Power) + 1;//���⼭ for�� ����
				//���⼭ �ش� ������Ʈ�ν��ָ��
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------�̹� ������ ������
			{
				{

					BlockTile* CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_, Tiles_->CenterWaveY_);//�˻��ϰ� �ִ� ���̺��� ������
					MapTile_->DeleteTile(TilePos.X, TilePos.Y - i);//���̺� �����ְ�
					for (int i = 0; i < CenterPos_->MyWave_.size(); i++)
					{
						if (CenterPos_->MyWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyWave_.erase(CenterPos_->MyWave_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock &&//-----------------------------�������� ������
				Tiles_->BlockType_ == BlockType::BushBlock)//�ν�������
			{
				//������ �����ִ� �Լ�
			}
		}
	}

	for (int i = 1; i <= IndexCount_; i++)//����Ǵ°����� �ݺ�, 0�� ���� �ѷ��ٰ���
	{
		TileIndex TilePos = _Pos;
		float4 TileCenterPos_ = MapTile_->GetWorldPostion(TilePos.X, TilePos.Y - i);
		BlockTile* Tiles_ = MapTile_->GetTile<BlockTile>(TilePos.X, TilePos.Y);//���� Ÿ��
		if (i == IndexCount_) //������������ �Ǹ�
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
			Tiles_->MyWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 
	
		}
		else//���������� �ƴϸ�
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
			Tiles_->MyWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 

		}

	}
}