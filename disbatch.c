#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void* getFile(void* arg);
int main()
{
  int countRec, countSrv;
  char input[256];
  countRec = 0;
  countSrv = 0;
  while(1){
    pthread_t thread;
    int status;
    // get user input for threads
    printf("What file would you like to access:");
    fgets(input, 256, stdin);
    countRec++;
    // create a thread
    if ((status = pthread_create (&thread, NULL,  getFile, &input)) != 0) {
        fprintf (stderr, "thread create error %d: %s\n", status, strerror(status));
        exit (1);
    }


  }
  return 0;
}
void* getFile(void* arg){
  // sleep function
  srand(rand());
  char *userInput = (char *) arg;
  printf("Searching for: %s", userInput);
  int random = rand() % 9;
  if(random <= 7){
    // we "read" a file %80 of the time
    sleep(1);
  }else{
    // we block because we are getting the file 20% of the time
    sleep((rand()%7)+3);
  }
  countSrv++;
  print("Accessed: %s", userInput);
}
