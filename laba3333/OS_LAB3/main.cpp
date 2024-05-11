#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <fcntl.h>


#define PORT 6978

using namespace std;

int sock;
struct sockaddr_in addr, addr1;
int  bytes_read, total = 0;
float a = 3.0, b = 4.0;

struct two_nums{
    float a, b;
};

int main() {
    float result, b2, ac4t, D;
    sem_unlink("/mul");
    sem_unlink("/mul1");
    sem_unlink("/sqrt");
    sem_unlink("/sqrt1");
    sem_unlink("/add");
    sem_unlink("/add1");

    sem_t* s = sem_open("/mul", O_CREAT, S_IRUSR | S_IWUSR,0);
    sem_t* s1 = sem_open("/mul1", O_CREAT, S_IRUSR | S_IWUSR, 0);
    sem_t* s6 = sem_open("/sqrt", O_CREAT, S_IRUSR | S_IWUSR,0);
    sem_t* s7 = sem_open("/sqrt1", O_CREAT, S_IRUSR | S_IWUSR, 0);
    sem_t* s8 = sem_open("/add", O_CREAT, S_IRUSR | S_IWUSR,0);
    sem_t* s9 = sem_open("/add1", O_CREAT, S_IRUSR | S_IWUSR, 0);

    system("../../OS_LAB3_1/cmake-build-release/OS_LAB3_1 &");

    cout << "a, b = " << a << ", " << b << endl;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int tmp = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    if (tmp < 0){
        exit(-1);
    }
    bool status;
    socklen_t len = sizeof(addr);

    sem_wait(s);
    recvfrom(sock, &status, sizeof(bool), 0, (struct sockaddr*)&addr, &len);

    two_nums bb = {b, b};
    sendto(sock, &bb, sizeof(bb), 0, (struct  sockaddr*)&addr, sizeof(addr));
    sem_post(s1);

    sem_wait(s);
    bytes_read = recv(sock, &b2, sizeof(b2), 0);
    cout << "b^2 = " << b2 << endl;

    two_nums aa = {a, a};
    sendto(sock, &aa, sizeof(aa), 0, (struct  sockaddr*)&addr, sizeof(addr));
    sem_post(s1);

    sem_wait(s);
    bytes_read = recv(sock, &result, sizeof(result), 0);
    cout << "a^2 = " << result << endl;

    system("../../OS_LAB3_5/cmake-build-release/OS_LAB3_5 &");
    float sum;
    two_nums plus {result, b2};

    sem_post(s9);
    sem_wait(s8);
    recvfrom(sock, &status, sizeof(bool), 0, (struct sockaddr*)&addr, &len);

    sendto(sock, &plus, sizeof(plus), 0, (struct  sockaddr*)&addr, sizeof(addr));
    sem_post(s9);

    sem_wait(s8);
    bytes_read = recv(sock, &sum, sizeof(sum), 0);
    cout << "a^2 + b^2 = " << sum << endl;

    system("../../OS_LAB3_4/cmake-build-release/OS_LAB3_4 &");
    float sqrt;
    sem_post(s7);
    sem_wait(s6);
    recvfrom(sock, &status, sizeof(bool), 0, (struct sockaddr*)&addr, &len);

    sendto(sock, &sum, sizeof(sum), 0, (struct  sockaddr*)&addr, sizeof(addr));
    sem_post(s7);

    sem_wait(s6);
    bytes_read = recv(sock, &sqrt, sizeof(sqrt), 0);
    cout << "(a^2 + b^2) ^ 1/2 = " << sqrt << endl;

    close(sock);
}