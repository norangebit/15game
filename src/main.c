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

#include "15game.h"
#include <stdio_ext.h>

int main(){
  int scelta, count=0;
  char nome[200];
  FILE *src=fopen("../Leaderboard.dat", "r");

  if(!src){
    src=fopen("../Leaderboard.dat", "w");
    fclose(src);
    src=fopen("../Leaderboard.dat", "r");
  }
  ReadLeaderboard(src);
  fclose(src);
  

  printf("Inserisci il tuo nome: ");
  scanf("%s", nome);
  printf("Benvenuto %s\n\n", nome);

  Genesis(mat);

  do{
    Print();

    do{
      printf("Inserisci il numero che vuoi spostare: ");
      scanf("%d", &scelta);
    }while(!Giocabile(scelta));

    count++;
    Replace(scelta);

  }while(!Win(mat));

  printf("\n   You Win!\n");
  printf("\nHai completato il puzzle in %d mosse.\n", count);
  AddLeaderboard(nome, count);
  PrintLeaderboard();

  src=fopen("../Leaderboard.dat", "w");
  SaveLeaderboard(src);
  fclose(src);

  __fpurge(stdin);
  getchar();
}
