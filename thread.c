#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

/**
* This class simulates a multithreaded server 
* accessing files while different processes are
* happening in the background
*
* @author Allison Bolen
* @author Alec Allain
* @version 9/22/18
*/

/** Instanciate methods */
void sigHandler (int signal);
void* workerThreadOne (void* insert);

/** Global variables */
pthread_t thread1;
char input;
int status;
//int pid;
int recvCount;
int sentCount;
//int random;
void* retrieve;

int main (int argc, char** argv) {

    signal(SIGINT, sigHandler);

    while(1) {
        printf("\nPlease enter a file name: ");
        scanf("%s", &input);

        // This creates a thread
        if ((status = pthread_create (&thread1, NULL, workerThreadOne, &input)) != 0) {
            fprintf (stderr, "\nThread create error %d: %s\n", status, strerror(status));
            exit(1);
        }
    recvCount++;
    }

    pthread_exit(NULL);
    return 0;
}

/**
* This method handles signals from the user
*
* @param signal is the specific signal to trigger the method (^C)
*/
void sigHandler (int signal) {

    printf("\nNow exiting program....\nThe program recieved %d files\nThe program sent %d files\n", recvCount, sentCount);

    if ((status = pthread_join (thread1, &retrieve)) != 0) {
        fprintf (stderr, "\nThread create error %d: %s\n", status, strerror(status));
        exit(1);
    }

    exit(0);
}

/**
* This method creates a seperate child thread
*
* @param insert is the data
*/
void* workerThreadOne (void* insert) {
    //printf("\nThis prints something");
    char* userInput = (char *) insert;
    int random = rand() % 9;

    if (random <= 7) {
        sleep(1);
    } else if (random > 7) {
        sleep(7);
    }

    printf("\nFile %s has been accessed", userInput);
    sentCount++;

    return NULL;
}
