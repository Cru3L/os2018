#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

typedef struct
 {
  char type;
  int amount;
  char unit;
 }item;

item buffer[BUFFER_SIZE];
int first =0;
int last =0;
 
sem_t s;

void produce(item *i)
 {
  while ((first +1) % BUFFER_SIZE ==0)
   { }
  sem_wait(&s);
  memcpy(&buffer[first],i,sizeof(item));
  first = (first +1) % BUFFER_SIZE;
  sem_post(&s);
 }

item* consume()
 {
  item *i =(item*)malloc(sizeof(item));
  while(first == last) 
   { }
  sem_wait(&s);
  memcpy(i,&buffer[last],sizeof(item));
  last = (last +1) % BUFFER_SIZE;
  sem_post(&s);
  return i;
 }

void *threadproceduce()
 {
  item t[3];
  t[0].type='1';
  t[0].amount=2;
  t[0].unit='0';

  t[1].type='2';
  t[1].amount=8;
  t[1].unit='0';
   
  t[2].type='1';
  t[2].amount=60 ;
  t[2].unit='1';

  printf("\nItem : \n");
  for (int i=0 ; i<3; i++)
  {  
   produce(&t[i]);
   printf("\n Item %d: %c, %d, %c \n First= %d, Last=%d \n",i+1,t[i].type ,t[i].amount, t[i].unit, first, last);
  }  
 }

void *threadconsumer()
 {
  item *consumerItem;
  printf("\nConsumed:\n");
  for (int i=0; i<3;i++)
   { 
    consumerItem = consume();    
    printf("\n Item %d: %c, %d, %c \n First= %d, Last=%d \n",i+1,consumerItem->type, consumerItem->amount, consumerItem->unit, first, last);
   }
 }

int main()
 {
  pthread_t tid1, tid2;
  sem_init(&s, 0,BUFFER_SIZE);
  pthread_create(&tid1,NULL,threadproceduce,NULL);
  pthread_create(&tid2,NULL,threadconsumer,NULL);
  pthread_join(tid2,NULL);
  sem_destroy(&s);
 }
