#include <stdio.h>
#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	DWORD n;
	HANDLE sum_slot = CreateMailslot("\\\\.\\mailslot\\slot_sum", 128, MAILSLOT_WAIT_FOREVER, NULL);
	HANDLE res_slot = CreateFile("\\\\.\\mailslot\\slot4", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE m = CreateMutex(NULL, TRUE, "mut_sum");
	while (true)
	{
		char a[128] = {}, b[128] = {}, c[128] = {};
		ReleaseMutex(m);

		ReadFile(sum_slot, &a, 127, &n, NULL);;
		//cout << "a = " << a << endl;
		ReleaseMutex(m);


		ReadFile(sum_slot, &b, 127, &n, NULL);
		//cout << "b = " << b << endl;

		sprintf_s(c, "%lf", atof(a) + atof(b));
		//cout << "a+b = " << c << endl;
		WriteFile(res_slot, c, strlen(c), &n, NULL);
		ReleaseMutex(m);
	}
}