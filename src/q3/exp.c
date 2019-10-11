#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>

struct exp
{
	clock_t start;
	int sample;
};


void *inc_count(void *t) {
	struct exp *tst = (struct exp *) t;
	clock_t end = clock();
	sleep(1);
	printf("Thread,%d,%f\n",tst->sample, ((double)end - (double)tst->start)/CLOCKS_PER_SEC);
 	pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
	int i;
	int samples = atoi(argv[1]);
	//declare threads
	pthread_t threads[samples];
	struct exp example;
	
	

	//time variables
	clock_t start;

	//create threads. we do not change attributes, so NULL
	//last arg will be passed as parameter to the inc_count funcion
	start = clock();
	example.start = start;
	example.sample = samples;
	for (int k = 0; k < samples; k++) {
		pthread_create(&threads[k], NULL, inc_count, (void*) &example);
	}

	//wait for thread termination
	for (i=0; i<samples; i++) {
		pthread_join(threads[i], NULL);

	}

	return 0;
}
