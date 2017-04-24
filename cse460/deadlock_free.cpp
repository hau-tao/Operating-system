#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <stdlib.h>
                                                                               
using namespace std;
                                                                               
bool value_consumed = true;
SDL_sem* tunnel;     //mutexes for accessing a, b
bool quit = false;
int thread1 ( void *data )
{

                                                                               
  while ( !quit ) {
    puts("Eastbound Train 1 is waiting.");
    SDL_SemWait(tunnel);
    puts("Eastbound Train 1 is in tunnel");
    SDL_Delay ( rand() % 3000 );
    SDL_SemPost(tunnel);
    puts("Eastbound Train 1 is quitting");
  }
 
                                                                               
  return 0;
}
                                                                               
int thread2 ( void *data )
{
                                                                                
  while ( !quit ) {
      puts("_____Westbound Train 2 is waiting.");
      SDL_SemWait(tunnel);
      puts("_____Westbound Train 2 is in tunnel");
      SDL_Delay ( rand() % 3000 );
      SDL_SemPost(tunnel);
      puts("_____Westbound Train 2 is quitting");
  }                                  
  return 0;
}
                                                                               
int main ()
{
  SDL_Thread *id1, *id2;                //thread identifiers
 tunnel = SDL_CreateSemaphore(1);
                                                                               
  //create the threads
  id1 = SDL_CreateThread ( thread1, NULL );
  id2 = SDL_CreateThread ( thread2, NULL );
                                                                               
  //experiment with 20 seconds
  for ( int i = 0; i < 10; ++i )
      SDL_Delay ( 2000 );
                                                                               
  quit = true;                  //signal the threads to return
                                                                               
  //wait for the threads to exit
  SDL_WaitThread ( id1, NULL );
  SDL_WaitThread ( id2, NULL );
                                                                               
  return 0;
}