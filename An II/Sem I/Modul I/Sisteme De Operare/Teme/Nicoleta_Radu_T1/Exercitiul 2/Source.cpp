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
		"Operatii Aritmetice", // text pentru bara de titlu a ferestrei
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
	char text[100] = "\0";

	int firstNum = 0;
	int secondNum = 0;
	int result = 0;
	char num_1[100] = "\0";
	char num_2[100] = "\0";
	char arithmetic[100] = "\0";;

	switch (iMsg) {
	case WM_INITDIALOG:
		return TRUE;

	case WM_CLOSE:
		dlgActive = FALSE;
		EndDialog(hDlg, 0);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case IDC_BUTTON_1:
			// Calcularea primului numar aleatoriu
			firstNum = 1 + (rand() % 100);
			sprintf_s(num_1, "%ld", firstNum);
			SetDlgItemText(hDlg, IDC_EDIT_1, num_1);
			return TRUE;

		case IDC_BUTTON_2:
			// Calcularea celui de al doilea numar aleatoriu
			secondNum = 1 + (rand() % 100);
			sprintf_s(num_2, "%ld", secondNum);
			SetDlgItemText(hDlg, IDC_EDIT_2, num_2);
			return TRUE;

		case IDC_BUTTON_ADUNARE:
			// Calcularea operatiei de adunare
			GetDlgItemText(hDlg, IDC_EDIT_1, num_1, 100);
			GetDlgItemText(hDlg, IDC_EDIT_2, num_2, 100);

			// Verificarea daca cumva nu a fost generat un numar
			if (strlen(num_1) == 0 || strlen(num_2) == 0)
			{
				MessageBox(hDlg, "Nu s-a generat niciun numar", "Eroare", MB_OK);
			}

			// Calcularea adunarii cu numerele obtinute
			result = (atoi(num_1)) + (atoi(num_2));
			sprintf_s(arithmetic, "%ld", result);
			sprintf_s(text, "%d + %d = %d", atoi(num_1), atoi(num_2), atoi(arithmetic));
			MessageBox(hDlg, text, "Adunare", MB_OK);
			return TRUE;

		case IDC_BUTTON_SCADERE:
			// Calcularea operatiei de scadere
			GetDlgItemText(hDlg, IDC_EDIT_1, num_1, 100);
			GetDlgItemText(hDlg, IDC_EDIT_2, num_2, 100);

			// Verificarea daca cumva nu a fost generat un numar
			if (strlen(num_1) == 0 || strlen(num_2) == 0)
			{
				MessageBox(hDlg, "Nu s-a generat niciun numar", "Eroare", MB_OK);
			}

			// Calcularea propriu-zisa cu numerele obtinute
			result = (atoi(num_1)) - (atoi(num_2));
			sprintf_s(arithmetic, "%ld", result);
			sprintf_s(text, "%d - %d = %d", atoi(num_1), atoi(num_2), atoi(arithmetic));
			MessageBox(hDlg, text, "Scadere", MB_OK);
			return TRUE;

		case IDC_BUTTON_INMULTIRE:
			// Calcularea operatiei de inmultire
			GetDlgItemText(hDlg, IDC_EDIT_1, num_1, 100);
			GetDlgItemText(hDlg, IDC_EDIT_2, num_2, 100);

			// Verificarea daca cumva nu a fost generat un numar
			if (strlen(num_1) == 0 || strlen(num_2) == 0)
			{
				MessageBox(hDlg, "Nu s-a generat niciun numar", "Eroare", MB_OK);
			}

			// Calcularea propriu-zisa cu numerele obtinute
			result = (atoi(num_1)) * (atoi(num_2));
			sprintf_s(arithmetic, "%ld", result);
			sprintf_s(text, "%d * %d = %d", atoi(num_1), atoi(num_2), atoi(arithmetic));
			MessageBox(hDlg, text, "Inmultire", MB_OK);
			return TRUE;

		case IDC_BUTTON_IMPARTIRE:
			// Calcularea operatiei de impartire
			GetDlgItemText(hDlg, IDC_EDIT_1, num_1, 100);
			GetDlgItemText(hDlg, IDC_EDIT_2, num_2, 100);

			// Verificarea daca cumva nu a fost generat un numar
			if (strlen(num_1) == 0 || strlen(num_2) == 0)
			{
				MessageBox(hDlg, "Nu s-a generat niciun numar", "Eroare", MB_OK);
			}
			// verificare daca se efectueaza impartirea la 0
			if ((atof(num_2) == 0))
			{
				MessageBox(hDlg, "Impartire la 0", "Impartire", MB_OK);
				break;
			}

			// Calcularea propriu-zisa cu numerele obtinute
			result = (atof(num_1)) / (atof(num_2));
			sprintf_s(arithmetic, "%ld", result);
			sprintf_s(text, "%d / %d = %f", atoi(num_1), atoi(num_2), atof(arithmetic));
			MessageBox(hDlg, text, "Impartire", MB_OK);
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