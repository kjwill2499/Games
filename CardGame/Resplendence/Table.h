
#ifndef _TABLE_H_
#define _TABLE_H_

#include "Boolean.h"
#include "Card.h"
#include "Player.h"

#define MAX_NUM_PLAYERS 4
#define MAX_NUM_NOBLES 5
#define NUM_LEVEL 3
#define NUM_CARDS_ROW 4


typedef struct
{
    GemType gemTokens[GemCount];
    Noble * nobles[MAX_NUM_NOBLES];
    Card * tableCards[NUM_LEVEL][NUM_CARDS_ROW];
    unsigned int pointValue;
    unsigned int goldTokens;
    Player * players[MAX_NUM_PLAYERS];
} Table;

bool TakeTurn(Table * table, Player player)
bool SetTable(Table * table);

bool PlayRound(Table * table);

void PrintTable(Table * table);

bool ShufflePile(void * pile[], unsigned int numCards);

#endif
