#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <iostream>

#define PORT 6978
int sock;
struct sockaddr_in addr;
using namespace std;

struct two_nums{
    float a, b;
};

int main() {
    sem_t* s8 = sem_open("/add", 0);
    sem_t* s9 = sem_open("/add1", 0);
    sem_wait(s9);
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    two_nums tmp{};
    float result;
    bool status = true;

    sendto(sock, &status, sizeof(bool), 0, (struct sockaddr*)&addr, sizeof(addr));
    sem_post(s8);

    sem_wait(s9);
    recvfrom(sock, &tmp, sizeof(tmp), 0, (struct sockaddr*)NULL, NULL);
    result = tmp.a + tmp.b;
    send(sock, &result, sizeof(result), 0);
    sem_post(s8);

    close(sock);
    exit(EXIT_SUCCESS);
}