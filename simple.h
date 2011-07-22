double sum(const int *args, const int size);
double mean(const int *args, const int size);
double median(const int *args, const int size);
void get_quartiles(double* quartiles, const int *args, const int size);

typedef struct {
  int sum;
  double mean;
  double quartiles[3];
} params_t;

params_t get_params(const int *args, const int size);

