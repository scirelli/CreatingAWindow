//INCLUDES ////////////
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include "mainMenu.h"
#include <mmsystem.h> //needed to play a sound using windows also need to insert winmm.lib

//////DEFINES //////////////
//defines for windows
#define WINDOW_CLASS_NAME "WINCLASS1"

//GLOBALS///////////////////
HWND main_window_handle = NULL; //save the window handle

//FUNCTIONS ///////////////
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//this is the main message handler of the system
	PAINTSTRUCT ps; // used in WM_PAINT
	HDC hdc; //handle to a device context
	//find out what the message is
	switch(msg)
	{
	case WM_CREATE: // called when window created
		{ //do initialization here
			return(0);
		} break;
	case WM_PAINT: // called when window needs repainting
		{ //simply validate the window
			
			ValidateRect(hwnd,NULL);
			//hdc = BeginPaint(hwnd, &ps);
			//EndPaint(hwnd, &ps);
			
			return(0);
		}break;
	case WM_DESTROY: //called when window is killed
		{
			//kill the application
			PostQuitMessage(0);
			return(0);
		}break;
	case WM_USER: //A user messages
		{
			//data_1 will be in wparam //SendMessage(hwnd, WM_USER, data_1, data_2);
			//data_2 will be in lparam
		}break;
	case WM_CHAR:
		{
			//get ascii code and data bits
			int ascii_code = (int) wparam;
			int key_bits = (int) lparam;
			//do whatever...
			//tell windows that you processed the message
			return(0);
		}break;
	case WM_COMMAND:
		{
			// get the dc
			hdc = GetDC(hwnd);

			// set the color
			SetTextColor(hdc,RGB(255,0,0));
			SetBkColor(hdc,RGB(0,0,0));
			SetBkMode(hdc,OPAQUE);
			switch (wparam)
			{
			case ID_MAINMENU_FILE_SAVE:
				{
					TextOut(hdc, 0,30, "No code for this option", strlen("No code for this option"));
				}break;
			case ID_MAINMENU_FILE_OPEN:
				{
					TextOut(hdc, 0,30, "No code for this option", strlen("No code for this option"));
				}break;
			case ID_MAINMENU_FILE_EXIT:
				{
					PostMessage(hwnd,WM_QUIT,0,0); //post a WM_QUIT message to the message queue
				}break;
			case ID_MAINMENU_HELP_ABOUT:
				{
					MessageBox(hwnd,"The programer has created this program for \n learning purposes. If you would like the \n source code, emial:\n\t themanimal@aol.com","About",MB_OK);
				}break;
			}
			ReleaseDC(hwnd, hdc);
		}

	default: break;
	}//end switch
	//process any messages that you don't take care of
	return (DefWindowProc(hwnd, msg, wparam, lparam));
} //end WinProc



//WINMAIN ////////////////////////////////
int WINAPI WinMain( HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{
	WNDCLASS winclass; //this will hold the class you create
	HWND hwnd; // generic window handle
	MSG msg; //generic message
	HDC hdc; //store the device context
	//first, fill in the window class structure
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_NO);
	winclass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName =  "mainMenu";
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	//registger the window clas
	if (!RegisterClass(&winclass))
		return(0);
	//create tghe window
	if( !(hwnd = CreateWindow(WINDOW_CLASS_NAME, /*class*/
							  "Hello Steve", /*title*/
							   WS_OVERLAPPEDWINDOW | WS_VISIBLE, /*flaggs*/
							  100,100, /*x,y*/
							  640,480, /*width, height */
							  NULL,  /*handle to parent*/
							  NULL,  /*handle to menu*/
							  hinstance, /*instance*/
							  NULL)))  /*creattion parameters*/
	return(0);
	//save the window handle in a global
	main_window_handle = hwnd;
	
	//create the pens and brushes
	HPEN green_pen = CreatePen(PS_SOLID, 0, RGB(0,255,0)); //CreatePen(pen style, pen width, pen color);
	HBRUSH red_brush= CreateSolidBrush(RGB(255,0,0));//create a brush
	//define brush
	HBRUSH blue_brush= CreateSolidBrush(RGB(0,0,255));
	HBRUSH bitmap_brush= CreatePatternBrush(LoadBitmap(hinstance,MAKEINTRESOURCE(103)));
	
	//play a sound
	//PlaySound("PhoHit00.wav", NULL, SND_FILENAME | SND_ASYNC);
	//----------------------enter main event loop---------------------
	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			//test whether this is a quit
			if(msg.message == WM_QUIT)
				break;
			//translate any accelerator keys
			TranslateMessage(&msg);
			//send the message to the window proc
			DispatchMessage(&msg);
		}//end if
		//-----------------main processing goes here------------------
		
		hdc= GetDC(hwnd);
		
		SetBkMode(hdc, TRANSPARENT); //set background color
		SetTextColor(hdc,RGB(0,0,255)); //set text color
		TextOut(hdc,0,0,"Hello World",strlen("Hello World")); //print text
		
		for(int i=100; i<=120; i++) //draw a line with pixels
			SetPixel(hdc,i,100, RGB(255,255,255)); // display pixel

		//select pen into the context
		SelectObject(hdc, green_pen); //makes green_pen current pen
		//------------draw the line
		MoveToEx(hdc, 100,100, NULL); //just the starting curse. does not draw. It holds the starting point of the line
		LineTo(hdc, 150, 150); //draws line from MoveToEx() spot to LineTo() spot. 
		LineTo(hdc, 50, 150); //Unless you make another MoveToEx() call the curse stays at endpoint and draws from there
		LineTo(hdc, 100, 100);
		
		//------------draw a rectangle
		SelectObject(hdc, bitmap_brush);
		Rectangle(hdc, 100,100,60,60); //creates solid rect with current pen (outline). Inside is current brush
		
		//draw filled and outlined rect (alternate way) 
		static RECT rect= {160,160,200,200}; //creates a rect obj static so its created only once
		static RECT rect2= {200,200,260,260}; //creates a rect obj static so its created only once
		//draw rect
		FrameRect(hdc, &rect, blue_brush);
		FillRect(hdc, &rect2, blue_brush);
		//------------draw an ellipse
		Ellipse(hdc, 190,90,200,110); //draws an ellipse with the current pen and brush
		
		// ReleaseDC
		ReleaseDC(hwnd, hdc);
		//PostMessage(hwnd,WM_QUIT,0,0); //post a WM_QUIT message to the message queue
	
	}//end while
	
	//delete pens and brushes, frees up space.  And stops resource leeks
	DeleteObject(green_pen); //make sure to delete pens, brushes, and the like when program is done.
	DeleteObject(red_brush);
	DeleteObject(blue_brush);

	//return to Windows like this
	return(msg.wParam);
}//end WinMain