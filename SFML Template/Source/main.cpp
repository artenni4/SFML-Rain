#include "window.h"
#include <Windows.h>


int main()
{
	HWND console = GetConsoleWindow();
	ShowWindow(console, SW_HIDE);

	Window win;
	win.ChooseDropColor();
	win.Init();

	ShowWindow(console, SW_HIDE);
}