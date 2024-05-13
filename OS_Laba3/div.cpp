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

using namespace std;

int main()
{
    sem_unlink("/div");
    unsigned int p;

    sem_t* s_main = sem_open("/s_main",0);
    sem_t* s_div = sem_open("/s_div", 0);
    mqd_t q_div = mq_open("/q_div", O_RDWR/*, 0666, NULL*/);

    sem_wait(s_div);
    while(true)
    {
        char a[128] = {}, b[128] = {}, c[128] = {};
        //cout << "im wait" << endl;
        //sem_wait(s_main);
        //cout << "im read" << endl;
        mq_receive(q_div, a, 128, 0);
        //cout << "a = " << a << endl;

        mq_receive(q_div, b, 128, 0);
        //cout << "b = " << b << endl;


        sprintf(c, "%lf", atof(a) / atof(b));
        //cout << "a*b = " << c << endl;
        mq_send(q_div, c, 128, 0);
        sem_post(s_main);
        sem_wait(s_div);
    }
}