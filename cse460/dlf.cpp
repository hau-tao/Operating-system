#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <stdlib.h>
                                                                               
using namespace std;
                                                                               
bool value_consumed = true;
SDL_mutex *mutexa, *mutexb;     //mutexes for accessing a, b
bool quit = false;
int a = 0, b = 0;
int thread1 ( void *data )
{
  char *tname = ( char * )data;
                                                                               
  while ( !quit ) {
    printf("I am %s. ", tname );
    SDL_mutexP ( mutexa );      //lock before processing a
    printf("%s has locked a\n", tname);
    ++a;                        //dummy instruction
    //do somehting
    SDL_Delay( 10 );
                                                                               
    //also need b value
    SDL_mutexP ( mutexb );      //lock before accessing b
    printf("%s has locked b\n", tname);
    a += b++;                   //dummy instruction
                                                                               
    //release lock b
    SDL_mutexV ( mutexb );
    //release lock a
    SDL_mutexV ( mutexa );
                                                                               
    //delay for a random amount of time
    SDL_Delay ( rand() % 3000 );
  }
  printf("%s quits\n", tname );
                                                                               
  return 0;
}
                                                                               
int thread2 ( void *data )
{
  char *tname = ( char * )data;
                                                                               
  while ( !quit ) {
    printf("I am %s. ", tname );
    SDL_mutexP ( mutexa );      //lock before accessing a
    printf("%s has locked b\n", tname);
    a += b;                   //dummy instruction
    
    SDL_mutexP ( mutexb );      //lock before processing b
    printf("%s has locked b\n", tname);
    ++b;                        //dummy instruction
    //do somehting
    SDL_Delay( 10 );
                                                                               
                                                                               
    //release the lock b
    SDL_mutexV ( mutexb );
    //release the lock a
    SDL_mutexV ( mutexa );
                                                                               
    //delay for a random amount of time
    SDL_Delay ( rand() % 3000 );
  }
  printf("%s quits\n", tname);
                                                                               
  return 0;
}
                                                                               
int main ()
{
  SDL_Thread *id1, *id2;                //thread identifiers
  char *tnames[2] = { "Arnold", "Groper" };     //names of threads
                                                                               
  mutexa = SDL_CreateMutex();
  mutexb = SDL_CreateMutex();
                                                                               
  //create the threads
  id1 = SDL_CreateThread ( thread1, tnames[0] );
  id2 = SDL_CreateThread ( thread2, tnames[1] );
                                                                               
  //experiment with 20 seconds
  for ( int i = 0; i < 10; ++i )
      SDL_Delay ( 2000 );
                                                                               
  quit = true;                  //signal the threads to return
                                                                               
  //wait for the threads to exit
  SDL_WaitThread ( id1, NULL );
  SDL_WaitThread ( id2, NULL );
                                                                               
  return 0;
}