//---------------------MATRIX FUNCTIONS
//MATRIX criarMatrix (MATRIX mat)
//MATRIX preencherMatrix(FILE* v,MATRIX mat)
//void printMatrix (MATRIX mat)

typedef struct
{
    int dX,dY;
    int** mat;
} MATRIX;

MATRIX criarMatrix (MATRIX mat)
{
    int index;

    mat.mat=(int**)malloc(mat.dX*sizeof(int*));
        for (index=0;index<mat.dX;index++)
            mat.mat[index]=(int*)malloc(mat.dY*sizeof(int));

    return(mat);
}

MATRIX preencherMatrix(FILE* v,MATRIX mat)
{
    int x,y;
    for(x=0;x<mat.dX;x++)
    {
        for(y=0;y<mat.dY;y++)
        {
            fscanf(v,"%d",&mat.mat[x][y]);
        }
    }
    return(mat);
}

void printMatrix (MATRIX mat)
{
    int x,y;

    printf("\n......MATRIX....... \n");
    for(x=0;x<mat.dX;x++)
    {
        for(y=0;y<mat.dY;y++)
        {
            printf("%d ",mat.mat[x][y]);
        }
    printf("\n");
    }
    printf("................... \n");
}

void destroyMatrix (MATRIX mat)
{
    free(&mat);
}
