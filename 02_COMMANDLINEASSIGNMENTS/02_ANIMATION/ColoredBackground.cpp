// the header
#include<windows.h>


// global declarations

#define MYTIMER 102 

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
		HICON WINAPI LoadIcon(HINSTACE, LPCSTR);
	*/

	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*
		HCURSOR WINAPI LoadCursor(HINSTANCE, LPCSTR);
	*/

	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	/*
		HGDI WINAPI GetStockObject (int);
	*/

	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the class
	RegisterClassEx(&wndclass);
	/*
		ATOM WINAPI RegisterClassEx(const WNDCLASSEX *);
	*/

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("Colored Background Animation "),
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
	HWND WINAPI CreateWindow(LPSTR, LPSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
	*/

	ShowWindow(hwnd, iCmdShw);
	/*
		BOOL WINAPI ShowWindow(HWND, UINT);
	*/

	UpdateWindow(hwnd);
	/*
		BOOL WINAPI UpdateWindow(HWND);
	*/

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
		/*
			BOOL WINAPI GetMessage(const MSG *, HWND, int, int);
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
	
	// declarations
	static HBRUSH hbrush[8];
	static int iPaintFlag = 0;
	RECT rc;
	PAINTSTRUCT ps;
	HDC hdc;
	


	switch (iMsg) {

	case WM_CREATE:
		hbrush[0] = CreateSolidBrush(RGB(255, 0, 0));
		hbrush[1] = CreateSolidBrush(RGB(0, 255, 0));
		hbrush[2] = CreateSolidBrush(RGB(0, 0, 255));
		hbrush[3] = CreateSolidBrush(RGB(0, 255, 255));
		hbrush[4] = CreateSolidBrush(RGB(255, 0, 255));
		hbrush[5] = CreateSolidBrush(RGB(255, 255, 0));
		hbrush[6] = CreateSolidBrush(RGB(0, 0, 0));
		hbrush[7] = CreateSolidBrush(RGB(255, 255, 255));
		/*
			HBRUSH WINAPI CreateSolidBrush( COLORREF);
		*/
		SetTimer(hwnd, MYTIMER, 1000, NULL);
		/*
			UINT_PTR WINAPI SetTimer(HWND, UINT_PTR, UINT, TIMERPROC );	
		*/
		break;

	case WM_TIMER:
		/*
			Never put a loop here as WM_TIMER itself is a loop.
			Suppose if the statements take 1 sec to work, then you'll have to first kill the timer as until they execute at that time another WM_TIMER can arise. So kill and then do the work and again set the timer.
			wParam : 2nd Param of SetTimer.
			lparam: 4th param of SetTimer.
		*/
		KillTimer(hwnd, MYTIMER);
		/*
			BOOL WINAPI KillTimer (HWND, UINT_PTR);
		*/
		if (iPaintFlag > 7) {
			iPaintFlag = -1;
		}
		iPaintFlag++;
		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd, MYTIMER, 1000, NULL);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, hbrush[iPaintFlag]);
		FillRect(hdc, &rc, hbrush[iPaintFlag]);
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