#ifndef POSORDEM_ARVORE_BINARIA_H
#define POSORDEM_ARVORE_BINARIA_H

/* --------------------------*/
void PosOrdem(pNohArvore raiz, FuncaoImpressao fi)
{
    if (raiz != NULL)
    {
        PosOrdem(raiz->esquerda, fi);
        PosOrdem(raiz->direita, fi);
        fi(raiz->info);
    }
}
#endif
