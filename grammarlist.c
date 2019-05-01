#include "grammarlist.h"


void FreeAltList(
        AltList * head)
{
    if (head == NULL)
    {
        return;
    }

    FreeAltList(head->next);
    free(head->string);
    free(head);
}


AltList * AppendAltList(
        AltList * head,
        char * string)
{
    AltList * current_node;

    char * new_string;

    if (string == NULL)
    {
        FreeAltList(head);
        return NULL;
    }

    size_t new_str_len = strlen(string) - 1;

    new_string = calloc(new_str_len, 1);

    if (new_string == NULL)
    {
        FreeAltList(head);
        return NULL;
    }

    memcpy(new_string, string, new_str_len);
    new_string[new_str_len] = 0;

    if (head == NULL)
    {
        head = calloc(1, sizeof(AltList));
        if (head == NULL)
        {
            FreeAltList(head);
            return NULL;
        }
        head->string = new_string;

        return head;
    }

    current_node = head;

    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }

    current_node->next = calloc(1, sizeof(AltList));
    if (current_node->next == NULL)
    {
        FreeAltList(head);
        return NULL;
    }

    current_node = current_node->next;
    current_node->string = new_string;

    return head;
}