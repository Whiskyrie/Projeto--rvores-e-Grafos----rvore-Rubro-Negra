#ifndef ENCONTRAMENOR_H
#define ENCONTRAMENOR_H

pNohArvore EncontrarMenor(pNohArvore raiz)
{
    if (raiz == NULL)
        return NULL;

    if (raiz->esquerda == NULL)
    {
        return raiz;
    }

    return EncontrarMenor(raiz->esquerda);
}

#endif