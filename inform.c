#include "inform.h"

void inform_printClientList(Client* list, int len)
{
    int i;

    if(client_getQuantity(list, len) != -1)
    {
        client_printFormatedClient(list, 0, HEADER);
        for(i = 0; i < len; i++)
        {
            if(list[i].isEmpty == TRUE)
            {
                continue;
            }
            else
            {
                client_printFormatedClient(list, i, BODY);
            }
        }
        client_printFormatedClient(list, 0, FOOTER);
    }
    else
    {
        printf(ERROR_EMPTY_LIST);
    }
}