
#include "Boolean.h"
#include "Table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void SkipRestOfLine(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) continue;
}


bool GetYOrNFromUser(void)
{
    int ch;
    do
    {
        printf(" (ENTER Y or N): ");
        ch = getchar();
        SkipRestOfLine();
    } while (ch != 'y' && ch != 'n' && ch != 'Y' && ch != 'N');
    if (ch == 'y' || ch == 'Y') return true;
    return false;
}


bool GetDigitFromUser(unsigned int * number, unsigned int min, unsigned int max, bool convertToIndex)
{
    int ch = getchar();
    SkipRestOfLine();
    if (ch < '0' +  (int)min || ch > '0' + (int)max)
    {
        printf("\n  ERROR: Entry must be a number betwen %u and %u\n", min, max);
        return false;
    }
    *number = (unsigned int)ch - '0';
    if (convertToIndex) --(*number);
    return true;
}


unsigned int SelectPlayerByName(Table * table)
{
    unsigned int playerIndex = 0;
    unsigned int playerSelected = 0;
    printf("\n");
    while (playerIndex < MAX_NUM_PLAYERS && table->players[playerIndex] != NULL) {
        printf("\n  %u) %s", (playerIndex + 1), table->players[playerIndex]->name);
        ++playerIndex;
    }
    do {
        printf("\n\n  Please Enter the number of the player to go first: ");
    } while(!GetDigitFromUser(&playerSelected, 1, table->numberOfPlayers, true));
    return playerSelected;
}


bool GetStringFromUser(char * name, unsigned int maxNameLength, char * compare)
{
    char *pos;
    fgets(name, maxNameLength, stdin);
    if ((pos = strchr(name, '\n')) != NULL) *pos = '\0';
    else SkipRestOfLine();
    _strupr(name);
    return strcmp(name, compare);
}


Table * InitializeTable()
{
    static Table table =
    {
        .tileBag.numOfType = {20, 20, 20, 20, 20},
        .tileBag.numTile = 100,
        .tilesOnTable = 0,
        .firstFromCenter = true,
        .startingPosition = (unsigned int) -1,
        .currentPlayer = 0,
        .numberOfPlayers = 0,
    };
/*
** Initialize the random number generator by calling srand() once per execution of program.
** Call rand() each time a new random integer is desired. Use % to constrain its values
** between 0 and N-1, where N is an integer of your choosing.
*/
    srand((unsigned int)(time(0)));
    
    printf("  Welcome to the Table.  This game is called Blau (german for blue).\n"
            "  it is modeled after the popular game Azul and is intended for private \n"
            "  use only.\n\n");
    {
        bool hasName = true;
        do {
            char name[MAX_NAME_LENGTH];
            char * keyword = "DONE";
            printf("\n  Please Enter Player #%u's name (or %s if no more players): ", (table.numberOfPlayers + 1), keyword);
            hasName = GetStringFromUser(name, MAX_NAME_LENGTH, keyword);
            if (hasName)
            {
                if (name[0] == '\0')
                {
                    strcpy(name, "Player  ");
                    name[7] = '1' + (char)table.numberOfPlayers;
                }
                table.players[table.numberOfPlayers] = CreatePlayer();
                strcpy(table.players[table.numberOfPlayers]->name, name);
                ++table.numberOfPlayers;
            }
        } while (table.numberOfPlayers < 4 && (hasName || table.numberOfPlayers == 0));
        table.numberOfFactories = table.numberOfPlayers * 2 + 1;
        table.currentPlayer = SelectPlayerByName(&table);
    }
    return &table;
}


unsigned int GetRandomNumber(unsigned int range)
{
    if (range == 0) return UINT_MAX;
    {
        /* Use division truncation to discover the largest number divisible by range. */
        const unsigned int randLimit = (RAND_MAX / range) * range;
        unsigned int number = randLimit;
        while (number >= randLimit) number = (unsigned int)rand();
        return number % range;
    }
}


void ClearTable(Table * table)
{
    if (table != NULL)
    {
        unsigned int playerIndex;
        for (playerIndex = 0; playerIndex < MAX_NUM_PLAYERS; ++playerIndex)
        {
            DestroyPlayer(table->players[playerIndex]);
            table->players[playerIndex] = NULL;
        }
    }
}


bool TileFromBag(TileType * tileFromBag, TileBag * tileBag)
{
    if (tileBag->numTile == 0)
    {
        printf("\n  The Tile Bag is Empty!");
        return false;
    }
    unsigned int rand = GetRandomNumber(tileBag->numTile);
    TileType index;
    for (index = 0; index < TileTypeCount; ++index)
    {
        if ((int) rand <= tileBag->numOfType[index])
        {
            --tileBag->numOfType[index];
            --tileBag->numTile;
            *tileFromBag = index;
            return true;
        }
        else
        {
            rand -= tileBag->numOfType[index];
        }
    }
    return false;
}


void FillFactories(Table * table)
{
    unsigned int factoryIndex;
    for (factoryIndex = 0; factoryIndex < table->numberOfFactories; ++factoryIndex)
    {
        unsigned int index;
        for (index = 0; index < TILES_IN_FACTORY; ++index)
        {
            TileType tileFromBag;
            if (TileFromBag(&tileFromBag, &table->tileBag))
            {
                ++table->tileFactory[factoryIndex][tileFromBag];
                ++table->tilesOnTable;
            }
            else break;
        }
    }
}


void PrintFactories(const Table * table)
{
    unsigned int factoryIndex;
    printf("\n\n");
    printf("    Center of Table 0)");
    if (table->startingPosition == (unsigned int)-1) printf("\n     [-1]"); 
    PrintFactory(table->centerOfTable, false);
    for (factoryIndex = 0; factoryIndex < table->numberOfFactories; ++factoryIndex)
    {
        printf("\n\n    Factory %u)", factoryIndex + 1);
        PrintFactory(table->tileFactory[factoryIndex], false);
    }
}


void PrintPlayersInRow(const Table * table)
{
    char playerSelect[2][5] = { "    ", " >>>" };
    unsigned int playerIndex;
    unsigned int rowIndex;
    printf("\n\n");
    for (playerIndex = 0; playerIndex < table->numberOfPlayers; ++playerIndex)
    {
        printf("%sName: %-*s     Score: %-17d    ", playerSelect[playerIndex == table->currentPlayer], 19, table->players[playerIndex]->name, table->players[playerIndex]->score);
    }
    printf("\n\n");
    for (rowIndex = 0; rowIndex < TileTypeCount; ++rowIndex)
    {
        for (playerIndex = 0; playerIndex < table->numberOfPlayers; ++playerIndex)
        {
            const Player * player = table->players[playerIndex];
            unsigned int columnIndex;
            printf("    ");
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
            printf("    ");
        }
        printf("\n\n");
    }
    for (playerIndex = 0; playerIndex < table->numberOfPlayers; ++playerIndex)
    {
        const Player * player = table->players[playerIndex];
        printf("      ");
        PrintBroken(player);
        printf("      ");
    }
}


void UndoTakeStartingTile(unsigned int * startingPosition, unsigned int * brokenTiles)
{
    *startingPosition = (unsigned int)-1;
    *brokenTiles -= (unsigned int)1;
}


bool AcceptBrokenTiles(unsigned int * playersBrokenTiles, unsigned int numberOfBroken)
{
    printf("  Take %u BROKEN TILES? ", numberOfBroken);
    if (GetYOrNFromUser())
    {
        *playersBrokenTiles += numberOfBroken;
        return true;
    }
    return false;
}


bool TakeTurn(Table * table, Player * player)
{
    TileType * factoryChoice;
    unsigned int factoryIndex;
    unsigned int tileChoice;
    bool tookStartingTile = false;
    printf("\n\n    It is %s's turn!", player->name);
    PrintTable(table);
    do
    {
        printf("\n\n  %s, Please Enter the Number of the Factory you would like to take Tiles From: ", player->name);
    } while (!GetDigitFromUser(&factoryIndex, 0, table->numberOfFactories, true));
    if (factoryIndex == (unsigned int)-1)
    {
        factoryChoice = table->centerOfTable;
    }
    else
    {
        factoryChoice = table->tileFactory[factoryIndex];
    }
    if (isFactoryEmpty(factoryChoice))
    {
        printf("INVALID SELECTION: Selection %u is EMPTY!\n\n  Press ENTER to RESTART TURN", factoryIndex + 1);
        SkipRestOfLine();
        return false;
    }

    if (factoryChoice == table->centerOfTable && table->startingPosition == (unsigned int)-1)
    {
        printf("\n  You are the first to take a tile out of the center of the table, you have to accept the starting position tile!");
        if (!AcceptBrokenTiles(&player->brokenTiles, 1)) return false;
        table->startingPosition = table->currentPlayer;
        tookStartingTile = true;
    }
    do
    {
        if (factoryChoice == table->centerOfTable && table->startingPosition == (unsigned int)-1) printf("\n    [-1]");
        PrintFactory(factoryChoice, true);
        printf("\n\n  %s, Please Enter the Number of the type of Tile you would like to take (Enter 0 to RESTART your turn) : ", player->name);
    } while (!GetDigitFromUser(&tileChoice, 0, TileTypeCount, true));
    if (tileChoice == (unsigned int)-1)
    {
        if (tookStartingTile) UndoTakeStartingTile(&table->startingPosition, &player->brokenTiles);
        return false;
    }
    if (factoryChoice[tileChoice] == 0)
    {
        printf("\n  INVALID SELECTION: There are no Tiles of that Type!\n\n  PRESS ENTER TO RESTART TURN");
        SkipRestOfLine();
        if (tookStartingTile) UndoTakeStartingTile(&table->startingPosition, &player->brokenTiles);
        return false;
    }
    {
        unsigned int rowChoice;
        unsigned int totalTiles;
        PrintPlayer(player);
        do
        {
            printf("\n\n  %s, Enter the patternline row you would like to put the %u %s (%c) tiles in (Enter 0 to RESTART your turn or 6 to take as BROKEN TILES) : ", player->name, factoryChoice[tileChoice], TypeToNames(tileChoice), TypeToChar(tileChoice, true));
        } while (!GetDigitFromUser(&rowChoice, 0, TileTypeCount + 1, true));
        if (rowChoice == (unsigned int)-1)
        {
            if (tookStartingTile) UndoTakeStartingTile(&table->startingPosition, &player->brokenTiles);
            return false;
        }
        if (rowChoice == 5 && AcceptBrokenTiles(&player->brokenTiles, factoryChoice[tileChoice]))
        {
            table->tileBag.numOfType[tileChoice] += factoryChoice[tileChoice];
            table->tileBag.numTile += factoryChoice[tileChoice];
        }
        else
        {
            if (player->patternLine.contents[rowChoice] != 0 && player->patternLine.type[rowChoice] != (int)tileChoice)
            {
                printf("\n  INVALID SELECTION: Row %u is assigned to %s (%c) \n\n  PRESS ENTER TO RESTART TURN", rowChoice + 1, TypeToNames(player->patternLine.type[rowChoice]), TypeToChar(player->patternLine.type[rowChoice], true));
                SkipRestOfLine();
                if (tookStartingTile) UndoTakeStartingTile(&table->startingPosition, &player->brokenTiles);
                return false;
            }
            if (player->wall[rowChoice][(tileChoice + rowChoice) % TileTypeCount])
            {
                printf("\n  INVALID SELECTION: TILE (%c) in ROW %u of the TILE WALL is already FILLED \n\n  PRESS ENTER TO RESTART TURN", TypeToChar(tileChoice , true), rowChoice + 1);
                SkipRestOfLine();
                if (tookStartingTile) UndoTakeStartingTile(&table->startingPosition, &player->brokenTiles);
                return false;
            }
            totalTiles = factoryChoice[tileChoice] + player->patternLine.contents[rowChoice];
            if (totalTiles > rowChoice + 1)
            {
                unsigned int numBroken = totalTiles - (rowChoice + 1);
                printf("\n  You cannot fit that many tiles into that pattern row without breaking tiles!");
                if (!AcceptBrokenTiles(&player->brokenTiles, numBroken))
                {
                    if (tookStartingTile) UndoTakeStartingTile(&table->startingPosition, &player->brokenTiles);
                    return false;
                }
                player->patternLine.contents[rowChoice] = rowChoice + 1;
                player->patternLine.type[rowChoice] = tileChoice;
                table->tileBag.numOfType[tileChoice] += numBroken;
                table->tileBag.numTile += numBroken;
            }
            else
            {
                printf("\n\n  Place %u (%c) tiles in row %u? ", factoryChoice[tileChoice], TypeToChar(tileChoice, true), rowChoice + 1);
                if (!GetYOrNFromUser())
                {
                    if (tookStartingTile) UndoTakeStartingTile(&table->startingPosition, &player->brokenTiles);
                    return false;
                }
                player->patternLine.type[rowChoice] = tileChoice;
                player->patternLine.contents[rowChoice] = totalTiles;
            }
        }
        table->tilesOnTable -= factoryChoice[tileChoice];
        factoryChoice[tileChoice] = 0;
        if (factoryChoice != table->centerOfTable)
        {
            unsigned int tileIndex;
            for (tileIndex = 0; tileIndex < TileTypeCount; ++tileIndex)
            {
                table->centerOfTable[tileIndex] += factoryChoice[tileIndex];
                factoryChoice[tileIndex] = 0;
            }
        }
    }
    PrintPlayer(player);
    printf("\n\n  Press Enter to END TURN!");
    SkipRestOfLine();
    return true;
}


void DeclareWinner(Table * table)
{
    unsigned int playerIndex;
    bool winningPlayer[MAX_NUM_PLAYERS] = {false};
    int highScore = INT_MIN;
    for (playerIndex = 0; playerIndex < table->numberOfPlayers; ++playerIndex)
    {
        if (table->players[playerIndex]->score > highScore) highScore = table->players[playerIndex]->score;
    }
    for (playerIndex = 0; playerIndex < table->numberOfPlayers; ++playerIndex)
    {
        if (table->players[playerIndex]->score >= highScore) winningPlayer[playerIndex] = true;
    }
    printf("\n\n    Winner(s) with %d points!", highScore);
    for (playerIndex = 0; playerIndex < table->numberOfPlayers; ++playerIndex)
    {
        if (winningPlayer[playerIndex]) printf("\n\n      %s!!!", table->players[playerIndex]->name);
    }
}


bool PlayRoundAndContinue(Table * table)
{
    FillFactories(table);
    if (table->startingPosition != (unsigned int)-1)
    {
        table->currentPlayer = table->startingPosition;
        table->startingPosition = (unsigned int)-1;
    }
    while (table->tilesOnTable > 0)
    {
        while (!TakeTurn(table, table->players[table->currentPlayer])) continue;
        table->currentPlayer = (table->currentPlayer + 1) % table->numberOfPlayers;
    }
    {
        bool completedRow = false;
        unsigned int playerIndex;
        for (playerIndex = 0; playerIndex < table->numberOfPlayers; ++playerIndex)
        {
            completedRow = ScorePlayerIsComplete(table->players[playerIndex], &table->tileBag) || completedRow;
        }
        PrintTable(table);
        if (completedRow) DeclareWinner(table);
        return !completedRow;
    }
}


void PrintTable(const Table * table)
{
    printf("\n\n");

#ifdef NDEBUG
    {
        int index;
        printf("  Tile Types:");
        for (index = 0; index < TileTypeCount; ++index)
        {
            printf("    %s -> (%c)", TypeToNames(index), TypeToChar(index, true));
        }
    }
#else 
    PrintTileBag(&table->tileBag);
#endif
    PrintFactories(table);
    printf("\n");
    PrintPlayersInRow(table);
}