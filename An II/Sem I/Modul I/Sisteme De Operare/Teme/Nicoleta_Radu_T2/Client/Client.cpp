#undef UNICODE
#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg,
WPARAM wParam, LPARAM lParam);

BOOL dlgActive = FALSE; //variabila pentru caseta de dialog
HWND hwndMain; //variabila handle a ferestrei principale

// Variabile pentru tema
LPCTSTR GetFromClip = "GetFromClipboard";
HWND hDialog;
HGLOBAL hGlobalMemory;
char* pGlobalMemory;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static char szAppName[] = "Client";
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
		"Client",    // text pentru bara de titlu a ferestrei
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
	// Variabile tema
	static HINSTANCE hInstance;
	static UINT WM_GETFROMCLIP;

	switch (iMsg)
	{
	case WM_CREATE: // operatiile ce se executa la crearea ferestrei
	   // se creaza caseta de dialog
		WM_GETFROMCLIP = RegisterWindowMessage(GetFromClip);
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

	if (iMsg == WM_GETFROMCLIP)
	{
		SendMessage(hDialog, WM_GETFROMCLIP, 0, 0);
		return 0;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

/////////////////////////////////////////////////////////////


BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	// Variabile tema - to send
	char text[100];
	static char bufferInput[100];
	static UINT WM_GETFROMCLIP;
	HWND hwndReceive;

	// Variabile tema - to receive
	BOOL bAvailable;
	HANDLE hClipMemory;
	RECT rect; //obiect dreptunghi
	char* pMyCopy, * pClipMemory;
	static char bufferResponse[100] = "Astept msg...";

	switch (iMsg) {

	case WM_INITDIALOG:
		// setari initiale	   
		hDialog = hDlg;
		WM_GETFROMCLIP = RegisterWindowMessage(GetFromClip);
		return TRUE;

	case WM_CLOSE:
		//dlgActive = FALSE;
		EndDialog(hDlg, 0);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_FACTORIAL: 

		   // citeste un text dintr-o caseta de editare
			GetDlgItemText(hDialog, IDC_EDIT, bufferInput, 100);

			// cauta fereastra cu numele server
			 hwndReceive = FindWindow("Server", "Server");
;
			// (SET)Daca o gaseste, scrie in zona de memorie
			if (hwndReceive != NULL)
			{
				SendMessage(hwndReceive, WM_GETFROMCLIP, 0, 0); //notificare receive pt. preluare date
				hGlobalMemory = GlobalAlloc(GHND, strlen(bufferInput) + 1); //alocare memorie in heap
				pGlobalMemory = (char*)GlobalLock(hGlobalMemory); //obtinerea unui pointer la memoria
					for (UINT i = 0; i < strlen(bufferInput); i++) //copiere date in heap
						*(pGlobalMemory++) = bufferInput[i];
				GlobalUnlock(hGlobalMemory);
				OpenClipboard(hDialog); //deschidere clipboard
				SetClipboardData(CF_TEXT, hGlobalMemory);//transmitere date
				CloseClipboard();//inchidere clipboard				
			}
			else
			{
				MessageBox(hDialog, "Nu am gasit Serverul!", "Eroare", MB_OK);
			}

			// Receptionez rezultatul si il salvez in clipboard
			// (GET) data
			bAvailable = IsClipboardFormatAvailable(CF_TEXT);
			if (bAvailable == FALSE) {
				//SetDlgItemText(hDialog, IDC_EDIT_REZULTAT, "Not available");
				return 0;
			}
			if (iMsg == WM_GETFROMCLIP) {
				OpenClipboard(hDialog);
				//obtinere handle la memoria clipboard
				hClipMemory = GetClipboardData(CF_TEXT);
				//alocare dinamica de memorie (buffer)
				pMyCopy = (char*)malloc(GlobalSize(hClipMemory));
				//obtinere pointer la memoria clipboard
				pClipMemory = (char*)GlobalLock(hClipMemory);
				strcpy(pMyCopy, pClipMemory); //copiere date
				strcpy_s(bufferResponse, pMyCopy);
				SetDlgItemText(hDialog, IDC_EDIT_REZULTAT, bufferResponse);
				GlobalUnlock(hClipMemory);
				CloseClipboard();
				return 0;
			}

			return TRUE;
		case IDC_CANCEL: // operatii ce se executa la actiunea apasarii but. CANCEL
			MessageBox(hDialog, "Abandon!", "Ati selectat CANCEL", MB_OK);
			//dlgActive = FALSE;
			EndDialog(hDialog, 0);
			return TRUE;
		}
		//break;
	}
	return FALSE;
}
