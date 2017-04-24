//fork_demo.cpp
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
 
using namespace std;
 
int main()
{
  int i;
                                                                                                        
  for ( i = 0; i < 3; ++i ) {
  	//cout <<"get id:"<< getpid<< endl;
    fork();
    cout << i << endl;
  }
  return 0;
}


