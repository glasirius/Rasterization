#pragma once
#include <windows.h>
class Screen
{
public:
	Screen();
	~Screen();

    static int Create(int w, int h, const TCHAR *title);
    static void ScreenClose();

private:
    static LRESULT screenEvents(HWND hWnd, UINT msg,
        WPARAM wParam, LPARAM lParam);
    static void screenDispatch();

	static int exit;
	static HDC screenDc;
	static HBITMAP screenOb;
	static HBITMAP screenHb;
	static HWND screenHandle;
    static unsigned char* screenFb;
    static long screenPitch;
};

enum CreateScreenResult
{
    CreateScreenSuccess,
    RegisterClassFailed,
    CreateWindowFailed,
    CreateDIBSectionFailed
};