// AFIK
// A - независимые процессы
// F - синхронизаци€ - мьютекс
// I - передача данных ммежду процессами - почтовые €чейки
// K - решение квадратного уравнени€ (x1, x2) = (-b +- sqrt(b*b - 4*a*c))

// MainProc Ц родительский процесс
// Writer - процесс, считывающий значение с клавиатуры дл€ главного процесса - читател€
// Sum - процесс-сумматор
// Sub - процесс-вычитатор
// Mul - процесс-умножатор
// Sqrt - процесс-квадратный корень

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int main()
{
	DWORD n;
	HANDLE mut_mul, mut_sub, mut_sqrt, mut_sum, mut_div;
	HANDLE slot_mul, slot_sqrt, slot_sub, slot_sum, slot_div;
	HANDLE slot1 = CreateMailslot("\\\\.\\mailslot\\slot1", 128, MAILSLOT_WAIT_FOREVER, NULL);
	HANDLE slot2 = CreateMailslot("\\\\.\\mailslot\\slot2", 128, MAILSLOT_WAIT_FOREVER, NULL);
	HANDLE slot3 = CreateMailslot("\\\\.\\mailslot\\slot3", 128, MAILSLOT_WAIT_FOREVER, NULL);
	HANDLE slot4 = CreateMailslot("\\\\.\\mailslot\\slot4", 128, MAILSLOT_WAIT_FOREVER, NULL);
	HANDLE slot5 = CreateMailslot("\\\\.\\mailslot\\slot5", 128, MAILSLOT_WAIT_FOREVER, NULL);
	
	WinExec("Multiplier.exe", SW_SHOW);
	WinExec("SquareRoot.exe", SW_SHOW);
	WinExec("Subtractor.exe", SW_SHOW);
	WinExec("Summator.exe", SW_SHOW);
	WinExec("Divider.exe", SW_SHOW);

	char a[128] = {}, b[128] = {}, c[128] = {}, buff1[128] = {}, buff2[128] = {}, buff3[128] = {}, x1[128] = {}, x2[128] = {};
	cout << "Input a: ";
	cin >> a;
	cout << "\nInput b: ";
	cin >> b;
	cout << "\nInput c: ";
	cin >> c;

	while ((mut_mul = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "mut_mul")) == NULL);
	while ((mut_sqrt = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "mut_sqrt")) == NULL);
	while ((mut_sub = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "mut_sub")) == NULL);
	while ((mut_sum = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "mut_sum")) == NULL);
	while ((mut_div = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "mut_div")) == NULL);
	
	slot_mul = CreateFile("\\\\.\\mailslot\\slot_mul", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	slot_sqrt = CreateFile("\\\\.\\mailslot\\slot_sqrt", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	slot_sub = CreateFile("\\\\.\\mailslot\\slot_sub", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	slot_sum = CreateFile("\\\\.\\mailslot\\slot_sum", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	slot_div = CreateFile("\\\\.\\mailslot\\slot_div", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//buff1 = B^2
	WaitForSingleObject(mut_mul, INFINITE);
	WriteFile(slot_mul, b, strlen(b), &n, NULL);
	ReleaseMutex(mut_mul);
	WriteFile(slot_mul, b, strlen(b), &n, NULL);
	ReleaseMutex(mut_mul);
	ReadFile(slot1, &buff1, 128, &n, NULL);

	//buff2 = 4*a
	ReleaseMutex(mut_mul);
	char tmp[128] = "4";
	WriteFile(slot_mul, tmp, strlen(tmp), &n, NULL);
	ReleaseMutex(mut_mul);
	WriteFile(slot_mul, a, strlen(a), &n, NULL);
	ReleaseMutex(mut_mul);
	ReadFile(slot1, &buff2, 128, &n, NULL);

	//buff2 = 4*a*c
	ReleaseMutex(mut_mul);
	WriteFile(slot_mul, buff2, strlen(buff2), &n, NULL);
	ReleaseMutex(mut_mul);
	WriteFile(slot_mul, c, strlen(c), &n, NULL);
	ReleaseMutex(mut_mul);
	ReadFile(slot1, &buff2, 128, &n, NULL);


	//buff1 = b^2 - 4*a*c
	WaitForSingleObject(mut_sub, INFINITE);
	WriteFile(slot_sub, buff1, strlen(buff1), &n, NULL);
	ReleaseMutex(mut_sub);
	WriteFile(slot_sub, buff2, strlen(buff2), &n, NULL);
	ReleaseMutex(mut_sub);
	ReadFile(slot3, &buff1, 128, &n, NULL);

	cout << "D = " << buff1 << endl;

	if (atof(buff1) >= 0)
	{

		//buff1 = sqrt(b^2 - 4*a*c)
		WaitForSingleObject(mut_sqrt, INFINITE);
		WriteFile(slot_sqrt, buff1, strlen(buff1), &n, NULL);
		ReleaseMutex(mut_sqrt);
		ReadFile(slot2, &buff1, 128, &n, NULL);


		//buff2 = -b
		ReleaseMutex(mut_sub);
		char tmp2[128] = "0";
		WriteFile(slot_sub, tmp2, strlen(tmp2), &n, NULL);
		ReleaseMutex(mut_sub);
		WriteFile(slot_sub, b, strlen(b), &n, NULL);
		ReleaseMutex(mut_sub);
		ReadFile(slot3, &buff2, 128, &n, NULL);

		//x1 = -b - sqrt(b^2 - 4*a*c)
		ReleaseMutex(mut_sub);
		WriteFile(slot_sub, buff2, strlen(buff2), &n, NULL);
		ReleaseMutex(mut_sub);
		WriteFile(slot_sub, buff1, strlen(buff1), &n, NULL);
		ReleaseMutex(mut_sub);
		ReadFile(slot3, &x1, 128, &n, NULL);

		//buff3 = 2*a
		ReleaseMutex(mut_mul);
		char tmp3[128] = "2";
		WriteFile(slot_mul, tmp3, strlen(tmp3), &n, NULL);
		ReleaseMutex(mut_mul);
		WriteFile(slot_mul, a, strlen(a), &n, NULL);
		ReleaseMutex(mut_mul);
		ReadFile(slot1, &buff3, 128, &n, NULL);

		//x1 = (-b - sqrt(b^2 - 4*a*c))/2*a
		WaitForSingleObject(mut_div, INFINITE);
		WriteFile(slot_div, x1, strlen(x1), &n, NULL);
		ReleaseMutex(mut_div);
		WriteFile(slot_div, buff3, strlen(buff3), &n, NULL);
		ReleaseMutex(mut_div);
		ReadFile(slot5, &x1, 128, &n, NULL);

		//x2 = -b + sqrt(b^2 - 4*a*c)
		WaitForSingleObject(mut_sum, INFINITE);
		WriteFile(slot_sum, buff2, strlen(buff2), &n, NULL);
		ReleaseMutex(mut_sum);
		WriteFile(slot_sum, buff1, strlen(buff1), &n, NULL);
		ReleaseMutex(mut_sum);
		ReadFile(slot4, &x2, 128, &n, NULL);

		//x1 = (-b + sqrt(b^2 - 4*a*c))/2*a
		ReleaseMutex(mut_div);
		WriteFile(slot_div, x2, strlen(x2), &n, NULL);
		ReleaseMutex(mut_div);
		WriteFile(slot_div, buff3, strlen(buff3), &n, NULL);
		ReleaseMutex(mut_div);
		ReadFile(slot5, &x2, 128, &n, NULL);

		cout << "x1 = " << x1 << endl;
		cout << "x2 = " << x2 << endl;
	}
	else
		cout << "D < 0 => no answer" << endl;

	ReleaseMutex(mut_mul);
	CloseHandle(mut_mul);
	ReleaseMutex(mut_sqrt);
	CloseHandle(mut_sqrt);
	ReleaseMutex(mut_sub);
	CloseHandle(mut_sub);
	ReleaseMutex(mut_sum);
	CloseHandle(mut_sum);
	ReleaseMutex(mut_div);
	CloseHandle(mut_div);

	CloseHandle(slot1);
	CloseHandle(slot2);
	CloseHandle(slot3);
	CloseHandle(slot4);
	CloseHandle(slot5);

	CloseHandle(slot_mul);
	CloseHandle(slot_sqrt);
	CloseHandle(slot_sub);
	CloseHandle(slot_sum);
	CloseHandle(slot_div);
	ExitProcess(0);
	return 0;
}
