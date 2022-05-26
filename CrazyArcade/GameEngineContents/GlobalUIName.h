#pragma once
#include <string>
class GlobalUIName
{
private:
	static GlobalUIName* Inst_;

public:
	inline static GlobalUIName* GetInst()
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

	bool Is1pUpdate()
	{
		return Is1pUpdate_;
	}

	bool Is2pUpdate()
	{
		return Is2pUpdate_;
	}

	void On1P()
	{
		Is1pUpdate_ = true;
	}
	
	void Off1P()
	{
		Is1pUpdate_ = false;
	}
	
	void On2P()
	{
		Is2pUpdate_ = true;
	}

	void Off2P()
	{
		Is2pUpdate_ = false;
	}

private:
	std::string NickName_1;
	std::string NickName_2;
	std::string RoomName_;

	bool Is1pUpdate_;
	bool Is2pUpdate_;


private:
	//construcuter destructer
	GlobalUIName();
	~GlobalUIName();

	//delete Function
	GlobalUIName(const GlobalUIName& _Other) = delete;
	GlobalUIName(GlobalUIName&& _Other) noexcept = delete;
	GlobalUIName& operator=(const GlobalUIName& _Other) = delete;
	GlobalUIName& operator=(GlobalUIName&& _Other) noexcept = delete;
};

