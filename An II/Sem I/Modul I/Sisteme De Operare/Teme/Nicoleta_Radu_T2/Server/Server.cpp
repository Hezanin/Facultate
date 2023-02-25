#undef UNICODE
#include <windows.h>
#include "resource.h"
#include <atlstr.h>

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
	static char szAppName[] = "Server";
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
		"Server",    // text pentru bara de titlu a ferestrei
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
int Factorial(int yourVariable)
{
	int result{ 1 };
	for (size_t i = 1; i <= yourVariable; i++)
	{
		result = result * i;
	}
	return result;
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	// Variabile tema - to send
	char text[100] = "abcdefghijklmnopqrstuvwyz";
	static char bufferInput[100];
	int num, factorial = 1, verif = 0;
	static UINT WM_GETFROMCLIP;
	HWND hwndReceive;

	// Variabile tema - to receive
	BOOL bAvailable;
	HANDLE hClipMemory;
	RECT rect; //obiect dreptunghi
	char* pMyCopy, * pClipMemory;
	char bufferResponse[100];
	static char BufferSend[100];

	switch (iMsg) {

	case WM_INITDIALOG:
		// setari initiale	   
		hDialog = hDlg;
		WM_GETFROMCLIP = RegisterWindowMessage(GetFromClip);
		return TRUE;

	case WM_CLOSE:
		//dlgActive = FALSE;
		EndDialog(hDialog, 0);
		return TRUE;
	}
	if (iMsg == WM_GETFROMCLIP)
	{
		// Verificam daca clipboardul este disponibil
		bAvailable = IsClipboardFormatAvailable(CF_TEXT);
		if (!bAvailable)
		{
			return 0;
		}

		// (GET) Copiere date din zona de memorie clipboard in "bufferInput[]"
		OpenClipboard(hDialog);
		hClipMemory = GetClipboardData(CF_TEXT);

		pMyCopy = (char*)(GlobalLock(hClipMemory));
		pClipMemory = (char*)GlobalLock(hClipMemory);
		strcpy(pMyCopy, pClipMemory);
		strcpy_s(bufferInput, pMyCopy);
		GlobalUnlock(hClipMemory);
		CloseClipboard();
		GetClientRect(hDialog, &rect);
		InvalidateRect(hDialog, &rect, TRUE);

		// Afisare numar in edit control
		SetDlgItemText(hDialog, IDC_EDIT_REZULTAT, bufferInput);

		// Transformare numarul primit in integer
		num = atoi(bufferInput);

		if (strcmp(bufferInput, text))
		{
			verif = 1; // daca nu s-a transmis un numar
		}
		else
		{
			if (num > 15 || num < 0)
			{
				verif = 2;
			}
			else
			{
				if (!strcmp(bufferInput, ""))
				{
					verif = 3;
				}
				else
				{
					factorial = Factorial(num);
					//char* numberstring[(((sizeof factorial) * CHAR_BIT) + 2) / 3 + 2];
					sprintf(bufferResponse, "%d", factorial);
				}				
			}
		}
		switch (verif)
		{
		case 1:
			strcpy(BufferSend, "Nu am primit un numar valid"); break;
		case 2:
			strcpy(BufferSend, "Am primit numar > 15. Domeniul este [0,16)"); break;
		case 3:
			strcpy(BufferSend, "Sir vid!"); break;
		case 4:
			strcpy(BufferSend, text); break;
		}

		// (SET) pune valoarea calculata in clipboard
		hwndReceive = FindWindow("Client", "Client");
		if (hwndReceive != NULL)
		{
			SendMessage(hwndReceive, WM_GETFROMCLIP, 0, 0); //notificare receive pt. preluare date
			hGlobalMemory = GlobalAlloc(GHND, strlen(bufferResponse) + 1); //alocare memorie in heap
			pGlobalMemory = (char*)GlobalLock(hGlobalMemory); //obtinerea unui pointer la memoria
			for (UINT i = 0; i < strlen(bufferResponse); i++) //copiere date in heap
				*(pGlobalMemory++) = bufferResponse[i];
			GlobalUnlock(hGlobalMemory);
			OpenClipboard(hDialog); //deschidere clipboard
			SetClipboardData(CF_TEXT, hGlobalMemory);//transmitere date
			CloseClipboard();//inchidere clipboard			
		}
		else
		{
			MessageBox(hDlg, "Nu am gasit Clientul!", "Eroare", MB_OK);
			SetDlgItemText(hDialog, IDC_EDIT_REZULTAT, "Nu am gasit client");
		}
	}
	return FALSE;
}
