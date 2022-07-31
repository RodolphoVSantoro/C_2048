#include <stdio.h>
#include <time.h>
#include "dmq.h"

int main(){
	srand((unsigned)time(NULL));
	int t,pts=0;
	int i,j;
	printf("Tamanho do tab?");
	scanf("%d",&t);
	int **tab = aloca2d(t);
	rand_num(tab,t);
	rand_num(tab,t);
	getchar();
	do{
		clear;
		printf("%d Pontos\n", pts);
		imprime(tab,t);
		pts+=jogada(tab,t);
	}while(rand_num(tab,t));
	imprime(tab,t);
	libera2d(&tab,t);
	printf("\nFim de jogo\n");
	return 0;
}