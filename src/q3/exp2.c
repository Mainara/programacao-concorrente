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
    clock_t end;
    for (int i = 0; i < samples; i++) {
        if(fork() == 0) {
            end = clock();
            sleep(1);
            printf("Process,%d,%f\n", samples, (double)end/CLOCKS_PER_SEC);
            exit(0);
        }
    }

    wait(NULL);
}
