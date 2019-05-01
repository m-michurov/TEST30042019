#include "stringlist.h"


void FreeString(
        StringList *head)
{
    if (head == NULL)
    {
        return;
    }

    FreeString(head->next);
    free(head);
}


void PrintString(
        StringList *head)
{
    while (head != NULL)
    {
        printf("%c", head->symbol);
        head = head->next;
    }

    printf("\n");
}


StringList * StringToList(
        const char * string)
{
    if (string == NULL)
    {
        return NULL;
    }

    StringList * head = NULL;
    StringList * buff = NULL;

    size_t string_length = strlen(string);

    if (string_length > 0)
    {
        head = calloc(1, sizeof(StringList));
        if (head == NULL)
        {
            return NULL;
        }
        head->symbol = string[0];

        buff = head;

        for (int k = 1; k < string_length; k++)
        {
            buff->next = calloc(1, sizeof(StringList));
            if (buff->next == NULL)
            {
                FreeString(head);
                return NULL;
            }
            buff->next->symbol = string[k];
            buff = buff->next;
        }
    }

    return head;
}


static StringList * _find_node_before_symbol(
        StringList *head,
        int symbol)
{
    if (head == NULL)
    {
        return NULL;
    }

    StringList * current_ptr;
    StringList * prev_ptr = NULL;
    
    for (current_ptr = head; current_ptr != NULL && current_ptr->symbol != symbol; current_ptr = current_ptr->next)
    {
        prev_ptr = current_ptr;
    }

    return prev_ptr;
}


StringList * FindEnd(
        StringList * head)
{
    if (head == NULL)
    {
        return NULL;
    }
    
    while (head->next != NULL)
    {
        head = head->next;
    }

    return head;
}


static int _replace_symbol(
        StringList ** head,
        StringList * new_substring,
        int symbol)
{
    if (*head == NULL)
    {
        return 0;
    }

    StringList * pre_symbol_node = _find_node_before_symbol(*head, symbol);
    StringList * buff;

    if (pre_symbol_node == NULL)
    {
        if (new_substring != NULL)
        {
            FindEnd(new_substring)->next = (*head)->next;
            free(*head);
            *head = new_substring;
        }
        else // if new_substring is NULL (an empty string)
        {
            buff = *head;
            *head = (*head)->next;
            free(buff);
        }
    }
    else
    {
        buff = pre_symbol_node->next;
        if (new_substring != NULL)
        {
            FindEnd(new_substring)->next = pre_symbol_node->next->next;
            pre_symbol_node->next = new_substring;
        }
        else // if new_substring is NULL (an empty string)
        {
            pre_symbol_node->next = pre_symbol_node->next->next;
        }
        free(buff);
    }
    return 0;
}


int ReplaceSymbol(
        StringList ** head,
        char * new_substring,
        int symbol)
{
    StringList * substr = StringToList(new_substring);

    return _replace_symbol(head, substr, symbol);
}