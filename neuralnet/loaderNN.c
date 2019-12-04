#include "loaderNN.h"
#include <err.h>

void save_NN(struct NN *mynet, char *name)
{
    FILE *myfile;
    myfile = fopen(name, "w");
    fprintf(myfile, "%lu\n{", mynet->size);
    for (size_t i = 0; i < mynet->size; i++)
    {
        fprintf(myfile, "%lu", mynet->layersize[i]);
        if (i < mynet->size - 1)
            fprintf(myfile, ",");
    }
    fprintf(myfile, ",}\n");
    for (size_t i = 0; i < mynet->size; i++)
    {
        for (size_t j = 0; j < mynet->layersize[i]; j++)
        {
            for (size_t k = 0; k < mynet->mat[i][j]->nb_inputs; k++)
            {
                fprintf(myfile, "%lf\n", mynet->mat[i][j]->weights[k]);
            }
            fprintf(myfile, "b\n%lf\n", mynet->mat[i][j]->bias);
        }
        fprintf(myfile, "$\n");
    }
    fclose(myfile);
}

struct NN *load_NN(char *name)
{
    FILE *file = fopen(name, "r");
    if (file == NULL)
    {
        printf("File does not exists");
        return NULL;
    }
    char line[100];
    //size_t len = 0;
    size_t mynb = 0;
    //double *myw = NULL;
    size_t lpos = 0;
    size_t posin = 0;
    int debug;
    //size_t linelen;
    debug = 1;
    if (debug == 1)
        debug = 2;
    debug = fscanf(file, "%s", line);
    mynb = (size_t)atoi(line);
    debug = fscanf(file, "%s", line);
    size_t index = 0;
    //size_t s = 0;
    size_t *layers = malloc(mynb * sizeof(size_t));
    for (size_t i = 1; line[i] != '}'; i++)
    {
        if (line[i] == ',')
        {
            layers[lpos] = posin;
            posin = 0;
            lpos += 1;
        }
        else
        {
            char nb[5] = "";
            char fu[1];
            fu[0] = line[i];
            strcat(nb, fu);
            posin = 10 * posin + (size_t)atoi(nb);
        }
    }
    size_t layer_pos = 0;
    size_t node_index = 0;
    double num = 0;
    struct NN *mynet = init_NN(layers, mynb);
    //handling the weights
    while (fscanf(file, "%s", line) != EOF || mynb > layer_pos)
    {
        if (line[0] == '$')
        {
            if (mynb <= layer_pos + 1)
                break;
            layer_pos += 1;
            node_index = 0;
        }
        else if (line[0] == 'b')
        {
            debug = fscanf(file, "%s", line);
            //sscanf(line,"%lf", num);
            //bias = atof(line);
            mynet->mat[layer_pos][node_index]->bias = atof(line);
            node_index += 1;
            index = 0;
        }
        else
        {

            num = atof(line);
            mynet->mat[layer_pos][node_index]->weights[index] = num;
            index += 1;
        }
    }
    fclose(file);
    return mynet;
}
