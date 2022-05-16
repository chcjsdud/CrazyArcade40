#pragma once
class CemeteryLevel
{
public:
	CemeteryLevel();
	~CemeteryLevel();


	CemeteryLevel(const CemeteryLevel& _Other) = delete;
	CemeteryLevel(CemeteryLevel&& _Other) noexcept = delete;
	CemeteryLevel& operator=(const CemeteryLevel& _Other) = delete;
	CemeteryLevel& operator=(CemeteryLevel&& _Other) noexcept = delete;
protected:

private:

};