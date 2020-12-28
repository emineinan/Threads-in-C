#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int count=0;
pthread_mutex_t mutex;

void* routine()
{
    for(int i=0;i<10000000;i++){
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }
}
int main()
{
   pthread_t th[8];
   int i;
   pthread_mutex_init(&mutex,NULL);
   
   for(i=0;i<8;i++){
	   if(pthread_create(&th[i],NULL,&routine,NULL)!=0){
	   perror("Failed to create thread");
       return 1;
	   }
	   printf("Thread %d has started\n", i);
   }
    for(i=0;i<8;i++){
	   if(pthread_join(th[i],NULL)!=0){
       return 2;
	   }
	   printf("Thread %d has finished execution\n", i);
   }
	
   pthread_mutex_destroy(&mutex);
   printf("count: %d\n",count);
   return 0;
}

