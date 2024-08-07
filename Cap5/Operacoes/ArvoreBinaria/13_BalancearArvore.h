#ifndef BALANCEAR_ARVORE_H
#define BALANCEAR_ARVORE_H

pNohArvore BalancearArvore(pNohArvore raiz)
{
    if (raiz == NULL)
        return NULL;

    // Caso 1: O nó atual é vermelho e seu filho esquerdo é vermelho
    if (raiz->cor == RED && raiz->esquerda != NULL && raiz->esquerda->cor == RED)
    {
        raiz = RotacaoDireita(raiz);
    }

    // Caso 2: O nó atual é vermelho e seu filho direito é vermelho
    if (raiz->cor == RED && raiz->direita != NULL && raiz->direita->cor == RED)
    {
        raiz = RotacaoEsquerda(raiz);
    }

    // Caso 3: O nó atual é preto e seus filhos são vermelhos
    if (raiz->cor == BLACK && raiz->esquerda != NULL && raiz->esquerda->cor == RED &&
        raiz->direita != NULL && raiz->direita->cor == RED)
    {
        InverteCor(raiz);
        InverteCor(raiz->esquerda);
        InverteCor(raiz->direita);
    }

    // Ajustar cores
    if (raiz->esquerda != NULL && raiz->esquerda->cor == RED &&
        raiz->esquerda->esquerda != NULL && raiz->esquerda->esquerda->cor == RED)
    {
        raiz = RotacaoDireita(raiz);
        InverteCor(raiz);
        InverteCor(raiz->direita);
    }

    if (raiz->esquerda != NULL && raiz->esquerda->cor == RED &&
        raiz->esquerda->direita != NULL && raiz->esquerda->direita->cor == RED)
    {
        raiz->esquerda = RotacaoEsquerda(raiz->esquerda);
        raiz = RotacaoDireita(raiz);
        InverteCor(raiz);
        InverteCor(raiz->direita);
    }

    if (raiz->direita != NULL && raiz->direita->cor == RED &&
        raiz->direita->esquerda != NULL && raiz->direita->esquerda->cor == RED)
    {
        raiz->direita = RotacaoDireita(raiz->direita);
        raiz = RotacaoEsquerda(raiz);
        InverteCor(raiz);
        InverteCor(raiz->esquerda);
    }

    if (raiz->direita != NULL && raiz->direita->cor == RED &&
        raiz->direita->direita != NULL && raiz->direita->direita->cor == RED)
    {
        raiz = RotacaoEsquerda(raiz);
        InverteCor(raiz);
        InverteCor(raiz->esquerda);
    }

    return raiz;
}

#endif