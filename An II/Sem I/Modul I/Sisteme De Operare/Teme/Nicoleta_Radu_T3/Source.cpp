//#undef UNICODE
#include <windows.h>
#include <stdio.h>
#include "resource.h"

#define MAX_ENV 2000

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg,
	WPARAM wParam, LPARAM lParam);

BOOL dlgActive = FALSE; //variabila pentru caseta de dialog
HWND hwndMain; //variabila handle a ferestrei principale

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static char szAppName[] = "Dialog";
	HWND        hwnd;
	MSG         msg;
	WNDCLASSEX  wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;  //optiuni pentru stilul clasei 
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// incarca pictograma fisierelor de tip aplicatie
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // incarca cursorul sageata  
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	// fondul ferstrei de culoare alba     
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, //numele clasei inregistrat cu RegisterClass
		"Un program simplu",    // text pentru bara de titlu a ferestrei
		WS_OVERLAPPEDWINDOW,   // stilul ferestrei
		CW_USEDEFAULT,      // pozitia orizontala implicit�
		CW_USEDEFAULT,      // pozitia verticala implicita
		CW_USEDEFAULT,       // latimea implicita
		CW_USEDEFAULT,       // inaltimea implicita
		NULL,               // handle-ul ferestrei parinte
		NULL,               // handle-ul meniului ferestrei
		hInstance,          // proprietara ferestrei 
		NULL);


	SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOACTIVATE);
	// schimba dimensiunea, pozitia si ordinea z a ferestrei copil, a ferestrei pop-up
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
	case WM_CREATE: // operatiile ce se executa la crearea ferestrei
	   // se creaza caseta de dialog
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		if (!dlgActive) {
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG),
				hwnd, DlgProc);
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			// insereaza un nou mesaj nou in coada de asteptare
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0); // insereaza un mesaj de incheiere 
		return 0;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

/////////////////////////////////////////////////////////////


BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	char delimitator[2] = "=";
	char buffer[MAX_ENV], *NumeVarMediu;
	char VarMed[100], lpBuffer[2000] = "", bufferList[2000] = "";

	HWND hwnd;
	LPTSTR lpszVariable;	

	//GetEnvironmentVariable(NumeVarMediu,lpBuffer,MAX_PATH-1);
	//printf("%s\n",lpBuffer);

	switch (iMsg) {

	case WM_INITDIALOG:
		// setari initiale	
		// aloca memorie pt copia blocului de variab de mediu
		NumeVarMediu = GetEnvironmentStrings();
		lpszVariable = (LPTSTR)NumeVarMediu;

		//hwnd = GetDlgItem(hDlg, IDC_EDIT_LIST);

		while (strlen(lpszVariable) > 0)
		{
			strcpy_s(buffer, lpszVariable);
			NumeVarMediu = strtok(buffer, delimitator);

			strcat_s(lpBuffer, NumeVarMediu);
			strcat_s(lpBuffer, "\r\n");
	
			SetDlgItemText(hDlg, IDC_EDIT_LIST, lpBuffer);
			lpszVariable = lpszVariable + strlen(lpszVariable) + 1;
		}
		// elibereaza memorie pentru copia blocului variab de mediu
		//FreeEnvironmentStrings(NumeVarMediu);
		
		return TRUE;

	case WM_CLOSE:
		dlgActive = FALSE;
		EndDialog(hDlg, 0);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case IDC_BUTTON_VALOARE: 
			GetDlgItemText(hDlg, IDC_EDIT_VARIABILA, VarMed, 100);
			if (GetEnvironmentVariable(VarMed, buffer, MAX_ENV))
			{
				MessageBox(hDlg, buffer,"Valoarea variabilei de mediu", MB_OK);
			}
			else
			{
				MessageBox(hDlg, "Nu s-a gasit variabila de mediu", "EROARE", MB_OK|MB_ICONSTOP);
			}
			return TRUE;

		case IDC_CANCEL: // operatii ce se executa la actiunea apasarii but. CANCEL
			MessageBox(hDlg, "Abandon!", "Ati selectat CANCEL", MB_OK);
			dlgActive = FALSE;
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}