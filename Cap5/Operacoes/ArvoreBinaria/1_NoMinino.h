#ifndef NOMINIMO_H
#define NOMINIMO_H

pNohArvore NoMinimo(pNohArvore raiz)
{
    if (raiz == NULL)
        return NULL;

    pNohArvore aux = raiz;
    pNohArvore antecessor = NULL;

    while (aux->esquerda != NULL)
    {
        antecessor = aux;
        aux = aux->esquerda;
    }

    // Troca as informações
    if (antecessor != NULL)
    {
        void *temp_info = antecessor->esquerda->info;
        antecessor->esquerda->info = raiz->info;
        raiz->info = temp_info;
    }
    else
    {
        // Caso em que o próprio nó é o menor
        raiz->info = aux->info;
    }

    return aux;
}

#endif