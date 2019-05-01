#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


#include "grammarlist.h"
#include "stringlist.h"
#include "grammar.h"


void HandleError(
        AltList * rules_array[MAX_NON_TERMINALS],
        StringList * string,
        int errcode)
{
    switch (errcode)
    {
        case ALLOCATION_ERROR:
            printf("Allocation error\n");
            break;
        case FORMAT_ERROR:
            printf("Bad input format\n");
            break;
        case READ_ERROR:
            printf("Error when reading input file\n");
            break;
        default:
            printf("Unknown error has occurred\n");
    }
    for (int k = 0; k < MAX_NON_TERMINALS; k++)
    {
        FreeAltList(rules_array[k]);
    }

    FreeString(string);
}


int main(
        int argc,
        char * argv[])
{
    FILE * input_file;
    int N;
    int errcode = 0;
    int rules_count[MAX_NON_TERMINALS] = { 0 };
    AltList * rules_array[MAX_NON_TERMINALS] = { 0 };
    StringList * string = NULL;
    char starting_non_terminal[2];

    srand(time(0));

    if (argc != 3)
    {
        printf("Bad number of arguments\n");
        return 0;
    }
    else
    {
        N = strtol(argv[1], NULL, 10);
        input_file = fopen(argv[2], "rt");

        if (N < 0 || input_file == NULL)
        {
            printf("Bad input\n");
            return 0;
        }

        fread(starting_non_terminal, 1, 1, input_file);
        starting_non_terminal[1] = 0;
        fseek(input_file, 0, 0);

        while (!feof(input_file) && errcode == 0)
        {
            errcode = GetRule(rules_array, input_file, rules_count);
        }

        if (errcode != 0)
        {
            HandleError(rules_array, string, errcode);
            return 0;
        }

        PrintRules(rules_array);

        for (int t = 0; t < 1024; t++)
        {
            string = StringToList(starting_non_terminal);

            RandomlyApplyRules(rules_array, rules_count, &string, (unsigned int) N);

            PrintString(string);

            FreeString(string);
        }


        for (int k = 0; k < MAX_NON_TERMINALS; k++)
        {
            FreeAltList(rules_array[k]);
        }

        FreeString(string);


        fclose(input_file);
    }

    return 0;
}