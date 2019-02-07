#pragma once


#ifndef _CARD_H_
#define _CARD_H_


#define MAX_TITLE_LENGTH 16
#define MAX_DESCRIPTION_LENGTH 256

typedef enum
{
    BOXSET_BASE,
    BOXSET_INTRIGUE,
    BOXSET_SEASIDE,
    BOXSET_ALCHEMY,
    BOXSET_PROSPERITY,
    BOXSET_CORNUCOPIA,
    BOXSET_HINTERLANDS,
    BOXSET_DARK_AGES,
    BOXSET_GUILDS,
    BOXSET_ADVENTURES,
    BOXSET_EMPIRES,
    BOXSEET_NOCTURNE,
    BOXSET_RENAISANCE,
    BOXSET_PROMO
} BoxSet;

typedef enum
{
    TYPE_ACTION    = 2,
    TYPE_TREASURE  = 3,
    TYPE_VICTORY   = 5,
    TYPE_REACTION  = 7,
    TYPE_ATTACK    = 11,
    TYPE_DURATION  = 13,
    TYPE_HEIRLOOM  = 17,
    TYPE_HEX       = 19,
    TYPE_STATE     = 23,
    TYPE_ARTIFACT  = 29,
    TYPE_PROJECT   = 31,
} CardType;

typedef enum
{
    NAME_CELLAR,
    NAME_CHAPEL,
    NAME_MOAT,
    NAME_CHANCELLOR,
    NAME_HARBINGER,
    NAME_MERCHANT,
    NAME_VILLAGE,
    NAME_WOODCUTTER,
    NAME_WORKSHOP,
    NAME_VASAAL,
    NAME_BUREAUCRAT,
    NAME_FEAST,
    NAME_GARDENS,
    NAME_MILITIA,
    NAME_MONEYLENDER,
    NAME_POACHERS,
    NAME_REMODEL,
    NAME_SMITHY,
    NAME_SPY,
    NAME_THIEF,
    NAME_THRONEROOM,
    NAME_BANDIT,
    NAME_COUNCILROOM,
    NAME_FESTIVAL,
    NAME_LABORATORY,
    NAME_MARKET,
    NAME_MINE,
    NAME_SENTRY,
    NAME_WITCH,
    NAME_ADVENTURER,
    NAME_ARTISAN,
    NAME_COPPER,
    NAME_SILVER,
    NAME_GOLD,
    NAME_ESTATE,
    NAME_DUCHY,
    NAME_PROVINCE,
    NAME_CURSE,
    NAME_COURTYARD,
    NAME_LURKER,
    NAME_PAWN,
    NAME_SECRETCHAMBER,
    NAME_GREATHALL,
    NAME_MASQUERADE,
    NAME_SHANTYTOWN,
    NAME_STEWARD,
    NAME_SWINDLER,
    NAME_WISHINGWELL,
    NAME_BARON,
    NAME_BRIDGE,
    NAME_CONSPIRATOR,
    NAME_COPPERSMITH,
    NAME_DIPLOMAT,
    NAME_IRONWORKS,
    NAME_MILL,
    NAME_MININGVILLAGE,
    NAME_SCOUT,
    NAME_SECRETPASSAGE,
    NAME_COURTIER,
    NAME_DUKE,
    NAME_MINION,
    NAME_PATROL,
    NAME_REPLACE,
    NAME_SABOTEUR,
    NAME_TORTURER,
    NAME_TRADINGPOST,
    NAME_TRIBUTE,
    NAME_UPGRADE,
    NAME_HAREM,
    NAME_NOBLES,
    NAME_EMBARGO,
    NAME_HAVEN,
    NAME_LIGHTHOUSE,
    NAME_NATIVE_VILLAGE,
    NAME_PEARLDIVER,
    NAME_AMBASSADOR,
    NAME_FISHING_VILLAGE,
    NAME_LOOKOUT,
    NAME_SMUGGLERS,
    NAME_WAREHOUSE,
    NAME_CARAVAN,
    NAME_CUTPURSE,
    NAME_ISLAND,
    NAME_NAVIGATOR,
    NAME_PIRATESHIP,
    NAME_SALVAGER,
    NAME_SEA_HAG,
    NAME_TREASURE_MAP,
    NAME_BAZAAR,
    NAME_EXPLORER,
    NAME_GHOST_SHIP,
    NAME_MERCHANT_SHIP,
    NAME_OUTPOST,
    NAME_TACTICIAN,
    NAME_TREASURY,
    NAME_WHARF,
    NAME_TRANSMUTE,
    NAME_VINEYARD,
    NAME_HERBALIST,
    NAME_APOTHECARY,
    NAME_SCRYING_POOL,
    NAME_UNIVERSITY,
    NAME_ALCHEMIST,
    NAME_FAMILIAR,
    NAME_PHILOSOPHERS_STONE,
    NAME_GOLEM,
    NAME_APPRENTICE,
    NAME_POSSESSION,
    NAME_POTION,
    NAME_LOAN,
    NAME_TRADE_ROUTE,
    NAME_WATCHTOWER,
    NAME_BISHOP,
    NAME_MONUMENT,
    CardNameCount
} CardName;

typedef struct
{
    char title[16]; 
    CardName name;                              /* The enumerated name of card, serves as an index to that card */
    CardType type;                              /* The enumerated type of tile */
    char title[MAX_TITLE_LENGTH];               /*String containing the card title for printing*/
    char description[MAX_DESCRIPTION_LENGTH];   /*Description contained on card*/
    short cost;             /* number of coin */
    unsigned short distanceFromStart; /* The number of steps this tile is from the start via the solutions search path */
} Card;

#endif
