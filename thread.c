#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

/**
* This class
*
* @author Allison Bolen
* @author Alec Allain
* @version 9/22/18
*/

/** Instanciate methods */
void sigHandler (int signal);
void* workerThreadOne (void* insert);
void* workerThreadTwo (void* insert);
void* workerThreadThree (void* insert);

/** Global variables */
pthread_t thread1, thread2, thread3;
char input;
int status;
//int pid;
int count;

int main (int argc, char** argv) {

    signal(SIGINT, sigHandler);

    printf("\nPlease enter a string: ");
    scanf("%s", &input);

    if ((status = pthread_create (&thread1, NULL, workerThreadOne, &input)) != 0) {
        fprintf (stderr, "\nThread create error %d: %s\n", status, stderror(status));
        exit(1);
    } else if ((status = pthread_create (&thread2, NULL, workerThreadTwo, &input)) != 0) {
        fprintf (stderr, "\nThread create error %d: %s\n", status, stderror(status));
        exit(1);
    } else if ((status = pthread_create (&thread3, NULL, workerThreadThree, &input)) != 0) {
        fprintf (stderr, "\nThread create error %d: %s\n", status, stderror(status));
        exit(1);
    }

    pthread_exit(NULL);
    return 0;
}

/**
* This method
*/
void sigHandler (int signal) {
    printf("\nNow exiting program....\n");

}

/**
* This method
*/
void* workerThreadOne (void* insert) {

    printf("\nThis prints something");

    return NULL;
}

/**
*
*/
void* workerThreadTwo (void* insert) {
    return NULL;
}

/**
*
*/
void* workerThreadThree (void* insert) {
    return NULL;
}
