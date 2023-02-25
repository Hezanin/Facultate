#undef UNICODE
#include <windows.h>
#include "resource.h"
#include <stdio.h>

#define _WIN32_WINNT _WIN32_WINNT_WINXP

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg,
    WPARAM wParam, LPARAM lParam);
BOOL dlgActive = FALSE; //variabila pentru caseta de dialog
HWND hwndMain; //variabila handle a ferestrei principale

DWORD WINAPI ThreadProc(LPVOID lpParam);

#define MAX_THREADS 3 

typedef struct
{
    int Start, Final;
    int idTh;
}info;
info infoTh[3];

HANDLE hThreads[3];
DWORD idT[3];
DWORD dwExitCode[3];
DWORD  waiter;
LPDWORD ExitCodeTest[3];

DWORD WINAPI ThreadFunc(LPVOID n)
{
    int suma=0;
    int id = int(n); // conversie id thread

    for (size_t i = infoTh[id].Start; i <= infoTh[id].Final; i++)
    {
		suma = suma + i;
    }
    return (DWORD)suma;
}

LRESULT APIENTRY WndProc(HWND, UINT, WPARAM, LPARAM);

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

template <typename T>
void Swap(T& a, T &b )
{
	T aux = a;
	a = b;
	b = aux;
}

static BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	char text[100], buffer[100], suma_thread_1[100], suma_thread_2[100], suma_thread_3[100];
	bool isReadyForExecution = true;

	LPSECURITY_ATTRIBUTES THREAD_ALL_ACCESS;

	switch (iMsg) {

	case WM_INITDIALOG:
		// setari initiale		
		return TRUE;

	case WM_CLOSE:
		dlgActive = FALSE;
		EndDialog(hDlg, 0);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_CALCULATE: 
			// salvarea datelor in array
			infoTh[0].idTh = 0;
			GetDlgItemText(hDlg, IDC_EDIT_THREAD_1_1, text, 100);
			infoTh[0].Start = atoi(text);
			GetDlgItemText(hDlg, IDC_EDIT_THREAD_1_2, text, 100);
			infoTh[0].Final = atoi(text);

			infoTh[1].idTh = 1;
			GetDlgItemText(hDlg, IDC_EDIT_THREAD_2_1, text, 100);
			infoTh[1].Start = atoi(text);
			GetDlgItemText(hDlg, IDC_EDIT_THREAD_2_2, text, 100);
			infoTh[1].Final = atoi(text);

			infoTh[2].idTh = 2;
			GetDlgItemText(hDlg, IDC_EDIT_THREAD_3_1, text, 100);
			infoTh[2].Start = atoi(text);
			GetDlgItemText(hDlg, IDC_EDIT_THREAD_3_2, text, 100);
			infoTh[2].Final = atoi(text);

			// verificare interval corect [0,10.000]
			if (infoTh[0].Start < 0 || infoTh[0].Final > 10000)
			{
				MessageBox(hDlg, "Eroare!", "Interval Gresit (Thread 1)!", MB_OK);
				isReadyForExecution = false;
			}
			if (infoTh[1].Start < 0 || infoTh[1].Final > 10000)
			{
				MessageBox(hDlg, "Eroare!", "Interval Gresit (Thread 1)!", MB_OK);
				isReadyForExecution = false;
			}
			if (infoTh[2].Start < 0 || infoTh[2].Final > 10000)
			{
				MessageBox(hDlg, "Eroare!", "Interval Gresit (Thread 1)!", MB_OK);
				isReadyForExecution = false;
			}

			// caz in care variabila "final" este mai mica decat cea "start"
			// vom inversa cele doua valori pentru a minimiza erorile in program
			if (infoTh[0].Start > infoTh[0].Final)
			{
				Swap(infoTh[0].Start, infoTh[0].Final);				
			}
			if (infoTh[1].Start > infoTh[1].Final)
			{
				Swap(infoTh[1].Start, infoTh[1].Final);
			}
			if (infoTh[2].Start > infoTh[2].Final)
			{
				Swap(infoTh[2].Start, infoTh[2].Final);
			}
			
			if (isReadyForExecution)
			{
				//creare thread
				hThreads[0] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)0, NULL, &idT[0]);
				hThreads[1] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)1, NULL, &idT[1]);
				hThreads[2] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)2, NULL, &idT[2]);

				// asteptare
				waiter = WaitForMultipleObjects(MAX_THREADS, hThreads,
					TRUE, INFINITE);

				// get exit code
				/*for (size_t i = 0; i < MAX_THREADS; i++)
				{
					GetExitCodeThread(hThreads[i], (LPDWORD)dwExitCode[i]);
				}*/
				
				dwExitCode[0] = ThreadFunc((LPVOID)0);
				dwExitCode[1] = ThreadFunc((LPVOID)1);
				dwExitCode[2] = ThreadFunc((LPVOID)2);

				//inchidere
				for (int i = 0; i < MAX_THREADS; i++) {
					CloseHandle(hThreads[i]);
				}

				// afisare rezultat final
				sprintf_s(buffer, "%lu", (unsigned int)dwExitCode[0] + (unsigned int)dwExitCode[1] + (unsigned int)dwExitCode[2]);
				sprintf_s(suma_thread_1, "%lu", (unsigned int)dwExitCode[0]);
				sprintf_s(suma_thread_2, "%lu", (unsigned int)dwExitCode[1]);
				sprintf_s(suma_thread_3, "%lu", (unsigned int)dwExitCode[2]);

				SetDlgItemText(hDlg, IDC_EDIT_THREAD_1_SUMA, suma_thread_1);
				SetDlgItemText(hDlg, IDC_EDIT_THREAD_2_SUMA, suma_thread_2);
				SetDlgItemText(hDlg, IDC_EDIT_THREAD_3_SUMA, suma_thread_3);
				SetDlgItemText(hDlg, IDC_EDIT_SUMA_TOTALA, buffer);
				
			}
			else
			{
				// programul nu poate fi executat
				MessageBox(hDlg, "Eroare!", "Programul nu poate executa!", MB_OK);
				return TRUE;
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