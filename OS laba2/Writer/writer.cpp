#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <iostream>

//argv[1] -mail, argv[2] - mutex
int main(int argc, char* argv)
{
	unsigned long n; // Сколько записано
	HANDLE mut, mail;

	char* a;
	scanf("%s", a);

	//a
	while ((mut = OpenMutex(MUTEX_ALL_ACCESS, TRUE, (LPCWSTR)argv[2])) == NULL);
	WaitForSingleObject(mut, INFINITE);

	mail = CreateFile((LPCWSTR)argv[1], GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(mail, a, strlen(a), &n, NULL);
}