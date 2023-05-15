#include <stdio.h>
#include <stdlib.h>

void substituicoes_sucessivas(double **A, double *b, double *x, int n) {
    for (int i = 0; i < n; i++) {
        double S = 0;
        for (int j = 0; j < i; j++) {
            S += A[i][j] * x[j];
        }
        x[i] = (b[i] - S) / A[i][i];
    }
}

void substituicoes_retroativas(double **A, double *b, double *x, int n) {
    for (int i = n - 1; i >= 0; i--) {
        double S = 0;
        for (int j = i + 1; j < n; j++) {
            S += A[i][j] * x[j];
        }
        x[i] = (b[i] - S) / A[i][i];
    }
}

double** identidade(int n) {
    double **m = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        m[i] = (double *)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            m[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
    return m;
}

void lu(double **A, double ***L, double ***U, int n) {
    *L = identidade(n);

    for (int k = 0; k < n - 1; k++) {
        for (int i = k + 1; i < n; i++) {
            double m = -A[i][k] / A[k][k];
            (*L)[i][k] = -m;

            for (int j = k + 1; j < n; j++) {
                A[i][j] = m * A[k][j] + A[i][j];
            }

            A[i][k] = 0;
        }
    }

    *U = A;
}

void lux(double **L, double **U, double *b, double *x, int n) {
    double *y = (double *)malloc(n * sizeof(double));

    substituicoes_sucessivas(L, b, y, n);
    substituicoes_retroativas(U, y, x, n);

    free(y);
}

void ldp(double **A, double ***L, double ***D, double ***P, int n) {
    *L = identidade(n);
    *D = (double **)malloc(n * sizeof(double *));

    for (int k = 0; k < n - 1; k++) {
        for (int i = k + 1; i < n; i++) {
            double m = -A[i][k] / A[k][k];

            // Atualiza a matriz L
            (*L)[i][k] = -m;

            for (int j = k + 1; j < n; j++) {
                A[i][j] = m * A[k][j] + A[i][j];
            }

            A[i][k] = 0;
        }
    }

  for (int i = 0; i < n; i++) {
      (*D)[i] = (double *)malloc(n * sizeof(double));

      for (int j = 0; j < n; j++) {
          (*D)[i][j] = (i == j) ? A[i][i] : 0.0;
      }

      double pivot = A[i][i];
      for (int j = i; j < n; j++) {
          A[i][j] = A[i][j] / pivot;
      }
  }

    *P = A;
}

void ldp_solver(double **L, double **D, double **P, double *b, double *x, int n) {
    double *s = (double *)malloc(n * sizeof(double));
    double *y = (double *)malloc(n * sizeof(double));

    substituicoes_sucessivas(L, b, s, n);

    for (int i = 0; i < n; i++) {
        y[i] = s[i] / D[i][i];
    }

    substituicoes_retroativas(P, y, x, n);

    free(s);
    free(y);
}

void imprimir_matriz(double **matriz, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%9.3f ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    
  int n;
  printf("Informe a ordem da matriz: ");
  scanf("%d", &n);

  // Alocar dinamicamente a matriz A
  double **A1 = (double **)malloc(n * sizeof(double *));
  for (int i = 0; i < n; i++) {
      A1[i] = (double *)malloc(n * sizeof(double));
  }

  // Alocar dinamicamente o vetor f
  double *f1 = (double *)malloc(n * sizeof(double));

  // Preencher a matriz A
  printf("Informe os elementos da matriz A:\n");
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
          printf("A[%d][%d]: ", i + 1, j + 1);
          scanf("%lf", &A1[i][j]);
      }
  }

  // Preencher o vetor b
  printf("\nInforme os elementos do vetor f:\n");
  for (int i = 0; i < n; i++) {
      printf("f[%d]: ", i + 1);
      scanf("%lf", &f1[i]);
  }
  
  double** A2 = (double**)malloc(n * sizeof(double*));
  for (int i = 0; i < n; i++) {
        A2[i] = (double*)malloc(n * sizeof(double));
      for (int j = 0; j < n; j++) {
          A2[i][j] = A1[i][j];
      }
  }

  double* f2 = (double*)malloc(n * sizeof(double));
  for (int i = 0; i < n; i++) {
      f2[i] = f1[i];
  }

  printf("\nMétodo de Fatoração LU normal:\n");
  double **L1, **U1, **D1;
  double *d1 = (double *)malloc(n * sizeof(double));
  lu(A1, &L1, &U1, n);
  /*
  printf("Matrix L:\n");
  imprimir_matriz(L1, n, n);
  printf("Matrix U:\n");
  imprimir_matriz(U1, n, n);
  */
  lux(L1, U1, f1, d1, n);
  printf("Vetor d:\n");
  for (int i = 0; i < n; i++) {
      printf("%9.3f\n", d1[i]);
  }

  printf("\nMétodo de Fatoração LDP:\n");
  double **L2, **U2, **D2, **P2;
  double *d2 = (double *)malloc(n * sizeof(double));
  ldp(A2, &L2, &D2, &P2, n);
  /*
  printf("Matrix L:\n");
  imprimir_matriz(L2, n, n);
  printf("Matrix D:\n");
  imprimir_matriz(D2, n, n);
  printf("Matrix P:\n");
  imprimir_matriz(P2, n, n);
  */
  
  ldp_solver(L2, D2, P2, f2, d2, n);
  printf("Vetor d:\n");
  for (int i = 0; i < n; i++) {
      printf("%9.3f\n", d2[i]);
  }

  return 0;
}
