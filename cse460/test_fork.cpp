//test_fork.cpp
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
  pid_t pid;    //process id
  char *message;
  int n;
  cout << "fork program starting\n";
  pid = fork();
  //cout <<" return begin "<< endl;
  switch ( pid ) {
  case -1:
    cout << "Fork failure!\n";
    return 1;
  case 0:
    message = "This is the child\n";
    n = 5;
    break;
  default:
    message = "This is the parent\n";
    n = 3;
    break;
  }
  for ( int i = 0; i < n; ++i ) {
    cout << message;
    cout << "n: "<< n<< endl;
    sleep ( 1 );
    cout << "i: "<<i<< endl;
  }
  //cout << " n outer loop:"<<n;

  return 0; 
}