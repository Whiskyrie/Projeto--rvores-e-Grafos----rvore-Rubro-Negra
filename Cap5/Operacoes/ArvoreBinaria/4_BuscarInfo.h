#ifndef BUSCAR_INFO_H
#define BUSCAR_INFO_H

pNohArvore BuscarInfoRecursivo(pNohArvore raiz, void *info, FuncaoComparacao pfc)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    int comparacao = pfc(info, raiz->info);

    if (comparacao == 0)
    {
        return raiz;
    }
    else if (comparacao < 0)
    {
        pNohArvore nodoDireito = BuscarInfoRecursivo(raiz->direita, info, pfc);
        if (nodoDireito != NULL)
        {
            return nodoDireito;
        }
        // Verificar e rebalancear a árvore AVL, se necessário
    }
    else
    {
        pNohArvore nodoEsquerdo = BuscarInfoRecursivo(raiz->esquerda, info, pfc);
        if (nodoEsquerdo != NULL)
        {
            return nodoEsquerdo;
        }
        // Verificar e rebalancear a árvore AVL, se necessário
    }

    return NULL;
}

pNohArvore BuscarInfo(pDArvore arvore, void *info, FuncaoComparacao pfc)
{
    if (arvore == NULL || arvore->raiz == NULL)
    {
        return NULL;
    }

    return BuscarInfoRecursivo(arvore->raiz, info, pfc);
}

#endif