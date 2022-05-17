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
	FixBlock,
	PullBlock,
	BushBlock,
	ItemBlock,
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