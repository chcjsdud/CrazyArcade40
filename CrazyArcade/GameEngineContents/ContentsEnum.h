#pragma once

enum class ORDER
{
	BACKGROUND,
	FRONTBACKGROUND,
	STAGE,
	MONSTER,
	PLAYER,
	EFFECT,
	UI
};

enum class BlockType
{
	FixBlock,// 안밀리는 타일
	PullBlock,//밀수있는 타일
	BushBlock, // 플레이어가 들어갈 수 있는 타일
	ItemBlock, // 아이템만 있는 타일
	BubbleBlock, // 물풍선있는 타일
	WaveBlock, //물풍선 터질때 생기는 타일
	Max
};

enum class ItemType
{
	Roller,
	Bubble,
	Fluid,
	RedDevil,
	Glove,
	Shoes,
	Max
};
enum class UIType
{
	BackGround,
	BackGroundButton,
	PopUp,
	PopUpButton,
	Mouse
};
