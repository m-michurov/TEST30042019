#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define offset(X) (X - 'A')

#define MAX_BUFF_LEN 1024

char * my_realloc(
        void * mem,
        size_t new_size)
{
    if (mem == 0)
    {
        return calloc(new_size, 1);
    }
    else
    {
        return realloc(mem, new_size);
    }
}


typedef struct st_List List;

struct st_List {
    List * next;
    char * string;
};


int get_rule(
        FILE * rules,
        char ** rules_for_non_terminals[26],
        int rules_count[26])
{
    int non_terminal;
    char rule_buff[MAX_BUFF_LEN];

    non_terminal = fgetc(rules);
    if (non_terminal == EOF)
    {
        return -1;
    }
    fgetc(rules); // '\n'

    do
    {
        fgets(rule_buff, MAX_BUFF_LEN, rules);

        if (rule_buff[0] == '|')
        {
            rules_count[offset(non_terminal)] += 1;

            rules_for_non_terminals[offset(non_terminal)] =
                        (char **) my_realloc(rules_for_non_terminals[offset(non_terminal)], (size_t) rules_count[offset(non_terminal)]);

            rules_for_non_terminals[offset(non_terminal)][rules_count[offset(non_terminal)] - 1] = malloc(strlen(rule_buff) - 2);

            strcpy(rules_for_non_terminals[offset(non_terminal)][rules_count[offset(non_terminal)] - 1], rule_buff + 2);

            rules_for_non_terminals[offset(non_terminal)][rules_count[offset(non_terminal)] - 1][strlen(rule_buff) - 3] = 0;

        }
    } while (rule_buff[0] != ';');

    return 0;
}


void print_rules(
        char ** rules_for_non_terminals[26],
        const int rules_count[26])
{
    for (int k = 'A'; k <= 'Z'; k++)
    {
        if (rules_count[offset(k)] != 0)
        {
            printf("%c\n", k);
            for (int p = 0; p < rules_count[offset(k)]; p++)
            {
                printf("| %s\n", rules_for_non_terminals[offset(k)][p]);
            }
            printf(";\n");
        }
    }
}


int replace(
        char ** string,
        int non_terminal,
        char * new_substring)
{
    char * rest_pointer;
    char * rest;

    size_t sub_len = strlen(new_substring);
    size_t str_len = strlen(*string);
    size_t rest_len;

    if (sub_len + str_len - 1 > MAX_BUFF_LEN)
    {
        *string = realloc(*string, sub_len + str_len - 1);
    }

    rest_pointer = strchr(*string, non_terminal) + 1;

    if (rest_pointer == NULL)
    {
        return -1;
    }

    rest_len = strlen(rest_pointer);

    rest = calloc(strlen(rest_pointer), 1);

    memcpy(rest, rest_pointer, strlen(rest_pointer));

    memcpy(rest_pointer - 1, new_substring, strlen(new_substring));
    memcpy(rest_pointer - 1 + sub_len, rest, rest_len);

    free(rest);

    return 0;
}


int substitute_all(
        char *** rules_for_non_terminals,
        const int * rules_count,
        char ** string,
        unsigned int N)
{
    char * current_rule;
    int current_non_terminal;

    unsigned int substitutions_count = 0;

    for (current_non_terminal = 'A'; current_non_terminal <= 'Z'; current_non_terminal++)
    {
        if (strchr(*string, current_non_terminal) != NULL)
        {
            current_rule = rules_for_non_terminals[offset(current_non_terminal)][0];
            while(!replace(string, current_non_terminal, current_rule))
            {
                substitutions_count++;
                if (substitutions_count == N)
                {
                    return 0;
                }
            }
        }
    }

    return 0;
}


int main(
        int argc,
        char * argv[])
{
    FILE * rules;
    int N;
    char *** rules_for_non_terminals = (char ***) calloc(26u, sizeof(char **));
    int rules_count[26] = { 0 };
    char * string = malloc(MAX_BUFF_LEN);

    if (argc != 3)
    {
        printf("Bad number of arguments\n");
        return 0;
    }
    else
    {
        N = strtol(argv[1], NULL, 10);
        rules = fopen(argv[2], "rt");

        if (N < 0 || rules == NULL)
        {
            printf("Bad input\n");
            return 0;
        }

        while (!get_rule(rules, rules_for_non_terminals, rules_count));

        print_rules(rules_for_non_terminals, rules_count);

        substitute_all(rules_for_non_terminals, rules_count, &string, (unsigned int) N);

        printf("%s", string);

        fclose(rules);
    }

    return 0;
}