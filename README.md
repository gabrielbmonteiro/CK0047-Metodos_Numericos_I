# CK0047 - Métodos Numéricos I 🧮

Este repositório centraliza os algoritmos de aproximação numérica e modelagem computacional desenvolvidos para as avaliações práticas da disciplina de **Métodos Numéricos I** da Universidade Federal do Ceará (UFC), sob a orientação do Prof. Joaquim Bento. 

O projeto foi construído utilizando soluções híbridas em **C** (foco em performance e controle de memória estruturada) e **Python** (foco em análise ágil de convergência e visualização de dados).

---

## 🚀 Escopo Prático e Trabalhos Implementados

O repositório é dividido estritamente de acordo com as duas grandes frentes da análise numérica linear e não-linear abordadas durante o semestre:

### 📐 Trabalho 01: Raízes de Equações (Análise Não-Linear)
Focado no cálculo do deslocamento ($d$) e análise de oscilação em estruturas de balanços físicos para mitigar riscos de ruptura (limite de estabilidade estrutural de $0.3\text{ cm}$).
* **Método de Newton-Raphson Original:** Resolução iterativa da raiz de $f(d) = 0$ utilizando a derivada analítica clássica.
* **Método de Newton Modificado com Fator de Limitação (FL):** Abordagem customizada para tratar casos em que a derivada local se aproxima perigosamente de zero ($f'(x_k) \to 0$). Implementa um parâmetro de controle próximo a zero ($\lambda = 0.05$), herdando o comportamento da última aproximação estável ($x_w$) caso $|f'(x_k)| \le \lambda$.
* **Derivação Numérica Integrada:** Algoritmo numérico para aproximação de derivadas por diferenças finitas para dispensar a necessidade de cálculo analítico prévio da função.

### 🏢 Trabalho 02: Sistemas de Equações Lineares (Análise Linear)
Focado no cálculo de uma matriz de deslocamentos múltiplos $\{d\}_{n \times 1}$ associados a sistemas mecânicos de vigas/balanços complexos, resolvendo a equação matricial de coeficientes rígidos $Cd = v$. O sistema monitora criticamente se as amplitudes extrapolam $3\text{ cm}$.
* **Método de Eliminação de Gauss Normal:** Algoritmo direto clássico com etapas de pivoteamento e triangulação superior seguidas de retrosubstituição.
* **Método de Gauss-Jordan:** Extensão que transforma a matriz de coeficientes $C$ diretamente em uma matriz identidade através de eliminação completa acima e abaixo da diagonal principal, obtendo o vetor resposta diretamente e calculando a inversa da matriz ($A^{-1}$).
* **Calibração e Quadro de Respostas:** Suite de testes internos utilizando matrizes de teste simétricas e diagonalmente dominantes:
    $$[C] = \begin{bmatrix} 10 & 1 & 1 \\ 1 & 10 & 1 \\ 1 & 1 & 10 \end{bmatrix}, \quad \{v\} = \begin{bmatrix} 12 \\ 12 \\ 12 \end{bmatrix}$$

---

## 📂 Organização dos Diretórios

```text
├── Trabalho 01/
│   └── Codigo/
│       ├── main.c           # Implementação core dos algoritmos de Newton (Original e FL) em C
│       └── main.py          # Script em Python para análise comparativa de convergência
├── Trabalho 02/
│   └── Código/
│       ├── main.c           # Implementação estruturada de Gauss e Gauss-Jordan em C
│       └── main.py          # Automação e geração de quadros resposta em Python
└── README.md                # Documentação técnica do repositório
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
