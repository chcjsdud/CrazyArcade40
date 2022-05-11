#include <Windows.h>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/CrazyArcade.h>
#include <GameEngineBase/GameEngineFile.h>

int __stdcall WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ char* lpCmdLine,
    _In_ int       nCmdShow)
{
    // 1. 아무 생각없이 이유가 없어
    //    이유 => 선생님
    //    자신의 이유가 없는 사람은 자기가 친 코드를 설명하기 싫거나 모른다
    //    내가 그걸 왜 말해야
    //    면접관들 앞에서는 떨면서 어떻게든 설명하려고 발악하면서
    //    선생님이 질문했을때 더 진지하게 답변을 해야하는데.
    //    선생님은 이 코드를 짠사람이야. 중요한 부분들을 질문하는건데.
    //    물어보는게 허투로 물어보는게 아닙니다.
    //    면접관들에게 가장 코드질문을 받았을때
    //    내가 짠 코드니까 내 약점을 알고 내 코드에서 나는 가장 핵심적인 부분들을 알아.
    //    그래서 그게 면접에 나왔을때 이코드가 왜 이렇게 질문받을때
    //    가장 핵심적인 부분이기 때문에 여러분들에게 물어봅니다.
    //    거기에 대해서 그냥이라고 한다.
    //    


    GameEngineFile NewFile = "D:\\aaa.tt";

    NewFile.Open(OpenMode::Write);


    new int();
    GameEngine::Start<CrazyArcade>();


}