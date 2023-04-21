#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

int n1 = 2;
int n2 = 1;
int n3 = 0;
int n4 = 2;

float** randm(int n);
float** mulmr(float c, float** mat, int n);

char** setVertexes(int n);


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    WNDCLASS w;

    w.lpszClassName = L"Lab 3";
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.hbrBackground = WHITE_BRUSH;
    w.style = CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if(!RegisterClass(&w))
        return 0;

    HWND hWnd;
    MSG lpMsg;

    hWnd = CreateWindow(L"Lab 3",
                        "Lab 3 by Halai Andrii",
                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                        100,
                        100,
                        1200,
                        700,
                        NULL,
                        NULL,
                        (HINSTANCE)hInstance,
                        NULL);

    ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&lpMsg, hWnd, 0, 0)) {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    void arrow(float fi, int px,int py) {
        fi = 3.1416*(180.0 - fi)/180.0;
        int lx,ly,rx,ry;
        lx = px+15*cos(fi+0.3);
        rx = px+15*cos(fi-0.3);
        ly = py+15*sin(fi+0.3);
        ry = py+15*sin(fi-0.3);
        MoveToEx(hdc, lx, ly, NULL);
        LineTo(hdc, px, py);
        LineTo(hdc, rx, ry);
        return 0;
    }

    switch(messg) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            char **nn;
            nn = setVertexes(10);

            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
}

float** randm(int n) {
    srand(2102);
    float** arr = (float**)malloc(n * sizeof(float*));
    for(int i = 0; i < n; i++){
        arr[i] = (float*)malloc(n * sizeof(float));
        for(int j = 0; j < n; j++){
            arr[i][j] = ((float)rand() / (float)RAND_MAX) * 2.0;
        }
    }
    return arr;
}

float** mulmr(float c, float** mat, int n) {
    float** res = (float**)malloc(n * sizeof(float*));
    for(int i = 0; i < n; i++){
        res[i] = (float*)malloc(n * sizeof(float));
        for(int j = 0; j < n; j++){
            res[i][j] = floor(mat[i][j] * c);
        }
    }
    return res;
}

char** setVertexes(int n) {
    char** arr = malloc(n * sizeof(char*));
    for(int i = 0; i < n; i++) {
        arr[i] = malloc(3 * sizeof(char));
        sprintf(arr[i], "%d", i+1);
    }
    return arr;
}


