#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

//shared variable
long count = 0;

void *inc_count(void *t) {
 	pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
 	int i;

	//declare threads
 	pthread_t threads[100];

	//create threads. we do not change attributes, so NULL
	//last arg will be passed as parameter to the inc_count funcion
	for (int k = 0; k < 100; k++) {
		pthread_create(&threads[k], NULL, inc_count, NULL);
	}

	//wait for thread termination
 	for (i=0; i<100; i++) {
 		pthread_join(threads[i], NULL);

 	}

	//with proper syncronization, we would have 3*1e7 printed
	printf("count %ld\n", count);
 	pthread_exit(NULL);
}
