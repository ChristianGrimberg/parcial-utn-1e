#include "inform.h"

static int clientMostSale_init(ClientMostSale* list, int len);

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

void inform_printSaleList(Sale* saleList, int saleLen, Client* clientList,
    int clientLen, Poster* posterList, int posterLen)
{
    int i;

    if(sale_getQuantity(saleList, saleLen) != -1)
    {
        sale_printTableOptions(saleList, saleLen, clientList, clientLen,
            posterList, posterLen, 0, HEADER);
        for(i = 0; i < saleLen; i++)
        {
            if(saleList[i].isEmpty == TRUE)
            {
                continue;
            }
            else
            {
                sale_printTableOptions(saleList, saleLen, clientList, clientLen,
                    posterList, posterLen, i, BODY);
            }
        }
        sale_printTableOptions(saleList, saleLen, clientList, clientLen,
            posterList, posterLen, 0, FOOTER);
    }
    else
    {
        printf(ERROR_EMPTY_LIST);
    }
}

int inform_printBestClient(Sale* saleList, int saleLen,
    Client* clientList, int clientLen, int field, int posterIndicator)
{
    int returnValue = -1;
    ClientMostSale clientSalesAux[clientLen];
    int i;
    int counter;
    int maxValue;
    int maxPoster;
    int indexClientAux;

    if(saleList != NULL && saleLen > 0
    && saleLen <= SALE_MAX && clientList != NULL
    && clientLen > 0 && clientLen <= CLIENT_MAX
    && !clientMostSale_init(clientSalesAux, clientLen)
    && field >= A_COBRAR && field <= TODAS_VENTAS
    && (posterIndicator == WITH_POSTER || posterIndicator == WITHOUT_POSTER))
    {
        counter = 0;
        maxValue = 0;
        maxPoster = 0;
        for(i = 0; i < saleLen; i++)
        {
            if(!(saleList+i)->isEmpty)
            {
                switch(field)
                {
                    case A_COBRAR:
                    case COBRADA:
                        if((saleList+i)->state == field)
                        {
                            (clientSalesAux+counter)->salesQty++;
                            //(clientSalesAux+counter)->posterQty += (clientSalesAux+counter)->posterQty;
                            if(posterIndicator == WITHOUT_POSTER
                            && (clientSalesAux+counter)->salesQty > maxValue)
                            {
                                maxValue = (clientSalesAux+counter)->salesQty;
                                indexClientAux = client_findId(clientList, clientLen,
                                    (saleList+i)->clientId);
                            }
                            else if(posterIndicator == WITH_POSTER
                            && (clientSalesAux+counter)->posterQty > maxPoster)
                            {
                                maxPoster = (clientSalesAux+counter)->posterQty;
                                indexClientAux = client_findId(clientList, clientLen,
                                    (saleList+i)->clientId);
                            }
                            counter++;
                        }
                        break;
                    case TODAS_VENTAS:
                        if((saleList+i)->state == A_COBRAR
                        || (saleList+i)->state == COBRADA)
                        {
                            (clientSalesAux+counter)->salesQty++;
                            if((clientSalesAux+counter)->salesQty > maxValue)
                            {
                                maxValue = (clientSalesAux+counter)->salesQty;
                                indexClientAux = client_findId(clientList, clientLen,
                                    (saleList+i)->clientId);
                            }
                            counter++;
                        }
                        break;
                }
                //printf("[DEBUG]: ClientName:%s Sales:%d\n", (clientList+indexClientAux)->name, );
            }
        }
        if(counter > 0)
        {
            client_print(clientList, indexClientAux);
            if(posterIndicator == WITHOUT_POSTER)
            {
                returnValue = maxValue;
            }
            else if(posterIndicator == WITH_POSTER)
            {
                returnValue = maxPoster;
            }
        }
    }

    return returnValue;
}

static int clientMostSale_init(ClientMostSale* list, int len)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0 && len <= CLIENT_MAX)
    {
        for(i = 0; i < len; i++)
        {
            list[i].client.isEmpty = TRUE;
            (list+i)->salesQty = 0;
            (list+i)->posterQty = 0;
        }
        if(i == len)
        {
            returnValue = 0;
        }
    }

    return returnValue;
}
