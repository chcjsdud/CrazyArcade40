#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineInput.h>
#include"TitleLevel.h"


TitleLevel::TitleLevel()
{

}
TitleLevel::~TitleLevel()
{

}
void TitleLevel::Loading()
{

}
void TitleLevel::Update()
{

    if (true == GameEngineInput::GetInst()->IsDown("MapTeamTest"))
    {
        GameEngine::GetInst().ChangeLevel("MapTeamTest");
    }
    if (true == GameEngineInput::GetInst()->IsDown("PlayerTeamTest"))
    {
        GameEngine::GetInst().ChangeLevel("PlayerTeamTest");
    }
    if (true == GameEngineInput::GetInst()->IsDown("UITeamTest"))
    {
        GameEngine::GetInst().ChangeLevel("UITeamTest");
    }
}
void TitleLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{

}
void TitleLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{

}