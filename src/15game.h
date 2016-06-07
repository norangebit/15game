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

#include "15game.c"

//Restituisce 1 se la matrice è ordinata, altrimenti 0
int Win(int *p);

//Restituisce 1 se la scelta dell'utente è accettabile
int Giocabile(int scelta);

//Stampa la matrice
void Print();

//Aggiorna i valori della matrice
void Replace(int scelta);

//Genera una matrice casuale
void Genesis(int *p);

//Crea una nuova voce nella leaderboard
void AddLeaderboard(char *nome, int score);

//Inserisce in modo ordinato un nuovo score nella leaderboard
void LinkLeaderboard(Score *New);

//Stampa la Leaderboard
void PrintLeaderboard();

//Legge da file la leaderboard
void ReadLeaderboard(FILE *src);

//Salva su file la leaderboard
void SaveLeaderboard(FILE *src);
