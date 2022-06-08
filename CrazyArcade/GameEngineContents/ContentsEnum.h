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
	FixBlock,// 안밀리는 타일
	PullBlock,//밀수있는 타일
	BushBlock, // 플레이어가 들어갈 수 있는 타일
	ItemBlock, // 아이템만 있는 타일
	BubbleBlock,
	BoomBlock,// 물풍선있는 타일
	WaveBlock, //물풍선 터질때 생기는 타일
	WallBlock,//안부서지는 타일
	NoBlock,
	NiddleBlock//가시있는 블록

};

enum class ItemType
{
	Max,
	Roller,//스피드+1
	Bubble,//풍선갯수+1
	Fluid,//물줄기+1
	UltraBubble,//물줄기Max
	RedDevil,//스피드MAx
	Devil,//입출력 반전
	Shoes,//물풍선 킥

	Niddle,//탈출
	Shield,//쉴드동안무적
	SuperJump,//한칸 점프

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