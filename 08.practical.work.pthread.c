#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BUFFER_SIZE 10

typedef struct 
 {
  char type; 
  int amount; 
  char unit; 
 } item;

item buffer[BUFFER_SIZE];
  int first = 0;
  int last = 0;

void produce(item *i)
 {
  while ((first + 1) % BUFFER_SIZE == last) 
  {}
  memcpy(&buffer[first], i, sizeof(item));
  first = (first + 1) % BUFFER_SIZE;
 }

item *consume() 
 {
  item *i = malloc(sizeof(item));
  while (first == last) 
  {}
  memcpy(i, &buffer[last], sizeof(item));
  last = (last + 1) % BUFFER_SIZE;
  return i;
 }

void *producer()
 {	
  item t[3];
  t[0].type = '1';
  t[0].amount = 3;
  t[0].unit = '1';

  t[1].type = '2';
  t[1].amount = 2;
  t[1].unit = '1';

  t[2].type = '3';
  t[2].amount = 3;
  t[2].unit = '1';
  for (int i = 0; i < 3; ++i)
   {
    produce(&t[i]);
    printf("\nItem %d: %c, %d, %c\nFirst = %d, Last = %d\n", i+1, t[i].type, t[i].amount, t [i].unit, first, last);
   }
 }

void *consumer()
 {
  item *cons;
  for (int i = 0; i < 3; ++i)
   {
    cons = consume();
    printf("\nConsumed item %d:\nFirst = %d, Last = %d\n", i+1, first, last);
   }
 }

int main() 
 {
  pthread_t tid1, tid2;
  pthread_create(&tid1,NULL,producer,NULL);
  pthread_create(&tid2,NULL,consumer,NULL);
  pthread_join(tid2,NULL);
  return 0;
 }
