//#include <windows.h>
//#include <stdlib.h>  // For using rand() and srand()
//#include <time.h>    // For initializing the random number generator
//
//void DrawChristmasTree(HDC hdc, int x, int y) {
//    int treeHeight = 150;   // Высота елки
//    int treeWidth = 100;    // Ширина елки
//    int trunkHeight = 30;   // Высота ствола
//    int trunkWidth = 20;    // Ширина ствола
//    int ornamentRadius = 5; // Радиус шарика
//
//    // Рисуем ствол
//    HBRUSH brushTrunk = CreateSolidBrush(RGB(139, 69, 19)); // Цвет ствола - коричневый
//    SelectObject(hdc, brushTrunk);
//    Rectangle(hdc, x - trunkWidth / 2, y, x + trunkWidth / 2, y + trunkHeight);
//    DeleteObject(brushTrunk);
//
//    // Рисуем елку
//    HBRUSH brushTree = CreateSolidBrush(RGB(34, 139, 34)); // Темно-зеленый цвет
//    POINT points[3] = {
//        {x, y - treeHeight},
//        {x - treeWidth / 2, y},
//        {x + treeWidth / 2, y}
//    };
//    SelectObject(hdc, brushTree);
//    Polygon(hdc, points, 3);
//
//    // Рисуем шарики в фиксированных местах
//    POINT ornaments[5] = {
//        {x, y - treeHeight + 45},
//        {x - 15, y - (treeHeight / 2) + 10},
//        {x + 15, y - (treeHeight) / 2 + 22},
//        {x - 25, y - (treeHeight / 3) + 20},
//        {x + 25, y - (treeHeight / 3) + 30}
//    };
//
//    for (int i = 0; i < 5; i++) {
//        int ornamentX = ornaments[i].x;
//        int ornamentY = ornaments[i].y;
//        HBRUSH brushOrnament = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)); // Случайный цвет
//        SelectObject(hdc, brushOrnament);
//        Ellipse(hdc, ornamentX - ornamentRadius, ornamentY - ornamentRadius, ornamentX + ornamentRadius, ornamentY + ornamentRadius);
//        DeleteObject(brushOrnament);
//    }
//
//    DeleteObject(brushTree);
//}
//
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//    switch (uMsg) {
//    case WM_PAINT: {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hwnd, &ps);
//        RECT rect;
//        GetClientRect(hwnd, &rect);
//        int centerX = (rect.right - rect.left) / 2;
//        int bottomY = rect.bottom - 50; // Отступ снизу
//        DrawChristmasTree(hdc, centerX, bottomY);
//        EndPaint(hwnd, &ps);
//        break;
//    }
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hwnd, uMsg, wParam, lParam);
//    }
//    return 0;
//}
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//    const char CLASS_NAME[] = "ChristmasTreeWindowClass";
//
//    WNDCLASS wc = {};
//    wc.lpfnWndProc = WindowProc;
//    wc.hInstance = hInstance;
//    wc.lpszClassName = L"ChristmasTreeWindowClass";
//    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//
//    RegisterClass(&wc);
//
//    HWND hwnd = CreateWindowEx(
//        0,
//        L"ChristmasTreeWindowClass",
//        L"Christmas Tree",
//        WS_OVERLAPPEDWINDOW,
//        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
//        NULL,
//        NULL,
//        hInstance,
//        NULL
//    );
//
//    if (hwnd == NULL) {
//        return 0;
//    }
//
//    ShowWindow(hwnd, nCmdShow);
//    UpdateWindow(hwnd);
//
//    MSG msg = {};
//    while (GetMessage(&msg, NULL, 0, 0)) {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//
//    return (int)msg.wParam;
//}