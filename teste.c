#include <stdio.h>

	//x=linha
	//y=coluna

void imprime(int mat[8][8]){
	int x,y;
	for(x=0;x<8;x++){
		for(y=0;y<8;y++){
			printf("%d,", mat[x][y]);
		}
		printf("\n");
	}
}

int main(){
	int x,y,i=1,j=1,a;
	int mat[8][8];
	for(x=0;x<8;x++)
		for(y=0;y<8;y++)
			mat[x][y]=0;
	for(x=1;x<8;x++){
		for(y=0;y<8;y++){
			if(x%2==1){
				mat[x][y]=i;
				i++;
			}
			else{
				mat[x][y]=j;
				j++;
			}
		}
	}
	imprime(mat);
	for(x=1;x<8;x++){
		for(y=0;y<8;y++){
			if(mat[x][y]!=0){
				for(a=x;a>0 && mat[a-1][y]==0;a--);
				if(mat[a-1][y]==mat[x][y]){
					mat[a-1][y]*=2;
					mat[x][y]=0;
				}
				else{
					if(a!=x){
						mat[a][y]=mat[x][y];
						mat[x][y]=0;
					}
				}
			}
		}
	}
	printf("\n");
	imprime(mat);
	return 0;
}