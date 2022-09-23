#include <stdio.h>
#include <stdlib.h>


typedef struct{
    char **blocos;
}Lado;

typedef struct{
    Lado lados[6];
}Cubo;

void inicializa_cubo(Cubo **x){
    char l[] = {'U', 'F', 'D', 'R', 'L', 'B'}; //lados
    *x = (Cubo*) malloc(sizeof(Cubo)); //malloca espaco do cubo
    for(int i = 0; i < 6; i++){
        (*x)->lados[i].blocos = (char**) malloc(3 * sizeof(char*));
        for(int j = 0; j < 3; j++){
            (*x)->lados[i].blocos[j] = (char*) malloc(sizeof(char));
        }
    }
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                (*x)->lados[i].blocos[j][k] = l[i];
            }
        }
    }
}

char **rotEsq(char **l){ //funcionando
    char **aux = (char**)malloc(3 * sizeof(char*));
    for(int i = 0; i < 3; i++){
        aux[i] = (char*) malloc(sizeof(char));
    }
    for(int i = 0; i < 3; i++){
        for(int j = 2; j >= 0; j--){
            aux[i][j] = l[j][i];
        }
    }
    char *x = aux[0];
    aux[0] = aux[2];
    aux[2] = x;
    return aux;
}

char **rotDir(char **l){
    char **aux = l;
    for(int i = 0; i < 3; i++){
        aux = rotEsq(aux);
    }
    return aux;
}

char *copia(char *v1, char *v2){
    char *aux = (char*) malloc(3*sizeof(char));
    for(int i = 0; i < 3; i++){
        aux[i] = v1[i]; //backup
    }
    for(int i = 0; i < 3; i++){
        v1[i] = v2[i];
    }
    return aux;
}

void move(char identidade, Cubo *x){
    char *aux = (char*) malloc(3 * sizeof(char));
    if(identidade == 'U'){
        x->lados[0].blocos = rotDir(x->lados[0].blocos);
        aux = copia(x->lados[3].blocos[0], x->lados[1].blocos[0]);
        aux = copia(x->lados[5].blocos[0], aux);
        aux = copia(x->lados[4].blocos[0], aux);
        aux = copia(x->lados[1].blocos[0], aux);
    }
    if(identidade == 'D'){
        x->lados[0].blocos = rotDir(x->lados[0].blocos);
        aux = copia(x->lados[3].blocos[2], x->lados[1].blocos[0]);
        aux = copia(x->lados[5].blocos[2], aux);
        aux = copia(x->lados[4].blocos[2], aux);
        aux = copia(x->lados[1].blocos[2], aux);
    }
}


void printa_cubo(Cubo *x){ //debug
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                printf(" %c ", x->lados[i].blocos[j][k]);
            }
            printf("\n");
        }
    }
}

int iguais(Cubo *a, Cubo *b){
    for(int k = 0; k < 6; k++){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(a->lados[k].blocos[i][j] != b->lados[k].blocos[i][j]){
                    return 0; //diferentes
                }
            }
        }
    }
    return 1; //iguais
}

int simulacao(char *input, Cubo *x){
    Cubo *ini;
    inicializa_cubo(&ini);
    int count = 0;
    while(!iguais(x, ini)){
        for(int i = 0; input[i] != '\0'; i++){
            move(input[i], x);
        }
        count++;
    }
    return count;
}

int main(void){
    char input[80];
    Cubo *x;
    inicializa_cubo(&x);
    
    scanf("%s", input);
    for(int i = 0; input[i] != '\0'; i++){
        move(input[i], x);
    }
    
    printf("%d", simulacao(input, x));


    return 0;
}