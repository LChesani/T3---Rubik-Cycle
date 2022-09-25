#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int **blocos;
} Lado;

typedef struct {
  Lado lados[6];
} Cubo;

void inicializa_cubo(Cubo **x) {
  *x = (Cubo *)malloc(sizeof(Cubo)); // malloca espaco do cubo
  for (int i = 0; i < 6; i++) {
    (*x)->lados[i].blocos = (int **)malloc(3 * sizeof(int *));
    for (int j = 0; j < 3; j++) {
      (*x)->lados[i].blocos[j] = (int *)malloc(3 * sizeof(int));
    }
  }
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        (*x)->lados[i].blocos[j][k] = i;
      }
    }
  }
}

int **rotEsq(int **l) { // funcionando
  int **aux = (int **)malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) {
    aux[i] = (int *)malloc(3 * sizeof(int));
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 2; j >= 0; j--) {
      aux[i][j] = l[j][i];
    }
  }
  int *x = aux[0];
  aux[0] = aux[2];
  aux[2] = x;
  return aux;
}

int **rotDir(int **l) {
  int **aux = l;
  for (int i = 0; i < 3; i++) {
    aux = rotEsq(aux);
  }
  return aux;
}

int *copia_linha(int *v1, int *v2) {
  int *aux = (int *)malloc(3 * sizeof(int));
  for (int i = 0; i < 3; i++) {
    aux[i] = v1[i]; // backup
  }
  for (int i = 0; i < 3; i++) {
    v1[i] = v2[i];
  }
  return aux;
}

int **copia_coluna(int **v1, int **v2, int coluna) {
  int **aux = (int **)malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) {
    aux[i] = (int *)malloc(3 * sizeof(int));
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      aux[i][j] = v1[i][j];
    }
  }

  for (int i = 0; i < 3; i++) {
    v1[i][coluna] = v2[i][coluna];
  }
  return aux;
}

int *linha_coluna(int **matriz, int *linha,
                  int coluna) { // copia linha para coluna
  int *aux = (int *)malloc(3 * sizeof(int));
  for (int i = 0; i < 3; i++) {
    aux[i] = matriz[i][coluna];
  }

  for (int i = 0; i < 3; i++) {
    matriz[i][coluna] = linha[i];
  }

  return aux;
}

void move(char identidade, Cubo *x) {
  int *aux = (int *)malloc(3 * sizeof(int));
  int **aux2 = (int **)malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) {
    aux2[i] = (int *)malloc(3 * sizeof(int));
  }
  if (identidade == 'U') {
    x->lados[0].blocos = rotDir(x->lados[0].blocos);
    aux = copia_linha(x->lados[4].blocos[0], x->lados[1].blocos[0]);
    aux = copia_linha(x->lados[5].blocos[0], aux);
    aux = copia_linha(x->lados[3].blocos[0], aux);
    aux = copia_linha(x->lados[1].blocos[0], aux);
  }
  else if (identidade == 'u') {
    x->lados[0].blocos = rotEsq(x->lados[0].blocos);
    aux = copia_linha(x->lados[1].blocos[0], x->lados[4].blocos[0]);
    aux = copia_linha(x->lados[3].blocos[0], aux);
    aux = copia_linha(x->lados[5].blocos[0], aux);
    aux = copia_linha(x->lados[4].blocos[0], aux);
  }
  else if (identidade == 'D') {
    x->lados[2].blocos = rotDir(x->lados[2].blocos);
    aux = copia_linha(x->lados[3].blocos[2], x->lados[1].blocos[2]);
    aux = copia_linha(x->lados[5].blocos[2], aux);
    aux = copia_linha(x->lados[4].blocos[2], aux);
    aux = copia_linha(x->lados[1].blocos[2], aux);
  }
  else if (identidade == 'd') {
    x->lados[2].blocos = rotEsq(x->lados[2].blocos);
    aux = copia_linha(x->lados[1].blocos[2], x->lados[3].blocos[2]);
    aux = copia_linha(x->lados[4].blocos[2], aux);
    aux = copia_linha(x->lados[5].blocos[2], aux);
    aux = copia_linha(x->lados[3].blocos[2], aux);
  }
  else if (identidade == 'R') {
    x->lados[3].blocos = rotDir(x->lados[3].blocos);
    aux2 = copia_coluna(x->lados[0].blocos, x->lados[1].blocos, 2);
    aux2 = copia_coluna(x->lados[5].blocos, aux2, 2);
    aux2 = copia_coluna(x->lados[2].blocos, aux2, 2);
    aux2 = copia_coluna(x->lados[1].blocos, aux2, 2);
  }
  else if (identidade == 'r') {
    x->lados[3].blocos = rotEsq(x->lados[3].blocos);
    aux2 = copia_coluna(x->lados[1].blocos, x->lados[0].blocos, 2);
    aux2 = copia_coluna(x->lados[2].blocos, aux2, 2);
    aux2 = copia_coluna(x->lados[5].blocos, aux2, 2);
    aux2 = copia_coluna(x->lados[0].blocos, aux2, 2);
  }
  else if (identidade == 'L') {
    x->lados[4].blocos = rotDir(x->lados[4].blocos);
    aux2 = copia_coluna(x->lados[0].blocos, x->lados[5].blocos, 0);
    aux2 = copia_coluna(x->lados[1].blocos, aux2, 0);
    aux2 = copia_coluna(x->lados[2].blocos, aux2, 0);
    aux2 = copia_coluna(x->lados[5].blocos, aux2, 0);
  }
  else if (identidade == 'l') {
    x->lados[4].blocos = rotEsq(x->lados[4].blocos);
    aux2 = copia_coluna(x->lados[5].blocos, x->lados[0].blocos, 0);
    aux2 = copia_coluna(x->lados[2].blocos, aux2, 0);
    aux2 = copia_coluna(x->lados[1].blocos, aux2, 0);
    aux2 = copia_coluna(x->lados[0].blocos, aux2, 0);
  }
  else if (identidade == 'F') {
    x->lados[1].blocos = rotDir(x->lados[1].blocos);
    aux = linha_coluna(x->lados[3].blocos, x->lados[0].blocos[2], 0);
    aux = copia_linha(x->lados[2].blocos[2], aux);
    aux = linha_coluna(x->lados[4].blocos, aux, 2);
    aux = copia_linha(x->lados[0].blocos[2], aux);
  }
  else if (identidade == 'f') {
    x->lados[1].blocos = rotEsq(x->lados[1].blocos);
    aux = linha_coluna(x->lados[4].blocos, x->lados[0].blocos[2], 2);
    aux = copia_linha(x->lados[2].blocos[2], aux);
    aux = linha_coluna(x->lados[3].blocos, aux, 0);
    aux = copia_linha(x->lados[0].blocos[2], aux);
  }
  else if (identidade == 'B') {
    x->lados[5].blocos = rotDir(x->lados[5].blocos);
    aux = linha_coluna(x->lados[4].blocos, x->lados[0].blocos[0], 0);
    aux = copia_linha(x->lados[2].blocos[0], aux);
    aux = linha_coluna(x->lados[3].blocos, aux, 2);
    aux = copia_linha(x->lados[0].blocos[0], aux);
  }
  else if (identidade == 'b') {
    x->lados[5].blocos = rotEsq(x->lados[5].blocos);
    aux = linha_coluna(x->lados[3].blocos, x->lados[0].blocos[0], 2);
    aux = copia_linha(x->lados[2].blocos[0], aux);
    aux = linha_coluna(x->lados[4].blocos, aux, 0);
    aux = copia_linha(x->lados[0].blocos[0], aux);
  }
  free(aux);
  for(int i = 0; i < 3; i++){
    free(aux2[i]);
  }
  free(aux2);
}

int iguais(Cubo *a, Cubo *b) {
  for (int k = 0; k < 6; k++) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (a->lados[k].blocos[i][j] != b->lados[k].blocos[i][j]) {
          return 0; // diferentes
        }
      }
    }
  }
  return 1; // iguais
}

void free_cubo(Cubo **x) {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      free((*x)->lados[i].blocos[j]);
    }
    free((*x)->lados[i].blocos);
  }
  free(*x);
}

int simulacao(char *input, Cubo *x) {
  Cubo *ini;
  inicializa_cubo(&ini);
  int count = 1;
  while (!iguais(x, ini)) {
    for (int i = 0; input[i] != '\0'; i++) {
      move(input[i], x);
    }
    count++;
  }
  free_cubo(&ini);
  return count;
}

int main(void) {
  char input[80];
  Cubo *x;
  while (scanf("%s", input) != EOF) {
    inicializa_cubo(&x);
    for (int i = 0; input[i] != '\0'; i++) {
      move(input[i], x);
    }

    printf("%d\n", simulacao(input, x));
    free_cubo(&x);
  }
  return 0;
}
