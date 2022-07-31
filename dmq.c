#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "dmq.h"

int digitos(int n){
	int d;
	for(d=1;n>=10;d++)
		n/=10;
	return d;
}

int pot(int b, int e){
	int i,r=1;
	for(i=0;i<e;i++)
		r*=b;
	return r;
}

int pot2(int e){
	return pot(2,e);
}

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int** aloca2d(int t){
	int i,j,**p=(int**)malloc(sizeof(int*)*t);
	for(i=0;i<t;i++)
		p[i]=(int*)malloc(sizeof(int)*t);
	for(i=0;i<t;i++)
		for(j=0;j<t;j++)
			p[i][j]=0;
	return p;
}

void libera2d(int ***p, int t){
	int i;
	for(i=0;i<t;i++)
		free((*p)[i]);
	free(*p);
	*p=NULL;
}

void imprime(int **tab, int t){
	int i, j, a;
	for(i=0;i<t;i++){
		for(j=0;j<t;j++)
			printf("------- ");
		printf("\n");
		for(j=0;j<t;j++)
			printf("|     | ");
		printf("\n");
		for(j=0;j<t;j++){
			if(tab[i][j]==0)
				printf("|     | ");
			else{
				printf("|");
				for(a=0;a<5-digitos(tab[i][j]);a++)
					printf(" ");
				printf("%d| ", tab[i][j]);
			}
		}
		printf("\n");
		for(j=0;j<t;j++)
			printf("|     | ");
		printf("\n");
	}
	for(j=0;j<t;j++)
			printf("------- ");
}

int rand_num(int **tab, int t){
	int i,j,vazios=0,a=0,r;
	for(i=0;i<t;i++)
		for(j=0;j<t;j++)
			if(tab[i][j]==0)
				vazios++;
	if(vazios==0)
		return 0;
	coor *vazia=(coor*)malloc(sizeof(coor)*vazios);
	for(i=0;i<t;i++)
		for(j=0;j<t;j++)
			if(tab[i][j]==0){
				vazia[a].x=i;
				vazia[a].y=j;
				a++;
			}
	r = rand()%vazios;
	coor c = vazia[r];
	free(vazia);
	r = (rand()%2)+1;
	tab[c.x][c.y]=pot2(r);
	return 1;
}

int jogada(int **tab, int t){
	int ca,pts=0,x,y,a,err;
	do{
		ca = getch();
		char c=(char)ca;
		err=0;
		switch(c){
			//esq
			case 'a':
			for(y=1;y<t;y++){
				for(x=0;x<t;x++){
					if(tab[x][y]!=0){
						for(a=y;a>0 && tab[x][a-1]==0;a--);
						if(a>0 && tab[x][a-1]==tab[x][y]){
							tab[x][a-1]*=2;
							tab[x][y]=0;
							pts+=tab[x][a-1];
							if(tab[x][a-1]==2048)
								printf("Vitoria\n");
						}
						else{
							if(a!=y){
								tab[x][a]=tab[x][y];
								tab[x][y]=0;
							}
						}
					}
				}
			}
			break;
			//dir
			case 'd':
			for(y=t-2;y>=0;y--){
				for(x=0;x<t;x++){
					if(tab[x][y]!=0){
						for(a=y;a<t-1 && tab[x][a+1]==0;a++);
						if(a<t-1 && tab[x][a+1]==tab[x][y]){
							tab[x][a+1]*=2;
							tab[x][y]=0;
							pts+=tab[x][a+1];
							if(tab[x][a+1]==2048)
								printf("Vitoria\n");
						}
						else{
							if(a!=y){
								tab[x][a]=tab[x][y];
								tab[x][y]=0;
							}
						}
					}
				}
			}
			break;
			//cima
			case 'w':
			for(x=1;x<t;x++){
				for(y=0;y<t;y++){
					if(tab[x][y]!=0){
						for(a=x;a>0 && tab[a-1][y]==0;a--);
						if(a>0 && tab[a-1][y]==tab[x][y]){
							tab[a-1][y]*=2;
							tab[x][y]=0;
							pts+=tab[a-1][y];
							if(tab[a-1][y]==2048)
								printf("Vitoria\n");
						}
						else{
							if(a!=x){
								tab[a][y]=tab[x][y];
								tab[x][y]=0;
							}
						}
					}
				}
			}
			break;
			//baixo
			case 's':
			for(x=t-2;x>=0;x--){
				for(y=0;y<t;y++){
					if(tab[x][y]!=0){
						for(a=x;a<t-1 && tab[a+1][y]==0;a++);
						if(a<t-1 && tab[a+1][y]==tab[x][y]){
							tab[a+1][y]*=2;
							tab[x][y]=0;
							pts+=tab[a+1][y];
							if(tab[a+1][y]==2048)
								printf("Vitoria\n");
						}
						else{
							if(a!=x){
								tab[a][y]=tab[x][y];
								tab[x][y]=0;
							}
						}
					}
				}
			}
			break;
			default:
			err=1;
			break;
		}
	}while(err==1);
	return pts;
}