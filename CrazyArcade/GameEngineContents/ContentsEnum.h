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
	FixBlock,// �ȹи��� Ÿ��
	PullBlock,//�м��ִ� Ÿ��
	BushBlock, // �÷��̾ �� �� �ִ� Ÿ��
	ItemBlock, // �����۸� �ִ� Ÿ��
	BubbleBlock, // ��ǳ���ִ� Ÿ��
	WaveBlock, //��ǳ�� ������ ����� Ÿ��
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
