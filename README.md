# CK0047 - Métodos Numéricos I 🧮

Este repositório centraliza os algoritmos de aproximação numérica desenvolvidos para as avaliações práticas da disciplina de **Métodos Numéricos I** da Universidade Federal do Ceará (UFC). 

O projeto foi construído utilizando soluções em **C** (foco em estruturação e performance) e **Python** (foco em scripts rápidos de teste).

---

## 🚀 Escopo Prático e Trabalhos Implementados

O repositório está dividido estritamente de acordo com as duas grandes frentes de análise numérica abordadas:

### ✈️ Trabalho 01: Raízes de Equações (Análise Não-Linear)
Focado no cálculo de raízes para a função analítica $f(x, a) = a \cdot x - x \cdot \ln(x)$, aplicada à análise estática/oscilação de aeronaves para determinação de limites de segurança (onde o programa avalia criticamente se a raiz extrapola o limite seguro de $2.0$, disparando um alerta se o avião corre risco de explodir).

* **Método da Bisseção:** Resolução intervalar clássica baseada no teorema do valor intermediário (com verificação de mudança de sinal no intervalo).
* **Método da Falsa Posição:** Abordagem iterativa que aproxima a raiz utilizando uma média ponderada pelos valores da função nos extremos do intervalo.
* **Método de Newton-Raphson:** Algoritmo de convergência rápida que utiliza a aproximação linear local por meio da derivada analítica exata da função ($f'(x, a) = a - \ln(x) - 1$).
* **Quadro Comparativo:** O programa em C processa os três métodos para $n$ aviões em simultâneo e aponta automaticamente qual método obteve a raiz com o menor erro/critério de parada.

### 🏢 Trabalho 02: Sistemas de Equações Lineares (Análise Linear)
Focado na resolução de sistemas lineares do tipo $Ax = b$ por meio de decomposição matricial direta, permitindo trabalhar com matrizes quadradas genéricas de ordem $n$.

* **Fatoração LU Clássica:** Decompõe uma matriz quadrada $A$ no produto de duas matrizes, $L$ (triangular inferior unitária) e $U$ (triangular superior obtida por eliminação gaussiana), resolvendo o sistema em duas etapas de substituição ($Ly = b$ e $Ux = y$).
* **Fatoração LDP:** Extensão do método LU que isola os fatores da diagonal principal de $U$ em uma matriz diagonal $D$, resultando no produto de três matrizes: $L$ (triangular inferior unitária), $D$ (matriz diagonal de pivôs) e $P$ (triangular superior unitária). A resolução é feita em três etapas ($Ls = b$, $Dy = s$ e $Px = y$).

---

## 📂 Organização dos Diretórios

```text
├── Trabalho 01/
│   └── Codigo/
│       ├── main.c           # Implementação dos métodos de Bisseção, Falsa Posição e Newton em C
│       ├── main.py          # Script Python com a estrutura isolada do método da Bisseção
│       └── output/
│           └── main.exe     # Executável do programa de análise dos aviões
└── Trabalho 02/
    └── Código/
        ├── main.c           # Implementação das estruturas de Fatoração LU e LDP em C
        └── main.py          # Script Python equivalente com os métodos LU e LDP
```
---

## 🛠️ Tecnologias Utilizadas
* Linguagens: C (padrão ANSI) e Python 3.x
* Bibliotecas (Python): Numpy para manipulação vetorial e álgebra linear matemática.

---

## 🔧 Compilação e Execução
### Módulos em C
Para compilar qualquer um dos projetos principais em ambiente Linux/Windows através do gcc:

  ```bash
    # Navegue até o diretório do código correspondente e execute:
    gcc main.c -o programa_numerico -lm

    # Executando o binário:
    ./programa_numerico
  ```

### Módulos em Python
Certifique-se de ter as dependências matemáticas instaladas em sua máquina ou ambiente virtual:

```bash
  pip install numpy

  # Executando as rotinas analíticas:
  python main.py
