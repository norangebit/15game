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

typedef struct Point{
  int i;//Row
  int j;//Column
}Point;

int mat[DIM][DIM];//Matrix of the game
Point X;//Position of empty blank
Point S;//Position of choice
Score *HEAD=NULL;//Head of Leaderboard

int Win(int *p){
  int i, ordinata=1;
  for(i=0;i<DIM*DIM-1 && ordinata;i++){
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

int Playable(int scelta){
  int giocabile=0, k;
  Point vet[DIM];

  for(k=0;k<DIM;k++){
    vet[k].i=X.i;
    vet[k].j=X.j;
  }

  if(X.i){
    vet[0].i=X.i-1;
    vet[0].j=X.j;
  }

  if(X.i!=3){
    vet[1].i=X.i+1;
    vet[1].j=X.j;
  }

  if(X.j){
    vet[2].i=X.i;
    vet[2].j=X.j-1;
  }

  if(X.j!=3){
    vet[3].i=X.i;
    vet[3].j=X.j+1;
  }

  for(k=0;k<DIM;k++)
    if(mat[vet[k].i][vet[k].j]==scelta){
      S.i=vet[k].i;
      S.j=vet[k].j;
      giocabile=1;
    }

  return(giocabile);
}

void Replace(int scelta){

  //Swap position of choice and blank
  mat[X.i][X.j]=scelta;
  mat[S.i][S.j]=16;
  X.i=S.i;
  X.j=S.j;
}

void Genesis(int *p){
  int i, j, ok, parity;

  srand(time(NULL));

  do{
    parity=0;
    for(i=0;i<DIM*DIM;i++){
      do{
        ok=1;
        *(p+i)=rand()%16+1;

        //Check uniqueness
        for(j=0;j<i && ok==1;j++)
          if(*(p+i)==*(p+j))
            ok=0;

      }while(!ok);

      if(*(p+i)==16){

          X.i=i/DIM;
          X.j=i%DIM;
        }
    }

    //Check solvability
    for(i=0;i<DIM*DIM-1;i++)
      for(j=i+1;j<DIM*DIM;j++)
        if(*(p+i)>*(p+j))
          parity++;
    parity+=X.i+X.j;

  }while(parity%2);
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

  printf("\n  ---Leaderboard---\n\n");
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
