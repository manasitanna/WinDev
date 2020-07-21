// header
#include<windows.h>

// global func declaration

LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// WinMain

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	
	// Declaration

	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("My Window");

	// Initialization

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW; // 0x0002 | 0x0001
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	/*
		HGDIOBJ WINAPI GetStockObject (int);
		void NEAR* HGDIOBJ
	*/
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	/*
		HICON WINAPI LoadIcon(HINSTANCE, LPCSTR);
	*/
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*
		HCURSOR WINAPI LoadCursor(HINSTANCE, LPCSTR);

	*/
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);
	/*
		ATOM WINAPI RegisterClassEx(const WNDCLASSEX *);
		WORD ATOM;
	*/
	hwnd = CreateWindow(szAppName,
		TEXT("Hello World"),
		(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME),
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	/*
		HWND WINMAIN CreateWindow(LPCSTR,
		LPCSTR,
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

	ShowWindow(hwnd, iCmdShow);
	/*
		BOOL WINAPI ShowWindow(HWND, int);
	*/

	UpdateWindow(hwnd);
	/*
		BOOL WINAPI UpdateWindow(HWND);
	*/

	// heart :  message loop

	while (GetMessage(&msg, NULL, 0, 0)) {
		/*
			BOOL WINAPI GetMessage( const MSG *, HWND, int, int);
		*/
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
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	TCHAR str[] = TEXT(" HELLO WORLD !!!");

	switch (iMsg) {
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		/*
			BOOL WINAPI GetClientRect(HWND, LPRECT);
		*/
		hdc = BeginPaint(hwnd, &ps);
		/*
			HDC BeginPaint(HWND, LPPAINTSTRUCT);
		*/
		SetBkColor(hdc, RGB(0, 0, 0));
		/*
			COLORREF WINAPI SetBkColor (HDC, COLORREF);
			DWORD COLORREF
		*/
		SetTextColor(hdc, RGB(0, 255, 0));
		/*
			COLORREF WINAPI SetTextColor(HDC, COLORREF)
		*/
		DrawText(hdc, str, -1, &rc, (DT_SINGLELINE | DT_CENTER | DT_VCENTER));
		/*
			int WINAPI DrawText(HDC, LPSTR, int, LPRECT, UINT);
		*/
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY: 
		PostQuitMessage(0);
		/*
			void WINAPI PostQuitMessage(int);
		*/
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}