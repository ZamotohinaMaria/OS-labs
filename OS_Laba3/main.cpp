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
    int sem_value;
    mq_unlink("/q_mul");
    mq_unlink("/q_sqrt");
    mq_unlink("/q_sub");
    mq_unlink("/q_sum");
    mq_unlink("/q_div");

    sem_unlink("/s_main");
    // sem_unlink("/s_main2");
    // sem_unlink("/s_main3");
    // sem_unlink("/s_main4");
    // sem_unlink("/s_main5");


    sem_unlink("/s_mul");
    sem_unlink("/s_sqrt");
    sem_unlink("/s_sub");
    sem_unlink("/s_sum");
    sem_unlink("/s_div");

    static struct mq_attr m;
    m.mq_maxmsg = 10;
    m.mq_msgsize = 128;
    m.mq_flags = 0;
    m.mq_curmsgs = 0;

    mqd_t q_mul = mq_open("/q_mul", O_CREAT|O_RDWR, 0666, &m);
    mqd_t q_sqrt = mq_open("/q_sqrt", O_CREAT|O_RDWR, 0666, &m);
    mqd_t q_sub = mq_open("/q_sub", O_CREAT|O_RDWR, 0666, &m);
    mqd_t q_sum = mq_open("/q_sum", O_CREAT|O_RDWR, 0666, &m);
    mqd_t q_div = mq_open("/q_div", O_CREAT|O_RDWR, 0666, &m);
  
    sem_t* s_main = sem_open("/s_main", O_CREAT, S_IRUSR | S_IWUSR,0);
    // sem_t* s_main2 = sem_open("/s_main2", O_CREAT, S_IRUSR | S_IWUSR,0);
    // sem_t* s_main3 = sem_open("/s_main3", O_CREAT, S_IRUSR | S_IWUSR,0);
    // sem_t* s_main4 = sem_open("/s_main4", O_CREAT, S_IRUSR | S_IWUSR,0);
    // sem_t* s_main5 = sem_open("/s_main5", O_CREAT, S_IRUSR | S_IWUSR,0);



    sem_t* s_mul = sem_open("/s_mul",O_CREAT, S_IRUSR | S_IWUSR,0);
    sem_t* s_sqrt = sem_open("/s_sqrt",O_CREAT, S_IRUSR | S_IWUSR,0);
    sem_t* s_sub = sem_open("/s_sub",O_CREAT, S_IRUSR | S_IWUSR,0);
    sem_t* s_sum = sem_open("/s_sum",O_CREAT, S_IRUSR | S_IWUSR,0);
    sem_t* s_div = sem_open("/s_div",O_CREAT, S_IRUSR | S_IWUSR,0);
    

    cout << "i want to create process" << endl;
    system("./mul &");
    system("./sqrt &");
    system("./sub &");
    system("./sum &");
    system("./div &");


    while(true)
    {
        char a[128] = {}, b[128] = {}, c[128] = {}, buff1[128] = {}, buff2[128] = {}, buff3[128] = {}, x1[128] = {}, x2[128] = {};
        cout << "Input a: ";
        cin >> a;
        cout << "\nInput b: ";
        cin >> b;
        cout << "\nInput c: ";
        cin >> c;

        //b*b
        mq_send(q_mul, b, 128, 31);
        mq_send(q_mul, b, 128, 30);
        sem_post(s_mul);
        sem_wait(s_main);
        mq_receive(q_mul, buff1, 128, 0);
        //cout << "buff1 = " << buff1 << endl;


        //4*a
        char tmp[128] = "4";
        mq_send(q_mul, tmp, 128, 31);
        mq_send(q_mul, a, 128, 30);
        sem_post(s_mul);
        sem_wait(s_main);
        mq_receive(q_mul, buff2, 128, 0);
        //cout << "buff2 = " << buff2 << endl;


        //4*a*c
        mq_send(q_mul, buff2, 128, 31);
        mq_send(q_mul, c, 128, 30);
        sem_post(s_mul);
        sem_wait(s_main);
        mq_receive(q_mul, buff2, 128, 0);
        //cout << "buff2 = " << buff2 << endl;

        //2*a
        char tmp3[128] = "2";
        mq_send(q_mul, tmp3, 128, 31);
        mq_send(q_mul, a, 128, 30);
        sem_post(s_mul);
        sem_wait(s_main);
        mq_receive(q_mul, buff3, 128, 0);
        //cout << "buff3 = " << buff3 << endl;

        //b*b-4*a*c
        mq_send(q_sub, buff1, 128, 31);
        mq_send(q_sub, buff2, 128, 30);
        sem_post(s_sub);
        sem_wait(s_main);
        mq_receive(q_sub, buff1, 128, 0);
        cout << "D = " << buff1 << endl;

        if (atof(buff1) >= 0)
        {
            //sqrt(D)
            mq_send(q_sqrt, buff1, 128, 31);
            sem_post(s_sqrt);
            sem_wait(s_main);
            mq_receive(q_sqrt, buff1, 128, 0);
            //cout << "buff1 = " << buff1 << endl;

            //-b
            char tmp2[128] = "0";
            mq_send(q_sub, tmp2, 128, 31);
            mq_send(q_sub, b, 128, 30);
            sem_post(s_sub);
            sem_wait(s_main);
            mq_receive(q_sub, buff2, 128, 0);
            //cout << "buff2 -b = " << buff2 << endl;

            //-b-sqrt(D)
            mq_send(q_sub, buff2, 128, 31);
            mq_send(q_sub, buff1, 128, 30);
            sem_post(s_sub);
            sem_wait(s_main);
            mq_receive(q_sub, x1, 128, 0);
            //cout << "buff -b-sqrt = " << x1 << endl;

            //-b+sqrt(D)
            mq_send(q_sum, buff2, 128, 31);
            mq_send(q_sum, buff1, 128, 30);
            sem_post(s_sum);
            sem_wait(s_main);
            mq_receive(q_sum, x2, 128, 0);
            //cout << "buff -b + sqrt= " << x2 << endl;


            //x1
            mq_send(q_div, x1, 128, 31);
            mq_send(q_div, buff3, 128, 30);
            sem_post(s_div);
            sem_wait(s_main);
            mq_receive(q_div, x1, 128, 0);
            cout << "x1 = " << x1 << endl;

            //x1
            mq_send(q_div, x2, 128, 31);
            mq_send(q_div, buff3, 128, 30);
            sem_post(s_div);
            sem_wait(s_main);
            mq_receive(q_div, x2, 128, 0);
            cout << "x2 = " << x2 << endl;
        }
        else
            cout << "D < 0 = > no answer" << endl;
        int flag;
        cout << "Do you want to continue? Press 0 if want exit." << endl;
        cin >> flag;
        if (flag == 0) break;
    }
    return 0;
}