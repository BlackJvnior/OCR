#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

struct NN
{
  size_t size;
  size_t *layersize;
  struct N ***mat;
};

struct N
{
  double *weights;
  size_t nb_inputs;
  struct N **inputs;
  double bias;
  double value;
};

void set_learning_rate(double x);
struct NN *init_NN(size_t *layersize, size_t size);
double *feedforward(struct NN *MyNet, double *inputs);
void backprop(struct NN *MyNet, double *input_t, double *output_t);
char get_char(size_t len, double *out);
