#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "neural.h"
#include "loaderNN.h"
#include "data_base.h"

void XOR_NN(struct NN *MyNet, size_t iter, double learning_rate)
{
  set_learning_rate(learning_rate);
  double input1[2] = {1, 1};
  double input2[2] = {1, 0};
  double input3[2] = {0, 1};
  double input4[2] = {0, 0};
  double output1[1] = {0};
  double output2[1] = {1};
  double output3[1] = {1};
  double output4[1] = {0};
  for (size_t i = 0; i < iter; i++)
  {
    backprop(MyNet, input1, output1);
    backprop(MyNet, input2, output2);
    backprop(MyNet, input3, output3);
    backprop(MyNet, input4, output4);
  }
}

void OCR_NN(struct NN *MyNet, size_t iter, double learning_rate)
{
  set_learning_rate(learning_rate);
  struct letter **l = init_database("../images/data.png");
  for (size_t i = 0; i < iter; i++)
  {
    printf("%zu / %zu\n", i, iter);
    train(MyNet, l, 66);
  }
}

int main()
{
  size_t layers[3] = {256, 128, 66};
  struct NN *MyNet = init_NN(layers, 3);
  OCR_NN(MyNet, 30000000, 0.005);
  save_NN(MyNet, "NN_savefiles/OCR_NN_11");
  return 1;
}
