#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

const int n1 = 2;
const int n2 = 1;
const int n3 = 0;
const int n4 = 2;
const int N = 10;

float** randm(int n);
float** mulmr(float c, float** mat, int n);

char** setVertexes(int n);
int* setCoordsX(int n);
int* setCoordsY(int n);

int mod(int x1, int x2);

void drawOrientedGraph(HDC hdc, int n, char **nn, int *nx, int *ny);


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
            int *nx;
            int *ny;

            drawOrientedGraph(hdc, N, nn, nx, ny);

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

int* setCoordsX(int n) {
    int *nx = malloc(n * sizeof(int));
    int vertSide = 2;
    int horizontalSide = (int) ceilf((float) n/2 - vertSide);
    if (horizontalSide > 1) {
        for (int i = 0; i < horizontalSide; i++) {
            nx[i] = 100 + i*100;
        }
        for (int i = horizontalSide; i < horizontalSide + vertSide; i++) {
            nx[i] = nx[i-1];
        }
        for (int i = horizontalSide+vertSide; i < 2*horizontalSide + vertSide; i++) {
            int j = 2*horizontalSide + vertSide;
            nx[i] = nx[j - i - 1];
        }
        for (int i = 2*horizontalSide + vertSide; i < n; i ++) {
            nx[i] = nx[i-1];
        }
    } else {
        int side = (int) ceilf((float)n/2);
        for (int i = 0; i < side; i++) {
            nx[i] = 100 + i*100;
        }
        for (int i = 1; i < n-side+1; i++) {
            nx[side+i-1] = nx[side - i];
        }
    }
    return nx;
}

int* setCoordsY(int n) {
    int *ny = malloc(n * sizeof(int));
    int vertSide = 2;
    int horizontalSide = (int) ceilf((float) n/2 - vertSide);
    if (horizontalSide > 1) {
        for (int i = 0; i < horizontalSide; i++) {
            ny[i] = 100;
        }
        for (int i = horizontalSide; i < horizontalSide + vertSide; i++) {
            ny[i] = ny[i-1] + 100;
        }
        for (int i = horizontalSide+vertSide; i < 2*horizontalSide + vertSide; i++) {
            ny[i] = ny[horizontalSide-1] + 300;
        }
        for (int i = 2*horizontalSide + vertSide; i < n; i ++) {
            ny[i] = ny[i-1] - 100;
        }
    } else {
        int side = (int) ceilf((float)n/2);
        for (int i = 0; i < side; i++) {
            ny[i] = 100;
        }
        for (int i = side; i < n; i++) {
            ny[i] = 200;
        }
    }
    return ny;
}

int mod(int x1, int x2) {
    int res = x1 - x2;
    if (res > 0) return res;
    else return (-1)*res;
}

void drawOrientedGraph(HDC hdc, int n, char **nn, int *nx, int *ny) {
    int vertSide = 2;
    int horizontalSide = (int) ceilf((float) n/2 - vertSide);
    float** matrix;
    matrix = randm(n);
    matrix = mulmr((1.0 - n3*0.02 - n4*0.005 - 0.25), matrix, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.0f ", matrix[i][j]);
        }
        printf("\n");
    }

    nn = setVertexes(n);
    nx = setCoordsX(n);
    ny = setCoordsY(n);
    int dx = 16, dy = 16, dtx = 5;

    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

    SelectObject(hdc, KPen);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((matrix[i][j] == 1) && (ny[i] == ny[j]) && (mod(i,j) < horizontalSide) && (mod(nx[i], nx[j]) > 100)) { //horzntl arc
                int y1 = mod(nx[i], nx[j])/5;
                Arc(hdc, nx[i], ny[i]-y1, nx[j], ny[i]+y1, nx[i], ny[i], nx[j], ny[j]);
            }
            else if (matrix[i][j] == 1 && nx[i] != nx[j]) { // horzntl line
                MoveToEx(hdc, nx[i], ny[i], NULL);
                LineTo(hdc, nx[j], ny[j]);
            } else if ((matrix[i][j] == 1) && (nx[i] == nx[j]) && (ny[i] != ny[j]) && (mod(ny[i],ny[j]) > 100)) { //vert arc
                if (mod(i, j) > 4 && nx[j] != 100 && nx[i] != 100) { // draw line if it is not same side
                    MoveToEx(hdc, nx[i], ny[i], NULL);
                    LineTo(hdc, nx[j], ny[j]);
                } else { // arc if it is the same side
                    int x1 = mod(ny[i], ny[j])/5;
                    Arc(hdc, nx[i]-x1, ny[i], nx[j]+x1, ny[j], nx[i], ny[i], nx[j], ny[j]);
                }
            } else if (matrix[i][j] == 1 && ny[i] != ny[j]) { // vert line
                MoveToEx(hdc, nx[i], ny[i], NULL);
                LineTo(hdc, nx[j], ny[j]);
            }
        }
    }

    SelectObject(hdc, BPen);

    for (int i = 0; i < n; i++) {
        Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
        if (strlen(nn[i]) < 2) {
            TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 1);
        } else {
            TextOut(hdc, nx[i] - dtx-4, ny[i] - dy / 2, nn[i], 2);
        }
    }

}
