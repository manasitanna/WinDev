// header
#include<Windows.h>

// global func declaration
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	// declarations

	WNDCLASSEX wndclass;
	MSG msg;
	TCHAR szAppName[] = TEXT("My Window");
	HWND hwnd;

	// initializing wndclass 

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	/*
		HICON LoadIcon(HINSTANCE, LPCSTR);
	*/
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*
		HCURSOR LoadCursor(HINSTANCE, LPCSTR);
	*/

	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	/*
		HGDI GetStockObject(int);
	*/

	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// registerclass

	RegisterClassEx(&wndclass);
	/*
		ATOM RegisterClassEx( const WNDCLASSEX *)
	*/

	hwnd = CreateWindow(szAppName,
		TEXT("Message Box Window"),
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

	ShowWindow(hwnd, iCmdShow);
	/*
		BOOL ShowWindow(HWND, int);
	*/

	UpdateWindow(hwnd);
	/*
		BOOL UpdateWindow(HWND);
	*/

	// message loop

	while (GetMessage(&msg, NULL, 0, 0))
		/*
			BOOL GetMessage(LPMSG, HWND, UINT, UINT);
		*/
	{
		TranslateMessage(&msg);
		/*
			BOOL TranslateMessage(LPMSG);
		*/
		DispatchMessage(&msg);
		/*
			LRESULT DispatchMessage(LPMSG);
		*/

	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	switch (iMsg) {

	case WM_CREATE :
		MessageBox(hwnd, TEXT("WM_CREATE received"), TEXT("Message"), MB_OK);
		break;

	case WM_LBUTTONDOWN :
		MessageBox(hwnd, TEXT("WM_LBUTTONDOWN received"), TEXT("Message"), MB_OK);
		break;

	case WM_RBUTTONDOWN :
		MessageBox(hwnd, TEXT("WM_RBUTTONDOWN received"), TEXT("Message"), MB_OK);
		break;

	case WM_KEYDOWN :
		MessageBox(hwnd, TEXT("WM_KEYDOWN received"), TEXT("Message"), MB_OK);
		break;

	case WM_DESTROY :
		MessageBox(hwnd, TEXT("WM_DESTROY received"), TEXT("Message"), MB_OK);
		PostQuitMessage(0);
		break;
		
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}