#ifndef dmq_H
#define dmq_H
#define clear system("clear")

typedef struct coordenada{
	int x,y;
}coor;

int getch(void);
int digitos(int n);
int pot(int b, int e);
int pot2(int e);
int** aloca2d(int t);
void libera2d(int ***p, int t);
void imprime(int **tab, int t);
int rand_num(int **tab, int t);
int jogada(int **tab, int t);

#endif