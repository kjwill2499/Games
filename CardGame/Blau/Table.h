
#ifndef _TABLE_H_
#define _TABLE_H_

#include "Boolean.h"
#include "Player.h"

#define MAX_NUM_PLAYERS 4
#define TILES_IN_FACTORY 4


typedef struct
{
    TileBag tileBag;
    TileType tileFactory[MAX_NUM_PLAYERS * 2 + 1][TileTypeCount];
    TileType centerOfTable[TileTypeCount];
    bool firstFromCenter;
    unsigned int tilesOnTable;
    Player * players[MAX_NUM_PLAYERS];
    unsigned int startingPosition;
    unsigned int currentPlayer;
    unsigned int numberOfPlayers;
    unsigned int numberOfFactories;
} Table;

/* Controls dialogue to determine the number of players and each players name*/
Table * InitializeTable();

void SkipRestOfLine(void);

void ClearTable(Table * table);

//bool RestartGame(Table * table);

bool PlayRoundAndContinue(Table * table);

void PrintTable(const Table * table);

#endif