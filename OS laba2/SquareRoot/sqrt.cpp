#include <stdio.h>
#include <windows.h>
#include <math.h>

//argv[2] = sqrt(argv[1])
//argv[3], argv[4]- мьютексы

int main(int argc, char* argv)
{
	unsigned long n; // Сколько записано
	HANDLE first_mut, second_mut, third_mut, mail;
	 char a[128], b[128];

	//argv[1]
	while ((first_mut = OpenMutex(MUTEX_ALL_ACCESS, TRUE, (LPCWSTR)argv[3])) == NULL);
	WaitForSingleObject(first_mut, INFINITE);

	mail = CreateFile((LPCWSTR)argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(mail, a, strlen(a), &n, NULL);

	*b = char(round(sqrt(int(a)*100)/100)); //округение до 2х знаков после запятой

	//argv[2]
	while ((third_mut = OpenMutex(MUTEX_ALL_ACCESS, TRUE, (LPCWSTR)argv[4])) == NULL);
	WaitForSingleObject(third_mut, INFINITE);

	mail = CreateFile((LPCWSTR)argv[2], GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(mail, b, strlen(b), &n, NULL);
}