#include <stdio.h>
#include <stdbool.h>
#define N 9

void liesSudoku(int (*spiel)[N][N]){
	int (*anfang)[N][N];
	FILE * stream=fopen("spiel.txt", "r");
	if(stream){
		int x;
		for(int i=0; i<N; i++){
			for(int j=0; j<N && fscanf(stream, "%d", &x)>0; j++){
				(*spiel)[i][j]=x;
				//printf("%d ", (*spiel)[i][j]);
			}
			//printf("\n");
		}
		fclose(stream);
	}	
	else{
		printf("Die Datei konnte nicht geöffnet werden.\n");
	}
}

void zeichneSudoku(int spiel[N][N]){

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			printf("%d ", spiel[i][j]);
		}
		printf("\n");
	}
}


int testeQuadrat(int mat[N][N], int x, int y){
	int quadrat[N]={0};
	for(int i=x; i<x+3; i++){
		for(int j=y; j<y+3; j++){
			int a=mat[i][j];
			quadrat[a-1]++;
		}
	}
	
	for(int k; k<N; k++){
		if(quadrat[k]!=1){
			printf("Werte im felherhaften Teilquadrat:\n");
			for(int l=0; l<N; l++){
				printf("%d: %d\n", l+1, quadrat[l]);
			}
			return 0;
		}
	}
	return 1;
}


int sudoku(int mat[N][N]){
	int i, j, k;
	for (i=0; i<N; i++){
		int zeile[N]={0};
		int spalte[N]={0};

		for(j=0; j<N; j++){
			int a=mat[i][j];
			int b=mat[j][i];
			if(a>=0 && a<=N)
				zeile[a-1]++;
			if(b>=0 && b<=N)
				spalte[b-1]++;
		}
	
		for(k=0; k<N; k++){
			if(zeile[k]!=1){
				printf("\nFehler in Zeile:%d\n", i+1);
				printf("Wert: %d", k+1);
				return 0;
			}
			if(spalte[k]!=1){
				printf("\nFehler in Spalte:%d\n", i+1);
				printf("Wert: %d", k+1);
				return 0;
			}
		}
	}
		
	int zaehler=0;
	for(i=0; i<N; i+=3){
		for(j=0; j<N; j+=3){
			if(testeQuadrat(mat, i, j)==0){
				printf("Fehler im Teilquadrat [%d][%d].\n", i+1, j+1);
				return 0;
			}
		}
	}
	
	return 1;
}

bool fuelleSudoku(int spiel[N][N], int i, int j){		//true=konnte ausgefüllt werden; false=unmöglich zu lösen
	if(sudoku(spiel)){
		printf("Sudoku gelöst: \n");
		zeichneSudoku(spiel);
		return true;
	}
	if(i==N || j==N)
		return false;
	
	int ii, jj;
	if(j==N-1){
		ii=++i;
		jj=0;
	}
	else{
		ii=i;
		jj=++j;
	}

	if(spiel[i][j]==0){
		spiel[i][j]=1;
		if(fuelleSudoku(spiel, ii, jj))
			return true;
		spiel[i][j]=2;
		if(fuelleSudoku(spiel, ii, jj))
			return true;
		spiel[i][j]=3;
		if(fuelleSudoku(spiel, ii, jj))
			return true;
		spiel[i][j]=4;
		if(fuelleSudoku(spiel, ii, jj))
			return true;
		spiel[i][j]=5;
		if(fuelleSudoku(spiel, ii, jj))
			return true;
		spiel[i][j]=6;
		if(fuelleSudoku(spiel, ii, jj))
			return true;
		spiel[i][j]=7;
		if(fuelleSudoku(spiel, ii, jj))
			return true;
		spiel[i][j]=8;
		if(fuelleSudoku(spiel, ii, jj))
			return true;
		spiel[i][j]=9;
		if(fuelleSudoku(spiel, ii, jj))
			return true;
	}
	else{
		if(fuelleSudoku(spiel, ii, jj))
			return true;
	}
	return false;
}


int main(){
	


	int spiel[N][N];
	int (*zeiger)[N][N];
	zeiger= &spiel;
	liesSudoku(zeiger);

	fuelleSudoku(spiel, 0, 0);

	/*
	int ergebnis=sudoku(spiel);
	if(ergebnis==1)
		printf("Einwandfrei\n");
	else if(ergebnis==0)
		printf("\nFehler im Sudoku\n");
	*/
	return 0;
}
