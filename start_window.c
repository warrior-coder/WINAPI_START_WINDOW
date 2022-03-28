#include <windows.h>


// ������� ��������� ��������� ������� ���������
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);


// ����� ����� ��� ���������� Windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc;                        // WNDCLASS (window class) � ����� ����
    HWND hwnd;                          // HWND (handle to the window) � ���������� ���� (���������� � ������������ �����, ������� �� ���������� ��� ������������� ��������)
    MSG msg;                            // MSG (message) � �������� ���������� � ���������� �� ������� ��������� ������
    LPCWSTR className = L"className";   // LPCWSTR (long pointer to const wide string) � ����������� ������ ����������� �������� ��������� Unicode


    // ������������ ����� ����
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = className;

    RegisterClass(&wc);


    // ������� ������� ����
    hwnd = CreateWindow(
        className,
        L"Start Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        400,
        320,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd) return 1;

    // ���������� ����
    ShowWindow(hwnd, SW_SHOWNORMAL);


    // �������� ���� ���������
    while (TRUE)
    {
        // �������� ���������
        // GetMessage() � �������, ���� �� ������� �� ����� �������� ���������
        // ������ ��� ����� ������������ PeekMessage() � ��������� ������� ��������� � ��������� ���������
        // ��� ���������� �� �� ��������� � ���� �������� �������
        if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
        {
            // ��������� ���������
            TranslateMessage(&msg); // ��������� ��������� ����������� ������ � ���������� ���������
            DispatchMessage(&msg);  // ���������� ��������� ������� ��������� WindowProc()

            if (msg.message == WM_QUIT)
            {
                break;
            }
        }
    }


    // ���������� ����
    DestroyWindow(hwnd);

    return 0;
}

// ������� ��������� Window Processing Function ������������ ��������� ����
// hwnd � ���������� ����
// uMsg � ��� ���������  (�������� ��������� WM_KEYDOWN ��������, ��� ���� ������ �������)
// wParam � lParam �������� �������������� ����������, ����������� � ���������
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_CLOSE)
    {
        // � ������ �������� ���� ���������� ��������� WM_QUIT � ������� ���������
        PostQuitMessage(0);
    }
    else if (message == WM_PAINT)
    {
        PAINTSTRUCT ps;

        // �������������� ��������� ���� � ��������� � ��������� ��������� PAINTSTRUCT ����������� �� ���������
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rc = ps.rcPaint; // ���������� �������������� ��� ����������

        // ������� ���������� ����� ���������� ��������� �����
        HBRUSH hb = CreateSolidBrush(
            RGB(0, 0, 255)
        );

        // ��������� ��� ������� ���������� �������������� �������� ������
        FillRect(hdc, &rc, hb);

        // ������������� � ���������� ��������� � ��������� ����
        EndPaint(hwnd, &ps);

        // ������� �����
        DeleteObject(hb);
    }
    else if (message == WM_KEYDOWN)
    {
        // � ������ ������� ������� Escape ���������� ��������� WM_QUIT � ������� ���������
        if (wParam == VK_ESCAPE) PostQuitMessage(0);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}