#include <windows.h>
#include <string>
using namespace std;

HWND hNum1, hNum2, hResult;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    char num1[20], num2[20];
    float n1, n2, res;
    int choice;

    switch(msg) {

        case WM_CREATE:
            CreateWindow("STATIC", "Num1:", WS_VISIBLE | WS_CHILD,
                         50, 50, 50, 20, hwnd, NULL, NULL, NULL);
            hNum1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                 100, 50, 100, 20, hwnd, NULL, NULL, NULL);

            CreateWindow("STATIC", "Num2:", WS_VISIBLE | WS_CHILD,
                         50, 80, 50, 20, hwnd, NULL, NULL, NULL);
            hNum2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                 100, 80, 100, 20, hwnd, NULL, NULL, NULL);

            // Buttons
            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD,
                         50, 120, 40, 30, hwnd, (HMENU)1, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD,
                         100, 120, 40, 30, hwnd, (HMENU)2, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD,
                         150, 120, 40, 30, hwnd, (HMENU)3, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD,
                         200, 120, 40, 30, hwnd, (HMENU)4, NULL, NULL);

            hResult = CreateWindow("STATIC", "Result:", WS_VISIBLE | WS_CHILD,
                                   50, 170, 200, 30, hwnd, NULL, NULL, NULL);
            break;

        case WM_COMMAND:
            GetWindowText(hNum1, num1, 20);
            GetWindowText(hNum2, num2, 20);

            n1 = atof(num1);
            n2 = atof(num2);

            choice = LOWORD(wp);

            switch(choice) {
                case 1: res = n1 + n2; break;
                case 2: res = n1 - n2; break;
                case 3: res = n1 * n2; break;
                case 4:
                    if(n2 != 0) res = n1 / n2;
                    else {
                        SetWindowText(hResult, "Error: Divide by zero");
                        return 0;
                    }
                    break;
            }

            char output[50];
            sprintf(output, "Result: %.2f", res);
            SetWindowText(hResult, output);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInst;
    wc.lpszClassName = "CalculatorWindow";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("CalculatorWindow", "C++ GUI Calculator",
                             WS_OVERLAPPEDWINDOW,
                             200, 200, 350, 300,
                             NULL, NULL, hInst, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}