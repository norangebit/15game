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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DIM 4

typedef struct Score{
  char *nome;
  int score;
  struct Score *next;
}Score;

int mat[DIM][DIM]={{1,2,3,4},{5,6,7,8},{9,10,15,11},{13,14,16,12}};
Score *HEAD=NULL;

int Win(int *p){
  int i, ordinata=1;
  for(i=0;i<DIM*DIM-1;i++){
    if(*(p++)>*(p))
      ordinata=0;
  }
  return(ordinata);
}

void Print(){
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

int Giocabile(int scelta){
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

void Replace(int scelta){
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

void LinkLeaderboard(Score *New){
  Score *cur=HEAD, *pre=NULL;

  while(cur && cur->score<=New->score){
    pre=cur;
    cur=cur->next;
  }

  if(!pre){
    New->next=HEAD;
    HEAD=New;
  }else{
    New->next=cur;
    pre->next=New;
  }
}

void AddLeaderboard(char *nome, int score){
  Score *New=(Score *)malloc(sizeof(Score));
  New->nome=(char *)calloc(strlen(nome)+1, sizeof(char));
  strcpy(New->nome, nome);
  New->score=score;

  LinkLeaderboard(New);
}

void PrintLeaderboard(){
  Score *cur=HEAD;
  int n=1;

  while(cur){
    printf("%d. %s  %d\n", n++, cur->nome, cur->score);
    cur=cur->next;
  }
}

void ReadLeaderboard(FILE *src){
  char nome[200];
  int score;

  while(fscanf(src, "%s", nome) !=EOF){
    fscanf(src, "%d", &score);
    AddLeaderboard(nome, score);
  }
}

void SaveLeaderboard(FILE *src){
  Score *cur=HEAD;

  while(cur){
    fprintf(src, "%s %d\n", cur->nome, cur->score);
    cur=cur->next;
  }
}
