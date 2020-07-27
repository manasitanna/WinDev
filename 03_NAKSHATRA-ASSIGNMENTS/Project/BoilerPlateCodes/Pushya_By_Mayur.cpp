

		/*		SHREE GOKHALE MASTER PRASSANA		*/	
/*************************************************************************************\
	
	THERE ARE CHANGES TO MAKE IN THIS CODE IN ORDER, YOUR CODE
	OF NAKSHATRA MUST RUN.

	READ THIS CAREFULLY AND DONT TRY TO CHANGE ANY OF THE OTHER 
	LINES OF THE CODE THE CHANGES NEEDED TO BE DONE ARE AS FOLLOWS:
	
	CHANGES:
		1)		LINE NO 67:	Change the name of the declared function (ONLY THE NAME DONT CHANGE THE PARAMETERS )
					By the name of your function.
					If you are drawing PUSHYA the the name of the 
					function will be
					Ex : Pushya_By_Manasi()

		2)		LINE NO 170:	As we are using Function Pointers So We need to register your function. It
					is done on line 170. So without changing anything just change the name of my function
					with your function name on line 170.

		3)		Definition of your funtion (LINE NO 373) in which you will be writing the code 
				for drawing the NAKSHATRA.
				( I WANT THREE DIFFERENT PROGRAMS FOR EACH NAKSHATRA and 
				the program file must be named as 
				1.)	Krittika_By_Hrituja.cpp
				2.)	Hasta_By_Hrituja.cpp	
				3.)	Revati_By_Hrituja.cpp)  

		4.)		The MACRO For The radius of Circle in Percent at Line no 45



\*************************************************************************************/

// HEADERS
#include <windows.h>
#include "resource.h"

//	CALLBACK FUNCTION DECLARATION
LRESULT CALLBACK WndProc( HWND , UINT , WPARAM, LPARAM);


// 	MACROS
#define 		NO_OF_WINDOWS		27 

#define			CIRCLE_RADIUS_PERCENT	1.5			/*******		CHANGE THE PERCENT FOR RADIUS HERE		*******/

#define			WIDTH_PEN_LINE			5
#define			WIDTH_PEN_DOT			1

// 	GLOBAL VARIABLES
typedef struct tagReferenceWindow
{
	DWORD	reference_window_move_y;
	DWORD	reference_window_resize_width; 
	DWORD	reference_window_resize_height;

	void (*fun_ptr_draw)(HDC, DWORD, DWORD, DWORD, DWORD);

}REFERENCEWINDOW;

REFERENCEWINDOW reference_window[NO_OF_WINDOWS];

/*******************************************		MY FUNCTION DECLARATION		************************************************/

void	Pushya_By_Mayur(HDC, DWORD, DWORD, DWORD, DWORD);		/********		CHANGE THE FUNCTION NAME HERE		**********/
	
void	DrawCircle(HDC, DWORD, DWORD, DWORD);

void 	DrawReferenceWindow(HWND, HDC, REFERENCEWINDOW);

DWORD	GetValueFromPercentage(DWORD, float);

DWORD 	GetHeightFromRatio(DWORD main_window_height, DWORD main_window_width, DWORD reference_window_width);

void	WriteTextToReferenceWindow(HDC, LPSTR, DWORD, DWORD, DWORD, DWORD);

/******************************************************************************************************************************/


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdline, int iCmdShow)
{


	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndcls;
	TCHAR szAppName[] = TEXT("NAKSHATRA");


	wndcls.cbSize = sizeof(WNDCLASSEX);
	wndcls.cbWndExtra = 0;
	wndcls.cbClsExtra = 0;
	wndcls.style = CS_VREDRAW | CS_HREDRAW;
	wndcls.hIcon = LoadIcon(NULL , IDI_APPLICATION);
	wndcls.hIconSm = LoadIcon(NULL , IDI_APPLICATION);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);;
	wndcls.hInstance = hInstance;
	wndcls.lpfnWndProc = WndProc;
	wndcls.lpszClassName = szAppName;
	wndcls.lpszMenuName = NULL;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	RegisterClassEx(&wndcls);

	hwnd = CreateWindow(szAppName,
		TEXT("Boiler Plate Code"),
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_OVERLAPPED,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	while(GetMessage(&msg, NULL, 0 ,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	RECT rc_main_window;

	HBITMAP hbitmap, hold_bitmap;

	BITMAP bitmap;

	static HINSTANCE hInstance;

	static DWORD main_window_height = 0;
	static DWORD main_window_width = 0;

	switch(iMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_CREATE:				//	CONSTRUCTOR
				
			GetClientRect(hwnd, &rc_main_window);

			hInstance = ((LPCREATESTRUCT) lParam)->hInstance;

			main_window_width = rc_main_window.right;
			main_window_height = rc_main_window.bottom;


			break;

		case WM_SIZE:	//	lParam 	->		LOWORD		->	mainwindow_width
						//			->		HIWORD		->	mainwindow_height
			
			main_window_width = LOWORD(lParam);
			main_window_height = HIWORD(lParam);		

			for( int i = 0 ; i < NO_OF_WINDOWS ; i++)
			{

				if( i == 0)
				{
					reference_window[i].fun_ptr_draw = Pushya_By_Mayur;		/********		CHANGE THE FUNCTION NAME HERE		**********/
					reference_window[i].reference_window_move_y = 0;
				}
				else
				{
					reference_window[i].fun_ptr_draw = NULL;
					reference_window[i].reference_window_move_y =  reference_window[i-1].reference_window_move_y + reference_window[i-1].reference_window_resize_height + 20;
				}
					

				reference_window[i].reference_window_resize_width = (6 * main_window_width ) /8;
				reference_window[i].reference_window_resize_height	=	GetHeightFromRatio( main_window_height ,
																							main_window_width,
																							reference_window[i].reference_window_resize_width);
			}
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case WM_PAINT:

			GetClientRect(hwnd, &rc_main_window);

			hdc = BeginPaint(hwnd, &ps);

			hbitmap = LoadBitmap(hInstance, IDB_GALAXY);
			GetObject(hbitmap, sizeof(BITMAP), &bitmap);
			hdcMem = CreateCompatibleDC(hdc);
			hold_bitmap = (HBITMAP) SelectObject(hdcMem, hbitmap);	

			StretchBlt(hdc,
				0,
				0,
				main_window_width,
				main_window_height,
				hdcMem,
				0,
				0,
				bitmap.bmWidth,
				bitmap.bmHeight,
				MERGECOPY);

			DeleteObject( SelectObject(hdc, hold_bitmap) );
			DeleteDC(hdcMem);

			for( int i = 0 ; i < NO_OF_WINDOWS ; i++)
			{

				DrawReferenceWindow(hwnd, 
					hdc, 
					reference_window[i]);
			}


			ReleaseDC(hwnd, hdc);
			EndPaint(hwnd, &ps);

			break;

		case WM_KEYDOWN:

			switch(LOWORD(wParam))
			{
				case VK_ESCAPE:
					DestroyWindow(hwnd);
					break;
			}
			break;

		case WM_CHAR:

			switch( LOWORD(wParam))
			{

				case 'w':
				case 'W':

					for( int i = 0 ; i < NO_OF_WINDOWS ; i++)
						reference_window[i].reference_window_move_y -= 10;
					
					InvalidateRect(hwnd, NULL, TRUE);
					break;

				case 's':
				case 'S':
					for( int i = 0 ; i < NO_OF_WINDOWS ; i++)
						reference_window[i].reference_window_move_y += 10;
					InvalidateRect(hwnd, NULL, TRUE);
					break;

				case 'q':
				case 'Q':
					
					for( int i = 0 ; i < NO_OF_WINDOWS ; i++)
					{

						if( reference_window[i].reference_window_resize_width < 20 )
							break;

						reference_window[i].reference_window_resize_width -= 20;
						reference_window[i].reference_window_resize_height	=	GetHeightFromRatio( main_window_height ,
																									main_window_width,
																									reference_window[i].reference_window_resize_width);
					}
					InvalidateRect(hwnd, NULL, TRUE);
					break;

				case 'e':
				case 'E':
					for( int i = 0 ; i < NO_OF_WINDOWS ; i++)
					{

						//if( reference_window[i].reference_window_resize_width > (main_window_width - 100) )
						//	break;

						reference_window[i].reference_window_resize_width += 20;
						reference_window[i].reference_window_resize_height	=	GetHeightFromRatio( main_window_height ,
																									main_window_width,
																									reference_window[i].reference_window_resize_width);
					
					}
					InvalidateRect(hwnd, NULL, TRUE);
					break;
			}
			break;


	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}



DWORD GetHeightFromRatio(DWORD main_window_height, DWORD main_window_width, DWORD reference_window_width)
{
	return ((DWORD) ((float)( main_window_height * reference_window_width ) /(float)main_window_width) );	
}



void DrawReferenceWindow(HWND hwnd, HDC hdc, REFERENCEWINDOW ref_wnd)
{

	// Variable Declaration	
	DWORD reference_window_x_pos = 0;
	DWORD reference_window_y_pos = 0;

	DWORD main_window_horizontal_half = 0;
	DWORD main_window_vertical_half = 0;

	HBRUSH hBrush_black = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hold = (HBRUSH) SelectObject(hdc, hBrush_black);

	RECT rc_main_window;

	// Code
	GetClientRect(hwnd, &rc_main_window);

	main_window_horizontal_half = rc_main_window.right / 2;
	main_window_vertical_half = rc_main_window.bottom / 2;


	reference_window_x_pos = main_window_horizontal_half - (ref_wnd.reference_window_resize_width / 2);
	reference_window_y_pos = main_window_vertical_half - (ref_wnd.reference_window_resize_height / 2);

	reference_window_y_pos = reference_window_y_pos + ref_wnd.reference_window_move_y;

	DeleteObject( SelectObject(hdc, hold));

	if( ref_wnd.fun_ptr_draw != NULL)
	{
		(*ref_wnd.fun_ptr_draw)(hdc, 
			reference_window_x_pos, 
			reference_window_y_pos,
			ref_wnd.reference_window_resize_width, 
			ref_wnd.reference_window_resize_height);
	}
	
}


void DrawCircle(HDC hdc, DWORD dot_1_x_pos, DWORD dot_1_y_pos, DWORD circle_radius)
{
	Ellipse(hdc,
		dot_1_x_pos - circle_radius,
		dot_1_y_pos - circle_radius,
		dot_1_x_pos + circle_radius,
		dot_1_y_pos + circle_radius);
}


DWORD GetValueFromPercentage(DWORD hundred_percent_value, float percent)
{
	return ((DWORD)((float)( hundred_percent_value * percent ) / (float) 100.0f));
}


void WriteTextToReferenceWindow(HDC hdc, LPSTR name_str, DWORD reference_window_x_pos, DWORD reference_window_y_pos, DWORD reference_window_width, DWORD reference_window_height)
{

	RECT rc_text;

	rc_text.left = reference_window_x_pos;
	rc_text.right  = reference_window_x_pos + reference_window_width;

	rc_text.top = reference_window_y_pos;
	rc_text.bottom  = reference_window_y_pos + reference_window_height;

	SetBkMode(hdc, TRANSPARENT);
	//SetBkColor(hdc ,RGB(0, 0, 0));
	SetTextColor(hdc ,RGB(0, 255, 255));

	DrawText(hdc,
		name_str,
		-1,
		&rc_text,
		DT_SINGLELINE);

}


/************************************************************* HERE YOUR FUNCTION DEFINITION	***************************************************************************/
/********		CHANGE THE FUNCTION NAME HERE		**********/
void Pushya_By_Mayur(HDC hdc, DWORD reference_window_x_pos, DWORD reference_window_y_pos, DWORD reference_window_width, DWORD reference_window_height)
{

	// Variable Declaration
	
	/*	DONT CHANGE THIS LINE	*/
	const DWORD circle_radius = GetValueFromPercentage( reference_window_width, CIRCLE_RADIUS_PERCENT );

	HBRUSH hbrush_red = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hbrush_cyan = CreateSolidBrush(RGB(0, 255, 255));
	HBRUSH hold_brush = 0;

	HPEN hpen_cyan_line = CreatePen( PS_SOLID, WIDTH_PEN_LINE, RGB(0, 255, 255));
	
	HPEN hpen_cyan_dot = CreatePen( PS_SOLID, WIDTH_PEN_DOT, RGB(0, 255, 255));
	HPEN hpen_red_dot = CreatePen( PS_SOLID, WIDTH_PEN_DOT, RGB(255, 0, 0));

	HPEN hold_pen;

	POINT point[6];
	POINT line_point[4];

	// Code
	point[0].x = reference_window_x_pos + ( reference_window_width / 2 ) - GetValueFromPercentage( (reference_window_width / 2) , 50 );
	point[0].y = reference_window_y_pos + (reference_window_height / 2) - GetValueFromPercentage( (reference_window_height/2), 25 );

	point[1].x = reference_window_x_pos + ( reference_window_width / 2 ) - GetValueFromPercentage((reference_window_width / 2), 15);
	point[1].y = reference_window_y_pos + (reference_window_height / 2) - GetValueFromPercentage( (reference_window_height/2), 30 );

	point[2].x = reference_window_x_pos + ( reference_window_width / 2 ) + GetValueFromPercentage( (reference_window_width / 2), 10);
	point[2].y = reference_window_y_pos + (reference_window_height / 2) - GetValueFromPercentage( (reference_window_height/2), 43 );

	point[3].x = reference_window_x_pos + ( reference_window_width / 2 ) + GetValueFromPercentage( (reference_window_width / 2), 38);
	point[3].y = reference_window_y_pos + (reference_window_height / 2) - GetValueFromPercentage( (reference_window_height/2), 80 );

	point[4].x = reference_window_x_pos + ( reference_window_width / 2 ) - GetValueFromPercentage((reference_window_width / 2), 30);
	point[4].y = reference_window_y_pos + (reference_window_height / 2) + GetValueFromPercentage( (reference_window_height/2), 75 );

	point[5].x = reference_window_x_pos + ( reference_window_width / 2 ) + GetValueFromPercentage( (reference_window_width / 2), 25);
	point[5].y = reference_window_y_pos + (reference_window_height / 2) + GetValueFromPercentage( (reference_window_height/2), 40 );


	line_point[0].x = point[1].x;
	line_point[0].y = point[1].y;

	line_point[1].x = point[4].x;
	line_point[1].y = point[4].y;

	line_point[2].x = point[5].x;
	line_point[2].y = point[5].y;

	line_point[3].x = point[2].x;
	line_point[3].y = point[2].y;

	/************	DRAWING LINES 	************/

	hold_pen = (HPEN)	SelectObject(hdc, hpen_cyan_line);
	Polyline(hdc, point, 4);
	Polyline(hdc, line_point, 4);
	DeleteObject( SelectObject(hdc, hold_pen));

	/*******************************************/


	/************	DRAWING DOTS 	************/

	hold_pen = (HPEN)	SelectObject(hdc, hpen_red_dot);
	hold_brush = (HBRUSH) SelectObject(hdc, hbrush_red);
	DrawCircle(hdc, point[1].x, point[1].y, circle_radius);
	DeleteObject( SelectObject(hdc, hold_brush));
	DeleteObject( SelectObject(hdc, hold_pen));

	hold_brush = (HBRUSH) SelectObject(hdc, hbrush_cyan);
	hold_pen = (HPEN)	SelectObject(hdc, hpen_cyan_dot);
	DrawCircle(hdc, point[0].x, point[0].y, circle_radius);
	DrawCircle(hdc, point[2].x, point[2].y, circle_radius);
	DrawCircle(hdc, point[3].x, point[3].y, circle_radius);
	DrawCircle(hdc, point[4].x, point[4].y, circle_radius);
	DrawCircle(hdc, point[5].x, point[5].y, circle_radius);
	DeleteObject( SelectObject(hdc, hold_pen));
	DeleteObject( SelectObject(hdc, hold_brush));

	/*******************************************/

	WriteTextToReferenceWindow(hdc, 
		TEXT("PUSHYA"), 
		reference_window_x_pos,
		reference_window_y_pos,
		reference_window_width,
		reference_window_height);

}


/*************************************************************************************************************************************************************/


