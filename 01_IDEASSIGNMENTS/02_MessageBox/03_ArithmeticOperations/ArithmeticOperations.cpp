// header
#include<windows.h>

// global declaration
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	// declarations
	HWND hwnd;
	WNDCLASSEX wndcls;
	MSG msg;
	TCHAR szAppName[] = TEXT("My Window");

	// initializations
	wndcls.cbSize = sizeof(WNDCLASSEX);
	wndcls.style = CS_HREDRAW | CS_VREDRAW;  //0x0002 | 0x001
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.lpfnWndProc = WndProc;
	wndcls.lpszClassName = szAppName;
	wndcls.lpszMenuName = NULL;
	wndcls.hInstance = hInstance;
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	/*
		HICON WINAPI LoadIcon(HINSTANCE, LPSTR;
	*/
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*
		HCURSOR WINAPI LoadCursor(HISNATNCE, LPSTR);	
	*/
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	/*
		HGDIOBJECT WINAPI GetStockObject(int);
	*/
	wndcls.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register class
	RegisterClassEx(&wndcls);
	/*
		ATOM WINAPI RegisterClassEx(const WNDCLASSEX *);
	*/

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("Arithmetic Operations"),
		(WS_CAPTION | WS_SYSMENU | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME),
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

	// show and update window

	ShowWindow(hwnd, iCmdShow);
	/*
		BOOL WINAPI ShowWindow( HWND, int);
	*/
	UpdateWindow(hwnd);
	/*
		BOOL WINAPI UpdateWindow(HWND);
	*/

	// heart: The message loop

	while (GetMessage(&msg, NULL, 0, 0)) {
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

	TCHAR str[255];
	int var1 = 50;
	int var2 = 30;
	int result = 0;

	switch (iMsg) {
		
	case WM_CHAR:
		switch (wParam) {

		case '+':
			result = var1 + var2;
			wsprintf(str, TEXT("The sum of %d and %d is: %d"), var1, var2, result);
			/*
				int WINAPIV wsprintf(LPSTR, LPSTR, ...);
			*/
			MessageBox(hwnd, str, TEXT("ADDITION"), MB_OK);
			/*
				int WINAPI MessageBox(HWND, LPSTR, LPSTR, UINT);
			*/
			break;


		case '-':
			result = var1 - var2;
			wsprintf(str, TEXT("The difference of %d and %d is: %d"), var1, var2, result);
			MessageBox(hwnd, str, TEXT("SUBTRACTION"), MB_OK);
			break;


		case '/':
			result = var1 / var2;
			wsprintf(str, TEXT("The division of %d and %d is: %d"), var1, var2, result);
			MessageBox(hwnd, str, TEXT("DIVISION"), MB_OK);
			break;


		case '*':
			result = var1 * var2;
			wsprintf(str, TEXT("The multiplication of %d and %d is: %d"), var1, var2, result);
			MessageBox(hwnd, str, TEXT("MULTIPLICATION"), MB_OK);
			break;


		case '%':
			result = var1 % var2;
			wsprintf(str, TEXT("The modulo division of %d and %d is: %d"), var1, var2, result);
			MessageBox(hwnd, str, TEXT("MODULO DIVISION"), MB_OK);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		/*
			VOID WINAPI PostQuitMessage( int );
		*/
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
	/*
		LRESULT WINAPI DefWindowProc(HWND, UINT, WPARAM, LPARAM);
	*/
}
