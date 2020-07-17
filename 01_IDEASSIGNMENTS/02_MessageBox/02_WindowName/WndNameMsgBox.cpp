// HEADER FILE
#include<windows.h>

// GLOBAL DECLARATION OF WndProc

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// Main

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	// Variable declaration

	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("My Window");

	// initialization

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW; // 0X0002 | 0X0001
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hInstance = hInstance;

	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	/*
		HICON WINAPI LoadIcon (HWND, LPCSTR);
	*/
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*
		HCURSOR WINAPI LoadCursor(HWND, LPCSTR);
	*/
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	/*
		HGDI WINAPI GetStockObject(int);
		void NEAR* HGDI;

	*/
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);
	/*
		ATOM WINAPI RegisterClassEx (const WNDCLASSEX *);
	*/

	hwnd = CreateWindow(szAppName,
		TEXT("Manasi's Window"),
		(WS_OVERLAPPED | WS_SYSMENU | WS_THICKFRAME |WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CAPTION),
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	/*
		HWND WINAPI CreateWindow(LPCSTR,
		LPCSTR,
		DWOED,
		int.
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

	// message loop

	while (GetMessage(&msg, NULL, 0, 0)) {

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

	TCHAR str[255];

	switch (iMsg) {

	case WM_CREATE:
		wsprintf(str, TEXT("The window name is: %s"), ((LPCREATESTRUCT)lParam)->lpszName);
		/*
			int WINAPIV wsprintf(LPCSTR, LPCSTR, ...)
			WINAPIV -> __cdecl -> right to left declaration.
		*/
		MessageBox(hwnd, str, TEXT("window message"), MB_OK);
		/*
			int WINAPI MessageBox(HWND, LPCSTR, LPCSTR, UINT); 
		*/
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		/*
			void __stdcall PostQuitMessage(int ExitCode);
		*/
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
	/*
		LRESULT WINAPI DefWindowProc(HWND, UINT, WPARAM,LPARAM);
	*/
}