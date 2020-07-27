// the headers
#include<windows.h>
#include "resource.h"

// global func declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShw) {
	// var declarations

	WNDCLASSEX wndclass;

	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	// code
	// init
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	// 0x0002 | 0x0001
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	/*
		HICON WINAPI LoadIcon(HINSTANCE hInstance, LPCSTR lpIconName);
	*/

	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*
		HCURSOR WINAPI LoadCursor(HINSTANCE hInstance, LPCSTR lpCursorName);
	*/

	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	/*
		HGDIOBJ WINAPI GetStockObject(int i);
	*/

	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	/*
		HICON WINAPI LoadIcon(HINSTANCE hInstance, LPCSTR lpIconName);
	*/

	// register the class
	RegisterClassEx(&wndclass);
	/*
		ATOM WINAPI RegisterClassEx(const WNDCLASSEX *arg1);
	*/

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("First Application"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	/*
		HWND WINAPI CreatWindow(LPCTR,
		LPCTR,
		DWORD,
		int,
		int,
		int,
		int,
		HWND,
		HMENU,
		HINSTANCE,
		LPVOID);
	*/

	ShowWindow(hwnd, iCmdShw);
	/*
		BOOL WINAPI ShowWindow( HWND, int);
	*/

	UpdateWindow(hwnd);
	/*
		BOOL WINAPI UpdateWindow(HWND);
	*/

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
		/*
			BOOL WINAPI GetMessage(LPMSG, HWND, UINT, UINT);
		*/
	{
		TranslateMessage(&msg);
		/*
			BOOL WINAPI TranslateMessage(const MSG *);
		*/

		DispatchMessage(&msg);
		/*
			LRESULT WINAPI DispatchMessage(const MSG *);
		*/
	}

	return((int)msg.wParam);

}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	// variable declarations
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	RECT rc;
	BITMAP bitmap;
	HBITMAP hbitmap, h_old_bitmap;

	static HINSTANCE hInstance;

	switch (iMsg) {

	case WM_CREATE: 
		
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		break;

	case WM_PAINT:
		
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		hbitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MyBitMap));
		GetObject(hbitmap, sizeof(BITMAP), &bitmap);
		hdcMem = CreateCompatibleDC(hdc);
		h_old_bitmap = (HBITMAP) SelectObject(hdcMem, hbitmap);
		StretchBlt(hdc,
			0,
			0,
			rc.right,
			rc.bottom,
			hdcMem,
			0,
			0,
			bitmap.bmWidth,
			bitmap.bmWidth,
			MERGECOPY);
		ReleaseDC(hwnd, hdc);
		EndPaint(hwnd, &ps);

		break;
	case WM_DESTROY:

		PostQuitMessage(0);
		/*
			void PostQuitMessage(int);
		*/
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
	/*
		LRESULT DefWindowProc(HWND, UINT, WPARAM, LPARAM);
	*/
}