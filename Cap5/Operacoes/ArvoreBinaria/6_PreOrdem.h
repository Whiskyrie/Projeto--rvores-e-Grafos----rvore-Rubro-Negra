#ifndef PREORDEM_ARVORE_BINARIA_H
#define PREORDEM_ARVORE_BINARIA_H

/* --------------------------*/
void PreOrdem(pNohArvore raiz, FuncaoImpressao fi)
{
    if (raiz != NULL)
    {
        fi(raiz->info);
        PreOrdem(raiz->esquerda, fi);
        PreOrdem(raiz->direita, fi);
    }
}

#endif
