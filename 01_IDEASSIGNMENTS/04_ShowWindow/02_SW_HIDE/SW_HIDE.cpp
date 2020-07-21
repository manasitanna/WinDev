// the header file
#include<windows.h>

// global func declaration
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// Main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	// initialization of wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	/*
		HICON WINAPI LoadIcon(HINSTACE, LPSTR);
	*/

	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*
		HCURSOR WINAPI LoadCursor(HINSTANCE, LPSTR);
	*/

	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	/*
		HGDIOBJECT WINAPI GetStockObject (int);
	*/

	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register class wndclass
	RegisterClassEx(&wndclass);
	/*
		ATOM WINAPI RegisterClassEx(const WNDCLASSEX *);
	*/

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("SW_HIDE"),
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
		HWND WINAPI CreateWindow(LPSTR,
		LPSTR,
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

	ShowWindow(hwnd, SW_HIDE);
	/*
		BOOL WINAPI ShowWindow(HWND, UINT);
	*/

	UpdateWindow(hwnd);
	/*
		BOOL WINAPI UpdateWindow(HWND);
	*/

	// message loop
	while (GetMessage(&msg, NULL, 0, 0)){
		/*
			BOOL WINAPI GetMessage(const MSG *, HWND, int, int);
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

	switch (iMsg) {
	
	case WM_DESTROY:
		PostQuitMessage(0);
		/*
			void WINAPI PostQuitMessage(int);
		*/
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
	/*
		LRESULT WINAPI DefWindowProc(HWND, UINT, WPARAM, LPARAM);
	*/
}