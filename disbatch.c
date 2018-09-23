#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



int main()
{
  int countRec, countSrv;
  char input[256];
  while(1){

    // get user input for threads
    printf("What file would you like to access:");

    fgets(input, 256, stdin);

  }
  return 0;
}
