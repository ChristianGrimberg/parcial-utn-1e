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

    if(!client_init(clients, CLIENT_MAX) && !sale_init(sales, SALE_MAX))
    {
        if(test_clientHardCode(clients, CLIENT_MAX) == -1)
        {
            menu_pauseScreen(ERROR_HARDCODE);
        }
        do
        {
            menu_clearScreen();
            if(!menu_showPrincipalMenu(&selectionMenu))
            {
                switch(selectionMenu)
                {
                    case 1:
                        if(!menu_loadClientAux(&clientAux)
                        && !client_add(clients, CLIENT_MAX, clientAux.name,
                            clientAux.lastName, clientAux.cuit))
                        {
                            printf("Cliente/a ingresado/a correctamente.\n");
                        }
                        else
                        {
                            printf("Carga de Cliente/a cancelada.\n");
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
                            indexAux))
                        {
                            printf("Se dio de baja el/la Cliente/a.\n");
                        }
                        else
                        {
                            printf("Baja cancelada.\n");
                        }
                        break;
                    case 4:
                        menu_clearScreen();
                        if(!menu_loadSaleAux(&saleAux, clients, CLIENT_MAX,
                            posters, POSTER_MAX)
                        && !sale_add(sales, SALE_MAX, saleAux.clientId,
                            saleAux.posterId, saleAux.posterQty, saleAux.zone))
                        {
                            printf("Venta ingresada correctamente.\n");
                        }
                        else
                        {
                            printf("Carga de Venta cancelada.\n");
                        }
                        break;
                    case 5:
                        if(!menu_editSaleOptions(sales, SALE_MAX,
                            &indexAux, &optionSubMenu)
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
                    case 7:
                        menu_clearScreen();
                        inform_printClientList(clients, CLIENT_MAX);
                        break;
                    case 8:
                        menu_clearScreen();
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
