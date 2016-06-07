/*
    Copyright (c) 2016 Orange_dugongo

    This file is part of 15game.

    15game is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    15game is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with 15game.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <time.h>
#define DIM 4
int Win(int *);
int Giocabile(int mat[DIM][DIM], int);
void Print(int mat[DIM][DIM]);
void Replace(int mat[DIM][DIM], int);
void Genesis(int *p);

int main(){
  int scelta, count=0, mat[DIM][DIM];//={{1,2,3,4},{5,6,7,8},{9,10,15,11},{13,14,16,12}};//test vittoria
  Genesis(mat);
  do{
    Print(mat);
    do{
      printf("Inserisci il numero che vuoi spostare: ");
      scanf("%d", &scelta);
    }while(!Giocabile(mat, scelta));
    count++;
    Replace(mat, scelta);
  }while(!Win(mat));
  printf("\n   You Win!\n");
  Print(mat);
  printf("\nHai completato il puzzle in %d mosse.", count);
}

int Win(int *p){
  int i, ordinata=1;
  for(i=0;i<DIM*DIM-1;i++){
    if(*(p++)>*(p))
      ordinata=0;
  }
  return(ordinata);
}

void Print(int mat[DIM][DIM]){
  int i, j;
  for(i=0;i<DIM;i++){
    for(j=0;j<DIM;j++){
      if(mat[i][j]==16)
        printf("   ");
      else
        printf("%3d", mat[i][j]);
    }
    printf("\n");
  }
}

int Giocabile(int mat[DIM][DIM], int scelta){
  int vet[DIM], giocabile=0, i, j;
  vet[0]=0;
  for(i=0;i<DIM && vet[0]==0;i++){
    for(j=0;j<DIM;j++){
      if(mat[i][j]==16){
        vet[0]=mat[i-1][j];
        vet[1]=mat[i+1][j];
        vet[2]=mat[i][j-1];
        vet[3]=mat[i][j+1];
      }
    }
  }
  if(vet[0]==scelta || vet[1]==scelta || vet[2]==scelta || vet[3]==scelta)
    giocabile=1;
  return(giocabile);
}

void Replace(int mat[DIM][DIM], int scelta){
  int i, j, a_i, a_j, b_i, b_j;
  for(i=0;i<DIM;i++){
    for(j=0;j<DIM;j++){
      if(mat[i][j]==16){
        a_i=i;
        a_j=j;
      }
      if(mat[i][j]==scelta){
        b_i=i;
        b_j=j;
      }
    }
  }
  mat[a_i][a_j]=scelta;
  mat[b_i][b_j]=16;
}

void Genesis(int *p){
  int i, j, ok;
  for(i=0;i<DIM*DIM;i++){
    do{
      ok=1;
      *(p+i)=rand()%16+1;
      for(j=0;j<i && ok==1;j++){
        if(*(p+i)==*(p+j))
          ok=0;
      }
    }while(!ok);
  }
}
