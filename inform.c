#include "inform.h"

void inform_printClientList(Client* list, int len)
{
    int i;

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