# OCR(e)

### Projet S3 EPITA Promo 2023

## The structure of the project

| Parties       | Etat     | Possible mise à jour |
| ------------- | ---------| -------------------- |
| MySDL         | Finis    | NO                   |
| UI            | Finis    | YES (priority 4)     |
| Preprocessing | Finis    | YES (priority 3)     |
| Segmentation  | Finis    | YES (priority 1)     |
| Neural Net    | Finis    | YES (priority 2)     |
| Data Base     | Finis    | NO                   |

### MySDL
Contiens les fonctions basiques pour mysdl obtenue dans le TP.

### UI
Contiens toutes les fonctions pour l'interface.

### Preproc
Contiens des fonctions pour le pré-traitement:
* Grayscale
* Otzu (black and white)

### Segmentation
Contiens toutes les fonctions pour la segmentation et la reconnaissance de charactère.

### Neuralnet
Le réseau de neurones a la structure suivante: Il s’agit d’une matrice de nœuds (voir ci-dessous).
Un nœud est constitué d'un ensemble d'entrées (couche précédente) et d'un ensemble de poids (sommets reliant des nœuds).
Le réseau de neurones est enregistré au format suivant (fichier txt):
```
/Size/ x
/Layers size/ {x,x,x,}
/Weights/
x.x
...
..
.
/Bias/
x.x
/Weights/
x.x

etc...
```
Les nœuds sont définis par leurs coordonnées dans la matrice du réseau de neurones.

### NN Training
Cette section explique comment former votre NN
aller à neuralnet/trainning.c
Choisir le nombre d'itérations (NUMBER_ITER)
Choisir le taux d'apprentissage (LEARNING_RATE)
Choisir le nom de notre fichier a enregistré (NAME_OF_SAVE_FILE)
make et run ./training
Approximation -> iter / time  : 7500 / min
```C
int main(){
    size_t layers[3] = {256,128,66};
    struct NN *MyNet = init_NN(layers,3);
    OCR_NN(MyNet,NUMBER_ITER,LEARNING_RATE);
    save_NN(MyNet,"NN_savefiles/NAME_OF_SAVE_FILE");
}
```

#### Comment tester le NN
Choisir le fichier a enregistré dans main.c
make et run ./main
Ensuite : cat Text.txt
Puis esssayer avec data.png et une fois avec img.png

```C
void OCR(struct letter **l, int nb_letters)
{
  FILE *fp = fopen("Text.txt","w");
  double resul_mat [16*16];
  struct NN *mynet = load_NN("neuralnet/NN_savefiles/NAME_OF_SAVE_FILE");
  for (int i = 0; i < nb_letters; i++)
  {
    resizePixels(l[i]->mat, resul_mat, l[i]->width, l[i]->height, 16, 16);
    double *output = feedforward(mynet, resul_mat);
    char tmp = get_char(66, output);
    fprintf(fp,"%c",tmp);
    if (l[i]->space_after)
      fprintf(fp,"%c",' ');
    if (l[i]->new_line)
      fprintf(fp,"%c",'\n');
  }
  fclose(fp);
}
```

