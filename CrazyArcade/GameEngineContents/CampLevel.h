#pragma once
class CampLevel
{
public:
	CampLevel();
	~CampLevel();


	CampLevel(const CampLevel& _Other) = delete;
	CampLevel(CampLevel&& _Other) noexcept = delete;
	CampLevel& operator=(const CampLevel& _Other) = delete;
	CampLevel& operator=(CampLevel&& _Other) noexcept = delete;
protected:

private:

};