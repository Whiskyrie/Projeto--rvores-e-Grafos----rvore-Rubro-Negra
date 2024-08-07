#ifndef DESENHA_ARVORE_H
#define DESENHA_ARVORE_H
#define ESPACO 5

void DesenhaArvoreRecursivo(pNohArvore raiz, int depth, char *path, int right, FuncaoImpressao fi)
{
    if (raiz == NULL)
        return;

    depth++;

    DesenhaArvoreRecursivo(raiz->direita, depth, path, 1, fi);

    path[depth - 2] = 0;

    if (right)
        path[depth - 2] = 1;

    if (raiz->esquerda)
        path[depth - 1] = 1;

    printf("\n");

    for (int i = 0; i < depth - 1; i++)
    {
        if (i == depth - 2)
            printf("+");
        else if (path[i])
            printf("|");
        else
            printf(" ");

        for (int j = 1; j < ESPACO; j++)
            printf(i < depth - 2 ? " " : "-");
    }

    fi(raiz->info);
    printf("[%c]", raiz->cor == RED ? 'R' : 'B'); // Assumindo que RED é 0 e BLACK é 1

    for (int i = 0; i < depth; i++)
    {
        printf(path[i] ? "|" : " ");

        for (int j = 1; j < ESPACO; j++)
            printf(" ");
    }

    DesenhaArvoreRecursivo(raiz->esquerda, depth, path, 0, fi);
}

void DesenhaArvore(pDArvore arvore, FuncaoImpressao fi)
{
    if (arvore == NULL || arvore->raiz == NULL)
    {
        printf("Árvore vazia!\n");
        return;
    }

    char path[255] = {0};
    DesenhaArvoreRecursivo(arvore->raiz, 0, path, 0, fi);
    printf("\n");
}

#endif