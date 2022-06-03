#include"MapGameObject.h"
#include"GameItemObject.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineString.h>
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

BlockType MapGameObject::CheckTile(float4 _Pos) {
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	if (0 > TileIndex_.X)
	{
		return BlockType::NoBlock;
	}
	if (0 > TileIndex_.Y)
	{
		return BlockType::NoBlock;
	}
	if (14 < TileIndex_.X)
	{
		return BlockType::NoBlock;
	}
	if (12 < TileIndex_.Y)
	{
		return BlockType::NoBlock;
	}

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


void MapGameObject::CreateBlock(float4 _Pos, std::string _Box)
{
	GameEngineString::ToUpper(_Box);

	if (BlockType::NoBlock == CheckTile(_Pos))
	{
		return;
	}

	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	BlockTile* Check = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	if (Check != nullptr)
	{
		return;
	}
	BlockTile* Block_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::PLAYER));
	Block_->Renderer = CreateRenderer();
	Block_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y - 4});
	Block_->Renderer->SetOrder(static_cast<int>(ORDER::PLAYER));


	//////////////////////////////////////////ķ ��///////////////////////////////////////////////

	if (_Box == "CAMPBLOCK1")
	{
		Block_->Renderer->SetImage("CampBlock1.BMP");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CAMPBLOCK2")
	{
		Block_->Renderer->SetImage("CampBlock2.BMP");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CAMPBUSH1")
	{
		Block_->Renderer->CreateAnimation("CampBush1.bmp", "CampBush1", 0, 4, 0.1f, false);
		Block_->Renderer->ChangeAnimation("CampBush1");
		Block_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y - 13.0f });
		Block_->BlockType_ = BlockType::BushBlock;
	}
	else if (_Box == "CAMPBUSH2")
	{
		Block_->Renderer->CreateAnimation("CampBush2.bmp", "CampBush2", 0, 5, 0.1f, false);
		Block_->Renderer->ChangeAnimation("CampBush2");
		Block_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y -10.0f});
		Block_->BlockType_ = BlockType::BushBlock;
	}
	else if (_Box == "CAMPMOVEBOX1")
	{
		Block_->Renderer->SetImage("CampMoveBox1.bmp");
		Block_->BlockType_ = BlockType::PullBlock;
	}
	else if (_Box == "CAMPMOVEBOX2")
	{
		Block_->Renderer->CreateAnimation("CampMoveBox2.bmp", "CampMoveBox2_1", 0, 0, 0.0f, false);
		Block_->Renderer->ChangeAnimation("CampMoveBox2_1");
		Block_->BlockHp_ = 3; 
		Block_->BlockType_ = BlockType::PullBlock;
	}
	else if (_Box == "CAMPMOVEBOX3")
	{
		Block_->Renderer->CreateAnimation("CampMoveBox2.bmp", "CampMoveBox2_3", 2, 2, 0.0f, false);
		Block_->Renderer->ChangeAnimation("CampMoveBox2_3");
		Block_->BlockHp_ = 1;
		Block_->BlockType_ = BlockType::PullBlock;
	}

	//////////////////////////////////////////���� ����///////////////////////////////////////////////

	if (_Box == "CEMETORYBLOCK1")
	{
		Block_->Renderer->SetImage("CemetoryBlock1.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK2")
	{
		Block_->Renderer->SetImage("CemetoryBlock2.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK3")
	{
		Block_->Renderer->SetImage("CemetoryBlock3.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK4")
	{
		Block_->Renderer->SetImage("CemetoryBlock4.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK5")
	{
		Block_->Renderer->SetImage("CemetoryBlock5.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK6")
	{
		Block_->Renderer->SetImage("CemetoryBlock6.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK7")
	{
		Block_->Renderer->SetImage("CemetoryBlock7.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYBLOCK8")
	{
		Block_->Renderer->SetImage("CemetoryBlock8.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYSTONE1")
	{
		Block_->Renderer->SetImage("CemetoryStone1.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYSTONE2")
	{
		Block_->Renderer->SetImage("CemetoryStone2.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "CEMETORYMOVEBOX1")
	{
		Block_->Renderer->SetImage("CemetoryMoveBox1.bmp");
		Block_->BlockType_ = BlockType::PullBlock;
	}
	else if (_Box == "CEMETORYMOVEBOX2")
	{
		Block_->Renderer->SetImage("CemetoryMoveBox2.bmp");
		Block_->BlockType_ = BlockType::PullBlock;
	}
	else if (_Box == "CEMETORYMOVEBOX2")
	{
		Block_->Renderer->SetImage("CemetoryMoveBox3.bmp");
		Block_->BlockType_ = BlockType::PullBlock;
	}

	////////////////////////////////////////// ������ ///////////////////////////////////////////////

	if (_Box == "VILLAGEBLOCK1")
	{
		Block_->Renderer->SetImage("VillageBlock1.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "VILLAGEBLOCK2")
	{
		Block_->Renderer->SetImage("VillageBlock2.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "VILLAGEMOVEBOX1")
	{
		Block_->Renderer->SetImage("VillageMoveBox1.bmp");
		Block_->BlockType_ = BlockType::PullBlock;
	}
	else if (_Box == "VILLAGEBUSH1")
	{
		Block_->Renderer->CreateAnimation("VillageBush1.bmp", "VillageBush1", 0, 4, 0.1f, false);
		Block_->Renderer->ChangeAnimation("VillageBush1");
		Block_->Renderer->SetPivot({ TileCenterPos_.x, TileCenterPos_.y - 20 });
		Block_->BlockType_ = BlockType::BushBlock;
	}

	////////////////////////////////////////// ���� ///////////////////////////////////////////////

	if (_Box == "MONSTERBLOCK1")
	{
		Block_->Renderer->SetImage("MonsterBlock1.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK2")
	{
		Block_->Renderer->SetImage("MonsterBlock2.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK3")
	{
		Block_->Renderer->SetImage("MonsterBlock3.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK4")
	{
		Block_->Renderer->SetImage("MonsterBlock4.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK5")
	{
		Block_->Renderer->SetImage("MonsterBlock5.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK6")
	{
		Block_->Renderer->SetImage("MonsterBlock6.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK7")
	{
		Block_->Renderer->SetImage("MonsterBlock7.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERBLOCK8")
	{
		Block_->Renderer->SetImage("MonsterBlock8.bmp");
		Block_->BlockType_ = BlockType::FixBlock;
	}
	else if (_Box == "MONSTERMOVEBOX1")
	{
		Block_->Renderer->SetImage("MonsterMoveBox1.bmp");
		Block_->BlockType_ = BlockType::PullBlock;
	}
	AllBlockTiles_.push_back(Block_);
}


void MapGameObject::CreateBoom(float4 _Pos, float _Power)
{
	TileIndex TileIndex_ = MapTile_->GetTileIndex(_Pos);
	float4 TileCenterPos_ = MapTile_->GetWorldPostion(TileIndex_.X, TileIndex_.Y);
	BlockTile* Check = MapTile_->GetTile<BlockTile>(TileIndex_.X, TileIndex_.Y);
	if (Check != nullptr)
	{
		return;
	}
	BlockTile* Boom_ = MapTile_->CreateTile<BlockTile>(TileIndex_.X, TileIndex_.Y, "TIleBase.bmp", static_cast<int>(ORDER::EFFECT));
	Boom_->BlockType_ = BlockType::BoomBlock;
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
	Wave_->BlockType_ = BlockType::BubbleBlock;
	Wave_->TileIndex_ = TileIndex_;
	Wave_->Renderer = CreateRenderer();
	Wave_->Renderer->SetPivot({ TileCenterPos_.x,TileCenterPos_.y });
	Wave_->Renderer->CreateAnimation("Center.bmp", "Center", 0, 5, 0.05f, true);
	Wave_->Renderer->CreateAnimation("Center.bmp", "Death", 0, 5, 0.05f, false);
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
		if (BoomBlockTiles_[i]->DeathTime_ <= 0.0f)
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
			for (int j = 0; j < WaveBlockTiles_[i]->MyLeftWave_.size(); j++)//��ǳ�� �߾ӿ��� �����ϴ� ���ٱ� ���͵��鼭
			{

				if (nullptr != WaveBlockTiles_[i]->MyLeftWave_[j]->Renderer)
				{

					WaveBlockTiles_[i]->MyLeftWave_[j]->Renderer->ChangeAnimation("Death");
					WaveBlockTiles_[i]->MyLeftWave_[j]->IsWaveDeathAni = true;
				}

			}

			for (int j = 0; j < WaveBlockTiles_[i]->MyRightWave_.size(); j++)//��ǳ�� �߾ӿ��� �����ϴ� ���ٱ� ���͵��鼭
			{
				if (nullptr != WaveBlockTiles_[i]->MyRightWave_[j]->Renderer)
				{

					WaveBlockTiles_[i]->MyRightWave_[j]->Renderer->ChangeAnimation("Death");
					WaveBlockTiles_[i]->MyRightWave_[j]->IsWaveDeathAni = true;
				}

			}
		

			for (int j = 0; j < WaveBlockTiles_[i]->MyDownWave_.size(); j++)//��ǳ�� �߾ӿ��� �����ϴ� ���ٱ� ���͵��鼭
			{
				if (nullptr != WaveBlockTiles_[i]->MyDownWave_[j]->Renderer)
				{

					WaveBlockTiles_[i]->MyDownWave_[j]->Renderer->ChangeAnimation("Death");
					WaveBlockTiles_[i]->MyDownWave_[j]->IsWaveDeathAni = true;
				}

			}

			for (int j = 0; j < WaveBlockTiles_[i]->MyUpWave_.size(); j++)//��ǳ�� �߾ӿ��� �����ϴ� ���ٱ� ���͵��鼭
			{
				if (nullptr != WaveBlockTiles_[i]->MyUpWave_[j]->Renderer)
				{

					WaveBlockTiles_[i]->MyUpWave_[j]->Renderer->ChangeAnimation("Death");
					WaveBlockTiles_[i]->MyUpWave_[j]->IsWaveDeathAni = true;
				}

			}

			WaveBlockTiles_[i]->Renderer->ChangeAnimation("Death");
			WaveBlockTiles_[i]->IsWaveDeath = false;
			
		}
		if (WaveBlockTiles_[i]->Renderer->IsEndAnimation() == true)//�ð��� ���پ�����
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
				for (int j = 0; j < WaveBlockTiles_[i]->MyLeftWave_.size(); j++)
				{

					MapTile_->DeleteTile(WaveBlockTiles_[i]->MyLeftWave_[j]->TileIndex_.X, WaveBlockTiles_[i]->MyLeftWave_[j]->TileIndex_.Y);//���ٱ� ������
				}
				for (int j = 0; j < WaveBlockTiles_[i]->MyRightWave_.size(); j++)
				{	

					MapTile_->DeleteTile(WaveBlockTiles_[i]->MyRightWave_[j]->TileIndex_.X, WaveBlockTiles_[i]->MyRightWave_[j]->TileIndex_.Y);//���ٱ� ������
				}
				for (int j = 0; j < WaveBlockTiles_[i]->MyDownWave_.size(); j++)
				{

					MapTile_->DeleteTile(WaveBlockTiles_[i]->MyDownWave_[j]->TileIndex_.X, WaveBlockTiles_[i]->MyDownWave_[j]->TileIndex_.Y);//���ٱ� ������
				}
				for (int j = 0; j < WaveBlockTiles_[i]->MyUpWave_.size(); j++)
				{

					MapTile_->DeleteTile(WaveBlockTiles_[i]->MyUpWave_[j]->TileIndex_.X, WaveBlockTiles_[i]->MyUpWave_[j]->TileIndex_.Y);//���ٱ� ������
				}

				WaveBlockTiles_[i]->MyUpWave_.clear(); //���ٱ� ���� Ŭ����
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
			ItemBlockTile* Ti_ = MapTile_->GetTile<ItemBlockTile>(TilePos.X - i, TilePos.Y);


			if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WallBlock) //-----------------------------------------�Ⱥμ����� ���� ���� ��

			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����
			}
			else if (Tiles_ != nullptr &&Tiles_->BlockType_ == BlockType::FixBlock ) //------------------------------------------------�μ����º�

			{
				MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = static_cast<int>(_Power) + 1;//���⼭ for�� ����
				//���⼭ �ش� ������Ʈ�ν��ָ��
			}
			else if (Tiles_ != nullptr&& Tiles_->BlockType_ == BlockType::PullBlock)//�и��»���
			{
				MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = static_cast<int>(_Power) + 1;//���⼭ for�� ����
				//���⼭ �ش� ������Ʈ�ν��ָ��
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BushBlock)
			{
				MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);
				IndexCount_ = i - 1;
				i = static_cast<int>(_Power) + 1;
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------�̹� ������ ������
			{
				{
			
					BlockTile*CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_,Tiles_->CenterWaveY_ );//�˻��ϰ� �ִ� ���̺��� ������
					MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);//���̺� �����ְ�
					for (int i = 0; i < CenterPos_->MyLeftWave_.size(); i++)
					{
						if (CenterPos_->MyLeftWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyLeftWave_.erase(CenterPos_->MyLeftWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyRightWave_.size(); i++)
					{
						if (CenterPos_->MyRightWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyRightWave_.erase(CenterPos_->MyRightWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyDownWave_.size(); i++)
					{
						if (CenterPos_->MyDownWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyDownWave_.erase(CenterPos_->MyDownWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyUpWave_.size(); i++)
					{
						if (CenterPos_->MyUpWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyUpWave_.erase(CenterPos_->MyUpWave_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//------------------------------wave�߾�
			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����


			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BoomBlock)//-------------------------------��ǳ���� ������
			{
				Tiles_->DeathTime_ = 0.0f;
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����


			}
		
			else if (Tiles_ != nullptr && Ti_-> BlockType_ == BlockType::ItemBlock )//-----------------------------�������� ������
			{
				GameItemObject::GameItemObject_->MapTile_->DeleteTile(TilePos.X - i, TilePos.Y);
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
			Tiles_->MyLeftWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 
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
			Tiles_->MyLeftWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 

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

			else if (Tiles_ != nullptr &&Tiles_->BlockType_ == BlockType::FixBlock)//------------------------------------------------�μ����º�
			{
				MapTile_->DeleteTile(TilePos.X + i, TilePos.Y);
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = static_cast<int>(_Power) + 1;//���⼭ for�� ����
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BushBlock)
			{
				MapTile_->DeleteTile(TilePos.X + i, TilePos.Y);
				IndexCount_ = i - 1;
				i = static_cast<int>(_Power) + 1;
			}

			else if (Tiles_ != nullptr&& Tiles_->BlockType_ == BlockType::PullBlock)//�и��»���
			{
				MapTile_->DeleteTile(TilePos.X + i, TilePos.Y);
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
					i = static_cast<int>(_Power) + 1;//���⼭ for�� ����
					//���⼭ �ش� ������Ʈ�ν��ָ��
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------�̹� ������ ������
			{
				{

					BlockTile* CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_, Tiles_->CenterWaveY_);//�˻��ϰ� �ִ� ���̺��� ������
					MapTile_->DeleteTile(TilePos.X + i, TilePos.Y);//���̺� �����ְ�
					for (int i = 0; i < CenterPos_->MyLeftWave_.size(); i++)
					{
						if (CenterPos_->MyLeftWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyLeftWave_.erase(CenterPos_->MyLeftWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyRightWave_.size(); i++)
					{
						if (CenterPos_->MyRightWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyRightWave_.erase(CenterPos_->MyRightWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyDownWave_.size(); i++)
					{
						if (CenterPos_->MyDownWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyDownWave_.erase(CenterPos_->MyDownWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyUpWave_.size(); i++)
					{
						if (CenterPos_->MyUpWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyUpWave_.erase(CenterPos_->MyUpWave_.begin() + i);
						}
					}
				}

			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//------------------------------wave�߾�
			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����


			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BoomBlock)//-------------------------------��ǳ���� ������
			{
				Tiles_->DeathTime_ = 0.0f;
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����


			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock )//-----------------------------�������� ������
			{
				GameItemObject::GameItemObject_->MapTile_->DeleteTile(TilePos.X +i, TilePos.Y);
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
			Tiles_->MyRightWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 
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
			Tiles_->MyRightWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 

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
			else if (Tiles_ != nullptr &&Tiles_->BlockType_ == BlockType::FixBlock ) //------------------------------------------------�μ����º�
			{
				MapTile_->DeleteTile(TilePos.X , TilePos.Y + i);
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = static_cast<int>(_Power) + 1;//���⼭ for�� ����
				//���⼭ �ش� ������Ʈ�ν��ָ��
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BushBlock) //------------------------------------------------�μ����º�
			{
				MapTile_->DeleteTile(TilePos.X, TilePos.Y + i);
				IndexCount_ = i - 1;
				i = static_cast<int>(_Power) + 1;
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::PullBlock)//�и��»���
			{
				MapTile_->DeleteTile(TilePos.X, TilePos.Y + i);
				IndexCount_ = i - 1;
				i = static_cast<int>(_Power) + 1;

			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------�̹� ������ ������
			{
				{

					BlockTile* CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_, Tiles_->CenterWaveY_);//�˻��ϰ� �ִ� ���̺��� ������
					MapTile_->DeleteTile(TilePos.X, TilePos.Y + i);//���̺� �����ְ�
					for (int i = 0; i < CenterPos_->MyLeftWave_.size(); i++)
					{
						if (CenterPos_->MyLeftWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyLeftWave_.erase(CenterPos_->MyLeftWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyRightWave_.size(); i++)
					{
						if (CenterPos_->MyRightWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyRightWave_.erase(CenterPos_->MyRightWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyDownWave_.size(); i++)
					{
						if (CenterPos_->MyDownWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyDownWave_.erase(CenterPos_->MyDownWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyUpWave_.size(); i++)
					{
						if (CenterPos_->MyUpWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyUpWave_.erase(CenterPos_->MyUpWave_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//------------------------------wave�߾�
			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����


			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BoomBlock)//-------------------------------��ǳ���� ������
			{
				Tiles_->DeathTime_ = 0.0f;
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����

			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock)//-----------------------------�������� ������
			{
				GameItemObject::GameItemObject_->MapTile_->DeleteTile(TilePos.X, TilePos.Y+i);
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
			Tiles_->MyDownWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 
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
			Tiles_->MyDownWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 

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
			else if (Tiles_ != nullptr &&Tiles_->BlockType_ == BlockType::FixBlock ) //------------------------------------------------�μ����º�//�и��»���
			{
				MapTile_->DeleteTile(TilePos.X, TilePos.Y -i);
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = static_cast<int>(_Power) + 1;//���⼭ for�� ����
				//���⼭ �ش� ������Ʈ�ν��ָ��
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BushBlock)
			{
				MapTile_->DeleteTile(TilePos.X, TilePos.Y - i);
				IndexCount_ = i - 1;
				i = static_cast<int>(_Power) + 1;
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::PullBlock)
			{
				MapTile_->DeleteTile(TilePos.X, TilePos.Y - i);
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = static_cast<int>(_Power) + 1;//���⼭ for�� ����
				//���⼭ �ش� ������Ʈ�ν��ָ��
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::WaveBlock)//-------------------------------�̹� ������ ������
			{
				{

					BlockTile* CenterPos_ = MapTile_->GetTile<BlockTile>(Tiles_->CenterWaveX_, Tiles_->CenterWaveY_);//�˻��ϰ� �ִ� ���̺��� ������
 					MapTile_->DeleteTile(TilePos.X, TilePos.Y - i);//���̺� �����ְ�
					for (int i = 0; i < CenterPos_->MyLeftWave_.size(); i++)
					{
						if (CenterPos_->MyLeftWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyLeftWave_.erase(CenterPos_->MyLeftWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyRightWave_.size(); i++)
					{
						if (CenterPos_->MyRightWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyRightWave_.erase(CenterPos_->MyRightWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyDownWave_.size(); i++)
					{
						if (CenterPos_->MyDownWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyDownWave_.erase(CenterPos_->MyDownWave_.begin() + i);
						}
					}
					for (int i = 0; i < CenterPos_->MyUpWave_.size(); i++)
					{
						if (CenterPos_->MyUpWave_[i] == Tiles_)//���̺� ���� ������ ã�� �ű⼭ ���� ��������� ���Ϳ��� ã�Ƽ� �����ְ�
						{
							CenterPos_->MyUpWave_.erase(CenterPos_->MyUpWave_.begin() + i);
						}
					}
				}
			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BubbleBlock)//------------------------------wave�߾�
			{
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����

			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::BoomBlock)//-------------------------------��ǳ���� ������
			{
				Tiles_->DeathTime_ = 0.0f;
				IndexCount_ = i - 1;//�̸�ŭ ����ȴ�.
				i = PowerCount_ + 1;//���⼭ for�� ����


			}
			else if (Tiles_ != nullptr && Tiles_->BlockType_ == BlockType::ItemBlock)
			{
				GameItemObject::GameItemObject_->MapTile_->DeleteTile(TilePos.X, TilePos.Y - i);
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
			Tiles_->MyUpWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 
			Tiles_->IsWaveDeath = true;
	
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
			Tiles_->MyUpWave_.push_back(Wave_);//�߾�Ÿ�Ͽ� ���͸���� ���� 

		}

	}
}