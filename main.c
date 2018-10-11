#include "menu.h"
#include "test.h"

int main()
{
    Client clients[CLIENT_MAX];
    Client clientAux;
    Sale sales[SALE_MAX];
    Sale saleAux;
    Poster posters[POSTER_MAX];
    int selectionMenu = -1;
    int optionSubMenu;
    char runProgram = 'S';
    int indexAux;
    int salesQty;
    int posterQty;

    if(!client_init(clients, CLIENT_MAX) && !sale_init(sales, SALE_MAX)
        && !poster_init(posters, POSTER_MAX))
    {
        if(test_clientHardCode(clients, CLIENT_MAX) == -1
        || test_posterHardCode(posters, POSTER_MAX) == -1
        || test_saleHardCode(sales, SALE_MAX) == -1)
        {
            menu_pauseScreen(ERROR_HARDCODE);
        }
        do
        {
            if(!menu_showPrincipalMenu(&selectionMenu))
            {
                menu_clearScreen();
                switch(selectionMenu)
                {
                    case 1:
                        if(!menu_loadClientAux(&clientAux)
                        && !client_add(clients, CLIENT_MAX, clientAux.name,
                            clientAux.lastName, clientAux.cuit))
                        {
                            printf("Carga exitosa.\n");
                        }
                        else
                        {
                            printf("Carga cancelada.\n");
                        }
                        break;
                    case 2:
                        if(!menu_editClientOptions(clients, CLIENT_MAX,
                            &indexAux, &optionSubMenu)
                        && !client_edit(clients, CLIENT_MAX,
                            indexAux, optionSubMenu))
                        {
                            printf("Modificacion exitosa.\n");
                        }
                        else
                        {
                            printf("Modificacion cancelada.\n");
                        }
                        break;
                    case 3:
                        if(menu_removeClientOptions(clients, CLIENT_MAX,
                            &indexAux)
                        && !client_remove(clients, CLIENT_MAX,
                            indexAux)
                        && !sale_removeByClient(sales, SALE_MAX,
                            clients, CLIENT_MAX, (clients+indexAux)->clientId))
                        {
                            printf("Baja exitosa.\n");
                        }
                        else
                        {
                            printf("Baja cancelada.\n");
                        }
                        break;
                    case 4:
                        if(!menu_loadSaleAux(&saleAux, clients, CLIENT_MAX,
                            posters, POSTER_MAX)
                        && !sale_add(sales, SALE_MAX, saleAux.clientId,
                            saleAux.posterId, saleAux.posterQty, saleAux.zone))
                        {
                            printf("Venta exitosa.\n");
                        }
                        else
                        {
                            printf("Venta cancelada.\n");
                        }
                        break;
                    case 5:
                        if(!menu_editSaleOptions(sales, SALE_MAX, clients, CLIENT_MAX,
                            posters, POSTER_MAX, &indexAux, &optionSubMenu)
                        && !sale_edit(sales, SALE_MAX,
                            clients, CLIENT_MAX, indexAux, optionSubMenu))
                        {
                            printf("Modificacion exitosa.\n");
                        }
                        else
                        {
                            printf("Modificacion cancelada.\n");
                        }
                        break;
                    case 6:
                        if(!menu_editSaleState(sales, SALE_MAX, clients, CLIENT_MAX,
                            posters, POSTER_MAX, &indexAux)
                        && !sale_invoice(sales, SALE_EDIT_MAX, indexAux))
                        {
                            printf("Venta cobrada con exito.\n");
                        }
                        break;
                    case 7:
                        inform_printClientList(clients, CLIENT_MAX);
                        inform_printSaleList(sales, SALE_MAX, clients, CLIENT_MAX, posters, POSTER_MAX);
                        break;
                    case 8:
                        if(!menu_showInformMenu(&selectionMenu))
                        {
                            menu_clearScreen();
                            switch(selectionMenu)
                            {
                                case 1:
                                    salesQty = inform_printBestClient(sales, SALE_MAX,
                                        clients, CLIENT_MAX, A_COBRAR, WITHOUT_POSTER);
                                    if(salesQty == -1)
                                    {
                                        printf("No se encuentra clientes con mas ventas a cobrar.\n");
                                    }
                                    else
                                    {
                                        printf("%d ventas a cobrar.\n", salesQty);
                                    }
                                    break;
                                case 2:
                                    salesQty = inform_printBestClient(sales, SALE_MAX,
                                        clients, CLIENT_MAX, COBRADA, WITHOUT_POSTER);
                                    if(salesQty == -1)
                                    {
                                        printf("No se encuentra clientes con mas ventas cobradas.\n");
                                    }
                                    else
                                    {
                                        printf("%d ventas cobradas.\n", salesQty);
                                    }
                                    break;
                                case 3:
                                    salesQty = inform_printBestClient(sales, SALE_MAX,
                                        clients, CLIENT_MAX, TODAS_VENTAS, WITHOUT_POSTER);
                                    if(salesQty == -1)
                                    {
                                        printf("No se encuentra clientes con mas ventas.\n");
                                    }
                                    else
                                    {
                                        printf("%d ventas totales.\n", salesQty);
                                    }
                                    break;
                                case 4:
                                    posterQty = inform_printBestClient(sales, SALE_MAX,
                                        clients, CLIENT_MAX, A_COBRAR, WITH_POSTER);
                                    if(posterQty == -1)
                                    {
                                        printf("No se encuentra clientes con mas afiches a cobrar.\n");
                                    }
                                    else
                                    {
                                        printf("Tiene %d afiches a cobrar.\n", posterQty);
                                    }
                                    break;
                                case 5:
                                    posterQty = inform_printBestClient(sales, SALE_MAX,
                                        clients, CLIENT_MAX, COBRADA, WITH_POSTER);
                                    if(posterQty == -1)
                                    {
                                        printf("No se encuentra clientes que haya comprado mas afiches.\n");
                                    }
                                    else
                                    {
                                        printf("Compro %d afiches.\n", posterQty);
                                    }
                                    break;
                            }
                        }
                        break;
                    case 9:
                        runProgram = 'N';
                        break;
                }
            }
            while((char)(toupper(runProgram)) != 'N'
            && !utn_getChar(&runProgram, RETRY,
                "Desea Continuar? (S/N): ", ERROR_MESSAGE))
            {
                if((char)(toupper(runProgram)) == 'N'
                || (char)(toupper(runProgram)) == 'S')
                {
                    menu_clearScreen();
                    break;
                }
            }
        }while((char)(toupper(runProgram)) != 'N');
    }
    else
    {
        printf("Error de inicializacion de listados.\n");
    }

    return 0;
}
