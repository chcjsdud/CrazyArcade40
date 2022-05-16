#pragma once
class Monster1Level
{
public:
	Monster1Level();
	~Monster1Level();


	Monster1Level(const Monster1Level& _Other) = delete;
	Monster1Level(Monster1Level&& _Other) noexcept = delete;
	Monster1Level& operator=(const Monster1Level& _Other) = delete;
	Monster1Level& operator=(Monster1Level&& _Other) noexcept = delete;
protected:

private:

};