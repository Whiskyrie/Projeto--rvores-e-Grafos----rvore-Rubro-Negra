#ifndef CRIAR_ARVORE_BINARIA_H
#define CRIAR_ARVORE_BINARIA_H
#define BLACK 'B'
#define RED 'R'

/* ---------------------------------------------------------------------*/
pNohArvore Avo(pNohArvore raiz)
{
    if (raiz == NULL)
        return NULL;

    if (raiz->pai == NULL)
        return NULL;

    return raiz->pai->pai;
}
/* ---------------------------------------------------------------------*/

pNohArvore Tio(pNohArvore raiz)
{
    if (raiz == NULL || raiz->pai == NULL)
        return NULL;

    if (Avo(raiz) != NULL && Avo(raiz)->esquerda == raiz->pai)
        return Avo(raiz)->direita;

    return Avo(raiz)->esquerda;
}
/* ---------------------------------------------------------------------*/

char CorTio(pNohArvore raiz)
{
    pNohArvore tioRaiz = Tio(raiz);
    if (tioRaiz == NULL)
        return 'X';

    return tioRaiz->cor;
}
/* ---------------------------------------------------------------------*/

void InverteCor(pNohArvore raiz)
{
    if (raiz == NULL)
        return;

    if (raiz->cor == RED)
        raiz->cor = BLACK;
    else
        raiz->cor = RED;
}
/* ---------------------------------------------------------------------*/

pNohArvore RotacaoDireita(pNohArvore raiz)
{
    // se n�o tem pai e av�, n�o rotaciona
    if (raiz == NULL || raiz->pai == NULL || Avo(raiz) == NULL)
        return NULL;

    pNohArvore avoRaiz = Avo(raiz);

    // altera a paternidade do filho e do pai
    avoRaiz->pai = raiz->pai;
    raiz->pai->pai = avoRaiz->pai;

    // ajusta as sub-arvores da raiz
    avoRaiz->esquerda = raiz->pai->direita;
    raiz->pai->direita = avoRaiz;

    // ajusta as cores
    raiz->pai->cor = BLACK;
    avoRaiz->cor = RED;

    return raiz->pai;
}

/* ---------------------------------------------------------------------*/

pNohArvore RotacaoEsquerda(pNohArvore raiz)
{
    // se n�o tem pai e av�, n�o rotaciona
    if (raiz == NULL || raiz->pai == NULL || Avo(raiz) == NULL)
        return NULL;

    pNohArvore avoRaiz = Avo(raiz);

    // altera a paternidade do filho e do pai
    raiz->pai->pai = avoRaiz->pai;
    avoRaiz->pai = raiz->pai;

    // ajusta as sub-arvores da raiz
    avoRaiz->direita = raiz->pai->esquerda;
    raiz->pai->esquerda = avoRaiz;

    // ajusta as cores
    raiz->pai->cor = BLACK;
    avoRaiz->cor = RED;

    return raiz->pai;
}

/* ---------------------------------------------------------------------*/

pNohArvore RotacaoEsquerdaDireita(pNohArvore raiz)
{
    if (raiz == NULL || raiz->pai == NULL || Avo(raiz) == NULL)
        return NULL;

    pNohArvore avoRaiz = Avo(raiz);
    pNohArvore paiRaiz = raiz->pai;

    // altera a paternidade do filho e do pai
    paiRaiz->pai = raiz;
    raiz->pai = avoRaiz;

    // ajusta as sub-arvores do filho(raiz) e do pai
    paiRaiz->direita = raiz->esquerda;
    raiz->esquerda = paiRaiz;

    // rota��o simples a direita
    return RotacaoDireita(paiRaiz);
}

/* ---------------------------------------------------------------------*/

pNohArvore RotacaoDireitaEsquerda(pNohArvore raiz)
{
    // se n�o tem pai e nem av�, n�o rotaciona
    if (raiz == NULL || raiz->pai == NULL || Avo(raiz) == NULL)
        return NULL;

    pNohArvore avoRaiz = Avo(raiz);
    pNohArvore paiRaiz = raiz->pai;

    // altera a paternidade do filho e do pai
    paiRaiz->pai = raiz;
    raiz->pai = avoRaiz;

    // ajusta as sub-arvores do filho(raiz) e do pai
    paiRaiz->esquerda = raiz->direita;
    raiz->direita = paiRaiz;

    // rota��o simples a esquerda
    return RotacaoEsquerda(paiRaiz);
}

/* ---------------------------------------------------------------------*/

pNohArvore IncluirInfoRecursivo(pNohArvore raiz, void *info, FuncaoComparacao pfc)
{

    // caso base
    if (raiz == NULL)
    {
        raiz = malloc(sizeof(NohArvore));
        raiz->info = info;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
        raiz->cor = RED;
        return raiz;
    }
    else
    {
        pNohArvore filho;
        /* caso recursivo */
        if (pfc(info, raiz->info) >= 0)
        {
            filho = IncluirInfoRecursivo(raiz->esquerda, info, pfc);
            if (filho->direita == raiz)
            {
                // houve rota��o a direita, n�o precisa alterar o filho esquerda,
                // somente ajusta a raiz para apontar para o filho
                raiz = filho;
            }
            else
            {
                filho->pai = raiz;
                raiz->esquerda = filho;
            }
        }
        else
        {
            filho = IncluirInfoRecursivo(raiz->direita, info, pfc);
            if (filho->esquerda == raiz)
            {
                // houve rota��o a esquerda, n�o precisa alterar o filho esquerda,
                // somente ajusta a raiz para apontar para o filho
                raiz = filho;
            }
            else
            {
                filho->pai = raiz;
                raiz->direita = filho;
            }
        }

        if (raiz->pai == NULL)
        {
            // � a raiz da �rvore, tem que ser BLACK
            raiz->cor = BLACK;
            return raiz;
        }

        // verifica a cor do pai
        if (raiz->cor == BLACK ||
            (raiz->cor == RED && filho->cor == BLACK))
        {
            // n�o precisa fazer nada, n�o tem como violar alguma das regras
            return raiz;
        }

        // ----------------------------------------------
        // caso 1: verifica se ambos o pai e o tio s�o RED,
        //         muda a cor de ambos para BLACK e a cor do
        //         av� para RED
        // ----------------------------------------------
        if (raiz->cor == RED && CorTio(filho) == RED)
        {

            raiz->cor = BLACK;
            Tio(filho)->cor = BLACK;
            if (Avo(filho) != NULL)
            {
                Avo(filho)->cor = RED;
            }

            return raiz;
        }

        // ----------------------------------------------
        // Caso 2: pai e tio com cores diferentes
        // S�o 4 possibilidades:
        if (raiz->cor == RED && CorTio(filho) != RED)
        {

            pNohArvore novaRaiz;

            if (raiz->esquerda == filho && raiz->pai->esquerda == raiz)
            {
                // caso 2.1 - Left-Left
                novaRaiz = RotacaoDireita(filho);
            }
            else if (raiz->direita == filho && raiz->pai->esquerda == raiz)
            {
                // caso 2.2 - Left-Right
                novaRaiz = RotacaoEsquerdaDireita(filho);
            }
            else if (raiz->direita == filho && raiz->pai->direita == raiz)
            {
                // caso 2.3 - Right-Right
                novaRaiz = RotacaoEsquerda(filho);
            }
            else if (raiz->esquerda == filho && raiz->pai->direita == raiz)
            {
                // caso 2.4 - Left-Right
                novaRaiz = RotacaoDireitaEsquerda(filho);
            }
            return novaRaiz;
        }
    }
    return raiz;
}

/* ----------------------------------------------------------*/
void IncluirInfo(pDArvore arvore, void *info, FuncaoComparacao pfc)
{

    printf("\n ----------- Incluindo: %d ----------- \n", *((int *)info));
    arvore->raiz = IncluirInfoRecursivo(arvore->raiz, info, pfc);
    arvore->raiz->cor = BLACK;
    arvore->quantidadeNohs++;

    printf("\n -----------------------------------------");
    DesenhaArvore(arvore, ImprimeInt);
    printf("\n ----------------------------------------- \n");
}

#endif
