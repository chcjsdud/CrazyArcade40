#pragma once
#include <string>
#include "ContentsEnum.h"
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


	inline void Set1P(int _Value)
	{
		Char_1P = _Value;
	}

	inline void Set2P(int _Value)
	{
		Char_2P = _Value;
	}

	inline int Get1PChar()
	{
		return Char_1P;
	}

	inline int Get2PChar()
	{
		return Char_2P;
	}


	inline void SetChoiceMap(int _Value)
	{
		ChoiceMap_ = _Value;
	}

	inline int GetChoiceMap()
	{
		return ChoiceMap_;
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

	inline void SetBubble_1P(const std::string& _BubbleName)
	{
		Bubble_1P = _BubbleName;
	}

	inline void SetBubble_2P(const std::string& _BubbleName)
	{
		Bubble_2P = _BubbleName;
	}

	std::string GetBubble_1P()
	{
		return Bubble_1P;
	}

	std::string GetBubble_2P()
	{
		return Bubble_2P;
	}

private:
	std::string NickName_1;
	std::string NickName_2;
	std::string RoomName_;
	
	int Char_1P;
	int Char_2P;
	int ChoiceMap_;

	bool Is1pUpdate_;
	bool Is2pUpdate_;

	std::string Bubble_1P;
	std::string Bubble_2P;

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

