#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>

int main (int argc, char *argv[]) {
    int status;
    int samples = atoi(argv[1]);;

    //time variables
    struct timeval *time;

    gettimeofday(time, NULL);
    
    long int start,end; 
    start = time->tv_sec*1000 + time->tv_usec;

    for (int i = 0; i < samples; i++) {
        if(fork() == 0) {
            gettimeofday(time, NULL);
            sleep(1);
            printf("Process,%ld,%d\n", (time->tv_sec*1000 + time->tv_usec) - start, samples);
            exit(0);
        }
    }

    wait(NULL);
}
