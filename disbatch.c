#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
/**
 * This exemplifies how threads work
 * and how to avoid memory issues between threads.
 *
 * @author Allison Bolen
 * @author Alec Allain
 * @version 9/27/18
 */
 
// Global variables
int countSrv = 0; // count served
int countReq = 0; // count requested
pthread_t thread[50]; // thread array to join on
int threadCount = 0; // current thread
int filled = 0; // boolean have we circled back to the begining of the array

// cleans up threads
void sigintHandlerParent (int sigNum);

// gets files
void* getFile(void* arg);

// main method
int main()
{
  srand(rand());
  signal(SIGINT, sigintHandlerParent);
  int status;
  char input[50][256]; // store input to avoid overwriting between threads
  while(1){
    // check the thread list for population
    if( threadCount == sizeof(thread)-1 ) {
      threadCount = 0;
      filled = 1;
    }
    // get user input for threads
    printf("What file would you like to access: ");
    fgets(input[threadCount], 256, stdin);
    while(*input[threadCount] =='\n' || *input[threadCount] == ' '){
        printf("\nBlank input, try again");
		    fgets(input[threadCount], 256, stdin);
	  }
    countReq++;
    // create a thread
    if ((status = pthread_create (&thread[threadCount], NULL,  getFile, &input[threadCount])) != 0) {
        fprintf (stderr, "thread create error %d: %s\n", status, strerror(status));
        exit (1);
    }
    threadCount++;
  }
  return 0;
}

/**
* Fakes getting a file using threads
*/
void* getFile(void* arg){
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

/** Signal overwrite for SIGINT
 *  join all threads that have been used and may still be open
 */
void sigintHandlerParent (int sigNum){
  int status;
  void* result;
  printf("\nStarting quit process: \n");
  printf("Closing the rest of the threads\n");
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
  printf("\nYou asked for %d files and recieved %d.\n", countReq, countSrv);
	exit(0);
}
