#include "grammar.h"


int GetRule(
        AltList * rules_array[MAX_NON_TERMINALS],
        FILE * input_file,
        int rule_count[MAX_NON_TERMINALS])
{
    int current_non_terminal;

    char buff[MAX_BUFF_LEN];
    char * nptr;

    fgets(buff, MAX_BUFF_LEN, input_file);

    if (buff[0] < 'A' || buff[0] > 'Z' || buff[1] != '\n')
    {
        return FORMAT_ERROR;
    }

    current_non_terminal = buff[0];

    do
    {
        nptr = fgets(buff, MAX_BUFF_LEN, input_file);

        if (nptr == NULL)
        {
            return READ_ERROR;
        }

        if (buff[0] == '|' && buff[1] == ' ')
        {
            rules_array[current_non_terminal - 'A'] = AppendAltList(rules_array[current_non_terminal - 'A'], buff + 2);

            if (rules_array[current_non_terminal - 'A'] == NULL)
            {
                return ALLOCATION_ERROR;
            }

            rule_count[current_non_terminal - 'A'] += 1;
        }
        else if ((buff[0] == ';' && buff[1] == '\n') || (buff[0] == ';' && strlen(buff) == 1))
        {
            return 0;
        }
        else
        {
            return FORMAT_ERROR;
        }
    } while (1);
}


int PrintRules(
        AltList * rules_array[MAX_NON_TERMINALS])
{
    AltList * current;

    if (rules_array == NULL)
    {
        return ALLOCATION_ERROR;
    }

    for (int k = 'A'; k <= 'Z'; k++)
    {
        if (rules_array[k - 'A'] != NULL){
            printf("%c\n", k);

            current = rules_array[k - 'A'];
            while (current != NULL)
            {
                printf("| %s\n", current->string);
                current = current->next;
            }

            printf(";\n");
        }
    }

    return 0;
}


static inline int _find_non_terminal(
        StringList * string)
{
    if (string == NULL)
    {
        return -404;
    }

    while (string != NULL && !(string->symbol >= 'A' && string->symbol <= 'Z'))
    {
        string = string->next;
    }

    if (string == NULL)
    {
        return -404;
    }

    return string->symbol;
}


int RandomlyApplyRules(
        AltList ** rules_array,
        const int * rules_count,
        StringList ** string,
        unsigned int N)
{
    int non_terminal;
    int rand_index = 0;
    int errcode;
    unsigned int applied_count = 0;
    AltList * current_node;

    while ((non_terminal = _find_non_terminal(*string)) >= 'A')
    {
        rand_index = rand() % rules_count[non_terminal - 'A'];

        current_node = rules_array[non_terminal - 'A'];

        while (rand_index > 0)
        {
            current_node = current_node->next;

            rand_index--;
        }

        errcode = ReplaceSymbol(string, current_node->string, non_terminal);

        if (errcode != 0)
        {
            printf("An error has occurred: errcode %d\n", errcode);
            return -1;
        }

        applied_count += 1;

        if (applied_count >= N)
        {
            return 0;
        }
    }

    return 1;
}