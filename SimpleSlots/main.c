//
//  main.c
//  SimpleSlots - A simple command-line slot machine game.
//
//  Created by Stephen Choate
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "Player.h"
#include "Results.h"

#define MAX_BET_VAL 10.0 //Macro for maximum bet allowed

//Check in player, collect attributes needed, return pointer to initialized player struct.
Player* checkInPlayer(void){
    char pName[26];
    float initialDeposit = 0;
    
    printf("Please enter your name: ");
    scanf("%1023[^\n]", pName);
    printf("Please enter your deposit: ");
    scanf("%f", &initialDeposit);
    printf("Player Name: %s", pName);
    printf("\nInitial Deposit: $%.2f\n", initialDeposit);

    Player *pl = malloc(sizeof(Player));
    pl->playerCash=initialDeposit;
    pl->totalDeposits=initialDeposit;
    size_t destStr = sizeof(pl->playerName);
    strncpy(pl->playerName, pName, destStr);
    pl->playerName[destStr-1] = '\0';
    return pl;
}

//Prompt user for cash deposit amount, add deposit to player cash.
void depositCash(Player* pl){
    float newDeposit;
    printf("\nPlease enter your cash deposit: ");
    scanf("%f", &newDeposit);
    pl->totalDeposits += newDeposit;
    pl->playerCash += newDeposit;
    printf("\nTotal Cash is now: $%.2f", pl->playerCash);
}

//Prompt user for revised bet, test against max limit set by global macro value. If 0, leave bet unchanged, otherwise update bet to user input.
float changeBet(float curBet){
    float newBet = 0;
    while (!newBet || newBet > MAX_BET_VAL){
        printf("\nPlease enter your new bet (0 to remain): ");
        scanf("%f", &newBet);
        if (newBet > MAX_BET_VAL){
            printf("\nBet exceeds max ($%.2f), please enter a lower number.", MAX_BET_VAL);
        }else if (!newBet){
            newBet = curBet;
        }
    }
    (newBet != curBet) ? printf("\nBet changed to: $%.2f", newBet) : printf("\nBet remains as: $%.2f", newBet);
    return newBet;
}

//Run a spin, gets three slot results, calculate winnings. Update player struct and notify user of spin outcome.
SpinResult* spin(Player* pl, float bet, SpinResult* pr){
    printf("\nSpinning...");
    Reelresult r1, r2, r3;
    float w = 0;
    r1 = getReelResult();
    r2 = getReelResult();
    r3 = getReelResult();
    
    //Ensure the user can afford bet, and that three valid reel results have been returned
    if (pl->playerCash < bet){
        printf("Not enough cash, please adjust your bet or deposit more cash.");
        return 0;
    }else if (!r1.rv || !r2.rv || !r3.rv){
        printf("\nSomething went wrong!");
        return 0;
    }else if (pl->playerCash >= bet){
        sleep(1);
        printf("\n%s", r1.rd);
        sleep(1);
        printf("    %s", r2.rd);
        sleep(1);
        printf("    %s", r3.rd);
        pl->playerCash -= bet;

        //Determine winnings
        if ((r1.rc == r2.rc) && (r1.rc == r3.rc)){
            switch(r1.rc){
                case 0:
                    w = 2*bet; break;
                case 1:
                    w = 3*bet; break;
                case 2: case 3:
                    w = 5*bet; break;
                case 4:
                    w = 7*bet; break;
                default:
                    w=bet; break;
            }
        }else if (((r1.rc == r2.rc) && (r1.rc != r3.rc)) || ((r1.rc != r2.rc) && (r1.rc == r3.rc))){
            switch(r1.rc){
                case 0:
                    w=bet;break;
                case 1:
                    w=2*bet;break;
                case 2: case 3:
                    w=3*bet;break;
                case 4:
                    w=5*bet;break;
                default:
                    w=bet;break;
            }
        }else if ((r2.rc == r3.rc) && (r2.rc != r1.rc)){
            switch(r2.rc){
                case 0:
                    w=bet;break;
                case 1:
                    w=2*bet;break;
                case 2: case 3:
                    w=3*bet;break;
                case 4:
                    w=5*bet;break;
                default:
                    w=bet;break;
            }
        }
        
        //If winnings exist, notify user and deposit, otherwise notify user of no win. Store history in result struct and return pointer.
        if(w>0){
            printf("\nYou win $%.2f\n", w);
            pl->playerCash += w;
        }else{
            printf("\nSorry, try again!\n");
        }
        pr = storeHist(r1.rd, r2.rd, r3.rd, bet, w, pr);
    }
    return pr;
}

//Cash out user, receive player struct, first result, last result pointers and number of spins as parameters. Call function to print player info, prompt user to run history printer with input on direction to print list (FtL, LtF)
void cashOut(Player *pl, SpinResult *fr, SpinResult *lr, int spins){
    printf("\nCashing out...");
    playerInfo(pl);
    int v=0;
    char resp;
    int orderParam = 0;
    while(!v){
        printf("\nWould you like to print your history?: ");
        scanf(" %c", &resp);
        switch(resp){
            case 'Y': case 'y':
                printf("\nFirst to Last (1) or Last to First (0): ");
                scanf("%i", &orderParam);
                orderParam = (!orderParam) ? 0 : 1;
                spins ? getResHist(fr,lr,orderParam,spins) : printf("\nSorry, you didn't have any spins, goodbye!");
                v++;
                break;
            case 'N': case 'n':
                printf("\nGoodbye!");
                v++;
                break;
            default:
                printf("\nInvalid input, try again.");
                break;
        }
        freeResHist(fr);
    }
    return;
}

//Main user menu driver function, receive pointer to Player struct. Loop on input until quit character received, call functions from user input.
void menu(Player* pl){
    int quitCmd = 0;
    int spins=0;
    float betValue = 1.00;

    SpinResult *pr = 0;
    SpinResult *s = 0;

    printf("\nDefault bet is set at $1.00");

    while (!quitCmd){
        char inChar;
        printf("\n[S]pin, set [B]et, [D]eposit cash, player [I]nfo, [C]ash out: ");
        scanf(" %c", &inChar);
        switch (toupper(inChar)){
            case 'C':
                cashOut(pl, s, pr, spins);
                quitCmd = 1;
                break;
            case 'D':
                depositCash(pl);
                break;
            case 'B':
                betValue = changeBet(betValue);
                break;
            case 'S':
                pr = spin(pl, betValue, pr);
                s = (!spins) ? pr : s;
                spins+= (pr) ? 1 : 0;
                break;
            case 'I':
                playerInfo(pl);
                break;
            default:
                printf("\nInvalid Entry, please try again.");
                break;
        }
        printf("\n");
    }
}

//Main - Initialize a player struct, passe pointer to looping menu until player quits.
int main(int argc, char *argv[]){
    printf("Welcome to Simple Slots!\n");
    Player* p = checkInPlayer();
    menu(p);
    return 0;
}
