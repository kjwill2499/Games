#pragma once

#include "Card.h"

#define MAX_NAME_LENGTH 16

typedef struct
{
    char name[MAX_NAME_LENGTH];
    GemType cardGems[GemCount];
    GemType tokenGems[GemCount];
    Noble nobles[5];
    unsigned int goldPieces;
    unsigned int victoryPoints;
} Player;


//bool IsAffordable(Player * player, const Card card);

//bool BuyCard(Player * player, const Card);

//bool ReserveCard(Player * player, const Card);

//bool TakeTokens(Player * player, Table * table);

