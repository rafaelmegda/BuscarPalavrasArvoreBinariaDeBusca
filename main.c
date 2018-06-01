#include <stdio.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"

int main(void){
	
	FILE *arq = fopen("listapalavras.txt", "r");
	if(arq == NULL){
		printf("Erro! Nao foi possivel abrir o arquivo.\n");
		return 1;
	}
		
	Arvore *a = ArvoreNovo(); /*Arvore*/
	/*inserir o dicionario na arvore somando o valor de seus caracteres*/
	char info[50]; /*Vetor que receberá a linha na função fgets*/
	while( (fgets(info, sizeof(info), arq))!= NULL ){
		int i = 0, c = 0; /*contador e variavel que armazena a soma dos caracteres da linha, respectivamente*/
		while(i < strlen(info)-1){/* -1, pois o fgets captura também \n, dessa forma, evita a soma de +10 ao valor*/
			c = c + info[i];
			i++;
		}
		ArvoreInserir(a, c, info);
	}

	while(a){
		system("cls");
		printf("Digite ! para sair a qualquer momento.\n>> ");
		char palavra[45];
		scanf("%s", palavra);
		
		/*Conversão de maiusculo para minusculo*/
		int i = 0;
		for(i = 0; i < strlen(palavra); i++){
			if(palavra[i] >= 65 && palavra[i] < 90){ /*Valores decimais respectivos aos caracteres 'A' e 'Z' em ASCII*/
				palavra[i] += 32; /*Valor necessario para realizar a conversão*/
			}
			if(palavra[i] == '!'){ /*fechar programa*/
				ArvoreDestruir(a);
				fclose(arq);
				return 0;
			}
		}
		

		Lista *aux = ListaNovo(); /*Lista auxiliar 'resposta'*/

		int asc = 0;
		i = 0;
		while(i < strlen(palavra)){
			asc = asc + palavra[i]; /*armazenando o valor da soma dos caracteres digitados pelo usuario*/
			i++;
		}
		
		NoArvore *temporario = a->Raiz; /*criando o Nó Temporario que percorre a Arvore*/	
		int totalAnagramas = 0;
				
		while(temporario){
	
			if(asc == temporario->Valor && strlen(palavra) == strlen(temporario->string)-1){ /* -1 para evitar o \n no final da string por conta fgets*/
				i = 0;
				while(i < strlen(temporario->string)-1){ /* -1 para evitar o \n no final da string temporario por conta fgets*/
					ListaInserir(aux, temporario->string[i]); /*inserindo elementos na lista aux*/
					i++;
				}

				i = 0;
				while(i <strlen(palavra)){
					ListaRemover(aux, palavra[i]);
					i++;
				}
				if(aux->Quantidade == 0){ /*se a Lista auxiliar estiver vazia, a palavra é válida*/
					printf("%s\n", temporario->string);
					totalAnagramas += 1;
				}
				
				/*reiniciando a Lista auxiliar*/
				ListaDestruir(aux);	
				aux = NULL;
				aux = ListaNovo();
			}
	
			if(asc < temporario->Valor){ /*navega pela arvore procurando valores iguais a soma total da string palavra*/
				temporario = temporario->E;
			}else{
				temporario = temporario->D;
			}
		}
		if(totalAnagramas == 0){
			printf("\nNao ha ocorrencias de anagramas contendo essas letras!\n\n");
		}
		/*printf("%d\n", totalPesquisas); /*numero de ocorrências onde a soma dos caracteres são iguais*/
		system("pause");
	}
	
	/*fechando o programa*/
	ArvoreDestruir(a);
	fclose(arq);
	return 0;
}
