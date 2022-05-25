#include "GameEngineWindow.h"
#include "GameEngineInput.h"
#include <GameEngine/KeyboardClass.h>
#include <GameEngine/KeyboardEvent.h>


// HWND hWnd � �����쿡 �������� ������� �� �������� �ڵ�
// UINT message �� �޼����� �߷ᰡ ����.
// WPARAM wParam
// LPARAM lParam

LRESULT CALLBACK GameEngineWindow::MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    {
        GameEngineWindow::GetInst().Off();
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_CLOSE:
    {
        GameEngineWindow::GetInst().Off();
        break;
    }
    case WM_MOUSEWHEEL:
    {
        GameEngineInput::GetInst()->WheelValue = (SHORT)HIWORD(wParam);
        break;
    }
    // Ű���� ���(ä�ñ�ɿ�)
    case WM_CHAR:
    {
        unsigned char ch = static_cast<unsigned char>(wParam);

        // ����ó�� : �ش� Ű���� input�� ����Ͽ� �����
        if (ch == '\b') // BackSpace Key Down
        {
            int a = 0;

            break;
        }
        else if (ch == '\r') // Enter Key Down
        {
            break;
        }

        // ���� �Է¿� ���� ť ���
        if (KeyboardClass::GetInst().IsCharsAutoRepeat())
        {
            KeyboardClass::GetInst().OnChar(ch);
        }
        else
        {
            const bool wasPressed = lParam & 0x40000000;
            if (!wasPressed)
            {
                KeyboardClass::GetInst().OnChar(ch);
            }
        }
        return 0;
    }
    case WM_KEYDOWN:
    {
        unsigned char keycode = static_cast<unsigned char>(wParam);

        // ����ó�� : �ش� Ű���� input�� ����Ͽ� �����
        if (keycode == '\b') // BackSpace Key Down
        {
            break;
        }
        else if (keycode == '\r') // Enter Key Down
        {
            break;
        }
        else if (keycode == ' ') // Space Key Down
        {
            break;
        }

        if (KeyboardClass::GetInst().IsKeysAutoRepeat())
        {
            KeyboardClass::GetInst().OnKeyPressed(keycode);
        }
        else
        {
            const bool wasPressed = lParam & 0x40000000;
            if (!wasPressed)
            {
                KeyboardClass::GetInst().OnKeyPressed(keycode);
            }
        }

        return 0;
    }
    case WM_KEYUP:
    {
        unsigned char keycode = static_cast<unsigned char>(wParam);
        KeyboardClass::GetInst().OnKeyReleased(keycode);

        return 0;
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

GameEngineWindow::GameEngineWindow() 
    : hInst_(nullptr)
    , hWnd_(nullptr)
    , WindowOn_(true)
    , HDC_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow() 
{
    // ���� ������ذ� �ƴ϶�� �� ������� �մϴ�.
    if (nullptr != HDC_)
    {
        ReleaseDC(hWnd_, HDC_);
        HDC_ = nullptr;
    }

    if (nullptr != hWnd_)
    {
        DestroyWindow(hWnd_);
        hWnd_ = nullptr;
    }
}

void GameEngineWindow::Off() 
{
    WindowOn_ = false;
}
void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    // ������ Ŭ���� ���
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MessageProcess;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";
    wcex.hIconSm = nullptr;
    RegisterClassExA(&wcex);
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    if (nullptr != hInst_)
    {
        MsgBoxAssert("�����츦 2�� ������ �߽��ϴ�.");
        return;
    }

    Title_ = _Title;
        // Ŭ���� ����� 1���� �Ϸ��� ģ �ڵ�
    hInst_ = _hInst;
    RegClass(_hInst);

    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", Title_.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    // ȭ�鿡 ���𰡸� �׸��� ���� �ڵ��Դϴ�.
    HDC_ = GetDC(hWnd_);

    if (!hWnd_)
    {
        return;
    }
}

void GameEngineWindow::ShowGameWindow() 
{
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("���� �����찡 ��������� �ʾҽ��ϴ� ȭ�鿡 ����Ҽ� �����ϴ�.");
        return;
    }

    // �̰� ȣ��Ǳ� �������� �׸����� ����.
    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}


void GameEngineWindow::MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)())
{
    // ������� �� �غ�Ǿ���.
    // ������ ��������
    // ���� �غ��Ұ� �ִٸ� �غ��Լ��� �����ش޶�.

    if (nullptr != _InitFunction)
    {
        _InitFunction();
    }

    MSG msg;

    // ������ ���ο����� ������ ������
    // std::list<MSG> MessageQueue;
    // �޼����� ó���ߴٸ� MessageQueue.clear();

    // �� while�� 1�ʿ� 60�� ���� 60������
    // 3000�������̶�°�?

    while (WindowOn_)
    {
        if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

            // �����찡 ������ �ʴ� ���� Ÿ��.
            // ���⼭ ���������� �������?

        if (nullptr == _LoopFunction)
        {
            continue;
        }

        _LoopFunction();

        
    }
}

void GameEngineWindow::SetWindowScaleAndPosition(float4 _Pos, float4 _Scale) 
{
    // �޴��� 

    RECT Rc = { 0, 0,  _Scale.ix(),  _Scale.iy() };

    // 1280 + �޴���

    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    Scale_ = _Scale;

    SetWindowPos(hWnd_, nullptr, _Pos.ix(), _Pos.iy(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}