#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  while((first + 1) % BUFFER_SIZE == last) 
  {}
  memcpy(&buffer[first], i,sizeof(item));
  first = (first + 1) % BUFFER_SIZE;
 }

item *consume() 
 {
  item *i = malloc(sizeof(item));
  while (first == last) 
  { }
  memcpy(i, &buffer[last],sizeof(item));
  last = (last + 1) % BUFFER_SIZE;
  return i;
 }

int main()
 { 
  item t1, t2;
  t1.type = '1';
  t1.amount = 4;
  t1.unit = '3';
  printf("Item 1: %c, %d, %c\n", t1.type, t1.amount, t1.unit);
  t2.type = '2';
  t2.amount = 1;
  t2.unit = '1';
  printf("Item 2: %c, %d, %c\n", t2.type, t2.amount, t2.unit);
  printf("First = %d, Last = %d\n\n", first, last);
  produce(&t1);
  printf("Produce Item 1:\tFirst = %d, Last=%d\n\n",first, last);
  produce(&t2);
  printf("Produce Item 2:\tFirst = %d, Last=%d\n\n",first, last);
  item *consumed_item = consume();
  printf("Consumed item: %c, %d, %c\tFirst = %d, Last=%d\n\n", consumed_item->type,   consumed_item->amount, consumed_item->unit, first, last);
  return 0;
 }
