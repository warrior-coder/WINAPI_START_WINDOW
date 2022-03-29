#include <windows.h>


// оконна€ процедура обработки оконных сообщений
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);


// точка входа дл€ приложени€ Windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc;                        // WNDCLASS (window class) Ц класс окна
    HWND hwnd;                          // HWND (handle to the window) Ц дескриптор окна (дескриптор Ц определенное число, которое ќ— использует дл€ идентификации объектов)
    MSG msg;                            // MSG (message) Ц содержит информацию о сообщени€х из очереди сообщений потока
    LPCWSTR className = L"className";   // LPCWSTR (long pointer to const wide string) Ц константна€ строка расширенных символов кодировки Unicode


    // регистрируем класс окна
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


    // создаем главное окно
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

    // показываем окно
    ShowWindow(hwnd, SW_SHOWNORMAL);


    // основной цикл программы
    while (TRUE)
    {
        // проверка сообщени€
        // GetMessage() Ц ожидает, пока из очереди не будет получено сообщение
        // вместо нее лучше использовать PeekMessage() Ц провер€ет очередь сообщений и извлекает сообщение
        // она использует те же параметры и один параметр очереди
        if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
        {
            // обработка сообщени€
            TranslateMessage(&msg); // переводит сообщени€ виртуальных клавиш в символьные сообщени€
            DispatchMessage(&msg);  // отправл€ет сообщение оконной процедуре WindowProc()

            if (msg.message == WM_QUIT)
            {
                break;
            }
        }
    }


    // уничтожаем окно
    DestroyWindow(hwnd);

    return 0;
}

// оконна€ процедура Window Processing Function обрабатывает сообщени€ окна
// hwnd Ц дескриптор окна
// uMsg Ц код сообщени€  (например сообщение WM_KEYDOWN означает, что была нажата клавиша)
// wParam и lParam содержат дополнительную информацию, относ€щуюс€ к сообщению
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_CLOSE)
    {
        // в случае закрыти€ окна отправл€ем сообщение WM_QUIT в очередь сообщений
        PostQuitMessage(0);
    }
    else if (message == WM_PAINT)
    {
        PAINTSTRUCT ps;

        // подготавливает указанное окно к отрисовке и заполн€ет структуру PAINTSTRUCT информацией об отрисовке
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rc = ps.rcPaint; // координаты пр€моугольника дл€ заполнени€

        // создает логическую кисть указанного сплошного цвета
        HBRUSH hb = CreateSolidBrush(
            RGB(0, 0, 255)
        );

        // заполн€ет всю область указанного пр€моугольника сплошным цветом
        FillRect(hdc, &rc, hb);

        // сигнализирует о завершении отрисовки в указанном окне
        EndPaint(hwnd, &ps);

        // удал€ем кисть
        DeleteObject(hb);
    }
    else if (message == WM_KEYDOWN)
    {
        // в случае нажати€ клавиши Escape отправл€ем сообщение WM_QUIT в очередь сообщений
        if (wParam == VK_ESCAPE) PostQuitMessage(0);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}