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
	Max,
	FixBlock,// �ȹи��� Ÿ��
	PullBlock,//�м��ִ� Ÿ��
	BushBlock, // �÷��̾ �� �� �ִ� Ÿ��
	ItemBlock, // �����۸� �ִ� Ÿ��
	BubbleBlock,
	BoomBlock,// ��ǳ���ִ� Ÿ��
	WaveBlock, //��ǳ�� ������ ����� Ÿ��
	WallBlock,//�Ⱥμ����� Ÿ��
	NoBlock,
	NiddleBlock//�����ִ� ���

};

enum class ItemType
{
	Max,
	Roller,//���ǵ�+1
	Bubble,//ǳ������+1
	Fluid,//���ٱ�+1
	UltraBubble,//���ٱ�Max
	RedDevil,//���ǵ�MAx
	Devil,//����� ����
	Shoes,//��ǳ�� ű

	Niddle,//Ż��
	Shield,//���嵿�ȹ���
	SuperJump,//��ĭ ����

	Turtle,
	SpaceShip,
	Owl,

	Bubble_Dark,
	Bubble_Boss,
	Bubble_Default

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

enum class Character
{
	BAZZI,
	LUXMARID,
	DAO,

	MAX,
};