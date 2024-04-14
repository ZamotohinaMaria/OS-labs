#include <stdio.h>
#include <windows.h>

//argv[1] - argv[2] = argv[3]
//argv[4], argv[5], argv[6] - мьютексы

int main(int argc, char* argv)
{
	unsigned long n; // Сколько записано
	HANDLE first_mut, second_mut, third_mut, mail;
	char a[128], b[128], c[128];

	//argv[1]
	while ((first_mut = OpenMutex(MUTEX_ALL_ACCESS, TRUE, (LPCWSTR)argv[4])) == NULL);
	WaitForSingleObject(first_mut, INFINITE);

	mail = CreateFile((LPCWSTR)argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(mail, a, strlen(a), &n, NULL);

	//argv[2]
	while ((second_mut = OpenMutex(MUTEX_ALL_ACCESS, TRUE, (LPCWSTR)argv[5])) == NULL);
	WaitForSingleObject(second_mut, INFINITE);

	mail = CreateFile((LPCWSTR)argv[2], GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(mail, b, strlen(b), &n, NULL);

	*c = char(int(a) - int(b));

	//argv[3]
	while ((third_mut = OpenMutex(MUTEX_ALL_ACCESS, TRUE, (LPCWSTR)argv[6])) == NULL);
	WaitForSingleObject(third_mut, INFINITE);

	mail = CreateFile((LPCWSTR)argv[3], GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(mail, c, strlen(c), &n, NULL);
}