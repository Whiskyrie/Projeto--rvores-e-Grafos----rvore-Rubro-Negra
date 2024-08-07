#ifndef QTDENOHS_ARVORE_BINARIA_H
#define QTDENOHS_ARVORE_BINARIA_H

/* -------------------------------------------*/
int QuantidadeNohsRecursiva(pNohArvore raiz)
{

    if (raiz == NULL)
        return 0;

    return 1 + QuantidadeNohsRecursiva(raiz->esquerda) + QuantidadeNohsRecursiva(raiz->direita);
}

int QuantidadeNohs(pDArvore arvore)
{
    return QuantidadeNohsRecursiva(arvore->raiz);
}
#endif
