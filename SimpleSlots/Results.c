//
//  Results.c
//  SimpleSlots
//
//  Created by Stephen Choate.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Reel result struct definition
typedef struct Reelresult{
    int rc;
    int rv;
    char rd[12];
}Reelresult;

//Slot result struct definition
typedef struct SpinResult{
    char rd1[12];
    char rd2[12];
    char rd3[12];
    float bet, win;

    struct SpinResult *pr;
    struct SpinResult *nr;
}SpinResult;

//Get a single reel result using random number generator, set code & description, return pointer to initialized reel result struct.
Reelresult getReelResult(){
    int r;
    int rc;
    r = rand() % 11;

    if (r <= 4){
        rc = 0;
        Reelresult res = {.rc = rc, .rd = "", .rv=1};
        strcpy(res.rd, "Bar");
        return res;
    }else if (r <= 7){
        rc = 1;
        Reelresult res = {.rc = rc, .rd = "", .rv=1};
        strcpy(res.rd, "Bar/Bar");
        return res;
    }else if (r == 8){
        rc = 2;
        Reelresult res = {.rc = rc, .rd = "", .rv=1};
        strcpy(res.rd, "Bar/Bar/Bar");
        return res;
    }else if (r == 9){
        rc = 3;
        Reelresult res = {.rc = rc, .rd = "", .rv=1};
        strcpy(res.rd, "Cherry");
        return res;
    }else if (r == 10){
        rc = 4;
        Reelresult res = {.rc = rc, .rd = "", .rv=1};
        strcpy(res.rd, "Seven");
        return res;
    }else{
        rc = 0;
        Reelresult res = {.rc = rc, .rd = "", .rv=1};
        strcpy(res.rd, "Bar");
        return res;
    }
}

//Create spin result struct initialized as node in linked list. Return pointer to newly created node.
SpinResult* storeHist(char r1[12], char r2[12], char r3[12], float b, float w, SpinResult* p){
    SpinResult *sr = malloc(sizeof(SpinResult));
    sr->bet=b;
    sr->win=w;
    sr->pr=(p) ? p : NULL;
    sr->nr=NULL;
    if(p){
        p->nr=sr;
    }
    strcpy(sr->rd1, r1);
    strcpy(sr->rd2, r2);
    strcpy(sr->rd3, r3);

    return sr;
}

//Print slot results descriptions and spin number. Return pointer to next item in linked list, goverened by order parameter p.
SpinResult* printResHist(SpinResult *sr, int r, int p){
    printf("\nSpin %i - Bet: $%.2f, Win: $%.2f. Result:    %s   %s   %s", r, sr->bet, sr->win, sr->rd1, sr->rd2, sr->rd3);
    return (p) ? sr->nr : sr->pr;
}

//Loop through result history, starting with first or last pointer, governed by order parameter. Call function to print each result.
void getResHist(SpinResult *fr, SpinResult *lr, int p, int s){
    SpinResult *cr;
    cr = (p) ? fr : lr;
    int runs = (p) ? 1 : s;

    do{
        cr = printResHist(cr, runs, p);
        (p) ? runs++ : runs--;
    }while(cr);
}

//Clear memory for result history structs, starting with first result pointer.
void freeResHist(SpinResult *fr){
    SpinResult *cr = fr;
    SpinResult *nr;
    
    do{
        nr = (cr->nr!=NULL) ? cr->nr : NULL;
        free(cr);
        cr=nr;
    }while (nr!=NULL);
}
