#ifndef CRIAR_ARVORE_H
#define CRIAR_ARVORE_H

pDArvore CriarArvore(int valorRaiz)
{
    pDArvore dArvore = malloc(sizeof(DArvore));
    dArvore->raiz = malloc(sizeof(NohArvore));
    dArvore->raiz->info = AlocaInt(valorRaiz);
    dArvore->raiz->esquerda = NULL;
    dArvore->raiz->direita = NULL;
    dArvore->quantidadeNohs = 1;
    dArvore->grau = 2; // Supondo que é uma árvore binária
    return dArvore;
}

#endif