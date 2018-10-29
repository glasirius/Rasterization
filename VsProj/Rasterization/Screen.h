#pragma once
#include "windows.h"
class Screen
{
public:
	int Width;
	int Height;
	int Exit;
	Screen(int w,int h);
	~Screen();
	LRESULT screen_events(HWND hWnd, UINT msg,
		WPARAM wParam, LPARAM lParam);
};

