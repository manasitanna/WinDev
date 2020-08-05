// header
#include<windows.h>
#include<windowsx.h>

// global declaration
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

 int iFlag = 1;

// main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {

	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndcls;
	TCHAR szAppName[] = TEXT("Dynamic Rect");

	// init

	wndcls.cbSize = sizeof(WNDCLASSEX);
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.lpfnWndProc = WndProc;
	wndcls.lpszClassName = szAppName;
	wndcls.lpszMenuName = NULL;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hCursor = LoadCursor(NULL, IDC_HAND);
	wndcls.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hInstance = hInstance;

	RegisterClassEx(&wndcls);

	hwnd = CreateWindow(szAppName,
		TEXT("Dynamic Window"),
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		100,
		100,
		800,
		800,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	static int x;
	static int y;
	static int width;
	static int height;

	
	static int iFlag1 = 0;
	

	HWND windowHwnd;
	RECT window_rc;

	static int click_down_x;
	static int click_down_y;

	static int click_up_x;
	static int click_up_y;

	static int current_x;
	static int current_y;
	
	HDC hdc;
	PAINTSTRUCT ps;
	RECT client_rc;

	RECT paint_rc;

	windowHwnd = GetDesktopWindow();
	GetClientRect(windowHwnd, &window_rc);


	switch (iMsg) {
	
	case WM_CREATE:

		x = ((LPCREATESTRUCT) lParam)->x;
		y = ((LPCREATESTRUCT)lParam)->y;
		width = ((LPCREATESTRUCT)lParam)->cx;
		height = ((LPCREATESTRUCT)lParam)->cy;

		break;

	case WM_CHAR:
		switch (wParam) {
		
		case 'M':
		case 'm':
			if (iFlag1 == 0) {
				SetWindowPos(hwnd, HWND_TOP, window_rc.left, window_rc.top, window_rc.right, window_rc.bottom, SWP_SHOWWINDOW);
				iFlag1 = 1;
			}

			else {
				SetWindowPos(hwnd, HWND_TOP, x, y, width, height, SWP_SHOWWINDOW);
				iFlag1 = 0;
			}
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		iFlag = 0;
		SetCapture(hwnd);
		TCHAR str1[500];

		click_down_x = LOWORD(lParam);
		click_down_y = HIWORD(lParam);
	
		
		InvalidateRect(hwnd, NULL, TRUE);
		
		break;

	case WM_LBUTTONUP:
		iFlag = 1;
		TCHAR str2[500];

		click_up_x = GET_X_LPARAM(lParam);
		click_up_y = GET_Y_LPARAM(lParam);
		ReleaseCapture();
		InvalidateRect(hwnd, NULL, TRUE);
		
		break;

	case WM_MOUSEMOVE:
		if (iFlag == 0) {
			current_x = GET_X_LPARAM(lParam);
			current_y = GET_Y_LPARAM(lParam);

			InvalidateRect(hwnd, NULL, TRUE);
		}
		
		break;

	case WM_PAINT:

		if (iFlag == 0) {

			GetClientRect(hwnd, &client_rc);
			hdc = BeginPaint(hwnd, &ps);
			paint_rc = { click_down_x, click_down_y, current_x, current_y };
			FillRect(hdc, &paint_rc, CreateSolidBrush(RGB(0, 255, 255)));
			EndPaint(hwnd, &ps);
			ReleaseDC(hwnd, hdc);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}