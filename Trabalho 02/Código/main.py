def substituicoes_sucessivas(A, b):
    '''Executa o método das substituições sucessivas para resolver o sistema 
       linear triangular inferior Ax=b.
       Parâmetros de entrada: A é uma matriz triangular inferior e b é o vetor constante. 
       Saída: vetor x
    '''
    ## n é a ordem da matriz A
    n = len(A)
    
    x = n * [0]
    for i in range(0, n):
      S = 0
      for j in range(0, i):
        S = S + A[i][j] * x[j]
      x[i] = (b[i]-S)/A[i][i]
    
    return x

def identidade(n):
    '''Cria uma matriz identidade de ordem n.
    Parâmetros de entrada:  n é a ordem da matriz.
    Saída: matriz identidade de ordem n.
    '''
    m = []
    for i in range(0, n):
      linha = [0] * n
      linha[i] = 1
      m.append(linha)
    return m

def lu(A):
    '''
    Decompõe a matriz A no produto de duas matrizes L e U. Onde L é uma matriz 
    triangular inferior unitária e U é uma matriz triangular superior.
    Parâmetros de entrada: A é uma matriz quadrada de ordem n.
    Saída: (L,U) tupla com as matrizes L e U
    '''
    n = len(A)
    
    ## Inicializa a matriz L com a matriz identidade
    L = identidade(n)
    
    for k in range(0, n-1):
      for i in range(k+1, n):
        m = - A[i][k]/A[k][k]
        L[i][k] = -m

        for j in range(k+1, n):
          A[i][j] = m * A[k][j] + A[i][j]

          A[i][k] = 0
    
    return (L, A)

def formata_matriz(M):
    m = len(M) # número de linhas
    n = len(M[0]) # número de colunas
    s = ""
    for i in range(m):
        for j in range(n):
           s += "%9.3f " % M[i][j]
        s += "\n"
    return s

def substituicoes_retroativas(A, b):
    '''Executa o método das substituições retroativas para resolver o sistema 
       linear triangular superior Ax=b.
       Parâmetros de entrada: A é uma matriz triangular superior e b é o vetor constante. 
    '''
    ## n é a ordem da matriz A
    n = len(A)
    
    ## inicializa o vetor x com tamanho n e elementos iguais a 0
    x = n * [0] 
    
    for i in range(n-1, -1, -1):
      S = 0
      for j in range(i+1, n):
        S = S + A[i][j] * x[j]
      x[i] = (b[i]-S)/A[i][i]
    
    return x

def lux(L,U,b):
    '''
    Resolve o sistema LUx=b.
    Esse método resolve os dois sistemas lineares triangulares.
    Parâmetros de entrada: L é uma matriz triangular inferior de ordem n,
    U é uma matriz triangular superior e b é o vetor constante.
    Saída: vetor x solução do sistema.
    '''
    
    y = substituicoes_sucessivas(L, b)

    x = substituicoes_retroativas(U, y)
    
    return x

def ldp(A):
    '''
    Decompõe a matriz A no produto de três matrizes L, D e P. 
    Onde L é uma matriz triangular inferior unitária, 
    D é uma matriz diagonal e P é uma matriz triangular superior com diagonal unitária (U = DP).
    
    Parâmetros de entrada: A é uma matriz quadrada de ordem n.
    Saída: (L, D, P) tupla com as matrizes L, D e P.
    '''
    n = len(A)
    
    L = identidade(n)
    D = identidade(n)
    
    for k in range(0, n-1):
        for i in range(k+1, n):
            m = -A[i][k] / A[k][k]
            
            # Atualiza a matriz L
            L[i][k] = -m
            
            for j in range(k+1, n):
                A[i][j] = m * A[k][j] + A[i][j]
            
                A[i][k] = 0
    
    # Atualiza a matriz D
    for i in range(n):
        D[i][i] = A[i][i]
        
        # Atualiza a matriz P
        pivot = A[i][i]
        for j in range(i, n):
            A[i][j] = A[i][j] / pivot

    
    return (L, D, A)

def ldp_solver(L, D, P, b):
    '''
    Resolve o sistema LDPx=b.
    Esse método resolve os três sistemas lineares.
    Parâmetros de entrada: L é uma matriz triangular inferior de ordem n,
    D é uma matriz diagonal, P é uma matriz triangular superior com diagonal unitária 
    e b é o vetor constante.
    Saída: vetor x solução do sistema.
    '''
    # Resolve Ls = b
    s = substituicoes_sucessivas(L, b)
    
    # Resolve Dy = s
    y = [s[i] / D[i][i] for i in range(len(D))]
    
    # Resolve Px = y
    x = substituicoes_retroativas(P, y)
    
    return x

def main():
    A1 = [[3, -2, 1],
    [1, -3, 4],
    [9, 4, -5]]

    b = [8, 6, 11]

    (L, U) = lu(A1)
    x1 = lux(L, U, b)
    print("Matrix L:")
    print(formata_matriz(L))
    print("Matrix U:")
    print(formata_matriz(U))
    print(x1)
    
    
    A2 = [[3, -2, 1],
    [1, -3, 4],
    [9, 4, -5]]
    

    (L, D, P) = ldp(A2)
    x2 = ldp_solver(L, D, P, b)
    
    print("Matrix L:")
    print(formata_matriz(L))
    print("Matrix D:")
    print(formata_matriz(D))
    print("Matrix P:")
    print(formata_matriz(P))
    print("Solution x:")
    print(x2)

if __name__ == "__main__":
    main()
