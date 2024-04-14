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

int main()
{

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	HANDLE a_mut = CreateMutex(NULL, FALSE, L"a_mut");
	ReleaseMutex(a_mut);
	HANDLE b_mut = CreateMutex(NULL, FALSE, L"b_mut");
	ReleaseMutex(b_mut);
	HANDLE c_mut = CreateMutex(NULL, FALSE, L"c_mut");
	ReleaseMutex(c_mut);
	HANDLE first_mut = CreateMutex(NULL, FALSE, L"first_mut");
	ReleaseMutex(first_mut);
	HANDLE second_mut = CreateMutex(NULL, FALSE, L"second_mut");
	ReleaseMutex(second_mut);

	HANDLE a_mailpost = CreateMailslot(L"\\\\.\\mailslot\\a_mail", 0, MAILSLOT_WAIT_FOREVER, NULL);
	HANDLE b_mailpost = CreateMailslot(L"\\\\.\\mailslot\\b_mail", 0, MAILSLOT_WAIT_FOREVER, NULL);
	HANDLE c_mailpost = CreateMailslot(L"\\\\.\\mailslot\\c_mail", 0, MAILSLOT_WAIT_FOREVER, NULL);
	HANDLE first_mailpost = CreateMailslot(L"\\\\.\\mailslot\\first_mail", 0, MAILSLOT_WAIT_FOREVER, NULL);
	HANDLE second_mailpost = CreateMailslot(L"\\\\.\\mailslot\\second_mail", 0, MAILSLOT_WAIT_FOREVER, NULL);
}
