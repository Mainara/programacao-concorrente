#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>

//shared variable
long count = 0;

void *inc_count(void *t) {
	clock_t start = (clock_t) t;
	clock_t end = clock();
	printf("%ld\n", end - start);
 	pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
	int i;
	int samples = atoi(argv[1]);
	//declare threads
	pthread_t threads[samples];

	//time variables
	clock_t start, end;
     	double cpu_time_used;

	//create threads. we do not change attributes, so NULL
	//last arg will be passed as parameter to the inc_count funcion
	start = clock();
	for (int k = 0; k < samples; k++) {
		pthread_create(&threads[k], NULL, inc_count, (void*) start);
	}
	end = clock();
	//compute time
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	//printf("%f\n", cpu_time_used);

	//wait for thread termination
	for (i=0; i<samples; i++) {
		pthread_join(threads[i], NULL);

	}

	return 0;
}
