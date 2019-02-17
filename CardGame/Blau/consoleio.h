
#ifndef _CONSOLEIO_H_
#define _CONSOLEIO_H_

#include <stdio.h>
#include "Tile.h"
#include "Player.h"
#include "Table.h"

void PrintTileBag(const TileBag * tileBag);

void PrintFactory(const TileType * tileFactory, bool withNumbers);

void PrintPlayer(Player * player);

void PrintBroken(const Player * player);

void PrintTable(const Table * table);

#endif
