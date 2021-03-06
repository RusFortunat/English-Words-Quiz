// English Words Quiz.cpp : Defines the entry point for the application.
//

#include <Windows.h>
#include "stdafx.h"
#include "English Words Quiz.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProc2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void CenterWindow(HWND hwnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ENGLISHWORDSQUIZ, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}



	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ENGLISHWORDSQUIZ));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ENGLISHWORDSQUIZ));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ENGLISHWORDSQUIZ);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS: In this function, we save the instance handle in a global variable and
//             create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	// Main Window Location
	SetWindowPos(hWnd, 0, 200, 200, 800, 600, SWP_SHOWWINDOW);
	// Center Window
	CenterWindow(hWnd);


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Background Image
	/*HWND hWndBackground;
	HANDLE hBitmap;
	hBitmap = LoadImage(NULL, TEXT("\beach.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap != NULL)
	{
		hWndBackground = CreateWindow(TEXT("STATIC"), TEXT("image box"),
			WS_CHILD | WS_VISIBLE | SS_BITMAP,
			0, 0, 470, 130,
			hWnd, (HMENU)2000, NULL, NULL);
		SendMessage(hWndBackground, STM_SETIMAGE, IMAGE_BITMAP, LPARAM(hBitmap));
	}*/

	// Font Settings
	LOGFONT HLogicalFont;//Global Variable
	HLogicalFont.lfHeight = 30;// Height
	HLogicalFont.lfWidth = 10;// Width
	HLogicalFont.lfEscapement = 0;// Escapement
	HLogicalFont.lfOrientation = 0;// Orientation
	HLogicalFont.lfWeight = FW_NORMAL;// Weight
	HLogicalFont.lfItalic = FALSE;// Italic
	HLogicalFont.lfUnderline = FALSE;// Underline
	HLogicalFont.lfStrikeOut = 0;// StrikeOut
	HLogicalFont.lfCharSet = DEFAULT_CHARSET; //RUSSIAN_CHARSET as noted by Mihai Nita, should not be used, since DEFAULT will always find a font that supports desired charset!
	HLogicalFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;// ClipPrecision
	HLogicalFont.lfQuality = DEFAULT_QUALITY;// Quality
	HLogicalFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;// PitchAndFamily
	wsprintfW(HLogicalFont.lfFaceName, L"%s", L"Courier New");// Facename; 

	// Stuff declaration
	TCHAR text0[] = L"Выберите Действие:";
	TCHAR text1[] = L"Выберите Категорию:";
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_PAINT:
	{
		// TODO: Add any drawing code that uses hdc here...
		HDC hdc = BeginPaint(hWnd, &ps);
		HFONT hfont; // new logical font handle 
		HFONT hfontOld; // original logical font handle 
		hfont = CreateFontIndirect(&HLogicalFont);
		if (hfont == NULL)
			return FALSE;
		hfontOld = (HFONT)SelectObject(hdc, hfont);
		TextOut(hdc, 50, 25, text0, _tcslen(text0));
		TextOut(hdc, 500, 25, text1, _tcslen(text1));
		SelectObject(hdc, hfontOld);
		DeleteObject(hfont);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CREATE:
	{
		// Check Boxes //
		HWND Action1 = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("Переводить английские слова на русский"),      // Button text 
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,   // Styles 
			50,         // x position 
			75,         // y position 
			400,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_Action_Box1,       // No menu.
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);      // Pointer not needed.
		CheckDlgButton(hWnd, 10, BST_UNCHECKED);

		HWND Action2 = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("Переводить русские слова на английский"),      // Button text 
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,   // Styles 
			50,         // x position 
			105,         // y position 
			400,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_Action_Box2,       // No menu.
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);      // Pointer not needed.
		CheckDlgButton(hWnd, 11, BST_UNCHECKED);

		HWND TopicButtonALL = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("Все"),      // Button text 
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,   // Styles 
			500,         // x position 
			75,         // y position 
			200,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_BUTTON_ALL,       // No menu.
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);      // Pointer not needed.
		CheckDlgButton(hWnd, 20, BST_UNCHECKED);

		HWND TopicButton1 = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"Семья",      // Button text 
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,  // Styles 
			500,         // x position 
			105,         // y position 
			200,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_BUTTON_1,       // No menu.
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);      // Pointer not needed.
		CheckDlgButton(hWnd, 21, BST_UNCHECKED);

		HWND TopicButton2 = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"Тело",      // Button text 
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,  // Styles 
			500,         // x position 
			135,         // y position 
			200,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_BUTTON_2,       // No menu.
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);      // Pointer not needed.
		CheckDlgButton(hWnd, 22, BST_UNCHECKED);

		HWND TopicButton3 = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"Rosetta Stone",      // Button text 
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,  // Styles 
			500,         // x position 
			165,         // y position 
			200,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_BUTTON_3,       // No menu.
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);      // Pointer not needed.
		CheckDlgButton(hWnd, 23, BST_UNCHECKED);

		// Button
		HWND Next_Button = CreateWindow(
			TEXT("BUTTON"),  // Predefined class; Unicode assumed 
			TEXT("Next >"),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			350,         // x position 
			400,         // y position 
			100,        // Button width
			50,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_BUTTON_NEXT,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		break;
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			// Check Boxes Selection
			case ID_Action_Box1:
			{
				BOOL checked_action1 = IsDlgButtonChecked(hWnd, 10);
				if (checked_action1) {
					CheckDlgButton(hWnd, 10, BST_UNCHECKED);
				}
				else {
					CheckDlgButton(hWnd, 10, BST_CHECKED);
					CheckDlgButton(hWnd, 11, BST_UNCHECKED);
				}
				break;
			}
			break;

			case ID_Action_Box2:
			{
				BOOL checked_action2 = IsDlgButtonChecked(hWnd, 11);
				if (checked_action2) {
					CheckDlgButton(hWnd, 11, BST_UNCHECKED);
				}
				else {
					CheckDlgButton(hWnd, 11, BST_CHECKED);
					CheckDlgButton(hWnd, 10, BST_UNCHECKED);
				}
				break;
			}
			break;

			case ID_BUTTON_ALL:
			{
				BOOL checked_category1 = IsDlgButtonChecked(hWnd, 20);
				if (checked_category1) {
					CheckDlgButton(hWnd, 20, BST_UNCHECKED);
					CheckDlgButton(hWnd, 21, BST_UNCHECKED);
					CheckDlgButton(hWnd, 22, BST_UNCHECKED);
					CheckDlgButton(hWnd, 23, BST_UNCHECKED);
				}
				else {
					CheckDlgButton(hWnd, 20, BST_CHECKED);
					CheckDlgButton(hWnd, 21, BST_CHECKED);
					CheckDlgButton(hWnd, 22, BST_CHECKED);
					CheckDlgButton(hWnd, 23, BST_CHECKED);
				}
				break;
			}
			break;

			case ID_BUTTON_1:
			{
				BOOL checked_category2 = IsDlgButtonChecked(hWnd, 21);
				if (checked_category2) {
					CheckDlgButton(hWnd, 21, BST_UNCHECKED);
				}
				else {
					CheckDlgButton(hWnd, 21, BST_CHECKED);
				}
				break;
			}
			break;

			case ID_BUTTON_2:
			{
				BOOL checked_category2 = IsDlgButtonChecked(hWnd, 22);
				if (checked_category2) {
					CheckDlgButton(hWnd, 22, BST_UNCHECKED);
				}
				else {
					CheckDlgButton(hWnd, 22, BST_CHECKED);
				}
				break;
			}
			break;

			case ID_BUTTON_3:
			{
				BOOL checked_category2 = IsDlgButtonChecked(hWnd, 23);
				if (checked_category2) {
					CheckDlgButton(hWnd, 23, BST_UNCHECKED);
				}
				else {
					CheckDlgButton(hWnd, 23, BST_CHECKED);
				}
				break;
			}
			break;

			// Next button
			case ID_BUTTON_NEXT:
			{


			}

		}
	}

	
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK PanelProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	switch (msg) {

	case WM_LBUTTONUP:

		MessageBeep(MB_OK);
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void CenterWindow(HWND hWnd) {

	RECT rc = { 0 };

	GetWindowRect(hWnd, &rc);
	int win_w = rc.right - rc.left;
	int win_h = rc.bottom - rc.top;

	int screen_w = GetSystemMetrics(SM_CXSCREEN);
	int screen_h = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(hWnd, HWND_TOP, (screen_w - win_w) / 2,
		(screen_h - win_h) / 2, 0, 0, SWP_NOSIZE);
}