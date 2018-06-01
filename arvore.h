#include <stdlib.h>
#include <string.h>

typedef struct NoArvore
{
	int Valor;
	char string[50];
	struct NoArvore *E; 
	struct NoArvore *D;
}NoArvore;

typedef struct Arvore
{
	NoArvore *Raiz;
	int Tamanho;
}Arvore;

Arvore* ArvoreNovo(void)
{
	Arvore *a = (Arvore*)malloc(sizeof(Arvore));
	a->Raiz = NULL;
	a->Tamanho = 0;
	
	return a;
}

int ArvoreInserir(Arvore *a, int Valor, char string[])
{
	if(a == NULL)
		return 0;
	
	NoArvore *no = (NoArvore*)malloc(sizeof(NoArvore));
	
	if(no == NULL)
		return 0;
	
	strcpy(no->string, string); //inserindo a string no nó
	//printf("no->String = %s\n", no->string);
	
	no->Valor = Valor;
	no->E = NULL;
	no->D = NULL;
	
	NoArvore *atual = a->Raiz;
	NoArvore *pai = NULL;
	
	while(atual != NULL)
	{
		pai = atual;
		if(no->Valor < atual->Valor)
		{
			atual = atual->E;
		}
		else
		{
			if(no->Valor == atual->Valor && strcmp(no->string, atual->string) == 0){/*Verificação para não inserir palavras repetidas*/
				return 1;
			}
			else	
				atual = atual->D;	
		}	
	}
	
	if(pai == NULL)
	{
		a->Raiz = no; //inserir na raiz
	}
	else if(Valor < pai->Valor)
	{
		pai->E = no;
	}
	else
	{
		pai->D = no;
	}
	
	//printf("no->Valor = %d\n", no->Valor);
	a->Tamanho++;
	
	return 1;
}

int ArvoreRemover(Arvore *a, int Valor)
{
	if(a == NULL || a->Tamanho == 0)
	{
		return 0;
	}
	
	NoArvore *atual = a->Raiz; //aponta para o elemento a ser removido;
	NoArvore *pai = NULL; //aponta para o pai do elemento a ser removido;
	
	while(atual != NULL && atual->Valor != Valor)
	{
		pai = atual;
		
		if(Valor < atual->Valor)
		{
			atual = atual->E;
		}
		else
		{
			atual = atual->D;
		}
	}
	
	if(atual == NULL)
	{
		//não encontrei o elemento 
		return 0;
	}
	
	if(atual->E == NULL && atual->D == NULL)
	{
		//remoção de nó folha
		
		if(pai == NULL)
		{
			//remoção da raiz
			a->Raiz = NULL;	
		}		
		else if(Valor < pai->Valor)
		{
			pai->E = NULL;
		}
		else
		{
			pai->D = NULL;
		}		
	}
	
	else if(atual->E != NULL && atual->D == NULL)
	{
		//nó com filho apenas à esquerda
		
		if(pai == NULL)
		{
			//remoção da raiz			
			a->Raiz = atual->E;
		}
		else if(Valor < pai->Valor)
		{
			pai->E = atual->E;
		}
		else
		{
			pai->D = atual->E;
		}
	}
	
	else if(atual->E == NULL && atual->D != NULL)
	{
		//nó com filho apenas à direita
		
		if(pai == NULL)
		{
			//remoção da raiz
			a->Raiz = atual->D;
		}
		else if(Valor < pai->Valor)
		{
			pai->E = atual->D;
		}
		else
		{
			pai->D = atual->D;
		}
	}
	
	else
	{
		//nó com ambos os filhos
		NoArvore *substituto = atual->E; //substituto do nó a ser removido
		NoArvore *paiSubstituto = atual;
		
		while(substituto->D != NULL)
		{
			paiSubstituto = substituto;
			substituto = substituto->D;
		}
		
		if(paiSubstituto != atual)
		{
			paiSubstituto->D = substituto->E;
			substituto->E = atual->E;
		}	
		
		substituto->D = atual->D;
		
		if(pai == NULL)
		{
			a->Raiz = substituto;
		}
		else if(Valor < pai->Valor)
		{
			pai->E = substituto;
		}
		else
		{
			pai->D = substituto;
		}
	}
			
	free(atual);
	atual = NULL;
	a->Tamanho--;
			
	return 1;
}

int ArvoreDestruir(Arvore *a){
	while(a->Raiz != NULL){
		ArvoreRemover(a, a->Raiz->Valor);
	}
	return 0;
}
	
