def bissecao(f, a, b, epsilon, maxIter = 50):
    """Executa o método da bisseção para achar o zero de f no intervalo 
       [a,b] com precisão epsilon. O método executa no máximo maxIter
       iterações.
       Retorna uma tupla (houveErro, raiz), onde houveErro é booleano.
    """
    ## Inicializa as variáveis Fa e Fb com os valores de f(a) e f(b), 
    ## respectivamente.
    Fa = f(a)
    Fb = f(b)
    
    ## Teste para saber se a função muda de sinal. Se não mudar, mostrar
    ## mensagem de erro
    if Fa * Fb > 0:
        ## Mostrar mensagem
        print("Erro! A função não muda de sinal.")
        return (True, None)
    
    ## Mostra na tela cabeçalho da tabela
    print("k\t  a\t\t  fa\t\t  b\t\t  fb\t\t  x\t\t  fx\t\tintervX")
    
    ## Inicializa tamanho do intervalo intervX usando a função abs, x e Fx
    intervX = abs(b - a)
    x = (a + b)/2
    Fx = f(x)
    
    ## Mostra dados de inicialização
    print("-\t%e\t%e\t%e\t%e\t%e\t%e\t%e" % (a, Fa, b, Fb, x, Fx, intervX))
    
    ## Teste se intervalo já é do tamanho da precisão e retorna a raiz sem erros
    if intervX <= epsilon:
        return (False, x)
    
    
    ## Iniciliza o k
    k = 1
    
    ## laço
    while k <= maxIter:
        ## Se a função não mudar de sinal entre a e x, então atualiza o a e Fa. 
        ## Senão, atualiza o b e Fb
        if Fa * Fx > 0:
            a = x
            Fa = Fx
        else:
            b = x
            Fb = Fx

        ## Atualiza intervX, x, e Fx
        intervX = abs(b - a)
        x = (a + b)/2
        Fx = f(x)
        
        ## Mostra valores na tela
        print("%d\t%e\t%e\t%e\t%e\t%e\t%e\t%e"%(k, a, Fa, b, Fb, x, Fx, intervX))
        
        ## Teste do critério de parada (usando apenas o tamanho do intervalo)
        if intervX <= epsilon:
            return (False, x)
    
        ## Incrementa o k
        k = k+1
    ## Se chegar aqui é porque o número máximo de iterações foi atingido
    ## Mostrar uma mensagem de erro e retorna que houve erro e a última raiz encontrada
    print("ERRO! número máximo de iterações atingido.")
    return (True, x)

def chute_inicial():
    a = -1
    b = 2
    k = 0
    while f(a) * f(b) > 0:
        if k % 2 == 0:
            a = 2*a
            k=+1
        else:
            b = 2*b
            k=+1

    return a, b

def f(x):
    return x**3 - 9*x + 3


a, b = chute_inicial()
epsilon = 0.001
maxIter = 20

(houveErro, raiz) = bissecao(f, a, b, epsilon, maxIter)

if houveErro:
    print("O Método da Bisseção retornou um erro.")
if raiz is not None:
    print("Raiz encontrada: %e" % raiz)