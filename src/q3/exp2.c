#include <stdio.h>



int main (int argc, char *argv[]) {
 	int status;

    for (int i = 0; i < 10; i++) {
        if(fork() == 0) {
            printf("Filho: %d", i);
        } else
        {
            wait(&status);
        }
        
    }
}
