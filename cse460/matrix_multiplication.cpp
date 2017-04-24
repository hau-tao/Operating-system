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

const int M = 3;
const int L = 3;
const int N = 3;

//shared variables
double A[M][L];
double B[L][N];
double C[M][N];
double sum;
 
/* This function is a thread entry point. */
typedef struct {
  int row;
  int column;
} ThreadData;
int dotProduct ( void *data )
{
    
    ThreadData  *tdata= (ThreadData*) data;
    sum = 0.0;                                                         
    for ( int i = 0; i < L; i++ ) 
      sum += A[tdata->row][i] * B[i][tdata->column];
    C[tdata->row][tdata->column] = sum;
    
    
    return 0;
}
void initMatrixA(double a[][L], int M)
{
  //some arbitrary data
  double value = 0.0;
  for ( int i = 0; i < M; i++ ) {
    for(int j=0; j< L; j++)
      a[i][j] = value++;
   
  }
}  
void initMatrixB(double b[][N], int L)
{
  //some arbitrary data
  double value = 1.0;
  for ( int i = 0; i < L; i++ ) {
    for(int j=0; j< N; j++)
      b[i][j] = value++;
   
  }
}                        



void print( const double a[][L], int M)
{
  int i, j;
  for (i = 0; i < M; i++) {
    printf("\n\t| ");
    for (j = 0; j < L; j++){
      printf("%.2f", a[i][j]);
      printf("\t ");
    }
    printf("|");
  }
}



int main()
{   
    cout << "Dimension of Matrix A: MxL\n ";
    initMatrixA(A, M);
    print(A,M);
    cout <<"\nDimension of Matrix B; LxN\n";
    initMatrixB(B,L);
    print(B,L);
    cout << endl;
    ThreadData *data = (ThreadData*) malloc(sizeof(ThreadData));
    SDL_Thread *sumThread;
    int i, j;
    for (i =0; i < M; i++){
      for(j=0;j < N; j++){
        data->row = i;
        data->column =j;
        sumThread = SDL_CreateThread( dotProduct, (void*) data);
        if ( sumThread == NULL ) 
            cout << "\nSDL_CreateThread failed: " <<  SDL_GetError() << endl;
        else{
            int returnValue;
            SDL_WaitThread( sumThread, &returnValue);
            
        }

     }
    }
    cout <<"The matrix multiplication is:\n";
    print(C,M);
    cout << endl;

   
    return 0;
}
