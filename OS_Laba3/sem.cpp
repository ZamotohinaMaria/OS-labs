#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include<unistd.h>   
sem_t empty, full;
int data;
void *Producer(void *arg){
while(1) {
printf("\nProducer");
sem_wait(&empty);
sleep(1);
data++;
sem_post(&full);
}
}
// Сначала empty=1 full=0
// empty:=empty-1
// full:=full+1
void *Consumer(void *arg){ // Сначала empty=1 full=0
while(1) {
sem_wait(&full);
sleep(1);// full:=full-1
printf("\nData=%d", data);
sem_post(&empty);
// empty:=empty+1
}
}
int main(){
pthread_t thread1, thread2;
sem_init(&empty,1,1); // Установлен в 1
sem_init(&full,1,0); // Установлен в 0
data = 0;
pthread_create(&thread1, NULL, &Producer, NULL);
pthread_create(&thread2, NULL, &Consumer, NULL);
sleep(20);
pthread_cancel(thread1);
pthread_cancel(thread2);
return 0;
}