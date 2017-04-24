#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <stdlib.h>
                                                                               
using namespace std;
                                                                               
SDL_bool condition = SDL_FALSE;
SDL_mutex* tunnel;     //mutexes for accessing a, b
SDL_cond *T1Queue;   //condition variable
SDL_cond *T2Queue;   //condition variable

int train_1 = 0;
int train_2 =0;
int active_train2 = 0;
/*void train1(){
  puts("Eastbound Train 1 is in the tunnel");

}
void train2(){
   puts("Westbound Train 2 is in the tunnel");

}*/
int thread1 ( void *data )
{
   
  while(1){
    SDL_Delay(rand() % 3000);
    SDL_LockMutex ( tunnel );
    while(!(train_2 == 0))
       SDL_CondWait ( T1Queue, tunnel );
    train_1++;
    SDL_UnlockMutex ( tunnel );
    puts("Eastbound Train 1 is in the tunnel");
    SDL_LockMutex ( tunnel);
    if ( --train_1== 0 )
      SDL_CondSignal ( T2Queue );
    SDL_UnlockMutex ( tunnel);

  }
}
                                                                               
int thread2 ( void *data )
{
                                                                                
  while (1) {
    SDL_Delay ( rand() % 3000);
    SDL_LockMutex(tunnel);
    train_2++;
    while ( !( (train_1 == 0) && (active_train2 == 0) ) )
            SDL_CondWait ( T2Queue, tunnel);
    active_train2++;
 
    SDL_UnlockMutex ( tunnel);
    puts("_____Westbound Train 2 is in the tunnel");
    SDL_LockMutex ( tunnel);
    active_train2--;       //only one writer at one time
    if(--train_2 == 0)
        SDL_CondSignal ( T1Queue );
    else
       SDL_CondSignal ( T2Queue );

    SDL_UnlockMutex ( tunnel);
  }                                  
  
}
                                                                               
int main ()
{
  SDL_Thread *id1, *id2;                //thread identifiers
  tunnel = SDL_CreateMutex();
  T1Queue = SDL_CreateCond();
  T2Queue = SDL_CreateCond();
                                                                               
  //create the threads
  id1 = SDL_CreateThread ( thread1, NULL );
  id2 = SDL_CreateThread ( thread2, NULL );
                                                                               
  //experiment with 20 seconds
  for ( int i = 0; i < 10; ++i )
      SDL_Delay ( 2000 );
                                                                               
  //quit = true;                  //signal the threads to return
                                                                               
  //wait for the threads to exit
  //SDL_WaitThread ( id1, NULL );
  SDL_WaitThread ( id2, NULL );
  SDL_DestroyCond ( T1Queue );
  SDL_DestroyCond ( T2Queue );
  SDL_DestroyMutex ( tunnel );
  return 0;
}