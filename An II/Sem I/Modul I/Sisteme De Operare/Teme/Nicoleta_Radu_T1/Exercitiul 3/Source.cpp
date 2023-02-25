//#undef UNICODE
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL dlgActive = FALSE;
HWND hwndMain;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static char szAppName[] = "Dialog2";
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);
	hwnd = CreateWindow(szAppName, // window class name
		"Test dialog", // window caption
		WS_OVERLAPPEDWINDOW, // window style
		CW_USEDEFAULT, // initial x position
		CW_USEDEFAULT, // initial y position
		CW_USEDEFAULT, // initial x size
		CW_USEDEFAULT, // initial y size
		NULL, // parent window handle
		NULL, // window menu handle
		hInstance, // program instance handle
		NULL); // creation parameters
	SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOACTIVATE);
	ShowWindow(hwnd, SW_HIDE);
	UpdateWindow(hwnd);
	hwndMain = hwnd;

		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	switch (iMsg)
	{
	case WM_CREATE: //operatii ce se executa la crearea ferestrei
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		if (!dlgActive) //dlgActive e false atunci
		{// se creaza caseta de dialog
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG),
				hwnd, (DLGPROC)DlgProc);
				PostMessage(hwnd, WM_CLOSE, 0, 0);
			//atasarea mesajului windows de închidere in coada de mesaje
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
/////////////////////////////////////////////////////////////
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HWND hwnd;
	char text[100] = "0";
	int min, max;
	min = 3;
	max = 3;

	int eur, dollar, ron, iCheck;
	float eurCurrency = 4.34;
	float dollarCurrency = 3.05;
	float ronCurrency = 4.9;

	//eurCurrency = roundf(eurCurrency * 100) / 100.0;
	//dollarCurrency = roundf(dollarCurrency * 100) / 100.0;
	//ronCurrency = roundf(ronCurrency * 100) / 100.0;

	static char userInput[100] = "\0";
	static char buffer_euro[100] = "\0";
	static char buffer_dollar[100] = "\0";
	static char buffer_ron[100] = "\0";

	switch (iMsg) {
	case WM_INITDIALOG:
		//Functia GetDlgItem obtine handler-ul unui control folosindu-se
		// identificatorul (IDC_CHECK3) acelui control
		//validare control
		hwnd = GetDlgItem(hDlg, IDC_RADIO_RON);
		SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);	
		hwnd = GetDlgItem(hDlg, IDC_RADIO_EUR);
		SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
		hwnd = GetDlgItem(hDlg, IDC_RADIO_DOLLAR);
		SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);

		// afisare curs valutar initial pentru euro
		snprintf(buffer_euro, sizeof buffer_euro, "%f", eurCurrency);
		SetDlgItemText(hDlg, IDC_EDIT_EUR_CURRENCY, buffer_euro);

		// afisare curs valutar initial pentru dolari
		snprintf(buffer_dollar, sizeof buffer_dollar, "%f", dollarCurrency);
		SetDlgItemText(hDlg, IDC_EDIT_DOLLAR_CURRENCY, buffer_dollar);

		// Setare pe 0 a casetelor de editare
		SetDlgItemText(hDlg, IDC_EDIT_RON_RES, text);
		SetDlgItemText(hDlg, IDC_EDIT_EUR_RES, text);
		SetDlgItemText(hDlg, IDC_EDIT_DOLLAR_RES, text);
		SetDlgItemText(hDlg, IDC_EDIT_USERINPUT, text);
		return TRUE;

	case WM_CLOSE:
		if (MessageBox(hDlg, "Close the window?", "Close",
			MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			DestroyWindow(hDlg);
		}
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_CHANGE_CURRENCY:
			// schimbarea cursului valutar cu generare aleatorie: EURO
			srand(time(NULL));
			do
			{
				eurCurrency = (float)(rand() % min + max);
				eurCurrency += ((float)rand() / RAND_MAX);
				// schimbarea cursului valutar si generarea unei valori DOLLAR mai mare decat cea EURO
				do
				{
					dollarCurrency = (float)(rand() % min + max);
					dollarCurrency += ((float)rand() / RAND_MAX);
				} while (dollarCurrency < eurCurrency);
			} while (eurCurrency > 5 && dollarCurrency > 5);		

			snprintf(buffer_euro, sizeof buffer_euro, "%f", eurCurrency);
			SetDlgItemText(hDlg, IDC_EDIT_EUR_CURRENCY, buffer_euro);
			snprintf(buffer_dollar, sizeof buffer_dollar, "%f", dollarCurrency);
			SetDlgItemText(hDlg, IDC_EDIT_DOLLAR_CURRENCY, buffer_dollar);
			break;
		case IDC_BUTTON_CONVERT:
			hwnd = GetDlgItem(hDlg, IDC_RADIO_RON);
			iCheck = (int)SendMessage(hwnd, BM_GETCHECK, 0, 0);

			// daca este selectat radio button pentru RON
			if (iCheck)
			{
				// RON 
				GetDlgItemText(hDlg, IDC_EDIT_USERINPUT, userInput, 100);
				SetDlgItemText(hDlg, IDC_EDIT_RON_RES, userInput);

				// EURO
				GetDlgItemText(hDlg, IDC_EDIT_EUR_CURRENCY, buffer_euro, 100);
				eurCurrency = atof(buffer_euro);
				eur = atof(userInput) / eurCurrency;
				sprintf_s(buffer_euro, "%ld", eur);
				SetDlgItemText(hDlg, IDC_EDIT_EUR_RES, buffer_euro);

				// DOLLAR
				GetDlgItemText(hDlg, IDC_EDIT_DOLLAR_CURRENCY, buffer_dollar, 100);
				dollarCurrency = atof(buffer_dollar);
				dollar = atof(userInput) / dollarCurrency;
				sprintf_s(buffer_dollar, "%ld", dollar);
				SetDlgItemText(hDlg, IDC_EDIT_DOLLAR_RES, buffer_dollar);
			}

			hwnd = GetDlgItem(hDlg, IDC_RADIO_EUR);
			iCheck = (int)SendMessage(hwnd, BM_GETCHECK, 0, 0);

			// daca este selectat radio button pentru EURO
			if (iCheck)
			{
				// EURO
				GetDlgItemText(hDlg, IDC_EDIT_USERINPUT, userInput, 100);
				SetDlgItemText(hDlg, IDC_EDIT_EUR_RES, userInput);

				// RON
				ron = atof(userInput) * eurCurrency;
				sprintf_s(buffer_ron, "%ld", ron);
				SetDlgItemText(hDlg, IDC_EDIT_RON_RES, buffer_ron);

				// DOLLAR
				GetDlgItemText(hDlg, IDC_EDIT_DOLLAR_CURRENCY, buffer_dollar, 100);
				dollarCurrency = atof(buffer_dollar);
				dollar = atof(userInput) * dollarCurrency;
				sprintf_s(buffer_dollar, "%ld", dollar);
				SetDlgItemText(hDlg, IDC_EDIT_DOLLAR_RES, buffer_dollar);
			}

			hwnd = GetDlgItem(hDlg, IDC_RADIO_DOLLAR);
			iCheck = (int)SendMessage(hwnd, BM_GETCHECK, 0, 0);

			// daca este selectat radio button pentru DOLLAR
			if (iCheck)
			{
				// DOLLAR
				GetDlgItemText(hDlg, IDC_EDIT_USERINPUT, userInput, 100);
				SetDlgItemText(hDlg, IDC_EDIT_DOLLAR_RES, userInput);

				// EURO
				GetDlgItemText(hDlg, IDC_EDIT_EUR_CURRENCY, buffer_euro, 100);
				eurCurrency = atof(buffer_euro);
				eur = atof(userInput) / eurCurrency;
				sprintf_s(buffer_euro, "%ld", eur);
				SetDlgItemText(hDlg, IDC_EDIT_EUR_RES, buffer_euro);

				// RON
				ron = atof(userInput) / ronCurrency;
				sprintf_s(buffer_ron, "%ld", ron);
				SetDlgItemText(hDlg, IDC_EDIT_RON_RES, buffer_ron);
			}
			break;

		case IDC_BUTTON_EXIT:
			MessageBox(hDlg, "Abandon!", "Ati selectat CANCEL", MB_OK);
			dlgActive = FALSE;
			EndDialog(hDlg, 0);
			return TRUE;
		}

			break;
	}
	return FALSE;
}