#include <stdio.h>
#include <windows.h>
#define PROGNAME L".\\CRACK108m.exe"
STARTUPINFO si;
PROCESS_INFORMATION pi;
WORD nopnop = 0x9090; /* ���� ���� ������ NOP */
DWORD old_flags; /* ������ ����� ������� */
DWORD p = 0x004010BA; /* �����, ���� ��������� ����� */
int main() {
    CreateProcess(PROGNAME, (LPWSTR)L"", NULL, NULL, TRUE, 0, NULL, NULL,
        (STARTUPINFO*)&si, (PROCESS_INFORMATION*)&pi);
    HANDLE h = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE,
        TRUE, pi.dwProcessId);
    VirtualProtectEx(h, (void*)p, 2, PAGE_EXECUTE_READWRITE, &old_flags);
    WriteProcessMemory(h, (void*)p, (void*)&nopnop, 2, NULL);
    CloseHandle(h);
    system("pause >nul");
}
