

#ifndef _TILE_H_
#define _TILE_H_

#include "Boolean.h"

#define MAX_BROKEN_TILES 7

typedef enum
{
    TILE_BLUE,
    TILE_YELLOW,
    TILE_RED,
    TILE_BLACK,
    TILE_WHITE,
    TileTypeCount
}TileType;

typedef struct
{
    TileType type[TileTypeCount];
    unsigned int contents[TileTypeCount];
} PatterLine;

typedef struct
{
    TileType numOfType[TileTypeCount];
    unsigned int numTile;
} TileBag;

bool HasAllOfType(const bool wall[TileTypeCount][TileTypeCount], const TileType tileType);

unsigned int NumberTouching(const bool wall[TileTypeCount][TileTypeCount], const unsigned int row, const unsigned int column, const bool isColumn);

const char * TypeToNames(TileType tileType);

char TypeToChar(TileType tileType, bool isUpper);

void PrintTileBag(const TileBag * tileBag);

void PrintFactory(const TileType * tileFactory, bool withNumbers);

bool isFactoryEmpty(const TileType * tileFactory);

#endif
