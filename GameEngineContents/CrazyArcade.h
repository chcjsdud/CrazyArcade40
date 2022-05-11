#pragma once
#include <GameEngine/GameEngine.h>

// ���� : �������� ������� ������ �����ϱ� �׳� ���͵�����̶� �������ϴ�.
//       �����е��� ���� �ڽ��� ������� ���ӿ� �´� �̸��� �̳༮���� �ٿ��ֽø� �˴ϴ�.
class CrazyArcade : public GameEngine
{
public:
	// constrcuter destructer
	CrazyArcade();
	~CrazyArcade();

	// delete Function
	CrazyArcade(const CrazyArcade& _Other) = delete;
	CrazyArcade(CrazyArcade&& _Other) noexcept = delete;
	CrazyArcade& operator=(const CrazyArcade& _Other) = delete;
	CrazyArcade& operator=(CrazyArcade&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

protected:

private:

};

