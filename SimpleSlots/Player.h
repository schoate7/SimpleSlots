//
//  Player.h
//  SimpleSlots
//
//  Created by Stephen Choate.
//

#ifndef Player_h
#define Player_h

/* Player structure - holds player name, total depost tracking, and player cash for ongoing increment/decrement as bets are placed/winnings deposited */
typedef struct Player{
    char playerName[26];
    double playerCash;
    double totalDeposits;
}Player;

/* Takes in a reference to a player structure and prints the attributes */
void playerInfo(Player* pl);

#endif /* Player_h */
