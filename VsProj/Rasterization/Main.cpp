// ConsoleApplication3.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Device.h"
#include "iostream"
#include "Renderer.h"
#include "Screen.h";
using namespace std;

int main()
{
    TCHAR *title = _T("hehe");
    Screen::Create(1000, 1000, title);
	getchar();
    return 0;
}

