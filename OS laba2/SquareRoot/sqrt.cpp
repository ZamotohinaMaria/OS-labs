#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <iostream>

using namespace std;

int main()
{
	DWORD n;
	HANDLE sqrt_slot = CreateMailslot("\\\\.\\mailslot\\slot_sqrt", 128, MAILSLOT_WAIT_FOREVER, NULL);
	HANDLE res_slot = CreateFile("\\\\.\\mailslot\\slot2", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE m = CreateMutex(NULL, TRUE, "mut_sqrt");
	while (true)
	{
		char a[128] = {}, b[128] = {};
		ReleaseMutex(m);

		ReadFile(sqrt_slot, &a, 127, &n, NULL);;
		//cout << "a = " << a << endl;
		ReleaseMutex(m);

		sprintf_s(b, "%lf", sqrt(atof(a)));
		//cout << "sqrt(a) = " << b << endl;
		WriteFile(res_slot, b, strlen(b), &n, NULL);
		ReleaseMutex(m);
	}
}