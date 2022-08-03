// test mutex on ubuntu linux
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int tickets = 100;
pthread_mutex_t mutex;

void * selltickets(void* arg){

	while(1){

		pthread_mutex_lock(&mutex);
		if(tickets>0){
			usleep(6000);
			printf("%ld : %d\n", pthread_self(), tickets);
			tickets--;
		}else{
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_mutex_unlock(&mutex);
		usleep(1);

	}
	return NULL;
}

int main(){
	pthread_mutex_init(&mutex,NULL);
	pthread_t pt1,pt2,pt3;

	pthread_create(&pt1,NULL,selltickets,NULL);
	pthread_create(&pt2,NULL,selltickets,NULL);
	pthread_create(&pt3,NULL,selltickets,NULL);

	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	pthread_join(pt3,NULL);

	pthread_exit(NULL);

	pthread_mutex_destroy(&mutex);
	return 0;
}
