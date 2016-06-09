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

int Win(){
  int i, ordinata=1;
  for(i=0;i<DIM*DIM-1 && ordinata;i++){
    if(mat[i/DIM][i%DIM]>mat[(i+1)/DIM][(i+1)%DIM])
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
  int k;

  if(!scelta)
    return 1;

  for(k=0;k<DIM*DIM;k++)
    if(mat[k/DIM][k%DIM]==scelta){
      S.i=k/DIM;
      S.j=k%DIM;
    }

  if(abs(X.i-S.i)+abs(X.j-S.j)!=1)
    return 0;

  return 1;
}

void Replace(){

  //Swap position of choice and blank
  mat[X.i][X.j]=mat[S.i][S.j];
  mat[S.i][S.j]=16;
  X.i=S.i;
  X.j=S.j;
}

void Shuffle(){
  int i, move;
  int n=rand()%30+20;

  for(i=0;i<n;i++){
    do{

      move=rand()%DIM;
      S=X;
      if(!move)
        S.i = X.i==0?0:X.i-1;
      else if(move==1)
        S.i = X.i==DIM-1?DIM-1:X.i+1;
      else if(move==2)
        S.j = X.j==0?0:X.j-1;
      else
        S.j = X.j==DIM-1?DIM-1:X.i+1;

    }while(!Playable(mat[S.i][S.j]));
    printf("\n%d\n", mat[S.i][S.j]);
    Replace();
  }
}

void Genesis(){
  int k, z, i, j, ok, parity;

  srand(time(NULL));

  do{
    parity=0;
    for(k=0;k<DIM*DIM;k++){
      i=k/DIM;
      j=k%DIM;
      do{
        ok=1;
        mat[i][j]=rand()%16+1;

        //Check uniqueness
        for(z=0;z<k && ok==1;z++)
          if(mat[i][j]==mat[z/DIM][z%DIM])
            ok=0;

      }while(!ok);

      if(mat[i][j]==16){
          X.i=i;
          X.j=j;
        }
    }

    //Check solvability
    for(k=0;k<DIM*DIM-1;k++)
      for(z=k+1;z<DIM*DIM;z++)
        if(mat[k/DIM][k%DIM]>mat[z/DIM][z%DIM])
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
