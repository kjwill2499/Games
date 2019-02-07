#include "Tile.h"
#include "Boolean.h"
#include <stdio.h>

bool HasAllOfType(const bool wall[TileTypeCount][TileTypeCount], const TileType tileType)
{
    unsigned int row;
    for (row = 0; row < TileTypeCount; ++row)
    {
        unsigned int column = (tileType + row) % TileTypeCount;
        if (wall[row][column] == 0)
        {
            return false;
        }
    }
    return true;
}

unsigned int NumberTouching(const bool wall[TileTypeCount][TileTypeCount], const unsigned int row, const unsigned int column, const bool isColumn)
{
    unsigned int touching = 0;
    bool hasNewTile = false;
    unsigned int index;
    for (index = 0; index < TileTypeCount; ++index)
    {
        if (isColumn)
        {
            if (wall[index][column] == true)
            {
                ++touching;
                if (index == row)  hasNewTile = true;
            }
            else
            {
                if (hasNewTile) break;
                touching = 0;
            }
        }
        else
        {
            if (wall[row][index] == true)
            {
                ++touching;
                if (index == column)  hasNewTile = true;
            }
            else
            {
                if (hasNewTile) return touching;
                touching = 0;
            }
        }
    }
    return touching;
}

const char * TypeToNames(TileType type)
{
    static const char * TypeToNames[TileTypeCount] = { "Blue", "Yellow", "Red", "Black", "White" };
    return TypeToNames[type];
}

char TypeToChar(TileType tileType, bool isUpper)
{
    char upper[TileTypeCount] = { 'B', 'Y', 'R', 'K', 'W' };
    return isUpper ? upper[tileType]  : upper[tileType] + ('a' - 'A');
}

bool isFactoryEmpty(const TileType * tileFactory)
{
    unsigned int index;
    for (index = 0; index < TileTypeCount; ++index)
    {
        if (tileFactory[index] != 0) return false;
    }
    return true;
}

void PrintFactory(const TileType * tileFactory, bool withNumbers)
{
    unsigned int typeIndex;
    for (typeIndex = 0; typeIndex < TileTypeCount; typeIndex++)
    {
        if (tileFactory[typeIndex] != 0)
        {
            int printIndex;
            printf("\n    ");
                if (withNumbers) printf("%u)", typeIndex + 1);
            for (printIndex = 0; printIndex < tileFactory[typeIndex]; ++printIndex)
            {
                printf(" (%c)", TypeToChar(typeIndex, true));
            }
        }
    }
}

void PrintTileBag(const TileBag * tileBag)
{
    TileType index;
    printf("\n\n    Number of Tiles in the Bag: %u\n    Tiles in Bag...", tileBag->numTile);

    for (index = 0; index < TileTypeCount; index++)
    {
        printf("    %s (%c): %u", TypeToNames(index), TypeToChar(index, true), tileBag->numOfType[index]);
    }
}