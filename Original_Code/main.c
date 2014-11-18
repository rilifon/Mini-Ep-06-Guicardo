/*
  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
  E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
  POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
  REPROVAÇÃO DIRETA NA DISCIPLINA.

  Nome: Guilherme Souto Schützer
  NUSP: 8658544

  IMDB: main.c 


  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:
  - função mallocc retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/


#include <stdio.h>  /* printf(), scanf() */ 
#include <time.h>   /* CLOCKS_PER_SECOND */
#include <string.h>

#include "main.h"

/* crieListaFilmes(), crieFilme(), insiraFilme(),  mergeSortFilmes() */
#include "filmes.h" 

/* carregueListaFilmes(), graveListaFilmes(), mostreFilme(), mostreListaFilmes() */
#include "iofilmes.h" 

#include "utils.h"    /* mallocSafe(), leiaString() */

/* imprime uma linha com tracos */
#define LINHA  printf("------------------------------------------"\
                      "--------------------------------------\n")



/*------------------------------------------------------------------- 
  P R O T O T I P O S 
*/

/* A funcao leiaOpcao so e usada neste arquivo. */
static char  leiaOpcao(); 


/*------------------------------------------------------------------- 
    M A I N 
*/
int 
main(int argc, char *argv[])
{
    ListaFilmes *lst = crieListaFilmes(); 
    char         opcao;
    clock_t start, end; /* usadas para medir tempo de processamento */
    double elapsed;
    /* declaracao das demais variaveis do main */

    /*-----------------------------------------------------*/
    /* iterara ate o usuario digitar 'x' para sair         */
    do 
    { 

	opcao = leiaOpcao();

	/* comeca a cronometrar */
	start = clock(); 

	switch (opcao) 
	{
	    /*---------------------------------------------*/
	case CARREGAR:
	{
	    carregueListaFilmes(lst);
	    break;
	}  
	    /*---------------------------------------------*/
	case GRAVAR:
	{
	    graveListaFilmes(lst);
	    break;
	}

	    /*---------------------------------------------*/
	case PROCURAR:
	{
		Filme *p; /* ponteiro auxiliar */

		char parte[TAM_STR+1]; /* entrada de parte do nome */
		char c = 'n'; /* entrada de opcao (s/n/x) */
		int  tParte, tNome; /* tamanho das strings */

		printf("Digite parte do nome a ser procurado: ");
		tParte = leiaString(parte, TAM_STR);


		p = lst->cab->prox;

		/* loop enquanto c == 'n' */

		do{
			/* pergunta se é o filme caso haja a parte procurada em seu nome */
			tNome  = strlen(p->nome);

			if(achePalavra((unsigned char*) parte, tParte, (unsigned char*) p->nome, tNome) == TRUE)
			{
				mostreFilme(p);

				printf("Esse é o filme procurado? [s/n/x] (x para sair): ");
				scanf(" %c", &c);

				/* sai da opcao caso c == 'x' */

				if (c == 'x') break;
			}

			/* passa para o próximo filme */

			if(c == 'n')
				p = p->prox;

		}while (c == 'n' && p != lst->cab);

		/* caso p tenha "dado a volta" na lista, sem sucesso */

		if (p == lst->cab)
		{
			printf("\nO filme desejado nao foi encontrado.\n");
		}

	    break;
	}

	    /*---------------------------------------------*/

	case INSERIR:
	{
	    Filme       *flm = NULL;      

	    char  dist[TAM_DIST+1];  
	    int   votos;             
	    float nota;              
	    char  nome[TAM_STR+1];   
	    int   ano;               

	    printf("Digite o nome do filme: ");
	    leiaString(nome, TAM_STR);

	    printf("Digite o ano: ");
	    scanf("%d", &ano);

	    printf("Digite a nota: ");
	    scanf("%f", &nota);

	    printf("Digite o numero de votos: "); 
	    scanf("%d", &votos);

	    printf("Digite a distribuicao: ");
	    leiaString(dist, TAM_DIST+1);
   
	    flm = crieFilme(dist, votos, nota, nome, ano);
	    mostreFilme(flm);

		/* insere o filme criado na lista */

	    insiraFilme(lst, flm);

	    break;
	}

	    /*---------------------------------------------*/
		/* Funciona igual a PROCURAR, com a diferença (1) */

	case REMOVER:
	{
		Filme *p; 

		char parte[TAM_STR+1];
		char c = 'n';
		int  tParte, tNome;


		printf("Digite parte do nome a ser procurado: ");
		tParte = leiaString(parte, TAM_STR);

		p = lst->cab->prox;


		do{
			tNome  = strlen(p->nome);

			if(achePalavra((unsigned char*) parte, tParte, (unsigned char*) p->nome, tNome) == TRUE)
			{
				mostreFilme(p);

				printf("Esse é o filme procurado? [s/n/x] (x para sair): ");
				scanf(" %c", &c);

				if (c == 'x') break;
			}

			if (c == 'n')
				p = p->prox;

		}while (c == 'n' && p != lst->cab);

		/* (1) Remove o filme caso seja este o procurado */

		if (p != lst->cab && c == 's')
		{
			removaFilme(lst, p);
			libereFilme(p);
		}

		else
		{
			printf("\nO filme desejado nao foi encontrado.\n");
		}

	    break;
	}

      	    /*---------------------------------------------*/
	case ORDENAR_NOTA_M:
	{

		/* chama a função mergeSortFilmes para ordenar por nota */

		mergeSortFilmes(lst, NOTA);

	    break;
	}

      	    /*---------------------------------------------*/
	case ORDENAR_NOME_M:
	{
		
		/* chama a função mergeSortFilmes para ordenar por nota */

		mergeSortFilmes(lst, NOME);

	    break;
	}

      	    /*---------------------------------------------*/
	case ORDENAR_NOTA_Q:
	{
		quickSortFilmes(lst, NOTA);

	    break;
	}

      	    /*---------------------------------------------*/
	case ORDENAR_NOME_Q:
	{
		quickSortFilmes(lst, NOME);

	    break;
	}

	    /*---------------------------------------------*/
	case MOSTRAR:
	{
		/* chama a funcao mostreListaFilmes */

		mostreListaFilmes(lst);

	    break;
	}

	    /*---------------------------------------------*/
	case MOSTRAR_MENOR:
	{	

		/* ordena a lista por nota e chama a funcao para mostrar utilizando os criterios requisitados */

		mergeSortFilmes(lst, NOTA);
		mostreMelhoresFilmes(lst);

	    break;
	}

	    /*---------------------------------------------*/
	case MOSTRAR_MAIOR:
	{

		/* análogo ao caso anterior */

		mergeSortFilmes(lst, NOTA);
		mostrePioresFilmes(lst);

	    break;
	}
      
	    /*---------------------------------------------*/
	case LIMPAR:
	{

		/* limpa a lista */

		libereListaFilmes(lst);

	    break;
	}

      	    /*---------------------------------------------*/
	case SAIR:
	{

		/* libera o que foi alocado durante a execução do programa */

		libereListaFilmes(lst);

	    break;
	}

	default :
	{
	    printf("main: opcao '%c' nao reconhecida\n", opcao);
	    break;
	}
	
	} /* switch */
	
	/* trava o cronometro */  
	end = clock();
	
	/* calcula o tempo */
	elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\n(%g segundos)\n", elapsed);

    } 
    while (opcao != SAIR);

	LINHA;
	printf("Mensagem dos nossos patrocinadores:\n"
	"\nKids are like buckets of disease that live in your house.\n"
	"                   -- Louis C.K.\n");


    return 0;
}


/*---------------------------------------------------------------------
  leiaOpcao()
   
  Le e retorna o caractere correspondente a opcao do usuario.
*/

char 
leiaOpcao()
{
    char opcao;

    printf(
	"\n================================================"
	"======================\n"
	"  (c) carregar um arquivo de dados\n"
	"  (g) gravar a lista atual em um arquivo\n"
	"  (p) procurar a nota de um filme\n"
	"  (i) inserir um filme\n"
	"  (r) remover um filme\n"
	"  (o) ordenar a lista de filmes por nota (mergeSort)\n"
	"  (O) ordenar a lista de filmes por nome (mergeSort)\n"
	"  (q) ordenar a lista de filmes por nota (quickSort, opcional)\n"
	"  (Q) ordenar a lista de filmes por nome (quickSort, opcional)\n"
	"  (m) mostrar todos os filmes\n"
	);

    printf(
	"  (<) mostrar N filmes com nota _menor_ que X e pelo menos V votos\n"
	"  (>) mostrar N filmes com nota _maior_ que X e pelo menos V votos\n"
	"  (l) limpar a lista de filmes\n"
	"  (x) sair do programa\n\n"
	);
    printf("Digite uma opcao: ");
    scanf(" %c", &opcao);

  /* main.c: warning: string length ‘679’ is greater than the length 
     ‘509’ ISO C90 compilers are required to support 
     [-Woverlength-strings] */

    return opcao;
}


