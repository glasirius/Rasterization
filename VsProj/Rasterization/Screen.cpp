#include "stdafx.h"
#include "Screen.h"

using namespace std;

Screen::Screen()
{
	
}

Screen::~Screen()
{
}

CreateScreenResult Screen::Create(int w, int h, const TCHAR *title)
{
    WNDCLASS wc = { CS_BYTEALIGNCLIENT, (WNDPROC)screenEvents, 0, 0, 0,
        NULL, NULL, NULL, NULL, _T("SCREEN3.1415926") };
    BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB,
        w * h * 4, 0, 0, 0, 0 } };
    RECT rect = { 0, 0, w, h };
    int wx, wy, sx, sy;
    LPVOID ptr;
    HDC hDC;
    ScreenClose();
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hInstance = GetModuleHandle(NULL);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    if (!RegisterClass(&wc))
    {
        return RegisterClassFailed;
    }

    screenHandle = CreateWindow(_T("SCREEN3.1415926"), title,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
    if (screenHandle == NULL)
    {
        return CreateWindowFailed;
    }

    exit = 0;

    hDC = GetDC(screenHandle);
    screenDc = CreateCompatibleDC(hDC);
    ReleaseDC(screenHandle, hDC);

    screenHb = CreateDIBSection(screenDc, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
    if (screenHb == NULL)
    {
        return CreateDIBSectionFailed;
    }
        
    screenOb = (HBITMAP)SelectObject(screenDc, screenHb);
    screenFb = (unsigned char*)ptr;
    screenPitch = w * 4;

    AdjustWindowRect(&rect, GetWindowLong(screenHandle, GWL_STYLE), 0);
    wx = rect.right - rect.left;
    wy = rect.bottom - rect.top;
    sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
    sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
    if (sy < 0) sy = 0;
    SetWindowPos(screenHandle, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
    SetForegroundWindow(screenHandle);

    ShowWindow(screenHandle, SW_NORMAL);
    screenDispatch();
    memset(screenFb, 0, w * h * 4);

    return CreateScreenSuccess;
}

LRESULT Screen::screenEvents(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:exit = 1; break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
	return 0;
}

int Screen::ScreenClose() {
	if (screenDc) {
		if (screenOb) {
			SelectObject(screenDc, screenOb);
			screenOb = NULL;
		}
		DeleteDC(screenDc);
		screenDc = NULL;
	}
	if (screenHb) {
		DeleteObject(screenHb);
		screenHb = NULL;
	}
	if (screenHandle) {
		CloseWindow(screenHandle);
		screenHandle = NULL;
	}
	return 0;
}

void Screen::screenDispatch() 
{
    MSG msg;
    while (1) 
    {
        if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;
        if (!GetMessage(&msg, NULL, 0, 0)) break;
        DispatchMessage(&msg);
    }
}