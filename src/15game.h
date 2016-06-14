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

//It returns 1 if the matrix is sorted, otherwise 0
int Win();

//Convert string to Point
void Convert(char *userSelection, Point *choice);

//It returns 1 if the user's choice is acceptable, otherwise 0
int Playable(Point choice);

//Print the matrix
void Print();

//Updates the values ​​of the matrix
void Replace(Point choice);

//Generates a random matrix
void Genesis();

//Make between 20 and 50 random moves
void Shuffle();





//CHECKPOINT'S FUNCTION
//Read from file,It returns 1 if the process has been successful
 int Restart(char *nome, int *count);

 //Save into file
 void SaveCheckpoint(char *nome, int count);





//LEADERBOARD'S FUNCTION
//Create a new entry in the leaderboard
void AddLeaderboard(char *name, int score);

//It fits neatly into a new score leaderboard
void LinkLeaderboard(Score *New);

//Print the Leaderboard
void PrintLeaderboard();

//It reads from file the leaderboard
void ReadLeaderboard(FILE *src);

//Save to file the leaderboard
void SaveLeaderboard(FILE *src);
