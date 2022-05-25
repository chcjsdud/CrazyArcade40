#pragma once

enum class ORDER
{
	BACKGROUND,
	FRONTBACKGROUND,
	BlOCK,
	MAPOBJECT,
	STAGE,
	MONSTER,
	EFFECT,
	PLAYER,
	UI
};

enum class BlockType
{
	FixBlock,// �ȹи��� Ÿ��
	PullBlock,//�м��ִ� Ÿ��
	BushBlock, // �÷��̾ �� �� �ִ� Ÿ��
	ItemBlock, // �����۸� �ִ� Ÿ��
	BubbleBlock,
	CenterWaveBlock,// ��ǳ���ִ� Ÿ��
	WaveBlock, //��ǳ�� ������ ����� Ÿ��
	WallBlock,//�Ⱥμ����� Ÿ��
	NoBlock,
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
	PopScreen,
	PopScreenButton,
	StartIntroUI = 20,
	Time = 21,
	Mouse = 22,

};
