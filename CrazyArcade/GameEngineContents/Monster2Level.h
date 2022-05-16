#pragma once
class Monster2Level
{
public:
	Monster2Level();
	~Monster2Level();


	Monster2Level(const Monster2Level& _Other) = delete;
	Monster2Level(Monster2Level&& _Other) noexcept = delete;
	Monster2Level& operator=(const Monster2Level& _Other) = delete;
	Monster2Level& operator=(Monster2Level&& _Other) noexcept = delete;
protected:

private:

};