#include <stdio.h>
#include "simple.h"

int main () {
  int args_size = 9;
  //int args[] = { 1, 2, 3, 4, 5 };
  
  int args[args_size];
  int i;
  for (i=0; i<args_size; i++) {
    scanf("%i", &args[i]);
  }

  params_t params = get_params(args, args_size);

  printf("%i  %f\n", params.sum, params.mean);
  printf("%f  %f  %f\n", 
	 params.quartiles[0], params.quartiles[1], params.quartiles[2]);

  return 0;
}
