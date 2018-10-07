#include "test.h"

int test_clientHardCode(Client* list, int len)
{
    int returnValue = -1;

    if(WITH_HARDCODE
    && (!cliente_addClient(list, len, "Homero", "Simpson", "11/2.222.222-3")
    && !cliente_addClient(list, len, "Barney", "Gomez", "12/3.456.789-0")
    && !cliente_addClient(list, len, "Marge", "Simpson", "22/3.333.333-4")
    && !cliente_addClient(list, len, "Ned", "Flanders", "56/7.890.123-4")
    && !cliente_addClient(list, len, "Montgomery", "Burns", "44/5.555.555-6")
    && !cliente_addClient(list, len, "Edna", "Krabappel", "98/7.654.321-0")))
    {
        returnValue = 0;
    }

    return returnValue;
}
