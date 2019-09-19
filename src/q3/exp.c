#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

//shared variable
long count = 0;

void *inc_count(void *t) {
 	pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
	int i;
	int samples = atoi(argv[1]);

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

	return 0;
}
