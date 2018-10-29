#include "stdafx.h"
#include "Screen.h"
using namespace std;

Screen::Screen(int w, int h)
{

	//WNDCLASS wc={CS_BYTEALIGNCLIENT,}
}


Screen::~Screen()
{
}

LRESULT Screen::screen_events(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:Exit = 1; break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
	return 0;
}