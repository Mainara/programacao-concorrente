#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

//shared variable
long count = 0;

void *inc_count(void *t) {
 	pthread_exit(NULL);
}

void get_memory_usage() {
	struct rusage r_usage;
	getrusage(RUSAGE_SELF, &r_usage);

	printf("Memory: %ld\n", r_usage.ru_maxrss);
}

int main (int argc, char *argv[]) {
	int i;
	int samples = atoi(argv[1]);
	get_memory_usage();
	//declare threads
	pthread_t threads[samples];

	//create threads. we do not change attributes, so NULL
	//last arg will be passed as parameter to the inc_count funcion
	for (int k = 0; k < samples; k++) {
		pthread_create(&threads[k], NULL, inc_count, NULL);
	}

	//wait for thread termination
	for (i=0; i<samples; i++) {
		pthread_join(threads[i], NULL);

	}

	get_memory_usage();
	return 0;
}
