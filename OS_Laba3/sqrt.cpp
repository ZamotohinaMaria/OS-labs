#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <mqueue.h>
#include <math.h>

using namespace std;

int main()
{
    sem_unlink("/sqrt");
    unsigned int p;

    sem_t* s_main = sem_open("/s_main",0);
    sem_t* s_sqrt = sem_open("/s_sqrt", 0);
    mqd_t q_sqrt = mq_open("/q_sqrt", O_RDWR/*, 0666, NULL*/);

    sem_wait(s_sqrt);
    while(true)
    {
        char a[128] = {}, b[128] = {}, c[128] = {};
        //cout << "im wait" << endl;
        //sem_wait(s_main);
        //cout << "im read" << endl;
        //sem_wait(s_main);

        mq_receive(q_sqrt, a, 128, 0);
        //cout << "a = " << a << endl;


        sprintf(c, "%lf", sqrt(atof(a)));
        //cout << "sqrt = " << c << endl;
        mq_send(q_sqrt, c, 128, 0);
        sem_post(s_main);
        sem_wait(s_sqrt);
    }
}