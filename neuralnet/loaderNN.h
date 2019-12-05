#ifndef LOADER_NN_H
#define LOADER_NN_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "neural.h"

void save_NN(struct NN *MyNet, char *name);
struct NN *load_NN(char *s);

#endif