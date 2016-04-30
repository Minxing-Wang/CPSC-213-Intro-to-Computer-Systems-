#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "uthread.h"
#include "spinlock.h"

#define MAX_ITEMS 10

int items = 0;

const int NUM_ITERATIONS = 200;
const int NUM_CONSUMERS  = 2;
const int NUM_PRODUCERS  = 2;

int producer_wait_count;     // # of times producer had to wait
int consumer_wait_count;     // # of times consumer had to wait
int histogram [MAX_ITEMS+1]; // histogram [i] == # of times list stored i items
spinlock_t consumer_lock; 
spinlock_t producer_lock; 

void produce() {
  // TODO ensure proper synchronization 
  while(1){
  while(items>=MAX_ITEMS||items<0){
    producer_wait_count++;
  }                       
  spinlock_lock(&producer_lock);
  if (items<MAX_ITEMS){
       break;
  }else{
    spinlock_unlock(&producer_lock);}
   }
  assert (items < MAX_ITEMS);
  items++;
  histogram [items] += 1;
  spinlock_unlock(&producer_lock); 
}

void consume() {
  // TODO ensure proper synchronization
 
  while(1){
  while(items==0){
  consumer_wait_count++;
  } 
  spinlock_lock(&consumer_lock);
  if (items>0){
      break;                         
  }else {
  spinlock_unlock(&consumer_lock);}
   }
  assert (items > 0);
  items--;
  histogram [items] += 1;
  spinlock_unlock(&consumer_lock);
}

void* producer() {
  // TODO - You might have to change this procedure slightly
 for (int i=0; i < NUM_ITERATIONS; i++){
    produce();
 }
return NULL;
}

void* consumer() {
   
 for (int i=0; i < NUM_ITERATIONS; i++){
    consume();
 }
return NULL; 
}
int main (int argc, char** argv) {
  // TODO create threads to run the producers and consumers
  uthread_init(4);
  
  spinlock_create (&consumer_lock);
 
  spinlock_create(&producer_lock);
  
  uthread_t t[4];

 for (int i = 0; i < 2; i++) {
    t[i] = uthread_create(producer, 0);
  }
  
   for (int i = 2; i < 4; i++) {
    t[i] = uthread_create(consumer, 0);
  }
   
  for (int i = 0; i < 4; i++) {
    uthread_join(t[i], 0);
  }
  
  for(int i = 0 ; i <4; i++){
  free(t[i]);
  }

  printf("Producer wait: %d\nConsumer wait: %d\n",
         producer_wait_count, consumer_wait_count);
  for(int i=0;i<MAX_ITEMS+1;i++)
    printf("items %d count %d\n", i, histogram[i]);
}