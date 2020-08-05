// the header
#include<windows.h>
#include<windowsx.h>

#define			BUTTON_HACK_WINDOW			101
#define			BUTTON_CLOSE_WINDOW			102
#define			BUTTON_X_RESIZE_POS			103
#define			BUTTON_X_RESIZE_NEG			104
#define			BUTTON_Y_RESIZE_POS			105
#define			BUTTON_Y_RESIZE_NEG			106
#define			BUTTON_X_MOVE_POS			107
#define			BUTTON_X_MOVE_NEG			108
#define			BUTTON_Y_MOVE_POS			109
#define			BUTTON_Y_MOVE_NEG			110
#define			BUTTON_WRITE				111
#define			BUTTON_CLOSE_MY_WINDOW		112
#define			BUTTON_CHANGE_ICON			113
#define			BUTTON_REMOVE_MENUBAR		114

//global function declaration
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
// global variable declarations
HWND note_pad_hwnd;
HWND note_pad_edit_hwnd;
HWND note_pad_menu_hwnd;
// my function declarations
void HackNotePadWindow(HWND hwnd);
void CloseAppWindow(HWND hwnd);
void IncreaseWidth(HWND hwnd, int left, int top, int right, int bottom);
void DecreaseWidth(HWND hwnd, int left, int top, int right, int bottom);
void IncreaseHeight(HWND hwnd, int left, int top, int right, int bottom);
void DecreaseHeight(HWND hwnd, int left, int top, int right, int bottom);
void MoveRight(HWND hwnd, int left, int top, int right, int bottom);
void MoveLeft(HWND hwnd, int left, int top, int right, int bottom);
void MoveUp(HWND hwnd, int left, int top, int right, int bottom);
void MoveDown(HWND hwnd, int left, int top, int right, int bottom);
void Write(HWND hwnd, LPSTR text);
void ChangeIcon(HWND hwnd);
void RemoveMenu(HWND hwnd);


// main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	
	// variable declarations
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Manasi's Program");
	WNDCLASSEX wndcls;

	// initialization
	wndcls.cbSize = sizeof(WNDCLASSEX);
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.lpfnWndProc = WndProc;
	wndcls.lpszClassName = szAppName;
	wndcls.lpszMenuName = NULL;
	wndcls.hInstance = hInstance; 
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register wndcls
	RegisterClassEx(&wndcls);

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("My NotePad Hack"),
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		0,
		0,
		800,
		750,
		NULL,
		NULL,
		hInstance,
		NULL);

	// show and update window
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	// message loop
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

// callback function definition
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	// declarations
	static HWND hwnd_hack_notepad_button;
	static HWND hwnd_close_notepad_button;
	static HWND hwnd_x_resize_pos;
	static HWND hwnd_x_resize_neg;
	static HWND hwnd_y_resize_pos;
	static HWND hwnd_y_resize_neg;
	static HWND hwnd_x_move_pos;
	static HWND hwnd_x_move_neg;
	static HWND hwnd_y_move_pos;
	static HWND hwnd_y_move_neg;
	static HWND hwnd_write;
	static HWND hwnd_close_my_window;
	static HWND hwnd_changeIcon;
	static HWND hwnd_remove_menubar;
	RECT rc, main_rc;
	static int left, top, right, bottom;
	HDC hdc;
	TCHAR text2[] = TEXT("HELLO NOTEPAD");
	

	// definition
	switch (iMsg) {
	case WM_CREATE:
		EnumWindows(EnumWindowsProc, NULL);
		EnumChildWindows(note_pad_hwnd, EnumChildProc, NULL);
		GetClientRect(note_pad_hwnd, &rc);
		
		right = rc.right;
		bottom = rc.bottom;

		GetWindowRect(note_pad_hwnd, &main_rc);

		left = main_rc.left;
		top = main_rc.top;

		MessageBox(hwnd, TEXT("Completed"), TEXT("Informatory"), MB_OK);
		

		
		// hack and close

		hwnd_hack_notepad_button = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("HACK NOTEPAD"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			10,         // x position 
			10,         // y position 
			200,        // Button width
			100,        // Button height
			hwnd,     // Parent window
			(HMENU)BUTTON_HACK_WINDOW,       
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		hwnd_close_notepad_button = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("CLOSE NOTEPAD"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			300,         // x position 
			10,         // y position 
			200,        // Button width
			100,        // Button height
			hwnd,     // Parent window
			(HMENU)BUTTON_CLOSE_WINDOW,       
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		// inc dec width
		hwnd_x_resize_pos = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("INCREASE WIDTH"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			10,         // x position 
			150,         // y position 
			200,        // Button width
			100,        // Button height
			hwnd,     // Parent window
			(HMENU)BUTTON_X_RESIZE_POS,       
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		hwnd_x_resize_neg = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("DECREASE WIDTH"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			300,         // x position 
			150,         // y position 
			200,        // Button width
			100,        // Button height
			hwnd,     // Parent window
			(HMENU) BUTTON_X_RESIZE_NEG,       
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		// inc dec height

		hwnd_y_resize_neg = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("INCREASE HEIGHT"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			10,         // x position 
			300,         // y position 
			200,        // Button width
			100,        // Button height
			hwnd,     // Parent window
			(HMENU) BUTTON_Y_RESIZE_NEG,       
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		hwnd_y_resize_pos = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("DECREASE HEIGHT"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			300,         // x position 
			300,         // y position 
			200,        // Button width
			100,        // Button height
			hwnd,     // Parent window
			(HMENU) BUTTON_Y_RESIZE_POS ,      
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		// move x

		hwnd_x_move_pos = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("MOVE RIGHT"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			10,         // x position 
			450,         // y position 
			200,        // Button width
			100,        // Button height
			hwnd,     // Parent window
			(HMENU)BUTTON_X_MOVE_POS,
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		hwnd_x_move_neg = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("MOVE LEFT"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			300,         // x position 
			450,         // y position 
			200,        // Button width
			100,        // Button height
			hwnd,     // Parent window
			(HMENU)BUTTON_X_MOVE_NEG,
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		// move y

		hwnd_y_move_pos = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("MOVE DOWN"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			10,         // x position 
			600,         // y position 
			200,        // Button width
			100,        // Button height
			hwnd,     // Parent window
			(HMENU)BUTTON_Y_MOVE_POS,
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);


		hwnd_y_move_neg = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("MOVE UP"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			300,         // x position 
			600,         // y position 
			200,        // Button width
			100,        // Button height
			hwnd,     // Parent window
			(HMENU)BUTTON_Y_MOVE_NEG,
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		hwnd_write = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("WRITE ON NOTEPAD"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			550,         // x position 
			300,         // y position 
			200,        // Button width
			100,        // Button height
			hwnd,     // Parent window
			(HMENU)BUTTON_WRITE,
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		hwnd_close_my_window = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("CLOSE APPLICATION"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			550,         // x position 
			450,         // y position 
			200,        // Button width
			100,        // Button height
			hwnd,     // Parent window
			(HMENU)BUTTON_CLOSE_MY_WINDOW,
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		hwnd_changeIcon = CreateWindow(
			TEXT("BUTTON"),
			TEXT("CHANGE ICON"),
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			550,
			10,
			200,
			100,
			hwnd,
			(HMENU)BUTTON_CHANGE_ICON,
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE ),
			NULL);

		hwnd_remove_menubar = CreateWindow(
			TEXT("BUTTON"),
			TEXT("REMOVE MENUBAR"),
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			550,
			150,
			200,
			100,
			hwnd,
			(HMENU)BUTTON_REMOVE_MENUBAR,
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		break;

	case WM_PAINT:
		
		 

		break;

	case WM_COMMAND:
		

		switch (LOWORD(wParam)) {
		case BUTTON_HACK_WINDOW:
			HackNotePadWindow(note_pad_hwnd);
			

			break;

		case BUTTON_CLOSE_WINDOW:
			CloseAppWindow(note_pad_hwnd);
			break;

		case BUTTON_X_RESIZE_POS:
			right = right + right / 4;
			IncreaseWidth(note_pad_hwnd, left, top, right, bottom);
			break;

		case BUTTON_X_RESIZE_NEG:
			right = right - right / 4;
			DecreaseWidth(note_pad_hwnd, left, top, right, bottom);
			break;

		case BUTTON_Y_RESIZE_POS:
			bottom = bottom - bottom / 4;
			IncreaseHeight(note_pad_hwnd, left, top, right, bottom);
			break;

		case BUTTON_Y_RESIZE_NEG:
			bottom = bottom + bottom / 4;
			DecreaseHeight(note_pad_hwnd, left, top, right, bottom);
			break;

		case BUTTON_X_MOVE_POS:
			left = left + left / 4;
			MoveRight(note_pad_hwnd, left, top, right, bottom);
			break;

		case BUTTON_X_MOVE_NEG:
			left = left - left / 4;
			MoveLeft(note_pad_hwnd, left, top, right, bottom);
			break;

		case BUTTON_Y_MOVE_POS:
			top = top + top / 4;
			MoveUp(note_pad_hwnd, left, top, right, bottom);
			break;

		case BUTTON_Y_MOVE_NEG:
			top = top - top / 4;
			MoveDown(note_pad_hwnd, left, top, right, bottom);
			break;

		case BUTTON_CHANGE_ICON:
			ChangeIcon(note_pad_hwnd);
			break;

		case BUTTON_WRITE:
			Write(note_pad_edit_hwnd, TEXT("Hello notepad"));
			break;

		case BUTTON_REMOVE_MENUBAR:
			RemoveMenu(note_pad_menu_hwnd);
			break;

		case BUTTON_CLOSE_MY_WINDOW:
			CloseAppWindow(hwnd);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam){
	
	// variable declarations
	TCHAR windowName[250];
	int nameLength = 250;
	int returnValue;
	static int windowNumber = 0;
	TCHAR str[255];

		memset(windowName, 0, sizeof(windowName));
		windowNumber = windowNumber + 1;
		
		returnValue = GetWindowText(hwnd, windowName, 256);

		/*wsprintf(str, TEXT(" Window %d: %s"), windowNumber, windowName);
		// MessageBox(NULL, str, TEXT("Window Details"), MB_OK);
		/*if (nameLength > 0)
			return(TRUE);
		else
			return(FALSE);*/

		if (lstrcmp(windowName, TEXT("Untitled - Notepad"))== 0) {
			note_pad_hwnd = hwnd;
			
		}
		
		return(TRUE);
		

}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
	
	TCHAR child_windowName[250];
	int nameLength = 250;
	int returnValue;
	static int child_windowNumber = 0;
	TCHAR str[255];
	
	
	GetClassName(hwnd, child_windowName, 255);
	//wsprintf(str, TEXT("  %s"), child_windowName);
	//MessageBox(NULL, str, TEXT("Child Window Details"), MB_OK);

	if (lstrcmp(child_windowName, TEXT("Edit")) == 0) 
		note_pad_edit_hwnd = hwnd;
	if (lstrcmp(child_windowName, TEXT("msctls_statusbar32")) == 0)
		note_pad_menu_hwnd = hwnd;

		return(TRUE);
	
	
}

void HackNotePadWindow(HWND notepad_hwnd) {
	
	SetWindowText(note_pad_hwnd, TEXT("HACKED"));

}

void CloseAppWindow(HWND hwnd) {

	SendMessage(hwnd, WM_DESTROY, NULL, NULL);
}

void IncreaseWidth(HWND hwnd, int left, int top, int right, int bottom) {
	
	SetWindowPos(
		hwnd,
		HWND_NOTOPMOST,
		left,
		top,
		right,
		bottom,
		SWP_SHOWWINDOW
	);
}

void DecreaseWidth(HWND hwnd, int left, int top, int right, int bottom) {
	

	SetWindowPos(
		hwnd,
		HWND_NOTOPMOST,
		left,
		top,
		right ,
		bottom,
		SWP_SHOWWINDOW
	);
}

void IncreaseHeight(HWND hwnd, int left, int top, int right, int bottom) {
	

	SetWindowPos(
		hwnd,
		HWND_NOTOPMOST,
		left,
		top,
		right,
		bottom,
		SWP_SHOWWINDOW
	);
}

void DecreaseHeight(HWND hwnd, int left, int top, int right, int bottom) {

	SetWindowPos(
		hwnd,
		HWND_NOTOPMOST,
		left,
		top,
		right,
		bottom,
		SWP_SHOWWINDOW
	);
}

void MoveRight(HWND hwnd, int left, int top, int right, int bottom) {
	
	SetWindowPos(
		hwnd,
		HWND_NOTOPMOST,
		left,
		top,
		right,
		bottom,
		SWP_SHOWWINDOW
	);
}

void MoveLeft(HWND hwnd, int left, int top, int right, int bottom) {
	
	SetWindowPos(
		hwnd,
		HWND_NOTOPMOST,
		left,
		top,
		right,
		bottom,
		SWP_SHOWWINDOW
	);
}

void MoveUp(HWND hwnd, int left, int top, int right, int bottom) {

	SetWindowPos(
		hwnd,
		HWND_NOTOPMOST,
		left,
		top,
		right,
		bottom,
		SWP_SHOWWINDOW
	);
}

void MoveDown(HWND hwnd, int left, int top, int right, int bottom) {
	
	SetWindowPos(
		hwnd,
		HWND_NOTOPMOST,
		left,
		top,
		right,
		bottom,
		SWP_SHOWWINDOW
	);
}

void Write(HWND hwnd, LPSTR text ) {
	HFONT hfont1;

	hfont1 = CreateFont(
	48,
	0,
	0,
	0,
	FW_BOLD,
	TRUE,
	FALSE,
	FALSE,
	DEFAULT_CHARSET,
	OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,
	PROOF_QUALITY,
	FIXED_PITCH,
	TEXT("Impact")
	);
	SendMessage(hwnd, WM_SETFONT,(WPARAM) hfont1,(LPARAM) TRUE);
	SendMessage(hwnd, WM_SETTEXT, NULL, (LPARAM) text);
}

void ChangeIcon(HWND hwnd) {
	HICON hIcon1;
	
	hIcon1 = LoadIcon(NULL, IDI_QUESTION);
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon1);
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM) hIcon1);
	
}

void RemoveMenu(HWND hwnd) {
	HMENU hMenu1;
	HMENU hMenu2;
	TCHAR str[255];
	TCHAR str2[255];
	//SetMenu(note_pad_hwnd, NULL);
	hMenu1 = GetMenu(note_pad_hwnd);
	hMenu2 = GetSubMenu(hMenu1, 0);
	int num = GetMenuItemCount(hMenu1);
	wsprintf(str, TEXT("%d"), num);
	MessageBox(NULL, str, TEXT("message"), MB_OK);
	int num2 = GetMenuItemID(hMenu1, 2);
	wsprintf(str2, TEXT("%d"), num);
	MessageBox(NULL, str2, TEXT("message"), MB_OK);
	EnableMenuItem(hMenu1, 5, MF_DISABLED);
	DrawMenuBar(note_pad_hwnd);
}