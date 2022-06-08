#pragma once

enum class ORDER
{
	BACKGROUND,
	FRONTBACKGROUND,
	BlOCK,
	STAGE,
	MAPOBJECT,
	EFFECT,
	PLAYER,
	BOSS,
	UI
};
enum class BlockDir
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX
};
enum class BlockType
{
	FixBlock,// �ȹи��� Ÿ��
	PullBlock,//�м��ִ� Ÿ��
	BushBlock, // �÷��̾ �� �� �ִ� Ÿ��
	ItemBlock, // �����۸� �ִ� Ÿ��
	BubbleBlock,
	BoomBlock,// ��ǳ���ִ� Ÿ��
	WaveBlock, //��ǳ�� ������ ����� Ÿ��
	WallBlock,//�Ⱥμ����� Ÿ��
	NoBlock,
	NiddleBlock,//�����ִ� ���
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

	PlayResultUI = 19,
	StartIntroUI = 20,
	Time = 21,
	Mouse = 22,

};
