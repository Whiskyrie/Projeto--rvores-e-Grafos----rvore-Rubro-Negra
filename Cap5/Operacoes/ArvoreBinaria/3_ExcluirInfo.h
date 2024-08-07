#ifndef EXCLUIR_INFO_H
#define EXCLUIR_INFO_H

// Funções auxiliares
pNohArvore RotacaoEsquerdaExclusao(pNohArvore *raiz, pNohArvore x)
{
    pNohArvore y = x->direita;
    x->direita = y->esquerda;
    if (y->esquerda != NULL)
        y->esquerda->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL)
        *raiz = y;
    else if (x == x->pai->esquerda)
        x->pai->esquerda = y;
    else
        x->pai->direita = y;
    y->esquerda = x;
    x->pai = y;
    return y;
}

pNohArvore RotacaoDireitaExclusao(pNohArvore *raiz, pNohArvore y)
{
    pNohArvore x = y->esquerda;
    y->esquerda = x->direita;
    if (x->direita != NULL)
        x->direita->pai = y;
    x->pai = y->pai;
    if (y->pai == NULL)
        *raiz = x;
    else if (y == y->pai->esquerda)
        y->pai->esquerda = x;
    else
        y->pai->direita = x;
    x->direita = y;
    y->pai = x;
    return x;
}

pNohArvore EncontrarMenorExclusao(pNohArvore no)
{
    while (no->esquerda != NULL)
        no = no->esquerda;
    return no;
}

void TransplantarArvore(pNohArvore *raiz, pNohArvore u, pNohArvore v)
{
    if (u->pai == NULL)
        *raiz = v;
    else if (u == u->pai->esquerda)
        u->pai->esquerda = v;
    else
        u->pai->direita = v;
    if (v != NULL)
        v->pai = u->pai;
}

void CorrigirExclusao(pNohArvore *raiz, pNohArvore x)
{
    while (x != *raiz && (x == NULL || x->cor == BLACK))
    {
        if (x == x->pai->esquerda)
        {
            pNohArvore w = x->pai->direita;
            if (w->cor == RED)
            {
                w->cor = BLACK;
                x->pai->cor = RED;
                RotacaoEsquerdaExclusao(raiz, x->pai);
                w = x->pai->direita;
            }
            if ((w->esquerda == NULL || w->esquerda->cor == BLACK) &&
                (w->direita == NULL || w->direita->cor == BLACK))
            {
                w->cor = RED;
                x = x->pai;
            }
            else
            {
                if (w->direita == NULL || w->direita->cor == BLACK)
                {
                    if (w->esquerda != NULL)
                        w->esquerda->cor = BLACK;
                    w->cor = RED;
                    RotacaoDireitaExclusao(raiz, w);
                    w = x->pai->direita;
                }
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                if (w->direita != NULL)
                    w->direita->cor = BLACK;
                RotacaoEsquerdaExclusao(raiz, x->pai);
                x = *raiz;
            }
        }
        else
        {
            pNohArvore w = x->pai->esquerda;
            if (w->cor == RED)
            {
                w->cor = BLACK;
                x->pai->cor = RED;
                RotacaoDireitaExclusao(raiz, x->pai);
                w = x->pai->esquerda;
            }
            if ((w->direita == NULL || w->direita->cor == BLACK) &&
                (w->esquerda == NULL || w->esquerda->cor == BLACK))
            {
                w->cor = RED;
                x = x->pai;
            }
            else
            {
                if (w->esquerda == NULL || w->esquerda->cor == BLACK)
                {
                    if (w->direita != NULL)
                        w->direita->cor = BLACK;
                    w->cor = RED;
                    RotacaoEsquerdaExclusao(raiz, w);
                    w = x->pai->esquerda;
                }
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                if (w->esquerda != NULL)
                    w->esquerda->cor = BLACK;
                RotacaoDireitaExclusao(raiz, x->pai);
                x = *raiz;
            }
        }
    }
    if (x != NULL)
        x->cor = BLACK;
}

pNohArvore ExcluirNoRecursivo(pNohArvore *raiz, void *info, FuncaoComparacao pfc)
{
    DArvore arvoreTemp = {*raiz, 0, 0}; // {raiz, quantidadeNohs, grau}
    pNohArvore z = BuscarInfoExclusao(&arvoreTemp, info, pfc);
    if (z == NULL)
        return *raiz;

    pNohArvore y = z;
    pNohArvore x;
    char y_cor_original = y->cor;

    if (z->esquerda == NULL)
    {
        x = z->direita;
        TransplantarArvore(raiz, z, z->direita);
    }
    else if (z->direita == NULL)
    {
        x = z->esquerda;
        TransplantarArvore(raiz, z, z->esquerda);
    }
    else
    {
        y = EncontrarMenorExclusao(z->direita);
        y_cor_original = y->cor;
        x = y->direita;
        if (y->pai == z)
        {
            if (x != NULL)
                x->pai = y;
        }
        else
        {
            TransplantarArvore(raiz, y, y->direita);
            y->direita = z->direita;
            y->direita->pai = y;
        }
        TransplantarArvore(raiz, z, y);
        y->esquerda = z->esquerda;
        y->esquerda->pai = y;
        y->cor = z->cor;
    }

    if (y_cor_original == BLACK)
    {
        if (x == NULL)
        {
            // Caso especial: nó nulo
            pNohArvore nulo = malloc(sizeof(NohArvore));
            nulo->cor = BLACK;
            nulo->pai = y->pai;
            nulo->esquerda = nulo->direita = NULL;
            if (y == y->pai->esquerda)
                y->pai->esquerda = nulo;
            else
                y->pai->direita = nulo;
            CorrigirExclusao(raiz, nulo);
            if (nulo->pai->esquerda == nulo)
                nulo->pai->esquerda = NULL;
            else
                nulo->pai->direita = NULL;
            free(nulo);
        }
        else
        {
            CorrigirExclusao(raiz, x);
        }
    }

    free(z);
    return *raiz;
}

void ExcluirInfo(pDArvore arvore, void *info, FuncaoComparacao pfc)
{
    if (arvore == NULL || arvore->raiz == NULL)
        return;

    arvore->raiz = ExcluirNoRecursivo(&(arvore->raiz), info, pfc);
    if (arvore->raiz != NULL)
        arvore->raiz->cor = BLACK;
    arvore->quantidadeNohs--;
}

#endif