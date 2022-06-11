#pragma once
#include <GameEngineContents/MapGameObject.h>

class Area;
class BossBoom : public MapGameObject
{
public:
	BossBoom();
	~BossBoom();
	BossBoom(const BossBoom& _Other) = delete;
	BossBoom(BossBoom&& _Other) noexcept = delete;
	BossBoom& operator=(const BossBoom& _Other) = delete;
	BossBoom& operator=(BossBoom&& _Other) noexcept = delete;


public:
	void BubbleBubblePop(std::map<int, Area>& _CanAttackAreas);
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* Bubble_;
	std::map<int, Area> CanAttackAreas_;

};

