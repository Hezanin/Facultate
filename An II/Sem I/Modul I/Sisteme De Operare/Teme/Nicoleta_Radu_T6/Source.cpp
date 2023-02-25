#undef UNICODE
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define NR_BILETE 20
#define NR_VANZATORI 4

int BileteDisponibile = NR_BILETE;

HANDLE hThread[NR_VANZATORI];
HANDLE semafor_bilet_rezervat;
DWORD idThread[NR_VANZATORI];

void VanzareBilete(LPVOID n)
{
	BOOL done = false;
	int id = (int)n;
	int BileteVanduteThread = 0;
	
	while (!done)
	{
		// decrementare valoare semafor
		WaitForSingleObject(semafor_bilet_rezervat, INFINITE);

		if (BileteDisponibile == 0)
		{
			done = true;
		}
		else
		{
			// calcule pentru a obtine biletele ramase si biletele vandute
			BileteVanduteThread++;
			BileteDisponibile--;
			printf("Thread %d a vandut 1 bilet (au ramas %d bilete)\n", id + 1, BileteDisponibile);
		}
		// incrementare val semafor
		ReleaseSemaphore(semafor_bilet_rezervat, 1, NULL);
	}
	printf("Thread %d a vandut %d bilete! \n", id + 1, BileteVanduteThread);
}

int main(void)
{
	int i;
	
	//creare semafor
	semafor_bilet_rezervat = CreateSemaphore(0, 0, NR_VANZATORI, NULL);

	for (size_t i = 0; i < NR_VANZATORI; i++)
	{
		// creare fire executie
		hThread[i] = CreateThread(NULL, 0, VanzareBilete, (LPVOID)i, 0, &idThread[i]);
	}

	// asteptare executie si terminare thread-uri
	WaitForMultipleObjects(NR_VANZATORI, hThread,TRUE, INFINITE);

	// inchiderea handle-lor firelor si semaforului
	CloseHandle(hThread);
	CloseHandle(semafor_bilet_rezervat);
	return 0;
}
