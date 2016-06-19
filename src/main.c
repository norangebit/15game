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
    int count=0;
    char *name=(char *)malloc(200*sizeof(char));
    char userSelection[2];//capturing user input
    Point choice;//Position of user choice
    FILE *src=fopen("../.Leaderboard.dat", "r");//Leaderboard file

    if(!src){
        src=fopen("../.Leaderboard.dat", "w");
        fclose(src);
        src=fopen("../.Leaderboard.dat", "r");
    }
    ReadLeaderboard(src);
    fclose(src);

    if(Restart(name, &count))
        printf("Welcome back %s\n\n", name);
    else{
        printf("Insert your name: ");
        scanf("%s", name);
        name=(char *)realloc(name, (strlen(name)+1)*sizeof(char));

        srand(time(NULL));
        Genesis();
    }

    do{
        Print();

        do{
            printf("\nType the number you want to move(0 for shuffle): ");
            scanf("%s", userSelection);
            Convert(userSelection, &choice);
        }while(!Playable(choice));

        count++;

        if(choice.i>=0)//Stanadard move
            Replace(choice);
        else//Special move
            if(choice.i==-1)
                Shuffle();
            else if (choice.i==-2)
                NewGame(name, &count);
            else if (choice.i==-3)
                Quit(name, count);


        if(!(count%5))
            SaveCheckpoint(name, count);

    }while(!Win());

    SaveCheckpoint(name, count);

    printf("\n   You Win!\n");
    printf("\nYou've completed the puzzle in %d moves.\n", count);
    AddLeaderboard(name, count);
    PrintLeaderboard();

    src=fopen("../.Leaderboard.dat", "w");
    SaveLeaderboard(src);
    fclose(src);

    __fpurge(stdin);
    getchar();
}
