#pragma once
#include <string>
class GlobalUIName
{
private:
	static GlobalUIName* Inst_;

public:
	static GlobalUIName* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}
public:
	const std::string& GetNickName_1ConstRef()
	{
		return NickName_1;
	}

	const std::string& GetNickName_2ConstRef()
	{
		return NickName_2;
	}

	const std::string& GetRoomName_ConstRef()
	{
		return 	RoomName_;
	}

	inline void SetNickName_1(const std::string& _Name)
	{
		NickName_1 = _Name;
	}

	inline void SetNickName_2(const std::string& _Name)
	{
		NickName_2 = _Name;
	}
	inline void SetRoomName(const std::string& _Name)
	{
		RoomName_ = _Name;
	}
private:
	std::string NickName_1;
	std::string NickName_2;
	std::string RoomName_;

	

public:
	//construcuter destructer
	GlobalUIName();
	~GlobalUIName();

	//delete Function
	GlobalUIName(const GlobalUIName& _Other) = delete;
	GlobalUIName(GlobalUIName&& _Other) noexcept = delete;
	GlobalUIName& operator=(const GlobalUIName& _Other) = delete;
	GlobalUIName& operator=(GlobalUIName&& _Other) noexcept = delete;
};

