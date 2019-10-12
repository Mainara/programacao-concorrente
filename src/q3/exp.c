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
	long int start;
	int sample;
};

typedef struct {
  long tv_sec;
  long tv_usec;
} timeval;


void *inc_count(void *t) {
	struct exp *tst = (struct exp *) t;
	timeval end;
	gettimeofday(&end, NULL);
	sleep(1);
	printf("Thread,%ld,%d\n", (end.tv_sec*1000+end.tv_usec) - tst->start, tst->sample);
 	pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
	int i;
	int samples = atoi(argv[1]);
	//declare threads
	pthread_t threads[samples];
	struct exp example;

	//time variables
	timeval start;

	//create threads. we do not change attributes, so NULL
	//last arg will be passed as parameter to the inc_count funcion
    gettimeofday(&start, NULL);

	example.start = start.tv_sec*1000 + start.tv_usec;
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
