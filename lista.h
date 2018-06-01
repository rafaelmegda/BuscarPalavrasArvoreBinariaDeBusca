#include <stdlib.h>

typedef struct NoLista
{
	int Valor;
	struct NoLista *Proximo;
}NoLista;

typedef struct Lista
{
	NoLista *Primeiro;
	int Quantidade;
}Lista;

Lista* ListaNovo(void)
{
	Lista *l = (Lista*)malloc(sizeof(Lista));
	l->Primeiro = NULL;
	l->Quantidade = 0;
	return l;
}

int ListaVazio(Lista *l)
{
	if(l == NULL || l->Quantidade > 0)
		return 0;
	
	return 1;
}

int ListaInserir(Lista *l, int Valor)
{
	if(l == NULL)
		return 0;
		
	NoLista *no = (NoLista*)malloc(sizeof(NoLista));
	
	if(no == NULL)
		return 0;
		
	no->Valor = Valor;
	
	NoLista *atual = l->Primeiro;
	NoLista *anterior = l->Primeiro;
	
	while(atual != NULL && atual->Valor < Valor)
	{
		anterior = atual;
		atual = atual->Proximo;
	}
	
	if(atual == anterior)
	{
		no->Proximo = l->Primeiro;
		l->Primeiro = no;
	}
	else
	{
		no->Proximo = atual;
		anterior->Proximo = no;
	}
	
	l->Quantidade++;
	return 1;
}

int ListaRemover(Lista *l, int Valor)
{
	if(l == NULL || l->Quantidade == 0)
		return 0;
	
	NoLista *atual = l->Primeiro;
	NoLista *anterior = l->Primeiro;
	
	while(atual != NULL && atual->Valor < Valor)
	{
		anterior = atual;
		atual = atual->Proximo;	
	}	
	
	if(atual == NULL || atual->Valor != Valor)
	{
		//Não encontrei o valor para remover
		return 0;
	}
	
	if(anterior == atual)
	{
		//remoção no início
		l->Primeiro = atual->Proximo;
	}
	else
	{
		//remoção no meio ou no final
		anterior->Proximo = atual->Proximo;		
	}
			
	free(atual);
	atual = NULL;
	l->Quantidade--;		
		
	return 1;
}

void ListaDestruir(Lista *l)
{
	if(l == NULL)
		return;
	
	while(!ListaVazio(l))
	{
		ListaRemover(l, l->Primeiro->Valor);
	}
	
	free(l);
	l = NULL;
}

