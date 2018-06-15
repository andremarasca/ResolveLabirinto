#include <stdio.h>
#include <stdlib.h>
#define MM 512

#define LIVRE 2000000000
#define PORTAL 2000000001
#define PAREDE 2000000002
#define CAMINHO 2000000003

int mapa[MM][MM][2];
int mapaP[MM][MM][2];

typedef struct nodo
{
    int i, j, k;
    struct nodo*proximo;
} Nodo;

typedef struct fila
{
    Nodo *primeiro;
    Nodo *ultimo;
} Fila;

void inicializa_fila(Fila *f)
{
    f->primeiro = NULL;
    f->ultimo = NULL;
}

void enfila (Fila *f, int i, int j, int k)
{
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
    novo->proximo = NULL;
    novo->i = i;
    novo->j = j;
    novo->k = k;
    if (f->primeiro != NULL)
    {
        f->ultimo->proximo = novo;
        f->ultimo = novo;
    }
    else
    {
        f->primeiro = novo;
        f->ultimo = novo;
    }
}

int desenfila (Fila *f)
{
    if (f->primeiro == NULL) return 0;
    if (f->primeiro == f->ultimo) f->ultimo = NULL;
    Nodo *tmp = f->primeiro;
    f->primeiro = f->primeiro->proximo;
    free(tmp);
    return 1;
}

int filavazia (Fila *f)
{
    if (f->primeiro == NULL) return 1;
    return 0;
}

void pegatopo(Fila *f, int *i, int *j, int *k)
{
    *i = f->primeiro->i;
    *j = f->primeiro->j;
    *k = f->primeiro->k;
}

void inundacao (int m, int n, int i, int j, int si, int sj)
{
    Fila fila;
    inicializa_fila(&fila);
    int cont = 0;
    int k = 0;
    int mn = m / 8, nn = n / 8;
    mapa[i][j][k] = cont++;

    while(i != si || j != sj || k != 0)
    {
        //printf("%d %d %d\n", i, j, k);
        if(k == 0 && mapaP[i][j][0] == PORTAL)
        {
            if (0 <= (i / 8) && (i / 8) < mn && 0 <= (j / 8) && (j / 8) < nn )
                if (mapa[i / 8][j / 8][1]  == PORTAL)
                {
                    //printf("Entrou portal!\n");
                    mapa[i / 8][j / 8][1] = mapa[i][j][k] + 1;;
                    enfila(&fila, i / 8, j / 8, 1);
                }
        }
        if(k == 1 && mapaP[i][j][1] == PORTAL)
        {
            if (0 <= (i * 8) && (i * 8) < m && 0 <= (j * 8) && (j * 8) < n )
                if (mapa[i * 8][j * 8][0] == PORTAL)
                {
                    //printf("Saiu portal!\n");
                    mapa[i * 8][j * 8][0] = mapa[i][j][k] + 1;;
                    enfila(&fila, i * 8, j * 8, 0);
                }

        }
        if ((0 <= (i + 1) && (i + 1) < m && 0 <= (j) && (j) < n && k == 0) || (0 <= (i + 1) && (i + 1) < mn && 0 <= (j) && (j) < nn && k == 1))
        {
            if (mapa[i + 1][j][k] == LIVRE || mapa[i + 1][j][k] == PORTAL)
            {
                mapa[i + 1][j][k] = mapa[i][j][k] + 1;
                enfila(&fila, i + 1, j, k);
            }
        }
        if ((0 <= (i - 1) && (i - 1) < m && 0 <= (j) && (j) < n && k == 0) || (0 <= (i - 1) && (i - 1) < mn && 0 <= (j) && (j) < nn && k == 1))
        {
            if (mapa[i - 1][j][k] == LIVRE || mapa[i - 1][j][k] == PORTAL)
            {
                mapa[i - 1][j][k] = mapa[i][j][k] + 1;
                enfila(&fila, i - 1, j, k);
            }
        }
        if ((0 <= (i) && (i) < m && 0 <= (j + 1) && (j + 1) < n && k == 0) || (0 <= (i) && (i) < mn && 0 <= (j + 1) && (j + 1) < nn && k == 1))
        {
            if (mapa[i][j + 1][k] == LIVRE || mapa[i][j + 1][k] == PORTAL)
            {
                mapa[i][j + 1][k] = mapa[i][j][k] + 1;
                enfila(&fila, i, j + 1, k);
            }
        }
        if ((0 <= (i) && (i) < m && 0 <= (j - 1) && (j - 1) < n && k == 0) || (0 <= (i) && (i) < mn && 0 <= (j - 1) && (j - 1) < nn && k == 1))
        {
            if (mapa[i][j - 1][k] == LIVRE || mapa[i][j - 1][k] == PORTAL)
            {
                mapa[i][j - 1][k] = mapa[i][j][k] + 1;
                enfila(&fila, i, j - 1, k);
            }
        }
        pegatopo(&fila, &i, &j, &k);
        desenfila(&fila);
        //printf("Contador = %d\n",cont);
    }
}

void caminha (int m, int n, int ci, int cj, int i, int j, int k)
{
    int cont = mapa[i][j][k];
    int mn = m / 8, nn = n / 8;
    mapa[i][j][k] = CAMINHO;
    while(i!= ci || j!= cj || k != 0)
    {
        //printf("%d %d %d\n", i, j, k);
        //printf("Cont = %d\n", cont);
        if (((0 <= (i + 1) && (i + 1) < m && 0 <= (j) && (j) < n && k == 0) || (0 <= (i + 1) && (i + 1) < mn && 0 <= (j) && (j) < nn && k == 1)) && (mapa[i + 1][j][k] < cont))
        {
            i = i + 1;
            printf("Baixo\n");
        }
        else if (((0 <= (i - 1) && (i - 1) < m && 0 <= (j) && (j) < n && k == 0) || (0 <= (i - 1) && (i - 1) < mn && 0 <= (j) && (j) < nn && k == 1)) &&(mapa[i - 1][j][k] < cont))
        {
            i = i - 1;
            printf("Cima\n");
        }
        else if (((0 <= (i) && (i) < m && 0 <= (j + 1) && (j + 1) < n && k == 0) || (0 <= (i) && (i) < mn && 0 <= (j + 1) && (j + 1) < nn && k == 1)) && (mapa[i][j + 1][k] < cont))
        {
            j = j + 1;
            printf("Direita\n");
        }
        else if (((0 <= (i) && (i) < m && 0 <= (j - 1) && (j - 1) < n && k == 0) || (0 <= (i) && (i) < mn && 0 <= (j - 1) && (j - 1) < nn && k == 1)) && (mapa[i][j - 1][k] < cont))
        {
            j = j - 1;
            printf("Esquerda\n");
        }
        else if (k == 0 && (0 <= (i / 8) && (i / 8) < mn && 0 <= (j / 8) && (j / 8) < nn ))
        {
            if (mapaP[i/8][j/8][1] == PORTAL && mapa[i/8][j/8][1] < cont)
            {
                printf("Entrar\n");
                i = i / 8;
                j = j / 8;
                k = 1;
            }
        }
        else if (k == 1 && (0 <= (i * 8) && (i * 8) < m && 0 <= (j * 8) && (j * 8) < n))
        {
            if (mapaP[i * 8][j * 8][0] == PORTAL && mapa[i * 8][j * 8][0] < cont)
            {
                printf("Sair\n");
                i = i * 8;
                j = j * 8;
                k = 0;
            }
        }
        cont = mapa[i][j][k];
        mapaP[i][j][k] = CAMINHO;
    }
    mapaP[i][j][k] = CAMINHO;
}

int main (void)
{
    int i, j, k, tmp;
    int m, n;
    int mn, nn;
    int ci, cj, si, sj;
    char c;

    scanf("%d %d", &m, &n);

    mn = m / 8;
    nn = n / 8;

    for (i = 0 ; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf(" %c", &c);
            if(c == '.')
                mapa[i][j][0] = LIVRE;
            else if(c == '#')
                mapa[i][j][0] = PAREDE;
            else if (c == 'S') // definir coordenadas do personagem
            {
                mapa[i][j][0] = LIVRE;
                si = i;
                sj = j;
            }
            else if(c == 'C') // definir coordenadas da casa
            {
                mapa[i][j][0] = LIVRE;
                ci = i;
                cj = j;
            }
            else
                mapa[i][j][0] = PORTAL;

            mapaP[i][j][0] = mapa[i][j][0];
        }
    }

    for (i = 0 ; i < mn; i++)
    {
        for (j = 0; j < nn; j++)
        {
            scanf(" %c", &c);
            if(c == '.')
                mapa[i][j][1] = LIVRE;
            else if(c == '#')
                mapa[i][j][1] = PAREDE;
            else
                mapa[i][j][1] = PORTAL;

            mapaP[i][j][1] = mapa[i][j][1];
        }
    }

    inundacao (m, n, ci, cj, si, sj);
    caminha (m, n, ci, cj, si, sj, 0);

    for (i = 0 ; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (mapaP[i][j][0] == PAREDE)
                printf("#");
            else if (mapaP[i][j][0] == LIVRE)
                printf(".");
            else if (mapaP[i][j][0] == CAMINHO)
                printf("*");
            else if (mapaP[i][j][0] == PORTAL)
                printf("P");
        }
        printf("\n");
    }
    for (i = 0 ; i < mn; i++)
    {
        for (j = 0; j < nn; j++)
        {
            if (mapaP[i][j][1] == PAREDE)
                printf("#");
            else if (mapaP[i][j][1] == LIVRE)
                printf(".");
            else if (mapaP[i][j][1] == CAMINHO)
                printf("*");
            else if (mapaP[i][j][1] == PORTAL)
                printf("P");
        }
        printf("\n");
    }

    return 0;
}
