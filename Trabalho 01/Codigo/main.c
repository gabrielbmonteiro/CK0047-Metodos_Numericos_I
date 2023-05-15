#include <stdio.h>
#include <math.h>

//  ------------------------------------------- FUNÇÃO --------------------------------------------

double f(double x, double a) {
    return a * x - x * log(x);
}

//  ------------------------------------------- DERIVADA DA FUNÇÃO --------------------------------------------

double flin(double x, double a) {
    return a-log(x)-1;
}

// -------------------------------------- MÉTODO DA BISSEÇÃO --------------------------------------

typedef struct {
    int houveErro;
    double raiz;
    double intervX;
} ResultadoBissecao;

/* 
    Executa o método da bisseção para achar o zero de f no intervalo 
    [a,b] com precisão epsilon. O método executa no máximo maxIter iterações.
    Retorna uma tupla (houveErro, raiz), onde houveErro é booleano.
*/
ResultadoBissecao bissecao(double (*funcao)(double, double), double a, double isolamentoA, double isolamentoB, double epsilon, int maxIter) {
    ResultadoBissecao resultado;
    // Inicializa as variáveis Fa e Fb com os valores de f(a) e f(b)
    double Fa = funcao(isolamentoA, a);
    double Fb = funcao(isolamentoB, a);

    // Teste para saber se a função muda de sinal. Se não mudar, mostrar mensagem de erro
    if (Fa * Fb > 0) {
        //printf("Erro! A função não muda de sinal.\n");
        resultado.houveErro = 1;
        return resultado;
    }

    // Mostra na tela cabeçalho da tabela
    //printf("\nk\ta\t\t\t\tfa\t\t\t\tb\t\t\t\tfb\t\t\t\tx\t\t\t\tfx\t\t\t\tintervX\n");

    // Inicializa tamanho do intervalo intervX usando a função abs, x e Fx
    double intervX = fabs(isolamentoB - isolamentoA);
    double x = (isolamentoA + isolamentoB) / 2;
    double Fx = funcao(x, a);

    // Mostra dados de inicialização
    //printf("-\t%e\t%e\t%e\t%e\t%e \t%e\t%e\n", a, Fa, b, Fb, x, Fx, intervX);

    // Testa se intervalo já é do tamanho da precisão e retorna a raiz sem erros
    if (intervX <= epsilon) {
        resultado.houveErro = 0;
        resultado.raiz = x;
        resultado.intervX = intervX;
        return resultado;
    }

    int k = 1;

    while (k <= maxIter) {
        // Se a função não mudar de sinal entre a e x, então atualiza o a e Fa. 
        // Senão, atualiza o b e Fb
        if (Fa * Fx > 0) {
            isolamentoA = x;
            Fa = Fx;
        } else {
            isolamentoB = x;
            Fb = Fx;
        }

        // Atualiza intervX, x, e Fx
        intervX = fabs(isolamentoB - isolamentoA);
        x = (isolamentoA + isolamentoB) / 2;
        Fx = funcao(x, a);

        // Mostra valores na tela
        //printf("%d\t%e\t%e\t%e\t%e\t%e\t%e\t%e\n", k, a, Fa, b, Fb, x, Fx, intervX);

        // Teste do critério de parada (usando apenas o tamanho do intervalo)
        if (intervX <= epsilon) {
            resultado.houveErro = 0;
            resultado.raiz = x;
            resultado.intervX = intervX;
            return resultado;
        }

        k++;
    }

    // Se chegar aqui é porque o número máximo de iterações foi atingido
    // Mostrar uma mensagem de erro e retorna que houve erro e a última raiz encontrada
    printf("ERRO! Número máximo de iterações atingido.\n");
    resultado.houveErro = 2;
    resultado.raiz = x;
    resultado.intervX = intervX;
    return resultado;
}

// ------------------------------------ MÉTODO DA POSIÇÃO FALSA ------------------------------------
typedef struct {
    int houveErro;
    double raiz;
    double intervX;
} ResultadoFalsaPosicao;

// Método da falsa posição
ResultadoFalsaPosicao falsa_posicao(double (*f)(double, double), double a, double isolamentoA, double isolamentoB, double epsilon, int maxIter) {
    // Variáveis
    ResultadoFalsaPosicao resultado;
    double Fa, Fb;
    double x, Fx;
    double intervaloX;

    Fa = f(isolamentoA, a);
    Fb = f(isolamentoB, a);

    // Iterações
    for (int k = 0; k < maxIter; k++) {
        // Atualiza x
        x = (isolamentoA * Fb - isolamentoB * Fa) / (Fb - Fa);
        Fx = f(x, a);
        intervaloX = isolamentoB - isolamentoA;

        // Testa se já é raiz
        if (fabs(Fx) <= epsilon || intervaloX <= epsilon) {
            resultado.houveErro = 0; // Não há erro
            resultado.raiz = x;
            resultado.intervX = intervaloX;
            return resultado;
        }

        // Troca de valores diminuindo o intervalo
        if (Fa * Fx > 0) {
            isolamentoA = x;
            Fa = Fx;
        } else {
            isolamentoB = x;
            Fb = Fx;
        }
    }

    // Se chegar no número máximo de iterações, ocorre o erro
    resultado.houveErro = 2; // Número máximo de iterações atingido
    resultado.raiz = x;
    resultado.intervX = intervaloX;
    return resultado;
}
// ------------------------------------ MÉTODO DE NEWTON-RAPHSON -----------------------------------

typedef struct {
    int houveErro;
    double raiz;
    double parada;
} ResultadoNewtonRaphson;

ResultadoNewtonRaphson newton(double (*funcao)(double, double), double (*flin)(double, double), double a, double isolamentoA, double isolamentoB, double epsilon, int maxIter) {
    ResultadoNewtonRaphson resultado;

    double x0 = (isolamentoA + isolamentoB) / 2;
  
    // Checa se x0 já é a raiz. 
    if (fabs(f(x0,a)) <= epsilon) {
        printf("%e\t", x0);
        resultado.houveErro = 1;
        resultado.raiz = x0;
        return resultado;
    }
    /*
    printf("Iterações método Newton-Raphson:\n");
    printf("k\t x\t\t f(x)\t\t f'(x)\n");
    printf("%d\t%e\t%e\t%e\n", 0, x0, f(x0,a), flin(x0,a));
    */  
    for (int k = 1; k <= maxIter; k++) {
        double x = x0 - (f(x0,a) / flin(x0,a));
        //printf("%d\t%e\t%e\t%e\n", k, x, f(x,a), flin(x,a));

        if (fabs(f(x,a)) <= epsilon) {
            resultado.houveErro = 0;
            resultado.raiz = x;
            resultado.parada = fabs(f(x,a));
            return resultado;
        }
      
       x0 = x;
    }

    printf("ERRO: Número máximo de iterações atingido\n");
    resultado.houveErro = 2;
    resultado.raiz = x0;
    resultado.parada = fabs(f(x0,a));
    return resultado;
}

// --------------------------------------------- MAIN ----------------------------------------------

int main() {

    int n;
    printf("Quantos aviões serão analizados? "); // pede o valor de "n"
    scanf("%d", &n);
    
    double biss_resultados[n][5];         // resultados do método da Bisseção
    double posifals_resultados[n][5]; // Resultados do método da Posição Falsa
    double newtraph_resultados[n][5];     // resultados do método de Newton-Raphson

    int maxIter = 50;                     // número máximo de iterações (arbitrário)

    for (int i = 0; i < n; i++) {
      double a;
      printf("Digite o valor de 'a' para a função f(d): ");      // pede o valor da constante de kd avião
      scanf("%lf", &a);

      double epsilon;
      printf("Digite o valor da precisão para a função f(d): ");
      scanf("%lf", &epsilon);
      
      double isolamentoA;
      printf("Digite o início do isolamento para a função f(d): ");
      scanf("%lf", &isolamentoA);

      double isolamentoB;
      printf("Digite o final do isolamento para a função f(d): "); 
      scanf("%lf", &isolamentoB);

      ResultadoBissecao resultado_biss = bissecao(f, a, isolamentoA, isolamentoB, epsilon, maxIter);
      biss_resultados[i][0] = i + 1;                       // valor de "n"
      biss_resultados[i][1] = a;                           // valor de "a"
      biss_resultados[i][2] = resultado_biss.houveErro;    // tipo de parada
      if (resultado_biss.houveErro != 1) {
        biss_resultados[i][3] = resultado_biss.raiz;       // valor da raiz (d)
        biss_resultados[i][4] = resultado_biss.intervX;    // valor do intervalo (|b - a|)
      }
      
      ResultadoFalsaPosicao resultado_falsa_pos = falsa_posicao(f, a, isolamentoA, isolamentoB, epsilon, maxIter);
      posifals_resultados[i][0] = i + 1; // Valor de "n"
      posifals_resultados[i][1] = a; // Valor de "a"
      posifals_resultados[i][2] = resultado_falsa_pos.houveErro; // Tipo de parada
      if (resultado_falsa_pos.houveErro != 1) { // Se não houver erro
          posifals_resultados[i][3] = resultado_falsa_pos.raiz; // Valor da raiz (d)
          posifals_resultados[i][4] = resultado_falsa_pos.intervX; // Valor do intervalo (|b - a|)
      }    
        
      ResultadoNewtonRaphson resultado_newtraph = newton(f, flin, a, isolamentoA, isolamentoB, epsilon, maxIter);
      newtraph_resultados[i][0] = i + 1; // valor de n
      newtraph_resultados[i][1] = a;
      newtraph_resultados[i][2] = resultado_newtraph.houveErro;
      if (resultado_newtraph.houveErro != 1) {
        newtraph_resultados[i][3] = resultado_newtraph.raiz;
        newtraph_resultados[i][4] = resultado_newtraph.parada;
      }
    
    }


    // Tabelas com os resultados
    printf("\n---------------------------------------------------\n");
    printf("Método da Bisseção:\n");
    printf("\nn:\ta:\td:\t\t\t\tStatus:\t\t\t\t\tErro:\t\t\t\tParada:\n");
    for (int i = 0; i < n; i++) {
      printf("%.0f\t",biss_resultados[i][0]);  // valor de "n"
      printf("%.f\t",biss_resultados[i][1]);  // valor de "a"

      if (biss_resultados[i][2] == 1.0) {       // analisa se houve erro no programa
        printf("-\t\t\t\t");                   // valor dado para "d"
        printf(" -\t\t\t\t\t\t");              // analisa se o avião vai explodir
        printf(" -\t\t\t\t\t");                  // valor dado para "intervX"
      } else {
        printf("%e\t",biss_resultados[i][3]);   // valor dado para "d"
        if (biss_resultados[i][3] > 2){         // analisa se o avião vai explodir
          printf("O avião irá explodir!\t");
        } else{
          printf("O avião não irá explodir!\t");
        }
        printf("%e\t\t",biss_resultados[i][4]);  // valor dado para "intervX"
      }

      if (biss_resultados[i][2] == 0.0) {     // identifica o erro (se houver)
        printf("Achou a raiz!\n");
      }
      if (biss_resultados[i][2] == 1.0) {    // identifica o erro (se houver)
        printf("No intervalo dado a função não muda de sinal!\n");
      }
      if (biss_resultados[i][2] == 2.0) {    // identifica o erro (se houver)
        printf("Número máximo de iterações atingido!\n");
      }

    }

    printf("\n---------------------------------------------------\n");
    printf("Método da Falsa Posição:\n");
    printf("\nn:\ta:\td:\t\t\t\tStatus:\t\t\t\t\tErro:\t\t\t\tParada:\n");
    for (int i = 0; i < n; i++) {
          printf("%.0f\t", posifals_resultados[i][0]);
          printf("%.f\t", posifals_resultados[i][1]);

          if (posifals_resultados[i][2] == 1.0) { // Se não houver raiz não mostra "-"
              printf("-\t\t\t\t");
              printf(" -\t\t\t\t\t\t");
              printf(" -\t\t\t\t");
          } else {
              printf("%e\t", posifals_resultados[i][3]);
              if (posifals_resultados[i][3] > 2) { // Se raiz for maior que 2...
                  printf("O avião irá explodir!\t");
              } else {
                  printf("O avião não irá explodir!\t");
              }
              printf("%e\t\t", posifals_resultados[i][4]); //
              }

    // Erros (ou não)
    if (posifals_resultados[i][2] == 0.0) {
        printf("Achou a raiz!\n");
    }
    if (posifals_resultados[i][2] == 1.0) {
        printf("No intervalo dado a função não muda de sinal!\n");
    }
    if (posifals_resultados[i][2] == 2.0) {
        printf("Número máximo de iterações atingido!\n");
    }
}
      
    printf("\n---------------------------------------------------\n");
    printf("Método de Newton-Raphson:\n");
    printf("\nn:\ta:\td:\t\t\t\tStatus:\t\t\t\t\tErro:\t\t\t\tParada:\n");
    for (int i = 0; i < n; i++) {
      printf("%.0f\t",newtraph_resultados[i][0]);  // valor de "n"
      printf("%.f\t",newtraph_resultados[i][1]);   // valor de "a"

      if (newtraph_resultados[i][2] == 1.0) {       // analisa se houve erro no programa
        printf("%e\t",newtraph_resultados[i][3]);   // valor dado para "d"
        printf(" -\t\t\t\t\t");                  // valor dado para "intervX"
        if (newtraph_resultados[i][3] > 2){         // analisa se o avião vai explodir
          printf("O avião irá explodir!\t");
        } else{
          printf("O avião não irá explodir!\t");
        }                    
      } else {
        printf("%e\t",newtraph_resultados[i][3]);   // valor dado para "d"
        if (newtraph_resultados[i][3] > 2){         // analisa se o avião vai explodir
          printf("O avião irá explodir!\t");
        } else{
          printf("O avião não irá explodir!\t");
        }
        printf("%e\t\t",newtraph_resultados[i][4]); // valor dado para "intervX"
      }

      if (newtraph_resultados[i][2] == 0.0) {     // identifica o erro (se houver)
        printf("Achou a raiz!\n");
      }
      if (newtraph_resultados[i][2] == 1.0) {    // identifica o erro (se houver)
        printf("Achou a raiz!\n");
      }
      if (newtraph_resultados[i][2] == 2.0) {    // identifica o erro (se houver)
        printf("Número máximo de iterações atingido.\n");
      }

    }


    // Comparação de resultados
    printf("\n---------------------------------------------------\n");
    printf("Comparação\n");
    printf("\nn:\tResultado:\n");
    for (int i = 0; i < n; i++){
      double menor  = INFINITY;
      int ident = -1;

      if (biss_resultados[i][2] != 1.0 &  biss_resultados[i][4] < menor){
        menor = biss_resultados[i][4];
        ident = 0;
      }
      if (posifals_resultados[i][2] != 1.0 &  posifals_resultados[i][4] < menor){  
        menor = posifals_resultados[i][4];
        ident = 1;
      }
      if (newtraph_resultados[i][4] < menor){
        menor = newtraph_resultados[i][4];
        ident = 2;
      }

      if (ident == 0){
        printf("%d\tO Método da Bisseção achou a raiz com o menor erro!\n", i+1);
      }
      if (ident == 1){
        printf("%d\tO Método da Falsa Posição achou a raiz com o menor erro!\n", i+1);
      }
      if (ident == 2){
        printf("%d\tO Método de Newton-Raphson achou a raiz com o menor erro!\n", i+1);
      }
      
    }

  return 0;
}