#pragma once

#ifndef TEST30042019_STRINGLIST_H
#define TEST30042019_STRINGLIST_H


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#ifndef ALLOCATION_ERROR
#define ALLOCATION_ERROR    -3
#endif


typedef struct st_List StringList;

struct st_List {
    StringList * next;
    char symbol;
};


StringList * StringToList(
        const char * string);


void FreeString(
        StringList *head);


void PrintString(
        StringList *head);


int ReplaceSymbol(
        StringList ** head,
        char * new_substring,
        int symbol);


StringList * FindEnd(
        StringList * head);


#endif
