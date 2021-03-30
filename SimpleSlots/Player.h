//
//  Player.h - Defines player struct, contains function to print player details.
//  SimpleSlots
//
//  Created by Stephen Choate.
//

#ifndef Player_h
#define Player_h

/* Player struct - holds name (char*), player cash (double), and total deposits (double). */
typedef struct Player{
    char playerName[26];
    double playerCash;
    double totalDeposits;
}Player;

/* playerInfo - Accepts pointer to a player struct as parameter, prints struct attributes. */
void playerInfo(Player* pl);

#endif /* Player_h */
