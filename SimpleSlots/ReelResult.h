//
//  ReelResult.h
//  SimpleSlots
//
//  Created by Stephen Choate.
//

#ifndef ReelResult_h
#define ReelResult_h
#include <stdio.h>

/* Reel result structure, holds code (int), description (char[]), value indicator(int) that result is valid */
typedef struct Reelresult{
    int rc;
    int rv;
    char rd[12];
}Reelresult;

/* Slot result structure for a spin, holds each reel description, bet amount and winnings. Pointer to previous and next result struct */
typedef struct Slotresult{
    char rd1[12];
    char rd2[12];
    char rd3[12];
    float bet, win;

    struct Slotresult *pr;
    struct Slotresult *nr;
}Slotresult;

/* Gets a single reel result using random number generator, returns pointer to initialized reel result struct */
Reelresult getReelResult(void);

/* Creates a spin result struct initialized as node in linked list. Returns pointer to newly created node */
Slotresult* storeHist(char r1[12], char r2[12], char r3[12], float b, float w, Slotresult* p);

/* Prints slot results descriptions and spin number from pointer and integer parameters. Returns pointer to next item in linked list, goverened by order parameter p.  */
Slotresult* printResHist(Slotresult *sr, int r, int p);

/* Loops through result history, starting with first pointer. Calls function to print result with current result pointer. Increments run counter, loops while next pointer is not null */
void getResHist(Slotresult *fr, Slotresult *lr, int p, int s);

/* Clear memory for result history structs, starting with input parameter for first result pointer to iterate over linked list */
void clearResHist(Slotresult *fr);

#endif /* ReelResult_h */
