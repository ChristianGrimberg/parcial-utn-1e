# Primer parcial Laboratorio de Computación 1
Una empresa de venta y colocación de afiches publicitarios en la vía pública, requiere un sistema para administrar la venta de afiches. El mismo deberá tener un registro de clientes y de afiches vendidos. Contará con el siguiente menú:
1. __Alta de cliente:__ Se da de alta un cliente con nombre, apellido, y CUIT. Se generará un ID único para este cliente que se imprimirá por pantalla por pantalla si el alta es correcta.
1. __Modificar datos de cliente:__ Se ingresa el ID de cliente y se permitirá cambiar el nombre, apellido y CUIT.
1. __Baja de cliente:__ Se ingresa el ID del cliente. Luego se preguntará si se quiere confirmar la eliminación, la cual implicará la eliminación de todas las ventas y del cliente.
1. __Vender afiches:__ Se pedirán los siguientes datos: ID de cliente, cantidad de afiches, nombre del archivo con la imagen del afiche y la zona donde se pegarán los afiches (CABA, ZONA SUR o ZONA OESTE). Se generará automáticamente un identificador numérico para la venta y se imprimirá en pantalla dicho ID en el caso que los datos ingresados sean correctos. La venta quedará en un estado "a cobrar". Mientras esté en este estado podrá ser modificada.
1. __Editar venta:__ Se listarán todas las ventas con todos sus campos. Se pedirá el ID de la venta y se permitirá cambiar la cantidad de afiches y la zona.
1. __Cobrar venta:__ Se listarán todas las ventas con todos sus campos. Se pedirá el ID de la venta y se imprimirá la información del cliente al que pertenece, luego se pedirá confirmación para cambiarse de estado y se cambiará al estado "Cobrada".
1. __Imprimir clientes:__ Se imprimirá una lista de clientes con todos sus datos junto con la cantidad de ventas "a cobrar" que posee.
> __Nota 0:__ El sistema soportará una capacidad máxima de 100 clientes y 1000 ventas.

> __Nota 1:__ Se deberán desearrollar bibliotecas por cada entidad las cuáles contendrán las funciones (Alta, Baja, Modificar, etc.). Los informes deberán estar en una biblioteca aparte.

> __Nota 2:__ El código deberá tener comentarios con la documentación de cada una de las funciones y respetar las reglas de estilo de la cátedra.