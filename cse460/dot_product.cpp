// dot_product.cpp
// Use thread to calculate dot product of two vectors
// @Author: T.L. Yu
 
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <iostream>
 
/* We must include SDL_thread.h separately. */
#include <SDL/SDL_thread.h>
#include <vector>

using namespace std;

//shared variables
vector <double> A;
vector <double> B;
double sum;
 
/* This function is a thread entry point. */
int dotProduct ( void *data )
{
    char *threadname;
 
    /* Anything can be passed as thread data.
       We will use it as a thread name. */
    threadname = (char *) data;
                                                                                  
    cout << "This is " <<  threadname << endl;;
                                                                                  
    int len;
    int na, nb;
    na = A.size();  
    nb = B.size();  
    if ( na > nb )  //take the shorter one
      len = nb;
    else
      len = na;                    

    sum = 0.0;                                                         
    for ( int i = 0; i < len; i++ )   
      sum += A[i] * B[i];
    
    return 0;
}

void initVectors()
{
  //some arbitrary data
  for ( int i = 1; i <= 3; i++ ) {
    A.push_back ( i );
    B.push_back ( i * i );
  }
}                        


void print ( const vector<double> &v )
{
   cout << "( " ;
   int n = v.size();
   for ( int i = 0; i < n; i++ ){
     cout << v[i];
     if ( i < n - 1 )
       cout << ", ";
     else
       cout << " )";
   }
}

int main()
{
    initVectors();

    SDL_Thread *sumThread;
    
    sumThread = SDL_CreateThread( dotProduct, ( void *) "Dot Product Thread");
   
    if ( sumThread == NULL ) {
         cout << "\nSDL_CreateThread failed: " <<  SDL_GetError() << endl;
    } else {
        // Wait for the thread to complete. 
        int returnValue;
        SDL_WaitThread( sumThread, &returnValue);
	cout <<  "Dot product of vectors: " ;
	print ( A );
	print ( B );
	cout << " is " << sum << endl; 
    }
    return 0;
}
