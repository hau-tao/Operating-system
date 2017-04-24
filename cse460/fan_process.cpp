//chain of 10 processes.cpp
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
 
using namespace std;
 
int main()
{
  pid_t pid;              //process id
  for( int i = 0; i < 10; i++){
       pid = fork();         //create another process
      

       if ( pid < 0 ) {      //fail
            cout << "\nFork failed" << endl;
            exit ( -1 );
        } else if ( pid == 0 ) {      //child

                cout << "I am child with process id " << getpid()
                << " and my parent is : " << getppid() << endl;
                exit ( 0 );
  
        } else {                      //parent
                wait ( NULL );              //wait for child
                
                
        }
     
 
  }

}
  