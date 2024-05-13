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
    sem_unlink("/mul");
    unsigned int p;

    sem_t* s_main = sem_open("/s_main",0);
    sem_t* s_mul = sem_open("/s_mul", 0);
    mqd_t q_mul = mq_open("/q_mul", O_RDWR/*, 0666, NULL*/);

    //cout << "mul wait" << endl;
    sem_wait(s_mul);
    while(true)
    {
        char a[128] = {}, b[128] = {}, c[128] = {};
        //cout << "im wait" << endl;
        //sem_wait(s_main);
        //cout << "im read" << endl;
        //sem_wait(s_main);
        //cout << "2mul wait" << endl;

        mq_receive(q_mul, a, 128, 0);
        //cout << "a = " << a << endl;

        mq_receive(q_mul, b, 128, 0);
        //cout << "b = " << b << endl;


        sprintf(c, "%lf", atof(a) * atof(b));
        //cout << "a*b = " << c << endl;
        mq_send(q_mul, c, 128, 0);
        sem_post(s_main);
        //cout << "fkfkdfk" << endl;
        sem_wait(s_mul);
    }
}