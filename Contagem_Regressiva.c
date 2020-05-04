/*
Gabriel Bonatto Justo
Compilar:
    gcc Contagem_Regressiva.c -o Contagem_Regressiva
Executar:
    ./Contagem_Regressiva <n>
*/


#include <stdio.h>
#include <stdlib.h>
#include<math.h>

#define MAX (pow(2,30)-1)


int* mem;
char** res;


int contagem(int n)
{
    if (n == 1)
        return 0;
    if (n == 2)
        return 1;
    if(n==3)
        return 1;
    if ( n%2 == 0 && n%3 == 0)
    {
        int op1 = contagem(n/2);
        int op2 = contagem(n/3);
        int op3 = contagem(n-1);

        int menor = op1;
        if(op2 < menor)
            menor = op2;
        if (op3 < menor)
            menor = op3;

        return menor + 1;
    }
    if (n%2 == 0)
    {
        int op1 = contagem(n/2);
        int op2 = contagem(n-1);

        int menor = op1;
        if(op2 < menor)
            menor = op2;

        return menor + 1;
    }
    if (n%3 == 0)
    {
        int op1 = contagem(n/3);
        int op2 = contagem(n-1);

        int menor = op1;
        if(op2 < menor)
            menor = op2;

        return menor + 1;
    }

    return contagem(n-1) + 1;   
}







int contagemMem(long int n)
{
    if (n == 1)
        return 0;
    
    if (n == 2)
    {
        res[n] = "/2";
        return 1;
    } 
    if(n==3)
    {
        res[n] = "/3";
        return 1;
    }
        
    if(mem[n] > 0)
        return mem[n];
        
    if ( n%2 == 0 && n%3 == 0)
    {
        int op1 = contagemMem(n/2);
        int op2 = contagemMem(n/3);
        int op3 = contagemMem(n-1);

        int menor = op1;
        res[n] = "/2";
        if(op2 < menor)
        {
            menor = op2;
            res[n] = "/3";
        }
        if (op3 < menor)
        {
            menor = op3;
            res[n] = "-1";
        }
        mem[n] = menor +1;
        return mem[n];
    }
    if (n%2 == 0)
    {
        int op1 = contagemMem(n/2);
        int op2 = contagemMem(n-1);

        int menor = op1;
        res[n] = "/2";
        if(op2 < menor)
        {
            menor = op2;
            res[n] = "-1";
        }
        mem[n] = menor + 1;
        return mem[n];
    }
    if (n%3 == 0)
    {
        int op1 = contagemMem(n/3);
        int op2 = contagemMem(n-1);

        int menor = op1;
        res[n] = "/3";
        if(op2 < menor)
        {
            menor = op2;
            res[n] = "-1";
        }

        mem[n] = menor +1;
        return mem[n];
    }

    mem[n] = contagemMem(n-1) + 1;
    res[n] = "-1";
    
    return mem[n]; 
    
}

void caminho(long int n)
{
    printf("\ncaminho: ");
    while(n>1)
    {
        printf("%s ", res[n]);
        if(res[n] == "/2")
            n /= 2;
        else if(res[n] == "/3")
            n /= 3;
        else 
            n --;
    }
}







int percorreVetor(int n)
{
    int cont = 1;
    while (n > 1)
    {
        if (res[n] == "/2")
            n /= 2;
        else if (res[n] == "/3")
            n /= 3;
        else
            n --;
        cont ++; 
    }

    return cont;
}

int contagemNaoRec(long int n)
{
    long int* contagem = malloc(sizeof(int)* MAX);
    double menor; // tamanho do menor caminho até o 1
    char* melhorOperacao; // operação que gera o menor caminho até o 1
    int cont; // número de passos até chagar no 1

    contagem[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        menor = INFINITY;
        if (i%2 == 0 && i%3 == 0)
        {
            cont = percorreVetor(i/2);
            menor = cont;
            melhorOperacao = "/2";


            cont = percorreVetor(i/3);
            if(cont < menor)
            {
                melhorOperacao = "/3";
                menor = cont;
            }


            cont = percorreVetor(i-1);
            if(cont < menor)
            {
                melhorOperacao = "-1";
                menor = cont;
            }
                
            res[i] = melhorOperacao;
            contagem[i] = menor;

        }
        else if (i%2 == 0)
        {
            cont = percorreVetor(i/2);
            menor = cont;
            melhorOperacao = "/2";


            cont = percorreVetor(i-1);
            if(cont < menor)
            {
                melhorOperacao = "-1";
                menor = cont;
            }
                
            res[i] = melhorOperacao;
            contagem[i] = menor;

        }
        else if (i%3 == 0)
        {
            cont = percorreVetor(i/3);
            melhorOperacao = "/3";
            menor = cont;


            cont = percorreVetor(i-1);
            if(cont < menor)
            {
                melhorOperacao = "-1";
                menor = cont;
            }
                
            res[i] = melhorOperacao;
            contagem[i] = menor;

        }
        else
        {
            res[i] = "-1";
            contagem[i] = cont;
        }
    }
    return contagem[n];
    
}



int main(int argc, char* argv[])
{
    mem = malloc(sizeof(int) * MAX);
    res = (char*)malloc(sizeof(char) * MAX);
    for (int i = 0; i < MAX; i++)
        mem[i] = 0;
    

    long int n = atol(argv[1]);
    printf("--\n");
    printf("contagem não recursiva: %d \n", contagemNaoRec(n));
    caminho(n);
    // printf("contagem recursiva com memória: %d \n", contagemMem(n));
    // printf("contagem recursiva %d \n", contagem(n));
    
    printf("\n");
}