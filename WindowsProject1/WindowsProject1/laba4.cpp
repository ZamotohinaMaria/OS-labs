#include <windows.h>
#include <string>
#include <iostream>
using namespace std;

// Глобальные переменные
HINSTANCE hInst;
LPCTSTR szWindowClass = TEXT("ChristmasTree");
LPCTSTR szTitle = TEXT("Christmas Tree");

// Прототипы функций
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    if (!hWnd) {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

void DrawTable(HWND hWnd, HDC hdc) {
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);

    int hCenter = (rcClient.right - rcClient.left) / 2;
    int right = rcClient.right;
    int left = rcClient.left;
    int top = rcClient.top;
    int bottom = rcClient.bottom;
    
    //Рисуем елочку
    HBRUSH TreeBrush = CreateSolidBrush(RGB(0, 141, 54)); // Зеленый цвет
    SelectObject(hdc, TreeBrush);

    //Верхний треугольник
    POINT points[3] = { { hCenter, top + 105 }, { hCenter + 35, top + 150 }, { hCenter - 35, top + 150 } };
    Polygon(hdc, points, 3);

    //Второй треугольник
    POINT points2[4] = {{hCenter-20, top + 150}, {hCenter + 20, top + 150}, 
                        {hCenter + 70, top + 205}, {hCenter - 70, top + 205} };
    Polygon(hdc, points2, 4);

    //Третий треугольник
    POINT points3[4] = { {hCenter - 30, top + 205}, {hCenter + 30, top + 205},
                        {hCenter + 110, top + 275}, {hCenter - 110, top + 275} };
    Polygon(hdc, points3, 4);

    //Четвертый треугольник
    POINT points4[4] = { {hCenter - 50, top + 275}, {hCenter + 50, top + 275},
                        {hCenter + 160, top + 365}, {hCenter - 160, top + 365} };
    Polygon(hdc, points4, 4);

    //Пятый треугольник
    POINT points5[4] = { {hCenter - 75, top + 365}, {hCenter + 75, top + 365},
                        {hCenter + 220, top + 470}, {hCenter - 220, top + 470} };
    Polygon(hdc, points5, 4);

    DeleteObject(TreeBrush);

    //Рисуем ствол
    HBRUSH WoodBrush = CreateSolidBrush(RGB(139, 69, 19)); // Коричневый цвет
    SelectObject(hdc, WoodBrush);

    Rectangle(hdc, hCenter - 20, top + 470, hCenter + 20, top + 540);
    DeleteObject(WoodBrush);

    //Рисуем звезду
    HBRUSH YellowBrush = CreateSolidBrush(RGB(255, 255, 0)); //Желтый цвет
    SelectObject(hdc, YellowBrush);

    POINT star1[4] = { {hCenter - 12, top + 120}, {hCenter + 12, top + 120},
                        {hCenter + 2, top + 90}, {hCenter - 2, top + 90} };
    Polygon(hdc, star1, 4);

    POINT star2[10] = { {hCenter, top + 90}, {hCenter - 20, top + 106},
                        {hCenter - 15, top + 85}, {hCenter - 32, top + 75},
                        {hCenter -10, top + 70}, {hCenter, top + 50},
                        {hCenter + 10, top + 70}, {hCenter + 32, top + 75},
                        {hCenter + 15, top + 85}, {hCenter + 20, top + 106}
    };
    Polygon(hdc, star2, 10);

    Ellipse(hdc, hCenter - 40, top + 170, hCenter - 10, top + 200);
    Ellipse(hdc, hCenter + 80, top + 300, hCenter + 120, top + 340);
    Ellipse(hdc, hCenter - 200, top + 420, hCenter - 150, top + 470);
    DeleteObject(YellowBrush);

    HBRUSH BlueBrush = CreateSolidBrush(RGB(71, 95, 250)); //Синий цвет
    SelectObject(hdc, BlueBrush);

    Ellipse(hdc, hCenter + 20, top + 200, hCenter + 40, top + 220);
    Ellipse(hdc, hCenter -10, top + 260, hCenter + 30, top + 300);
    Ellipse(hdc, hCenter -50, top + 450, hCenter, top + 500);
    Ellipse(hdc, hCenter +200, top + 450, hCenter + 240, top + 490);
    DeleteObject(BlueBrush);

    HBRUSH RedBrush = CreateSolidBrush(RGB(255, 51, 51)); //Красный цвет
    SelectObject(hdc, RedBrush);
    Ellipse(hdc, hCenter + 100, top + 390, hCenter + 140, top + 430);
    Ellipse(hdc, hCenter - 90, top + 350, hCenter - 60, top + 380);
    Ellipse(hdc, hCenter , top + 120, hCenter + 20, top + 140);

    //// Отрисовка стола
    //HBRUSH hTableBrush = CreateSolidBrush(RGB(0, 141, 54)); // Зеленый цвет для стола
    //SelectObject(hdc, hTableBrush);
    //RoundRect(hdc, rcClient.left + 50, rcClient.top + 50, rcClient.right - 250, rcClient.bottom - 250, 0, 0); // Прямоугольник со скругленными углами
    //DeleteObject(hTableBrush);

    //// Отрисовка коричневой окантовки стола
    //HPEN hBorderPen = CreatePen(PS_SOLID, 30, RGB(139, 69, 19)); // Коричневый цвет для окантовки
    //SelectObject(hdc, hBorderPen);
    //RoundRect(hdc, rcClient.left + 45, rcClient.top + 45, rcClient.right - 45, rcClient.bottom - 45, 20, 20); // Окантовка прямоугольника
    //DeleteObject(hBorderPen);



    //// Отрисовка луз
    //HBRUSH hTableBrush_w = CreateSolidBrush(RGB(51, 25, 0)); // Зеленый цвет для стола
    //SelectObject(hdc, hTableBrush_w);
    //HPEN hPocketPen = CreatePen(PS_SOLID, 10, RGB(139, 69, 19)); // Коричневый цвет для окантовки
    //SelectObject(hdc, hPocketPen);
    //Ellipse(hdc, rcClient.left + 20, rcClient.top + 20, rcClient.left + 80, rcClient.top + 80); // Луза в верхнем левом углу
    //Ellipse(hdc, (rcClient.left + rcClient.right) / 2 - 20, rcClient.top + 20, (rcClient.left + rcClient.right) / 2 + 40, rcClient.top + 80); // Луза в верхнем левом углу
    //Ellipse(hdc, rcClient.right - 80, rcClient.top + 20, rcClient.right - 20, rcClient.top + 80); // Луза в верхнем правом углу
    //Ellipse(hdc, rcClient.left + 20, rcClient.bottom - 80, rcClient.left + 80, rcClient.bottom - 20); // Луза в нижнем левом углу
    //Ellipse(hdc, (rcClient.left + rcClient.right) / 2 - 20, rcClient.bottom - 80, (rcClient.left + rcClient.right) / 2 + 40, rcClient.bottom - 20); // Луза в нижнем левом углу
    //Ellipse(hdc, rcClient.right - 80, rcClient.bottom - 80, rcClient.right - 20, rcClient.bottom - 20); // Луза в нижнем правом углу
    //DeleteObject(hPocketPen);
    //;

    //// Отрисовка шаров и кия (пример)
    //// Кий (пример)
    //HBRUSH hCueBrush = CreateSolidBrush(RGB(139, 69, 19)); // Коричневый цвет для кия
    //POINT cuePoints[4] = { {rcClient.left + 150, rcClient.top + 310},
    //                        {rcClient.left + 150, rcClient.top + 350},
    //                        {rcClient.left + 650, rcClient.top + 335} ,
    //                        {rcClient.left + 650, rcClient.top + 332} }; // Треугольная форма кия
    //SelectObject(hdc, hCueBrush);
    //Polygon(hdc, cuePoints, 4); // Отрисовка кия
    //DeleteObject(hCueBrush);

    //HBRUSH hCueBrush2 = CreateSolidBrush(RGB(169, 169, 19)); // Коричневый цвет для кия
    //POINT cuePoints2[4] = { {rcClient.left + 50, rcClient.top + 10},
    //                        {rcClient.left + 50, rcClient.top + 50},
    //                        {rcClient.left + 150, rcClient.top + 35} ,
    //                        {rcClient.left + 150, rcClient.top + 32} }; // Треугольная форма кия
    //SelectObject(hdc, hCueBrush2);
    //Polygon(hdc, cuePoints2, 4); // Отрисовка кия
    //DeleteObject(hCueBrush2);

    ////HBRUSH hCueBrush2 = CreateSolidBrush(RGB(255,255,255)); 
    ////HPEN hEmptyPen1 = CreatePen(PS_SOLID, 2, RGB(7, 107, 45));
    ////SelectObject(hdc, hEmptyPen1);
    ////POINT cuePoints2[4] = { {rcClient.left + 650, rcClient.top + 340} ,
    ////                        {rcClient.left + 650, rcClient.top + 330},
    ////                        {rcClient.left + 670, rcClient.top + 330},
    ////                        {rcClient.left + 670, rcClient.top + 340} };
    ////SelectObject(hdc, hCueBrush2);
    ////Polygon(hdc, cuePoints2, 4); // Отрисовка кия
    ////DeleteObject(hCueBrush2);

    //HBRUSH hBallBrush = CreateSolidBrush(RGB(255, 255, 255));
    //HPEN hEmptyPen = CreatePen(PS_SOLID, 2, RGB(7, 107, 45));
    //SelectObject(hdc, hEmptyPen);
    //int startX = (((rcClient.left + rcClient.right) / 2) + rcClient.right) / 2 - 40;
    //int startY = (rcClient.top + rcClient.bottom) / 2;
    //int radius = 20;
    //int x, y;
    //int count_text = 0;
    //wstring text[15] = { L"1", L"5", L"3", L"7", L"2", L"6", L"8" , L"4", L"9", L"10" , L"12", L"15", L"13", L"14", L"11" };
    //for (int i = 0; i < 5; ++i) {
    //    int count = 0;

    //    for (int j = 5; j > i; --j) {
    //        x = startX + count * 2 * radius;
    //        y = startY - count * radius;
    //        count++;
    //        SelectObject(hdc, hBallBrush);
    //        Ellipse(hdc, x + radius, y + radius, x - radius, y - radius); // Отрисовка шара

    //        TextOut(hdc, x - 5, y - 5, text[count_text].c_str(), 2);
    //        DeleteObject(hBallBrush);
    //        count_text++;
    //    }

    //    startX = (((rcClient.left + rcClient.right) / 2) + rcClient.right) / 2 - 40 + (i + 1) * 2 * radius;
    //    startY = (rcClient.top + rcClient.bottom) / 2 + (i + 1) * radius;
    //    //startY -= (2 * i + 1) * radius;
    //}
    //HBRUSH hBallBrush_red = CreateSolidBrush(RGB(178, 34, 34));
    //SelectObject(hdc, hBallBrush_red);
    //startX = ((rcClient.left + rcClient.right) / 2) + 10;
    //startY = (rcClient.top + rcClient.bottom) / 2;
    //Ellipse(hdc, startX + radius, startY + radius, startX - radius, startY - radius);
    //DeleteObject(hBallBrush_red);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawTable(hWnd, hdc);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
