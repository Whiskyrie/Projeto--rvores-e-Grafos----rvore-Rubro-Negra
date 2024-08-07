#ifndef ALTURA_ARVORE_BINARIA_H
#define ALTURA_ARVORE_BINARIA_H

/* -------------------------------------------*/
int AlturaRecursiva(pNohArvore raiz)
{
  if (raiz == NULL)
    return 0;

  // � uma folha
  if (raiz->esquerda == NULL && raiz->direita == NULL)
    return 1;

  int alturaEsq, alturaDir;

  alturaEsq = 1 + AlturaRecursiva(raiz->esquerda);
  alturaDir = 1 + AlturaRecursiva(raiz->direita);

  if (alturaEsq > alturaDir)
    return alturaEsq;

  return alturaDir;
}

int Altura(pDArvore arvore)
{
  return AlturaRecursiva(arvore->raiz);
}
#endif
