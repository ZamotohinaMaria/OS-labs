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
    sem_unlink("/sub");
    unsigned int p;

    sem_t* s_main = sem_open("/s_main", 0);
    sem_t* s_sub = sem_open("/s_sub", 0);
    mqd_t q_sub = mq_open("/q_sub", O_RDWR/*, 0666, NULL*/);

    cout << "im wait" << endl;
    sem_wait(s_sub);
    while(true)
    {
        char a[128] = {}, b[128] = {}, c[128] = {};
        //sem_wait(s_main);
        //cout << "im read" << endl;
        //sem_wait(s_main);

        mq_receive(q_sub, a, 128, 0);
        //cout << "a = " << a << endl;

        mq_receive(q_sub, b, 128, 0);
        //cout << "b = " << b << endl;


        sprintf(c, "%lf", atof(a) - atof(b));
        //cout << "a-b = " << c << endl;
        mq_send(q_sub, c, 128, 0);
        int k;
        sem_getvalue(s_main, &k);
        //cout << "main = " << k << endl;
        sem_post(s_main);
        sem_wait(s_sub);
    }
}