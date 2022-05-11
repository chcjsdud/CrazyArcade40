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
    // 1. �ƹ� �������� ������ ����
    //    ���� => ������
    //    �ڽ��� ������ ���� ����� �ڱⰡ ģ �ڵ带 �����ϱ� �Ȱų� �𸥴�
    //    ���� �װ� �� ���ؾ�
    //    �������� �տ����� ���鼭 ��Ե� �����Ϸ��� �߾��ϸ鼭
    //    �������� ���������� �� �����ϰ� �亯�� �ؾ��ϴµ�.
    //    �������� �� �ڵ带 §����̾�. �߿��� �κе��� �����ϴ°ǵ�.
    //    ����°� ������ ����°� �ƴմϴ�.
    //    �������鿡�� ���� �ڵ������� �޾�����
    //    ���� § �ڵ�ϱ� �� ������ �˰� �� �ڵ忡�� ���� ���� �ٽ����� �κе��� �˾�.
    //    �׷��� �װ� ������ �������� ���ڵ尡 �� �̷��� ����������
    //    ���� �ٽ����� �κ��̱� ������ �����е鿡�� ����ϴ�.
    //    �ű⿡ ���ؼ� �׳��̶�� �Ѵ�.
    //    


    GameEngineFile NewFile = "D:\\aaa.tt";

    NewFile.Open(OpenMode::Write);


    new int();
    GameEngine::Start<CrazyArcade>();


}