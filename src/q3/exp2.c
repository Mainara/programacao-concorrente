#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>


long get_memory_usage(int proc) {
	struct rusage r_usage;
	getrusage(proc, &r_usage);

	//printf("Memory: %ld\n", r_usage.ru_maxrss);
    return r_usage.ru_maxrss;
}

int main (int argc, char *argv[]) {
    int status;
    int samples = atoi(argv[1]);
    long sum = 0;
    sum += get_memory_usage(RUSAGE_SELF);

    //time variables
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    for (int i = 0; i < samples; i++) {
        if(fork() == 0) {
            exit(0);
        } else
        {
            sum += get_memory_usage(RUSAGE_CHILDREN);
            wait(&status);
        }
    }
    end = clock();
    //compute time
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_used);

    get_memory_usage(RUSAGE_SELF);
    //printf("sum: %ld\n", sum);
}
