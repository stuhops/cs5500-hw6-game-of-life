#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <stdlib.h>

#define MCW MPI_COMM_WORLD

using namespace std;

void printBoard(int arr[], const int ROW_SIZE) {
  cout << " Grid:\n";
  for(int i = 0; i < ROW_SIZE; ++i) {
    for(int j = 0; j < ROW_SIZE; ++j) {
      if(arr[ROW_SIZE * i + j])
        cout << " 0";
      else
        cout << " -";
    }
    cout << endl;
  }
  cout << endl;
}


int calcNeighbors(int arr[], const int ROW_SIZE, int i, int j) {
  int neighbors = 0;

  //north 3
  if(i != 0) {
    // Upper left
    if(j != 0)
      neighbors += arr[ROW_SIZE * (i-1) + (j-1)];
    // Upper
    neighbors += arr[ROW_SIZE * (i-1) + j];
    // Upper right
    if(j+1 < ROW_SIZE)
      neighbors += arr[ROW_SIZE * (i-1) + (j+1)];
  }

  // Middle 2
  // Left
  if(j != 0)
    neighbors += arr[ROW_SIZE * (i) + (j-1)];
  // Right
  if(j+1 < ROW_SIZE)
    neighbors += arr[ROW_SIZE * (i) + (j+1)];

  // South 3 
  if(i+1 < ROW_SIZE) {
    // Upper left
    if(j != 0)
      neighbors += arr[ROW_SIZE * (i+1) + (j-1)];
    // Upper
    neighbors += arr[ROW_SIZE * (i+1) + j];
    // Upper right
    if(j+1 < ROW_SIZE)
      neighbors += arr[ROW_SIZE * (i+1) + (j+1)];
  }

  return neighbors;
}


int main(int argc, char **argv) {
  const int ROW_SIZE = 8;
  int arr[ROW_SIZE * ROW_SIZE] = {0,0,0,0,0,0,0,0,
                                  0,1,0,0,0,0,0,0,
                                  0,0,1,1,0,0,0,0,
                                  0,1,1,0,0,0,0,0,
                                  0,0,0,0,0,0,0,0,
                                  0,0,0,0,0,0,0,0,
                                  0,0,0,0,0,0,0,0,
                                  0,0,0,0,0,0,0,0};

  int tmpArr[ROW_SIZE * ROW_SIZE];
  for(int i = 0; i < ROW_SIZE; ++i) {
    for(int j = 0; j < ROW_SIZE; ++j) {
      tmpArr[ROW_SIZE * i + j] = arr[ROW_SIZE * i + j];
    }
  }

  printBoard(arr, ROW_SIZE);

  for(int cnt = 0; cnt < 10; cnt++){
    for(int i = 0; i < ROW_SIZE; ++i) {
      for(int j = 0; j < ROW_SIZE; ++j) {
        int neighbors = calcNeighbors(arr, ROW_SIZE, i, j);

        if(neighbors == 0 || neighbors == 1)
          tmpArr[ROW_SIZE * i + j] = 0;
        else if(neighbors == 3)
          tmpArr[ROW_SIZE * i + j] = 1;
        else if(neighbors > 3)
          tmpArr[ROW_SIZE * i + j] = 0;
      }
    }

    for(int i = 0; i < ROW_SIZE; ++i) {
      for(int j = 0; j < ROW_SIZE; ++j) {
        arr[ROW_SIZE * i + j] = tmpArr[ROW_SIZE * i + j];
      }
    }
    printBoard(arr, ROW_SIZE);
  }

  return 0;
}