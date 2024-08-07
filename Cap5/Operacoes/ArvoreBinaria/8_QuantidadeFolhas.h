#ifndef QTDEFOLHAS_ARVORE_BINARIA_H
#define QTDEFOLHAS_ARVORE_BINARIA_H

/* -------------------------------------------*/
int QuantidadeFolhasRecursiva(pNohArvore raiz)
{
   if (raiz == NULL)
      return 0;

   if (raiz->esquerda == NULL && raiz->direita == NULL)
      return 1; /*  É uma folha */

   return QuantidadeFolhasRecursiva(raiz->esquerda) + QuantidadeFolhasRecursiva(raiz->direita);
}

int QuantidadeFolhas(pDArvore arvore)
{
   return QuantidadeFolhasRecursiva(arvore->raiz);
}
#endif
