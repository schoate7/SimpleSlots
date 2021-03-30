//
//  Player.c
//  SimpleSlots
//
//  Created by Stephen Choate.
//

#include <stdio.h>

//Player struct definition.
typedef struct Player{
    char playerName[26];
    double playerCash;
    double totalDeposits;
}Player;

//Print attributes of Player struct parameter.
void playerInfo(Player* pl){
    printf("\nPlayer Information:");
    printf("\nPlayer: %s", pl->playerName);
    printf("\nTotal Cash Deposited: $%.2f", pl->totalDeposits);
    printf("\nCash Available: $%.2f", pl->playerCash);
}
