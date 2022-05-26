#include "GlobalUIName.h"

GlobalUIName* GlobalUIName::Inst_ = new GlobalUIName();

GlobalUIName::GlobalUIName()
	: NickName_1("")
	, NickName_2("")
	, RoomName_("")
{
}

GlobalUIName::~GlobalUIName()
{
}
