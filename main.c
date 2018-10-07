#include "menu.h"
#include "test.h"
#include "inform.h"

int main()
{
    Client clients[CLIENT_MAX];
    Client clientAux;
    Sale sales[SALES_MAX];
    Sale saleAux;
    int optionMenu;
    int selectionMenu = -1;
    int optionSubMenu;
    char runProgram = 'S';
    int indexAux;

    if(!client_init(clients, CLIENT_MAX) && !sale_init(sales, SALES_MAX))
    {
        if(test_clientHardCode(clients, CLIENT_MAX) == -1)
        {
            menu_pauseScreen(ERROR_HARDCODE);
        }
        do
        {
            menu_clearScreen();
            optionMenu = menu_showPrincipalMenu(&selectionMenu);
            switch(selectionMenu)
            {
                case 1:
                    if(!menu_loadNewClientByUser(&clientAux)
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
                    if(!menu_editClientByUser(clients, CLIENT_MAX,
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
                    if(menu_removeClientByUser(clients, CLIENT_MAX,
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
                    if(!menu_loadNewVentaByUser(&saleAux, clients, CLIENT_MAX)
                    && !venta_addVenta(sales, SALES_MAX, saleAux.clientId,
                        saleAux.cantidadAfiches, saleAux.nombreAfiche, saleAux.zona))
                    {
                        printf("Venta ingresada correctamente.\n");
                    }
                    else
                    {
                        printf("Carga de Venta cancelada.\n");
                    }
                    break;
                case 5:
                    if(!menu_editVentaByUser(sales, SALES_MAX,
                        &indexAux, &optionSubMenu)
                    && !venta_editVentaByIndex(sales, SALES_MAX,
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
            while((char)(toupper(runProgram)) != 'N'
            && !utn_getChar(&runProgram, RETRY,
                "Desea Continuar? (S/N): ", ERROR_MESSAGE))
            {
                if((char)(toupper(runProgram)) == 'N')
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
