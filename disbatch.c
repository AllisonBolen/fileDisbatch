#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

// Global variables
int countRec = 0;
int countSrv = 0;
void* result;
pthread_t thread[50];
int threadCount = 0;
int status;
int filled = false;
// cleans up threads
void sigintHandlerParent (int sigNum);
// gets files

void* getFile(void* arg);
// main method
int main()
{
  signal(SIGINT, sigintHandlerParent);

  char input[256];

  while(1){
    // get user input for threads
    printf("What file would you like to access: ");
    fgets(input, 256, stdin);
    countRec++;
    // check the thread list for population
    if( threadCount == sizeof(thread) ) {
      threadCount = 0;
      filled = true;
    }
    // create a thread
    if ((status = pthread_create (&thread[threadCount], NULL,  getFile, &input)) != 0) {
        fprintf (stderr, "thread create error %d: %s\n", status, strerror(status));
        exit (1);
    }
    threadCount++;

  }
  return 0;
}

void* getFile(void* arg){
  // sleep function
  srand(rand());
  char *userInput = (char *) arg;
  printf("\n\tSearching for: %s", userInput);
  int random = rand() % 9;
  if(random <= 7){
    // we "read" a file %80 of the time
    sleep(1);
  }else{
    // we block because we are getting the file 20% of the time
    sleep((rand()%7)+3);
  }
  countSrv++;
  printf("\tAccessed: %s", userInput);
  return NULL;
}

/** Signal overwrite for SIGINT */
void sigintHandlerParent (int sigNum){
  printf("\nQuiting: \n");
  printf("You asked for %d files and recieved %d.\n", countRec, countSrv);
  if(filled){ // if the thread list was fully used
    for( int i = 0; i < sizeof(thread); i++){
      if ((status = pthread_join (thread[i], &result)) != 0) {
            fprintf (stderr, "join error %d: %s\n", status, strerror(status));
            exit (1);
        }
    }
  }else{
    for( int i = 0; i < threadCount; i++){ // if the thread list was partially used
      if ((status = pthread_join (thread[i], &result)) != 0) {
            fprintf (stderr, "join error %d: %s\n", status, strerror(status));
            exit (1);
        }
    }
  }
	exit(0);
}
