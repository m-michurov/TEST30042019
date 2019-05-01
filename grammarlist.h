#pragma once

#ifndef TEST30042019_GRAMMARLIST_H
#define TEST30042019_GRAMMARLIST_H


#define MAX_NON_TERMINALS 26u


#include <stdlib.h>
#include <string.h>


#ifndef ALLOCATION_ERROR
#define ALLOCATION_ERROR    -3
#endif


typedef struct st_Alt_List AltList;

struct st_Alt_List{
    char * string;
    AltList * next;
};


AltList * AppendAltList(
        AltList *head,
        char *string);


void FreeAltList(
        AltList * head);


#endif
