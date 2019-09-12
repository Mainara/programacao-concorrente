#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main (int argc, char *argv[]) {
 	int status;

    for (int i = 0; i < 100; i++) {
        if(fork() == 0) {
            exit(0);
        } else
        {
            wait(&status);
        }
    }
}
