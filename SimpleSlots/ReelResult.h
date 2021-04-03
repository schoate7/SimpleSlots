//
//  ReelResult.h - Defines structure for reel and spin results. Functions to get, store and print results, initialize structs and manage memory.
//  SimpleSlots
//
//  Created by Stephen Choate.
//

#ifndef ReelResult_h
#define ReelResult_h
#include <stdio.h>

/* Reelresult - Struct for a single reel spin, holds code (int), description (char[]), value indicator(int) that result is valid. */
typedef struct Reelresult{
    int rc;
    int rv;
    char rd[12];
}Reelresult;

/* Slotresult - Strcut for a spin's results. Holds description for each reel (char*), bet amount and winnings (float). Holds pointer to previous and next result structs (struct Slotresult). */
typedef struct Slotresult{
    char rd1[12];
    char rd2[12];
    char rd3[12];
    float bet, win;

    struct Slotresult *pr;
    struct Slotresult *nr;
}Slotresult;

/* getReelResult - Returns pointer to a single reel result, created using random number generator. */
Reelresult getReelResult(void);

/* storeHist - Accepts 3x reel descriptions (char*), bet and winnings (float) and Slotresult struct as parameters. Creates a spin result struct initialized as node in doubly-linked list. Returns pointer to newly created node */
Slotresult* storeHist(char r1[12], char r2[12], char r3[12], float b, float w, Slotresult* p);

/* printResHist - Accepts pointer to first Slotresult in linked list, spin number (int) and direction parameter (int). Loops through linked list and prints slot result descriptions and spin number from pointer and integer parameters. Returns pointer to next item in linked list, goverened by order parameter p. */
Slotresult* printResHist(Slotresult *sr, int r, int p);

/* getResHist - Accepts first and last Slotresult pointer, order parameter (int) and number of spins (int). Loops through result history, starting with first pointer. Calls function to print result with current result pointer. Continues until next node is null. */
void getResHist(Slotresult *fr, Slotresult *lr, int p, int s);

/* clearResHist - Accepts first result pointer. Loops through linked list first-to-last to clear memory for result history structs. */
void clearResHist(Slotresult *fr);

#endif /* ReelResult_h */
