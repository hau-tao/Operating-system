#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<iostream>
#include<ctype.h>
#include<deque>
 
/* modify the code */
using namespace std;

class Cframe {
public:
  int frameNo;    // frame number
  int pageNo;     // page number
  int r;          // reference bit
  Cframe ( int n, int p )       // constructor
  {
     frameNo = n;
     pageNo =  p;  // no page loaded at beginning
     r = 0;
  }
};
 
deque <Cframe> Q;
int nFaults = 0;
int  page, frame;
SDL_mutex *mutex;
SDL_cond *updateQueue;  //condition variable
bool update = false;
bool quit = false;

#define MAX_TEXT 512

struct my_msg_st {
    long int my_msg_type;
    char some_text[BUFSIZ];
};

int main()
{
    int running = 1;
    int msgid;
    struct my_msg_st some_data;
    long int msg_to_receive = 0;

/* First, we set up the message queue. */

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
/* Then the messages are retrieved from the queue, until an end message is encountered.
 Lastly, the message queue is deleted. */
   
    while(running) {
        if (msgrcv(msgid, (void *)&some_data, BUFSIZ,
                   msg_to_receive, 0) == -1) {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        //printf("You wrote: %s", some_data.some_text);
     
    sscanf ( some_data.some_text, "%d,%d,%d", &page, &frame, &nFaults );
    printf("%4d\t%5d\t%10d\n", page, frame, nFaults);
      
        if (strncmp(some_data.some_text, "end", 3) == 0) {
            running = 0;
        }
    }

    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}


