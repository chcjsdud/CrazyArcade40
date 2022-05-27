#pragma once
#include "GameEnginePath.h"

enum class OpenMode
{
	Read,
	Write,
};

// Ό³Έν :
class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const char* _Path);
	GameEngineFile(std::filesystem::path _Path);
	GameEngineFile(const GameEngineFile& _Other);
	~GameEngineFile();

	// delete Function
	void Open(OpenMode _Mode);

	void ReadOpen() 
	{
		Open(OpenMode::Read);
	}

	void WriteOpen()
	{
		Open(OpenMode::Write);
	}

	void Close();

	void Create()
	{
		Open(OpenMode::Write);
		Close();
	}

	void Write(const std::string& _Name)
	{
		int Size = static_cast<int>(_Name.size());
		Write(&Size, sizeof(int));

		Write(_Name.c_str(), _Name.size());
	}

	void Write(const void* _Data, size_t _Size)
	{
		fwrite(_Data, _Size, 1, FilePtr);
	}


	void Read(std::string& _Name)
	{
		_Name.clear();
		int Size = static_cast<int>(_Name.size());
		Read(&Size, sizeof(int));
		_Name.resize(Size);
		Read(&_Name[0], Size);
	}


	void Read(void* _Data, size_t _Size)
	{
		fread_s(_Data, _Size, _Size, 1, FilePtr);
	}

protected:


private:
	FILE* FilePtr;
};

