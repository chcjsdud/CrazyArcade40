#include "GlobalUIName.h"

GlobalUIName* GlobalUIName::Inst_ = new GlobalUIName();

GlobalUIName::GlobalUIName()
	: NickName_1("")
	, NickName_2("")
	, RoomName_("")
	, Char_1P(0)
	, Char_2P(2)
{
}

GlobalUIName::~GlobalUIName()
{
}
