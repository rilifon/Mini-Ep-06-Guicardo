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

  IMDB: filmes.c


  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:
  - função mallocc retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/


/*----------------------------------------------------------*/
/* filmes.h e a interface para as funcoes neste modulo      */
#include "filmes.h" 

/*----------------------------------------------------------*/
#include <stdlib.h>  /* NULL, free() */
#include <stdio.h>   /* printf(), scanf() */ 
#include <string.h>  /* strlen(), strncpy(), strcmp() */

#include "utils.h"     /* Bool, mallocSafe() */
#include "iofilmes.h"

/*----------------------------------------------------------------------
    crieFilme(dist, votos, nota, nome, ano)

    Recebe informacoes dobre um filme 

        - dist  : distribuicao de notas
        - votos : numero de votos
        - nota  : nota do filme 
        - ano   : ano de producao do filme

    e cria uma celula do tipo Filme para armazenar essa informacao. 
    A funcao retorna o endereco da celula criada.
*/

Filme *
crieFilme (char dist[], int votos, float nota, char *nome, int ano)
{
    Filme *flm;
    int    len = strlen(nome) + 1; /* +1 para o '\0' */
    
    flm = mallocSafe(sizeof *flm);
    
    strncpy(flm->dist, dist, TAM_DIST+1); /* +1 para o '\0' */
    
    flm->votos = votos;
    flm->nota  = nota;
    
    flm->nome = mallocSafe(len*sizeof(char));
    strncpy(flm->nome, nome, len);
    
    flm->ano  = ano;
    
    flm->prox = flm->ant = NULL; /* paranoia */
    
    return flm;
 
}



/*----------------------------------------------------------------------
    crieListaFilmes()
  
    Cria uma estrutura que representa lista de filmes vazia.
    A funcao retorna o endereco dessa estrutura.

    Um lista de filmes e representada por uma lista encadeada 
    com cabeca duplamente ligada. 
*/

ListaFilmes *
crieListaFilmes()
{
    ListaFilmes *lst;
    
    lst =  mallocSafe(sizeof *lst);

    lst->nFilmes = 0;   
    lst->cab = mallocSafe(sizeof *lst->cab);

    lst->cab->ant  = lst->cab->prox = lst->cab;
    
    return lst;
}


/*----------------------------------------------------------------------
    libereListaFilmes(lst)

    Recebe um ponteiro lst para uma estrutura que representa uma lista 
    de filmes e libera toda a memoria alocada para a lista.

    Esta funcao utiliza a funcao libereFilme().
*/

void
libereListaFilmes(ListaFilmes *lst)
{
  Filme *p, *morta;   /* ponteiros: de navegação e a ser liberado */

  p = lst->cab->prox; /* inicializa p */

  while (lst->nFilmes > 0) /* libera-se até que o tamanho da lista seja 0 */
  {

    morta = p; /* morta recebe o endereco do filme a liberar */

    p = p->prox; /* p é "incrementado" em 1 */

    removaFilme(lst, morta); /* remove *morta */

    libereFilme(morta); /* libera *morta */

    lst->nFilmes--; /* decresce em um o número de filmes da lista */
  }

  return;
}


/*----------------------------------------------------------------------
    libereFilme(flm)

    Recebe um ponteiro flm para uma estrutura que representa um 
    filme e libera a area alocada.

*/

void 
libereFilme(Filme *flm)
{
  free(flm->nome); /* libera o vetor nome */
  free(flm);       /* libera o filme apontado por flm */
  flm = NULL;      /* narapoia */
  return;
}

/*----------------------------------------------------------------------
    insiraFilme(lst, flm)

    Recebe um ponteito lst para uma estrutura que representa
    uma lista de filmes e um ponteiro para uma estrutura
    que representa uma filme.

    A funcao insere o filme na lista.
    
*/

void 
insiraFilme(ListaFilmes *lst, Filme *flm)
{
  Filme *p; /* ponteiro de navegação */

  p = lst->cab->ant; /* inicializa p  na última posição da lista*/

  p->prox = flm; /* próxima célula recebe flm */
  flm->ant = p;  /* campo ant de flm recebe p */
  flm->prox = lst->cab; /* campo prox de flm recebe a cabeca */
  lst->cab->ant = flm; /* campo ant da cabeca recebe flm */

  lst->nFilmes++; /* incremento no número de filmes */

  return;
}


/*---------------------------------------------------------------------
    contemFilme(lst, flm)

    Recebe um ponteito lst para uma estrutura que representa
    uma lista de filmes e um ponteiro para uma estrutura
    que representa uma filme.
  
    A funcao retorna  TRUE se o filme esta na lista e 
    FALSE em caso contrario. 
  
    Consideramos que dois filmes f e g sao iguais se

         - f->nome  e' igual a g->nome )
         - f->nota  e' igual a g->nota
         - f->ano   e' igual a g->ano 

    Para comparar dois nomes voce pode usar alguma funcao da 
    bibliteca do c  como strcmp, strncmp (string,h) 
    ou a funcao strCmp (utils.h).

*/

Bool 
contemFilme(ListaFilmes *lst, Filme *flm)
{
  Filme *p; /* ponteiro de navegação */

  p = lst->cab->prox; /* incializa o ponteiro */

  while (p != lst->cab) /* percorre a lista */
  {
    /* Caso: */

    if (strCmp(p->nome, flm->nome) == 0 && /* o nomes */
        p->nota == flm->nota &&            /* as notas */
        p->ano  == flm->ano)               /* e os anos 
        dos filmes apontados por p e flm sejam iguais,
        retorna TRUE */
    return TRUE;

    p = p->prox; /* "incremento" de p em 1 */

  }

  /* se chegar aqui, é sinal que não contém o filme */

  return FALSE;
}


/*----------------------------------------------------------------------
     removaFilme(lst, flm)

     Remove da lista e filmes lst o filme dado por flm.
     
     Pre-condicao: a funcao supoe que o filme flm esta 
           na lista lst.
*/

void 
removaFilme(ListaFilmes *lst, Filme *flm)
{
  Filme *p; /* ponteiro de navegação */

  p = flm->ant; /* p inicializa na posição anterior a flm */
  p->prox = flm->prox; /* próximo de p deixa de ser flm, passa a ser flm->prox */
  flm->prox->ant = p; /* anterior a flm->prox passa a ser p */

  lst->nFilmes--; /* decréscimo em 1 do número de filmes na lista */

  return;
}


/*----------------------------------------------------------------------
    mergeSortFilmes(lst, criterio)

    Ordena uma lista de filmes utilizando o algoritmo mergeSort 
    recursivo adaptado para listas encadeadas duplamente ligadas.

    Se criterio == NOTA, entao a lista deve ser ordenada
    em ordem decrescente de nota.
  
    Se criterio == NOME, entao a lista deve ser ordenada
    em ordem crescente de nome (ordem alfabetica).

    ------------------------------------------------------------------
    A ordenacao deve ser feita 'in-place', ou seja   
    o conteudo das celulas nao deve ser copiado,  
    apenas os ponteiros devem ser alterados.

    A funcao so deve utilizar espaco extra O(1).
    (Hmmm, ok, sem levar em consideracao o espaco O(lg n)
    utilizado pela pilha da recursao).
    Em outras palavras, a funcao pode conter apenas declaracoes
    de umas poucas variaveis (um vetor v[0..n] conta como 
    n variaveis).

    ------------------------------------------------------------------
    Para ordenar por nome, veja a funcao strCmp em utils.[h|c].
*/

/*----------------------------------------------------------------------
    A função foi implementada com base na aula 20 de MAC0122
*/

void 
mergeSortFilmes(ListaFilmes *lst, Criterio criterio)
{

  Filme          *p; /* ponteiro para navegacao na listas */
  ListaFilmes    *e, *d; /* listas auxiliares (parte esquerda e direita) */

  int  tamanho; /* recebe o tamanho de lst */
  int        i; /* contador */

  /* inicializa tamanho */

  tamanho = lst->nFilmes;

  if (tamanho <= 1)
    return;

  /* inicializa listas auxiliares */
  
  e = crieListaFilmes();
  d = crieListaFilmes();

  e->nFilmes = d->nFilmes = 0;

  /* inicializa ponteiro */

  p  = lst->cab->prox; 

  /* insere a primeira metade de lst na lista da esquerda */
  /* caso tamanho%2 = 1, adiciona a metade arredondada para cima */

  for(i = 0; i < tamanho/2 + tamanho%2; i++)
  {
    removaFilme(lst, p); /* remove *p de lst */
    insiraFilme(e, p);   /* insere o filme *p em e */
    p = lst->cab->prox;
  }


  /* insere a segunda metade de lst na lista da direita */

  for(i = 0; i < tamanho/2; i++)
  {

    /* análogo às inserções na lista e */

    removaFilme(lst, p);
    insiraFilme(d, p);
    p = lst->cab->prox;
  }

  /* chamadas recursivas para a lista da esquerda e da direita */

  mergeSortFilmes(e, criterio);
  mergeSortFilmes(d, criterio);

  /* intercala em ordem crescente a lista da esquerda e da direita em lst */

  intercala(lst, e, d, criterio);

  /* libera as listas auxiliares */

  libereListaFilmes(e);
  libereListaFilmes(d);

  return;
}


/*----------------------------------------------------------------------
    intercala(lst, e, d, criterio)
    
    Função auxiliar para o mergeSortFilmes:

    Recebe três listas e intercala os filmes das duas últimas 
    em ordem decrescente de nota ou crescente de nome na primeira.
    Campo criterio muda o criterio de comparacao para ordem.
 
*/

void
intercala(ListaFilmes *lst, ListaFilmes *e, ListaFilmes *d, Criterio criterio)
{

  Filme *p;

  /* intercala até que e e d estejam vazias */

  while (e->nFilmes > 0 || d->nFilmes > 0)
  {
    switch (criterio){

      case NOTA:  /* caso criterio == NOTA, (1) */
      {

        /* insere intercalado na ordem caso ambas e e d não estejam vazias */

        if (e->nFilmes > 0 && d->nFilmes > 0){ 

          /* (1) ordem é determinada pela menor nota */

          if (e->cab->prox->nota >= d->cab->prox->nota)
          {
            p = e->cab->prox;
            removaFilme(e, e->cab->prox);
            insiraFilme(lst, p);
          }

          else
          {
            p = d->cab->prox;
            removaFilme(d, d->cab->prox);
            insiraFilme(lst, p);
          }
        }

        /* insere o resto dos filmes caso e->nFilmes > 0 e d->nFilmes == 0 */

        else if(e->nFilmes > 0)
        { 
          p = e->cab->prox;
          removaFilme(e, e->cab->prox);
          insiraFilme(lst, p);
        }

        /* insere o resto dos filmes caso d->nFilmes > 0 e e->nFilmes == 0 */

        else if(d->nFilmes > 0)
        {
          p = d->cab->prox;
          removaFilme(d, d->cab->prox);
          insiraFilme(lst, p);
        }

        break;

      }

      case NOME: /* caso criterio == NOME, (2) */
      {

        /* insere intercalado na ordem caso ambas e e d não estejam vazias */

        if (e->nFilmes > 0 && d->nFilmes > 0)
        {

          /* ordem é determinada pelo alfabeto */
          /* (se strCmp(str 1, str 2) < 0, a string 1 é lexicograficamente menor que a string 2) */


          if (strCmp(e->cab->prox->nome, d->cab->prox->nome) <= 0)
          {
            p = e->cab->prox;
            removaFilme(e, e->cab->prox);
            insiraFilme(lst, p);
          }
          else
          {
            p = d->cab->prox;
            removaFilme(d, d->cab->prox);
            insiraFilme(lst, p);
          }
        }

        /* o resto desse caso é análogo ao caso anterior (criterio == NOTA) */

        else if(e->nFilmes > 0)
        {
          p = e->cab->prox;
          removaFilme(e, e->cab->prox);
          insiraFilme(lst, p);
        }

        else if(d->nFilmes > 0)
        {
          p = d->cab->prox;
          removaFilme(d, d->cab->prox);
          insiraFilme(lst, p);
        }

        break;

      }
    }
  }

  return;

}



/*----------------------------------------------------------------------
    quickSortFilmes(lst, criterio) [opcional]

    Ordena uma lista de filmes utilizando o algoritmo quickSort 
    adaptado para listas encadeadas duplamente ligadas.

    Se criterio == NOTA, entao a lista deve ser ordenada
    em ordem decrescente de nota.

    Se criterio == NOME, entao a lista deve ser ordenada
    em ordem crescente de nome (ordem alfabetica).

    ------------------------------------------------------------------
    A ordenacao deve ser feita 'in-place', ou seja   
    o conteudo das celulas nao deve ser copiado,  
    apenas os ponteiros devem ser alterados.

    A funcao so deve utilizar espaco extra O(1).
    Hmmm, ok, sem levar em consideracao o espaco O(lg n)
    utilizado pela pilha da recursao).
    Em outras palavras, a funcao pode conter apenas declaracoes
    de umas poucas variaveis (um vetor v[0..n] conta como 
    n variaveis).

    ------------------------------------------------------------------
    Para ordenar por nome, veja a funcao strCmp em utils.[h|c].

*/

/*----------------------------------------------------------------------
  qSort foi feito como adaptação do algoritmo quickSort
  apresentado em aula (aula 21). quickSortFilmes chama a função

*/

void 
quickSortFilmes(ListaFilmes *lst, Criterio criterio)
{

  int i;
  i = lst->nFilmes + 1;

  /* primeiro p = 1 e primeiro r = nFilmes + 1 */

  qSort(1, i, lst, criterio);
  return;  
}

void
qSort(int p, int r, ListaFilmes *lst, Criterio criterio)
{
  if (p < r-1)
  {
    int q = separa (p, r, lst, criterio);
    qSort(p, q, lst, criterio);
    qSort(q+1, r, lst, criterio);
  }
  return;
}

int
separa(int p, int r, ListaFilmes *lst, Criterio criterio)
{

  /* ponteiros que relacionam p, r, i e j com as posicoes na lista */

  Filme *ptrP, *ptrR, *ptrI, *ptrJ;
  Filme *aux;
  int i = p-1, j, x;

  /* incializa os ponteiros */

  ptrP = ptrR = ptrI = ptrJ = lst->cab;

  /* equivalente a relacionar o índice com o conteúdo */

  j = p;

  percorre(ptrP, p);
  percorre(ptrR, r);
  percorre(ptrI, i);
  percorre(ptrJ, j);

  /* equivalente a x = v[r-1] */

  if(criterio == NOTA)
    x = ptrR->ant->nota;

  for(j = p; j < r; j++)
  {
    switch (criterio)
    {
      case NOTA:
      {
        /* caso nota apontada por ptrJ <= x */

        if (ptrJ->nota <= x)
        {

          /* equivalente a t = v[++i] */

          ptrI = ptrI->prox;
          i++;
          aux = ptrI;

          /* equivalente a v[i] = v[j] */

          ptrI->ant = ptrJ->ant;
          ptrI->prox = ptrJ->prox;

          /* equivalente a v[ptrJ] = t */

          ptrJ->prox = aux->prox;
          ptrJ->ant = aux->ant;
        }
      }

      case NOME:
      {

        /* análogo ao caso anterior */

        if (strCmp(ptrJ->nome, ptrR->ant->nome) <= 0)
        {

          ptrI = ptrI->prox;
          i++;
          aux = ptrI;

          ptrI->ant = ptrJ->ant;
          ptrI->prox = ptrJ->prox;

          ptrJ->prox = aux->prox;
          ptrJ->ant = aux->ant;

        } 
      }
    }
    ptrJ = ptrJ->prox;
  }

  return i;

}

/* função que percorre a lista com o
ponteiro conforme o índice i */

void
percorre(Filme *flm, int i)
{
  int cont;
  for(cont = -1; cont < i; cont++)
    flm = flm->prox;
}

