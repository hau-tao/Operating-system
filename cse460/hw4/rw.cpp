/*
  readers_writers.cpp
  Compile:  g++ -o  readers_writers readers_writers.cpp -lSDL -lpthread
  Execute:  ./readers_writers
*/

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
using namespace std;

SDL_bool condition = SDL_FALSE;
SDL_mutex *mutex;
SDL_cond *readerQueue;   //condition variable
SDL_cond *writerQueue;   //condition variable

int readers = 0;
int writers = 0;
int num = 1;
void read(){
	
	
    try
    {
    	string line,new1;
        ifstream fin("counter.txt"); 
        string data;
       
 
        while (getline (fin,line))
		{
   			new1=line;
		}  
		cout  <<"Counter: " << new1<< " was read.\n"; 
        fin.close(); //close file

       
    }
    catch(exception &e)
    {
        cerr<<e.what()<<endl; //display any error that may occur
        
    }
  
}

void write(){ 

	
  try
    {
        ofstream fout("counter.txt",ios::app); //open file for writing and append to it
        cout <<"Writing: " << num;
        fout << num << endl;
        num++;
        cout <<" to the file \n"<< endl;
        fout.close(); //close the file
       
    }
    catch(exception &e)
    {
        cerr<<e.what(); //write any exceptions that may occur when trying to write to file
        
    }
   

}

int reader ( void *data )
{
  SDL_LockMutex ( mutex );
  while ( !(writers == 0) )
      SDL_CondWait ( readerQueue, mutex );

  readers++;
  printf("\nThis is %s thread\n", (char *) data );
  SDL_UnlockMutex ( mutex );
  read();
  SDL_Delay ( rand() % 3000);
  SDL_LockMutex ( mutex );
  //printf("\nThis is %s thread\n", (char *) data );
  if ( --readers == 0 )
      SDL_CondSignal ( writerQueue );
  SDL_UnlockMutex ( mutex );
}

int writer ( void *data )
{
  SDL_LockMutex(mutex);
  while ( !( (readers == 0) && (writers == 0) ) )
      SDL_CondWait ( writerQueue, mutex );

  writers++;
  printf("\nThis is %s thread\n", (char *) data );
  SDL_UnlockMutex ( mutex );
  write();
  SDL_Delay ( rand() % 3000);
  SDL_LockMutex ( mutex );
  writers--;       //only one writer at one time
  //printf("\nThis is %s thread\n", (char *) data );
  SDL_CondSignal ( writerQueue );
  SDL_CondBroadcast ( readerQueue );
  SDL_UnlockMutex ( mutex );
}

int main ()
{
  SDL_Thread *idr[20], *idw[3];          	      //thread identifiers
  char *rnames[] = { "reader 1", "reader 2", "reader 3", 
  "reader 4", "reader 5", "reader 6", "reader 7", "reader 8", "reader 9", "reader 10", 
  "reader 11", "reader 12", "reader 13", 
  "reader 14", "reader 15", "reader 16", "reader 17", "reader 18", "reader 19", "reader 20"}; //names of threads
  char *wnames[] = { "writer 1", "writer 2", "writer 3" }; //names of threads

  mutex = SDL_CreateMutex();
  readerQueue = SDL_CreateCond();
  writerQueue = SDL_CreateCond();
  int i,j;
  while(1){
      for (  i = 0; i < 20; i++ ){
          idr[i] = SDL_CreateThread ( reader, rnames[i] );
          SDL_Delay ( rand() % 3000);
      }
      for (  j = 0; j < 3; j++ ){
          idw[j] = SDL_CreateThread ( writer, wnames[j] );
          SDL_Delay ( rand() % 3000);
      } 
  }
  
  i=j=0;
  
  for ( i = 0, j=0; i < 20 or j<3; i++, j++ ){
    SDL_WaitThread ( idr[i], NULL );
    SDL_WaitThread ( idw[j], NULL );
  }

  SDL_DestroyCond ( readerQueue );
  SDL_DestroyCond ( writerQueue );
  SDL_DestroyMutex ( mutex );
  return 0;
}

