#include <stdio.h>
#include "simple.h"

double sum(const int *args, const int size){
  double result = 0;
  int i;
  for (i = 0; i < size; i++){
    result += args[i];
  }
  return result;
}

double mean(const int *args, const int size){
  double s = sum(args, size);
  double mean = s/size;
  return mean;
}

// based on:
// http://en.wikiversity.org/wiki/C_source_code_to_find_the_median_and_mean
double median(const int *args, const int size){
  int tmpArgs[size];
  int temp;
  int i, j;
  for(i=0; i<size-1; i++) {
    tmpArgs[i] = args[i];
  }
  // sort array tmpArgs
  for(i=0; i<size-1; i++) {
    for(j=i+1; j<size; j++) {
      if(tmpArgs[j] < tmpArgs[i]) {
	temp = tmpArgs[i];
	tmpArgs[i] = tmpArgs[j];
	tmpArgs[j] = temp;
      }
    }
  }
  
  if(size%2==0) {
    return((args[size/2] + args[size/2 - 1]) / 2.0);
  } else {
    return args[size/2];
  }
}

void get_quartiles(double* quartiles, const int *args, const int size){
  int tmpArgs[size];
  int temp;
  int i, j;
  int qidx = (size-1)/4;
  for(i=0; i<size; i++) {
    tmpArgs[i] = args[i];
  }
  // sort array tmpArgs
  for(i=0; i<size-1; i++) {
    for(j=i+1; j<size; j++) {
      if(tmpArgs[j] < tmpArgs[i]) {
	temp = tmpArgs[i];
	tmpArgs[i] = tmpArgs[j];
	tmpArgs[j] = temp;
      }
    }
  }
  if (size%2==0) {
    quartiles[1] = (tmpArgs[size/2 - 1] + tmpArgs[size/2]) / 2.0;
    if ((size)%4==0) {
      quartiles[0] = (tmpArgs[qidx - 1] + tmpArgs[qidx]) / 2.0;
      quartiles[2] = (tmpArgs[size - 1 - qidx] + tmpArgs[size - qidx]) / 2.0;
    } else {
      quartiles[0] = tmpArgs[qidx];
      quartiles[2] = tmpArgs[size - 1 - qidx];
    }
  } else {
    quartiles[1] = tmpArgs[size/2];
    if ((size-1)%4==0) {
      quartiles[0] = (tmpArgs[qidx - 1] + tmpArgs[qidx]) / 2.0;
      quartiles[2] = (tmpArgs[size - 1 - qidx] + tmpArgs[size - qidx]) / 2.0;
    } else {
      quartiles[0] = tmpArgs[qidx];
      quartiles[2] = tmpArgs[size - 1 - qidx];
    }
  }
}

params_t get_params(const int *args, const int size) {
  params_t params;
  params.sum = sum(args, size);
  params.mean = mean(args, size);
  get_quartiles(params.quartiles, args, size);
  return params;
}
