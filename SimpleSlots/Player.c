//
//  Player.c
//  SimpleSlots
//
//  Created by Stephen Choate.
//

#include <stdio.h>

/* Player struct */
typedef struct Player{
    char playerName[26];
    double playerCash;
    double totalDeposits;
}Player;

/* Player info */
void playerInfo(Player* pl){
    printf("\nPlayer Information:");
    printf("\nPlayer: %s", pl->playerName);
    printf("\nTotal Cash Deposited: $%.2f", pl->totalDeposits);
    printf("\nCash Available: $%.2f", pl->playerCash);
}
