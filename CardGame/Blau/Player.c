

#include "Player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FULL_COLUMN_BONUS 7
#define FULL_ROW_BONUS 2
#define ALL_OF_TYPE_BONUS 10

const int brokenValue[MAX_BROKEN_TILES] = { -1, -1, -2, -2, -2, -3, -3 };

const unsigned int brokenCost[MAX_BROKEN_TILES] = { 1, 2, 4, 6, 8, 11, 14 };

void PlayerSkipRestOfLine(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) continue;
}

void PrintBroken(const Player * player)
{
    unsigned int brokenTileIndex;
printf("Broken: ");
for (brokenTileIndex = 0; brokenTileIndex < MAX_BROKEN_TILES; ++brokenTileIndex)
{
    if (brokenTileIndex < player->brokenTiles) printf("[(%d)]", brokenValue[brokenTileIndex]);
    else printf("[ %d ]", brokenValue[brokenTileIndex]);
}
}

void PrintPlayer(Player * player)
{
    unsigned int rowIndex;
    printf("\n\n    Name: %-*s     Score: %-17d    ", 19, player->name, player->score);
    for (rowIndex = 0; rowIndex < TileTypeCount; ++rowIndex)
    {
        unsigned int columnIndex;
        printf("\n\n    %u) ", rowIndex + 1);
        for (columnIndex = TileTypeCount; columnIndex >= 1; --columnIndex)
        {
            if (columnIndex > (rowIndex + 1)) printf("     ");
            else if (columnIndex > ((rowIndex + 1) - player->patternLine.contents[rowIndex])) printf("[(%c)]", TypeToChar(player->patternLine.type[rowIndex], true));
            else printf("[   ]");
        }
        printf(" -> ");
        for (columnIndex = 0; columnIndex < TileTypeCount; ++columnIndex)
        {
            if (player->wall[rowIndex][columnIndex])
            {
                printf(" (%c) ", TypeToChar((TileTypeCount + columnIndex - rowIndex) % TileTypeCount, true));
            }
            else printf("  %c  ", TypeToChar((TileTypeCount + columnIndex - rowIndex) % TileTypeCount, false));
        }
    }
    printf("\n\n    6)   ");
    PrintBroken(player);
}

bool ScorePlayerIsComplete(Player * player, TileBag * tileBag)
{
    unsigned int row;
    bool isComplete = false;
    for (row = 0; row < TileTypeCount; ++row)
    {
        if (player->patternLine.contents[row] >= row + 1)
        {
            unsigned int tileType = player->patternLine.type[row];
            unsigned int column = (tileType + row) % TileTypeCount;
            if (player->wall[row][column] == false)
            {
                unsigned int newPoints = 0;
                unsigned int rowPoints = 0;
                unsigned int columnPoints = 0;
                player->wall[row][column] = true;
                tileBag->numOfType[player->patternLine.type[row]] += player->patternLine.contents[row] - 1;
                tileBag->numTile += player->patternLine.contents[row] - 1;
                player->patternLine.contents[row] = 0;
                columnPoints = NumberTouching(player->wall, row, column, true);
                if (columnPoints == TileTypeCount) columnPoints += FULL_COLUMN_BONUS;
                if (columnPoints == 1) columnPoints = 0;
                rowPoints = NumberTouching(player->wall, row, column, false);
                if (rowPoints == TileTypeCount)
                {
                    rowPoints += FULL_ROW_BONUS;
                    isComplete = true;
                }
                if (rowPoints == 1) rowPoints = 0;
                newPoints += (rowPoints + columnPoints);
                if (newPoints == 0) newPoints = 1;
                if (HasAllOfType(player->wall, tileType)) newPoints += ALL_OF_TYPE_BONUS;
                printf("\n\n  %s placed a %s tile in row %u for %u points!", player->name, TypeToNames(tileType), row + 1, newPoints);
                player->score += newPoints;
                PrintPlayer(player);
                printf("\n\n  Press ENTER to continue!");
                PlayerSkipRestOfLine();
            }
        }
    }
    if (player->brokenTiles > 0)
    {
        unsigned int negativePoints;
        if (player->brokenTiles > MAX_BROKEN_TILES)
        {
            negativePoints = brokenCost[MAX_BROKEN_TILES - 1] + (player->brokenTiles - MAX_BROKEN_TILES) * 3;
        }
        else negativePoints = brokenCost[player->brokenTiles - 1];
        player->score -= negativePoints;
        printf("\n\n  %s had %u broken tiles for -%u points.", player->name, player->brokenTiles, negativePoints);
        player->brokenTiles = 0;
        PrintPlayer(player);
    }
    printf("\n\n  %s now has %d points", player->name, player->score);
    printf("\n\n  Press ENTER to continue!");
    PlayerSkipRestOfLine();
    return isComplete;
}


Player * CreatePlayer(void)
{
    Player * player = (Player *)calloc(1, sizeof(Player));
    if (player == NULL) return NULL;
    strcpy(player->name, "Default Name");
    return player;
}

void DestroyPlayer(Player * player)
{
    if (player != NULL)
    {
        free(player);
    }
}

