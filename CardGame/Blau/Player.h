#pragma once
#include "Tile.h"

#ifndef _PLAYER_H_
#define _PLAYER_H_

#define MAX_NAME_LENGTH 16

typedef struct
{
    char name[MAX_NAME_LENGTH]; 
    PatterLine patternLine;
    bool wall[TileTypeCount][TileTypeCount];
    unsigned int brokenTiles;
    int score;
} Player;

Player * CreatePlayer(void);

void DestroyPlayer(Player * player);

void PrintPlayer(Player * player);

void PrintBroken(const Player * player);

/*Scores the round and returns true if any row of wall is complete at end*/
bool ScorePlayerIsComplete(Player * player, TileBag * tileBag);



#endif