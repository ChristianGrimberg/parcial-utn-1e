#include "inform.h"

void inform_printClientList(Client* list, int len)
{
    int i;

    if(client_getQuantity(list, len) != -1)
    {
        client_printTableOptions(list, 0, HEADER);
        for(i = 0; i < len; i++)
        {
            if(list[i].isEmpty == TRUE)
            {
                continue;
            }
            else
            {
                client_printTableOptions(list, i, BODY);
            }
        }
        client_printTableOptions(list, 0, FOOTER);
    }
    else
    {
        printf(ERROR_EMPTY_LIST);
    }
}

void inform_printPosterList(Poster* list, int len)
{
    int i;

    if(poster_getQuantity(list, len) != -1)
    {
        poster_printTableOptions(list, 0, HEADER);
        for(i = 0; i < len; i++)
        {
            if(list[i].isEmpty == TRUE)
            {
                continue;
            }
            else
            {
                poster_printTableOptions(list, i, BODY);
            }
        }
        poster_printTableOptions(list, 0, FOOTER);
    }
    else
    {
        printf(ERROR_EMPTY_LIST);
    }
}