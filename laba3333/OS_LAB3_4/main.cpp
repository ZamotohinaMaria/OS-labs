#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <iostream>
#include <cmath>

#define PORT 6978
int sock;
struct sockaddr_in addr;
using namespace std;

int main() {
    sem_t* s6 = sem_open("/sqrt", 0);
    sem_t* s7 = sem_open("/sqrt1", 0);
    sem_wait(s7);
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    float tmp;
    float result;
    bool status = true;

    sendto(sock, &status, sizeof(bool), 0, (struct sockaddr*)&addr, sizeof(addr));
    sem_post(s6);

    sem_wait(s7);
    recvfrom(sock, &tmp, sizeof(tmp), 0, (struct sockaddr*)NULL, NULL);
    result = pow(tmp, 0.5);
    send(sock, &result, sizeof(result), 0);
    sem_post(s6);

    close(sock);
    exit(EXIT_SUCCESS);
}