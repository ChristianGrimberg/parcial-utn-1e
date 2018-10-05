#include "menu.h"
#include "test.h"

int main()
{
    Client clients[CLIENT_MAX];
    Client clientAux;
    Venta ventas[VENTAS_MAX];
    Venta ventaAux;
    int optionMenu;
    int selectionMenu = -1;
    int optionSubMenu;
    char runProgram = 'S';
    int indexAux;

    if(cliente_init(clients, CLIENT_MAX) == 0 && venta_init(ventas, VENTAS_MAX) == 0)
    {
        if(WITH_HARDCODE && test_clientHardCode(clients, CLIENT_MAX) == -1)
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
                    && cliente_addClient(clients, CLIENT_MAX, clientAux.name,
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
                    if(menu_editClientByUser(clients, CLIENT_MAX,
                        &indexAux, &optionSubMenu) == 0
                    && cliente_editClientByIndex(clients, CLIENT_MAX,
                        indexAux, optionSubMenu) == 0)
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
                        &indexAux) == 1
                    && cliente_removeClientByIndex(clients, CLIENT_MAX,
                        indexAux) == 0)
                    {
                        printf("Se dio de baja el/la Cliente/a.\n");
                    }
                    else
                    {
                        printf("Baja cancelada.\n");
                    }
                    break;
                case 4:
                    if(menu_loadNewVentaByUser(&ventaAux, clients, CLIENT_MAX) == 0
                    && venta_addVenta(ventas, VENTAS_MAX, ventaAux.clientId,
                        ventaAux.cantidadAfiches, ventaAux.nombreAfiche, ventaAux.zona) == 0)
                    {
                        printf("Venta ingresada correctamente.\n");
                    }
                    else
                    {
                        printf("Carga de Venta cancelada.\n");
                    }
                    break;
                case 5:
                    if(menu_editVentaByUser(ventas, VENTAS_MAX,
                        &indexAux, &optionSubMenu) == 0
                    && venta_editVentaByIndex(ventas, VENTAS_MAX,
                        clients, CLIENT_MAX, indexAux, optionSubMenu) == 0)
                    {
                        printf("Modificacion exitosa.\n");
                    }
                    else
                    {
                        printf("Modificacion cancelada.\n");
                    }
                    break;
                case 7:
                    cliente_printClientList(clients, CLIENT_MAX);
                    break;
                case 8:
                    runProgram = 'N';
                    break;
            }
            if((char)(toupper(runProgram)) == 'N')
            {
                break;
            }
            else
            {
                while(utn_getChar(&runProgram, RETRY,
                    "Desea Continuar? (S/N): ", "Valor Incorrecto. ") == 0
                && (char)(toupper(runProgram)) != 'S')
                {
                    if((char)(toupper(runProgram)) == 'N')
                    {
                        optionMenu = -1;
                        break;
                    }
                }
            }
        }while(optionMenu == 0);
    }
    else
    {
        printf("Error de inicializacion de nomina de Empleados.\n");
    }

    return 0;
}
