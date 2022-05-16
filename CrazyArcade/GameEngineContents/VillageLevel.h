#pragma once

class VillageLevel
{
public:
	VillageLevel();
	~VillageLevel();


	VillageLevel(const VillageLevel& _Other) = delete;
	VillageLevel(VillageLevel&& _Other) noexcept = delete;
	VillageLevel& operator=(const VillageLevel& _Other) = delete;
	VillageLevel& operator=(VillageLevel&& _Other) noexcept = delete;
protected:

private:

};