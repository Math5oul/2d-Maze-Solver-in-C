#include <stdio.h>#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//-----------------------------MATRIX FUNCTIONS
#include "matrix.h"
//MATRIX criarMatrix (MATRIX mat)
//MATRIX preencherMatrix(FILE* v,MATRIX mat)
//void printMatrix (MATRIX mat)
//void destroyMatrix (MATRIX mat)

//-----------------------------STACKS FUNCTIONS
#include "stack.h"
//STACK* createStack()
//NODE* createNode()
//int isEmpty(STACK* stackPtr)
//void pushStack(STACK* stackPtr, void* dataPtr)
//void* popStack(STACK* stackPtr)
//void destroyStack(STACK* stackPtr)

//------------------------------------FUNCTIONS

typedef struct {
    int dX, dY;
} COORDENADAS;

COORDENADAS* criaCOORDENADAS (int x, int y)
{
    COORDENADAS* elemento;
    elemento=(COORDENADAS*)malloc(sizeof(COORDENADAS));
    elemento->dX=x;
    elemento->dY=y;

    return(elemento);
}

bool isOnTheStack (int x, int y,STACK* uniBloco)
{
    NODE* aux;
    aux=uniBloco->top;

    while(aux!=NULL)
    {
        if (((COORDENADAS*)aux->dataPtr)->dX==x && ((COORDENADAS*)aux->dataPtr)->dY==y)
            return(true);

        aux=aux->link;
    }
    return(false);
}

bool isOne (int x, int y, MATRIX mat)
{
    if (mat.mat[x][y]==1)
        return(true);
    return(false);
}

void findAdjacents (int x, int y, STACK* uniBloco, MATRIX mat)
{
    COORDENADAS* elemento;
    if (isOne(x,y,mat))
    {
        elemento=criaCOORDENADAS(x,y);
        pushStack(uniBloco,elemento);

        if (x<mat.dX-1 && isOne(x+1,y,mat))//down
            if (!isOnTheStack(x+1,y,uniBloco))
                findAdjacents(x+1,y,uniBloco,mat);

        if (y<mat.dY-1 && isOne(x,y+1,mat))//right
            if (!isOnTheStack(x,y+1,uniBloco))
                findAdjacents(x,y+1,uniBloco,mat);

        if (x>0 && isOne(x-1,y,mat))//up
            if (!isOnTheStack(x-1,y,uniBloco))
                findAdjacents(x-1,y,uniBloco,mat);

        if (y>0 && isOne(x,y-1,mat))//left
            if (!isOnTheStack(x,y-1,uniBloco))
                findAdjacents(x,y-1,uniBloco,mat);
    }
}
void printBlocks (STACK* uniBloco)
{
    NODE* aux;
    aux=uniBloco->top;

    printf("\n%d elementos: ",uniBloco->count);
    while(aux!=NULL)
    {
        if (((COORDENADAS*)aux->dataPtr)->dX == -1)

            printf("---------Bloco %d\n",((COORDENADAS*)aux->dataPtr)->dY);
        else
        printf("(%d,%d) ",((COORDENADAS*)aux->dataPtr)->dX,((COORDENADAS*)aux->dataPtr)->dY);

        aux=aux->link;
    }
}

bool isNoExitLeft  (int x, int y, MATRIX lab, STACK* noExit)
{
    if (lab.mat[x][y-1]==0 || isOnTheStack(x,y-1,noExit))
        return(true);
    return(false);
}
bool isNoExitRight  (int x, int y, MATRIX lab, STACK* noExit)
{
    if (lab.mat[x][y+1]==0 || isOnTheStack(x,y+1,noExit))
        return(true);
    return(false);
}
bool isNoExitDown (int x, int y, MATRIX lab, STACK* noExit)
{
    if (lab.mat[x+1][y]==0 || isOnTheStack(x+1,y,noExit))
        return(true);
    return(false);
}
bool isNoExitUp  (int x, int y, MATRIX lab, STACK* noExit)
{
    if (lab.mat[x-1][y]==0 || isOnTheStack(x-1,y,noExit))
        return(true);
    return(false);
}

bool isNoExit (int x, int y, MATRIX lab, STACK* noExit)
{
    if (x>0 && y>0 && y<lab.dY-1 && x<lab.dX-1)
    {
        if ((isNoExitUp(x,y,lab,noExit)) && (isNoExitRight(x,y,lab,noExit)))
            if(isNoExitDown(x,y,lab,noExit))
                return(true);
        if ((isNoExitLeft(x,y,lab,noExit)) && (isNoExitRight(x,y,lab,noExit)))
            if(isNoExitDown(x,y,lab,noExit))
                return(true);
        if ((isNoExitLeft(x,y,lab,noExit)) && (isNoExitUp(x,y,lab,noExit)))
            if(isNoExitDown(x,y,lab,noExit))
                return(true);
        if ((isNoExitLeft(x,y,lab,noExit)) && (isNoExitUp(x,y,lab,noExit)))
            if(isNoExitRight(x,y,lab,noExit))
                return(true);
    }

    return(false);
}

void pathFinder (STACK* path, STACK* noExit, MATRIX lab,COORDENADAS* exit, int x, int y)
{
    COORDENADAS* elemento;
    COORDENADAS* descarte;

    elemento=criaCOORDENADAS(x,y);
    pushStack(path,elemento);
    printf("\n(%d,%d) ",x,y);

    if (isNoExit(x,y,lab,noExit))
    {
        pushStack(noExit,elemento);
        descarte=popStack(path);

        x=elemento->dX;
        y=elemento->dY;

        if (x<lab.dX-1 && isOne(x+1,y,lab))//down
            if(!isOnTheStack(x+1,y,noExit))
                {
                    pathFinder(path,noExit,lab,exit,x+1,y);
                    return(0);
                }

        if (y<lab.dY-1 && isOne(x,y+1,lab))//right
            if(!isOnTheStack(x,y+1,noExit))
                {
                    pathFinder(path,noExit,lab,exit,x,y+1);
                    return(0);
                }

        if (x>0 && isOne(x-1,y,lab))//up
            if(!isOnTheStack(x-1,y,noExit))
                {
                    pathFinder(path,noExit,lab,exit,x-1,y);
                    return(0);
                }

        if (y>0 && isOne(x,y-1,lab))//left
            if(!isOnTheStack(x,y-1,noExit))
                {
                    pathFinder(path,noExit,lab,exit,x,y-1);
                    return(0);
                }
    }

    while (true)
    {
        if (x==exit->dX && y==exit->dY)
            return(0);

        if (x<lab.dX-1 && isOne(x+1,y,lab))//down
            //if(!isNoExit(x+1,y,lab,noExit))
                if(!isOnTheStack(x+1,y,noExit))
                    if(!isOnTheStack(x+1,y,path))
                    {
                        pathFinder(path,noExit,lab,exit,x+1,y);
                        return(0);
                    }

        if (y<lab.dY-1 && isOne(x,y+1,lab))//right
            //if(!isNoExit(x,y+1,lab,noExit))
                if(!isOnTheStack(x,y+1,noExit))
                    if(!isOnTheStack(x,y+1,path))
                    {
                        pathFinder(path,noExit,lab,exit,x,y+1);
                        return(0);
                    }

        if (x>0 && isOne(x-1,y,lab))//up
            //if(!isNoExit(x-1,y,lab,noExit))
                if(!isOnTheStack(x-1,y,noExit))
                    if(!isOnTheStack(x-1,y,path))
                    {
                        pathFinder(path,noExit,lab,exit,x-1,y);
                        return(0);
                    }

        if (y>0 && isOne(x,y-1,lab))//left
            //if(!isNoExit(x,y-1,lab,noExit))
                if(!isOnTheStack(x,y-1,noExit))
                    if(!isOnTheStack(x,y-1,path))
                    {
                        pathFinder(path,noExit,lab,exit,x,y-1);
                        return(0);
                    }
    }
}

void main()
{
    FILE *doc;
    doc=fopen("documento2.txt","r");
    if (doc==NULL){
        printf("Nao ha como abrir o arquivo");
        return(-1);
    }
    MATRIX mat;
    fscanf(doc,"%d %d",&mat.dX,&mat.dY);
    mat=criarMatrix(mat);
    mat=preencherMatrix(doc,mat);
    printMatrix(mat);

    STACK* uniBlocos;
    uniBlocos=createStack();

    int x,y;
    for(x=0;x<mat.dX;x++)
        for(y=0;y<mat.dY;y++)
            if (!isOnTheStack(x,y,uniBlocos) && isOne(x,y,mat))
                findAdjacents(x,y,uniBlocos,mat);

    srand(time(NULL));
    int firstHouse;
    firstHouse=rand()%uniBlocos->count;
    COORDENADAS* start;
    for (firstHouse; firstHouse>=0; firstHouse--)
        start=popStack(uniBlocos);
    start=criaCOORDENADAS(start->dX,start->dY);
    printf("\n\n-------START(%d,%d)",start->dX,start->dY);

    STACK* path;
    path=createStack();
    STACK* noExit;
    noExit=createStack();
    COORDENADAS* exit;
    exit=criaCOORDENADAS(8,9);

    pathFinder(path,noExit,mat,exit,start->dX,start->dY);
    //pathFinder(path,noExit,mat,exit,2,6);
    //pathFinder(path,noExit,mat,exit,2,7);

    STACK* realPath;
    realPath=createStack();

    printf("\n\nPath:   ");
    printBlocks(path);
    printf("\n\nnoExit:   ");
    printBlocks(noExit);

    destroyStack(uniBlocos);
    destroyStack(path);
    destroyStack(noExit);
    destroyMatrix(mat);
    free(start);
    free(exit);
}
