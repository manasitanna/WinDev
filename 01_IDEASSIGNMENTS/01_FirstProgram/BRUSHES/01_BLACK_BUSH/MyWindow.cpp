// the header
#include<windows.h>
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
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	/*
		HICON LoadIcon(HINSTACE, LPCSTR);
	*/
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*
		HCURSOR LoadCursor(HINSTANCE, LPCSTR);
	*/
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	/*
		HGDI GetStockObject (int);
	*/
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the class
	RegisterClassEx(&wndclass);
	/*
		ATOM RegisterClassEx(const WNDCLASSEX *);
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
		HWND CreateWindow(LPSTR, LPSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
		*/

	ShowWindow(hwnd, iCmdShw);
	/*
		BOOL ShowWindow(HWND, UINT);
	*/
	UpdateWindow(hwnd);
	/*
		BOOL UpdateWindow(HWND);
	*/

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	/*
		BOOL GetMessage(const MSG *, HWND, int, int);
	*/ {
		TranslateMessage(&msg);
		/*
			BOOL TranslateMessage(const MSG *);
		*/
		DispatchMessage(&msg);
		/*
			LRESULT DispatchMessage(const MSG *);
		*/
	}

	return((int)msg.wParam);
	
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	// code
	switch (iMsg) {
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