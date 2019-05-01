#pragma once

#ifndef TEST30042019_GRAMMAR_H
#define TEST30042019_GRAMMAR_H


#include <stdio.h>


#include "grammarlist.h"
#include "stringlist.h"


#define MAX_BUFF_LEN        1024u


#define FORMAT_ERROR        -2
#define READ_ERROR          -5

#ifndef ALLOCATION_ERROR
#define ALLOCATION_ERROR    -3
#endif


int GetRule(
        AltList * rules_array[MAX_NON_TERMINALS],
        FILE * input_file,
        int rule_count[MAX_NON_TERMINALS]);


int PrintRules(
        AltList * rules_array[MAX_NON_TERMINALS]);


int RandomlyApplyRules(
        AltList ** rules_array,
        const int * rules_count,
        StringList ** string,
        unsigned int N);

#endif
