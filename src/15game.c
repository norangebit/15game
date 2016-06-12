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
#include <ctype.h>
#define DIM 4

typedef struct Score{
  char *name;
  int score;
  struct Score *next;
}Score;

typedef struct Point{
  int i;//Row
  int j;//Column
}Point;

int mat[DIM*DIM];//Matrix of the game
Point blank;//Position of blank
Score *HEAD=NULL;//Head of Leaderboard

int Win(){
  int i, sorted=1;
  for(i=0;i<DIM*DIM-1 && sorted;i++){
    if(mat[i]>mat[i+1])
      sorted=0;
  }
  return(sorted);
}

void Print(){
  int i, j;
  for(i=0;i<DIM*DIM;i++){
    if(!(i%DIM))
      putchar('\n');

    if((j=mat[i])==16)
      printf("   ");
    else
      printf("%3d", j);
  }
  putchar('\n');
}

void Convert(char *userSelection, Point *choice){
  int intSelection, k;

  if(isdigit(userSelection[0])){//Selection by the numbers
    intSelection=atoi(userSelection);

    if(!intSelection)//For shuffle
      choice->i=-1;
    else{
      for(k=0;k<DIM*DIM;k++)
        if(mat[k]==intSelection){
          choice->i=k/DIM;
          choice->j=k%DIM;
          break;
        }
    }

  }else{//Selection by the letter
    *choice=blank;

    if(userSelection[0]=='k')//Up shift
      choice->i = blank.i==0?0:blank.i-1;//check border of matrix
    else if(userSelection[0]=='j')//Down shift
      choice->i = blank.i==DIM-1?DIM-1:blank.i+1;
    else if(userSelection[0]=='h')//Letf shift
      choice->j = blank.j==0?0:blank.j-1;
    else if(userSelection[0]=='l')//Right shift
      choice->j = blank.j==DIM-1?DIM-1:blank.j+1;
  }
}

int Playable(Point choice){

  //Shuffle test
  if(choice.i==-1)
    return 1;

  //Collision test
  if(abs(blank.i-choice.i)+abs(blank.j-choice.j)!=1)
    return 0;

  return 1;
}

void Replace(Point choice){

  //Swap position of choice and blank
  mat[blank.i*DIM + blank.j]=mat[choice.i*DIM + choice.j];
  mat[choice.i*DIM + choice.j]=16;
  blank=choice;
}

void Shuffle(){
  int i, move;
  Point randomChoice;////Position of random choice
  int n=rand()%30+20;//number of random moves

  for(i=0;i<n;i++){

    do{
      move=rand()%DIM;
      randomChoice=blank;

      if(!move)//Up shift
        randomChoice.i = blank.i==0?0:blank.i-1;//check border of matrix
      else if(move==1)//Down shift
        randomChoice.i = blank.i==DIM-1?DIM-1:blank.i+1;
      else if(move==2)//Letf shift
        randomChoice.j = blank.j==0?0:blank.j-1;
      else//Right shift
        randomChoice.j = blank.j==DIM-1?DIM-1:blank.j+1;

    }while(!Playable(randomChoice));

    Replace(randomChoice);
  }
}

void Genesis(){
  int k, z, ok, parity;

  do{
    parity=0;
    for(k=0;k<DIM*DIM;k++){
      do{
        ok=1;
        mat[k]=rand()%16+1;

        //Check uniqueness
        for(z=0;z<k && ok==1;z++)
          if(mat[k]==mat[z])
            ok=0;

      }while(!ok);

      if(mat[k]==16){
          blank.i=k/4;
          blank.j=k%4;
        }
    }

    //Check solvability
    for(k=0;k<DIM*DIM-1;k++)
      for(z=k+1;z<DIM*DIM;z++)
        if(mat[k]>mat[z])
          parity++;
    parity+=blank.i+blank.j;

  }while(parity%2);
}

void LinkLeaderboard(Score *New){
  Score *cur=HEAD, *pre=NULL;//current and previous initialization

  //list scrolling
  while(cur && cur->score<=New->score){
    pre=cur;
    cur=cur->next;
  }

  if(!pre){//add in head
    New->next=HEAD;
    HEAD=New;
  }else{//add in the queue or in the middle
    New->next=cur;
    pre->next=New;
  }
}

void AddLeaderboard(char *name, int score){
  Score *New=(Score *)malloc(sizeof(Score));
  New->name=(char *)calloc(strlen(name)+1, sizeof(char));
  strcpy(New->name, name);
  New->score=score;

  LinkLeaderboard(New);
}

void PrintLeaderboard(){
  Score *cur=HEAD;
  int n=1;

  printf("\n  ---Leaderboard---\n\n");
  while(cur){
    printf("%d. %s  %d\n", n++, cur->name, cur->score);
    cur=cur->next;
  }
}

void ReadLeaderboard(FILE *src){
  char name[200];
  int score;

  while(fscanf(src, "%s", name) !=EOF){
    fscanf(src, "%d", &score);
    AddLeaderboard(name, score);
  }
}

void SaveLeaderboard(FILE *src){
  Score *cur=HEAD;

  while(cur){
    fprintf(src, "%s %d\n", cur->name, cur->score);
    cur=cur->next;
  }
}
