//*//#undef UNICODE
//*//go to Project Properties > Advanced > Character Set and put Not Set
#include <windows.h>
#include <string>
#include <atlstr.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//*//DLGPROC CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL dlgActive = FALSE; //variabila pentru casetadedialog
HWND hwndMain; //variabila handle a ferestrei principale

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static char szAppName[] = "Dialog";
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //optiuni pentru stilul clasei
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
		"Un program simplu", // text pentru bara de titlu a ferestrei
		WS_OVERLAPPEDWINDOW, // stilul ferestrei
		CW_USEDEFAULT, // pozitia orizontala implicitã
		CW_USEDEFAULT, // pozitia verticala implicita
		CW_USEDEFAULT, // latimea implicita
		CW_USEDEFAULT, // inaltimea implicita
		NULL, // handle-ul ferestrei parinte
		NULL, // handle-ul meniului ferestrei
		hInstance, // proprietara ferestrei
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
			//*//hwnd, (DLGPROC)DlgProc);
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			// insereaza un nou mesaj nou in coada de asteptare
			// sa te inserezi tu in pizda matii si facultate de cacat
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0); // insereaza un mesaj de incheiere
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

unsigned int factorial(unsigned int n)
{
	if (n == 0 || n == 1)
		return 1;
	return n * factorial(n - 1);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	char text[100];
	int randomNumber{};
	unsigned int factorialOfRandomNumber{};

	char stringNumberBuffer[100] = "\0";
	char stringFactorialBuffer[100] = "\0";;

	switch (iMsg) {
	case WM_INITDIALOG:
		return TRUE;

	case WM_CLOSE:
		dlgActive = FALSE;
		EndDialog(hDlg, 0);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case IDC_RANDOM:
			// Calcularea numarului aleatoriu
			randomNumber = rand() % 16;
			// Includerea acestuia sub forma unui C-style string "stringNumberBuffer"
			sprintf_s(stringNumberBuffer, "%ld", randomNumber);
			SetDlgItemText(hDlg, IDC_EDIT_NR, stringNumberBuffer);
			return TRUE;

		case IDC_CALC:
			// Luarea numarului aleatoriu din caseta de editare IDC_EDIT_NR
			GetDlgItemText(hDlg, IDC_EDIT_NR, stringFactorialBuffer, 100);

			// Verificarea daca cumva nu a fost generat un numar
			if (strlen(stringFactorialBuffer) == 0)
			{
				MessageBox(hDlg, "Nu s-a generat niciun numar", "Eroare", MB_OK);
			}
			// Calcularea factorialului folosing functia "factorial" scrisa mai sus
			factorialOfRandomNumber = factorial(atoi(stringFactorialBuffer));
			sprintf_s(stringFactorialBuffer, "%ld", factorialOfRandomNumber);
			SetDlgItemText(hDlg, IDC_EDIT_REZ, stringFactorialBuffer);
			return TRUE;

		case ID_CANCEL: 
			dlgActive = FALSE;
			MessageBox(hDlg, "Iesire!", "Ati selectat CANCEL", MB_OK);
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}