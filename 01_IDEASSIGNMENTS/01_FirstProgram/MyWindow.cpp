// the header
#include<windows.h>

// global func declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	/*
	The CALLBACK keyword defines the calling convention of the function.
	*/

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShw) {
	// var declarations

	WNDCLASSEX wndclass;
	// Can also use WNDCLASS which has 10 members that exclude cb.Size and hIconSm
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	// code
	// init
	wndclass.cbSize = sizeof(WNDCLASSEX);
	// cb: count of bytes

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	// CS: Class Style HREDRAW means if extended horizontally, the window be redrawn horizontally, VREDRAW means if extended vertically, the window be redrawn vertically. 
	
	wndclass.cbClsExtra = 0;
	// ClsExtra: Extra information about class

	wndclass.cbWndExtra = 0;
	// WndExtra: Extra information about Window

	wndclass.lpfnWndProc = WndProc;
	// lpfn: long ptr to function WndProc

	wndclass.hInstance = hInstance;
	// hInstance: handle to current instance.

	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// hIcon: handle to Icon
	/*
		HICON LoadIcon(HINSTANCE hInstance, LPCSTR lpIconName);
	*/

	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	// hCursor: handle to cursor
	/*
		HCURSOR LoadCursor(HINSTANCE hInstance, LPCSTR lpCursorName);
	*/

	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	// hbrBackground: handle to the bush of specified backgroud
	/*
		HGDIOBJ GetStockObject(int i);
	*/

	wndclass.lpszClassName = szAppName;
	// lpsz: long ptr to zero terminated string

	wndclass.lpszMenuName = NULL;
	// lpszMenuName: specify the name of menu. We dont have any hence NULL

	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	// hIconSm: handle to small icon
	/*
		HICON LoadIcon(HINSTANCE hInstance, LPCSTR lpIconName);
	*/

	// register the class
	RegisterClassEx(&wndclass);
	/*
		ATOM RegisterClassEx(const WNDCLASSEX *arg1);
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
	// Create the window using the following properties
	/*
		1. Name
		2. Caption
		3. Window Style
		4. x
		5. y
		6. w
		7. h
		8. handle to parent (makes desktop the parent when NULL
		9. handle to Menu
		10. handle to instance
		11. lpParam (extra information)
	*/
	/*
		HWND CreatWindow(LPCTR,
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
	// Create window just creates the Window in RAM. ShowWindow() is used to display it.
	/*
		BOOL ShowWindow( HWND, int);
	*/

	UpdateWindow(hwnd);
	// Draws the client area
	/*
		BOOL UpdateWindow(HWND);
	*/

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	/*
		BOOL GetMessage(LPMSG, HWND, UINT, UINT);
		1. Pointer to msg struct
		2. Handle to the window. NULL because if multiple windows there will be one message loop only thus to get messages of all windows NULL.
		3. Start range
		4. End range
	*/
	{
		TranslateMessage(&msg);
		/*
			BOOL TranslateMessage( const MSG *);
			TranslateMessage does low level conversion of h/w messages.
			In this process many software msgs are also created which are given to OS. Only the h/w message is given to further.

		*/

		DispatchMessage(&msg);
		/*
			LRESULT DispatchMessage(const MSG *);
			Dispatches the message to WndProc.	
		*/
	}
	/*
		We'll come out of the loop only when WM_QUIT is encountered by GetMessage. Thus implies, GetMessage checks the message and return true for every message except WM_QUIT.
		WM_QUIT's third param is set to 0 by PostQuitMessage.
		Thus returns 0.
	*/
	return((int)msg.wParam);
	
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	// code

	switch (iMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		/*
			void PostQuitMessage(int return value)
		*/
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
	/*
		If the case is not handled then it is sent back to the OS.
		LRESULT DefWindowProc(HWND, UINT, WPARAM, LPARAM);
	*/
}