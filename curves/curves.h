/* 2018 ReVoL Primer Template */
/* curves.h */
#pragma once
#include "targetver.h"
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include "resource.h"
#define MW_W 800
#define MW_H 500
#define GW_W (MW_W - 80)
#define GW_H (MW_H - 80)
HWND hWndMain;
HWND hWndGDE;
HDC GDC;
HINSTANCE hInst;
int loaded = 0;
void draw();
LRESULT CALLBACK MWProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int wmIdent;
    switch (message) {
    case WM_COMMAND: {
        wmIdent = LOWORD(wParam);
        switch (wmIdent) {
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
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
LRESULT CALLBACK GDProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message) {
    case WM_PAINT:
        InvalidateRect(hWndGDE, 0, 0);
        hdc = BeginPaint(hWnd, &ps);
        if (loaded) draw();
        EndPaint(hWnd, &ps);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    int SW, SH, CW, CH;
    int ccx, ccy;
    RECT mr;
    SW = GetSystemMetrics(SM_CXSCREEN);
    SH = GetSystemMetrics(SM_CYSCREEN);
    hInst = hInstance;
    hWndMain = CreateWindowA("CURVESAPP", "Curves Primer App", 0x80c80000,
        (SW - MW_W) / 2, (SH - MW_H) / 2, MW_W, MW_H, 0, 0, hInstance, 0);
    if (!hWndMain) return FALSE;
    GetClientRect(hWndMain, &mr);
    CW = mr.right;
    CH = mr.bottom;
    ccx = (CW - GW_W) / 2;
    ccy = (CH - GW_H) / 2;
    hWndGDE = CreateWindow("CURVESGDE", 0, WS_CHILD | WS_VISIBLE, ccx, ccy, GW_W, GW_H, hWndMain, 0, hInst, 0);
    if (!hWndGDE) return FALSE;
    ShowWindow(hWndMain, nCmdShow);
    UpdateWindow(hWndMain);
    GDC = GetDC(hWndGDE);
    HPEN pen = CreatePen(0, 0, RGB(255, 255, 255));
    SelectObject(GDC, pen);
    HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
    SelectObject(GDC, brush);
    SetBkMode(GDC, TRANSPARENT);
    return TRUE;
}
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MWProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CURVES));
    wcex.hCursor = LoadCursor(0, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = "CURVESAPP";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    if (!RegisterClassEx(&wcex)) return 0;
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = GDProc;
    wcex.hIcon = 0;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = "CURVESGDE";
    wcex.hIconSm = 0;
    return RegisterClassEx(&wcex);
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MyRegisterClass(hInstance);
    if (!InitInstance(hInstance, nCmdShow)) return FALSE;
    MSG msg;
    loaded = 1;
    InvalidateRect(hWndGDE, 0, 0);
    while (GetMessage(&msg, 0, 0, 0)) {
        if (msg.message == WM_KEYDOWN && msg.wParam == 27) {
            SendMessage(hWndMain, WM_DESTROY, 0, 0);
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    ReleaseDC(hWndGDE, GDC);
    return (int)msg.wParam;
}
