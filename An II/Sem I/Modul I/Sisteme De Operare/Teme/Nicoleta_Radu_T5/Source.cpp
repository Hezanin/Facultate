#undef UNICODE
#include <windows.h>
#include <math.h>
#include <process.h>
#include "resource.h"

#define REP              10000

#define Oprire			  0
#define STATUS_WORKING    1
#define STATUS_DONE       2
#define STATUS_NOTSTARTED 3

#define WM_CALC_DONE     (WM_USER + 0)
#define WM_CALC_ABORTED  (WM_USER + 1)

typedef struct
{
	HWND   hwnd;
	HANDLE hEvent;
	int contor;
	BOOL   bPornit;
	BOOL   bStop;
} PARAMS, * PPARAMS;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg,
	WPARAM wParam, LPARAM lParam);

BOOL dlgActive = FALSE; //variabila pentru caseta de dialog
HWND hwndMain; //variabila handle a ferestrei principale

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static char szAppName[] = "HelloWin";
	HWND        hwnd;
	MSG         msg;
	WNDCLASSEX  wndclass; // obiectul instantiat din structura WNDCLASSEX

	wndclass.cbSize = sizeof(wndclass);//Dimensiunea structurii
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //Stilul ferestrei
	wndclass.lpfnWndProc = WndProc; // Procedura de fereastra care trateaza mesajele
	// Doua c�mpuri care permit rezervarea de spatiu suplimentar in structura class, respectiv structura window.
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance; //Identificatorul instantei ferestrei
	//Stabileste o pictograma pentru toate ferestrele create pe baza clasei window
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//Stabileste o pictograma pentru cursor
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//Specifica culoarea de fundal a ferestrei
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL; // Specifica meniul feresterei
	wndclass.lpszClassName = szAppName; // Specifica numele clasei feresterei
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//Inregistrarea clasei de fereastra
	RegisterClassEx(&wndclass);

	// Crearea ferestrei pe baza clasei de fereastra
	hwnd = CreateWindow(szAppName,         // window class name
		"Un program simplu",     // window caption
		WS_OVERLAPPEDWINDOW,     // window style
		CW_USEDEFAULT,           // initial x position
		CW_USEDEFAULT,           // initial y position
		CW_USEDEFAULT,           // initial x size
		CW_USEDEFAULT,           // initial y size
		NULL,                    // parent window handle
		NULL,                    // window menu handle
		hInstance,               // program instance handle
		NULL);		             // creation parameters

	ShowWindow(hwnd, iCmdShow); // afiseaza fereastra pe ecran
	//transmite catre WndProc un mesaj de tip WM_PAINT, care are ca rezultat
	//redesenarea ferestrei, adica reactualizarea zonei client a ferestrei
	UpdateWindow(hwnd); // 

	// preia si distribuie mesaje pana se primeste WM_QUIT
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // traduce mesajul
		DispatchMessage(&msg); // transmite mesajul catre procedura de fereastra
	}
	return msg.wParam;
}

void Thread1(PVOID pvoid)
{
	int i;
	char text[100];
	static HANDLE hEvent;
	PPARAMS pparams = (PPARAMS)pvoid;

	while (true)
	{
		WaitForSingleObject(pparams->hEvent, INFINITE);
		
		// verificare daca bStop este TRUE, daca da se iese din while
		if (pparams->bStop == TRUE) break;

		// verificare daca avem butonul Pornire activ
		if (pparams->bPornit == TRUE)
		{
			// daca da, setare eveniment
			SetEvent(hEvent);
			for (i = 0; i <= 500 && pparams->bPornit; i++) {
				
				wsprintf(text, "%d", i);				
				pparams->contor = i;
			}
		}
		
		// se asteapta dupa un eveniment semnalat
		if (pparams->contor < 0)
		{
			pparams->contor = 0;
		}
		if (pparams->contor == 500)
		{
			SendMessage(pparams->hwnd, pparams->bStop, 0,500);
		}
		// suspendare 500ms
		Sleep(500);
		//incrementare contor si afisare in caseta de text
	}
	_endthread();
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
				hwnd, (DLGPROC)DlgProc);
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

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	// Variabile tema - to send
	HWND hEditControl;
	HFONT hFont;
	static HANDLE hEvent;
	static INT iStatus;

	static PARAMS params;
	char text[200] = "0";

	switch (iMsg) {

	case WM_INITDIALOG:
		// setari initiale	   

		hFont = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
			OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			VARIABLE_PITCH, TEXT("Times New Roman"));

		hEditControl = GetDlgItem(hDlg,IDC_EDIT);
		SendMessage(hEditControl, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		SetDlgItemText(hDlg,IDC_EDIT,text);

		params.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
		params.hwnd = hDlg;
		params.bPornit = FALSE;
		params.bStop = FALSE;

		iStatus = STATUS_NOTSTARTED;

		EnableWindow(GetDlgItem(hDlg, Oprire), FALSE);
		_beginthread(Thread1, 0, &params);

		return TRUE;

	case WM_CLOSE:
		//dlgActive = FALSE;
		EndDialog(hDlg, 0);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case IDC_BUTTON_PORNIRE:
			iStatus = STATUS_WORKING;
			params.bPornit = TRUE;
			params.bStop = FALSE;
			SetEvent(hEvent);
			InvalidateRect(hDlg, NULL, TRUE);

			return TRUE;
		case IDC_BUTTON_OPRIRE:
			params.bStop = TRUE;
			params.bPornit = FALSE;

			InvalidateRect(hDlg, NULL, TRUE);
			return TRUE;

		case IDC_CANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}


