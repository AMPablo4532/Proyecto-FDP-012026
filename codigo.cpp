#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

// acumuladores de ventas del dia
double totalRecaudadoDia = 0.0;
int totalAlmuerzosDia = 0;
int totalPupusasDia = 0;
int totalPanesDia = 0;
int totalBebidasDia = 0;
int totalVentasRealizadas = 0;
int otraCompra = 1; 

// control de menu y compra cliente
int opcionPrincipal = 0;
int productoSeleccionado = 0;
int cantidad = 0;

// cantidades individuales carrito
int cantAlmuerzo = 0;
int cantPupusas = 0;
int cantPanes = 0;
int cantBebida = 0;

// lista de precios fijos
double precioAlmuerzo = 3.25;
double precioPupusas = 0.60;
double precioPanes = 2.00;
double precioBebida = 1.00;

// variables globales de calculo
double subtotal = 0.0;
double descuento = 0.0;
double totalPagar = 0.0;
int esEstudiante = 0; 

// arreglo para guardar el total de cada venta que se hace en el dia
const int MAX_VENTAS = 100;
double historialVentas[MAX_VENTAS];

// arreglos paralelos con info de los productos, para poder recorrerlos con un for
string nombreProductos[4] = {"Almuerzo Ejecutivo", "Pupusa", "Pan con Pollo", "Bebida/Refresco"};
double preciosProductos[4] = {precioAlmuerzo, precioPupusas, precioPanes, precioBebida};

// declaracion de funciones
void procesarFacturacion();
void guardarVenta();
void mostrarReporte();

int main() {
    SetConsoleOutputCP(CP_UTF8);

    do {
        opcionPrincipal = 0; // limpia seleccion anterior

        cout << "\n=====================================================" << endl;
        cout << "=== BIENVENIDO AL SISTEMA DE COMIDA UNIVERSITARIA ===" << endl;
        cout << "=====================================================" << endl;

        while(opcionPrincipal != 4) {
            cout << "\n--- MENU PRINCIPAL ---" << endl;
            cout << "1. Ver Menu y Agregar Productos" << endl;
            cout << "2. Ver Detalle del Pedido Actual" << endl;
            cout << "3. Cancelar Compra (Vaciar Carrito)" << endl;
            cout << "4. Proceder al Pago y Facturar" << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcionPrincipal;

            switch(opcionPrincipal) {
                case 1: 
                    cout << "\n--- PRODUCTOS DISPONIBLES ---" << endl;
                    cout << "1. Almuerzo Ejecutivo ------- $" << precioAlmuerzo << endl;
                    cout << "2. Pupusa (unidad) ---------- $" << precioPupusas << endl;
                    cout << "3. Pan con Pollo ------------ $" << precioPanes << endl;
                    cout << "4. Bebida / Refresco -------- $" << precioBebida << endl;
                    cout << "Seleccione el numero de producto que desea: ";
                    cin >> productoSeleccionado;

                    if(productoSeleccionado >= 1 && productoSeleccionado <= 4) {
                        cout << "Ingrese la cantidad que desea llevar: ";
                        cin >> cantidad;

                        if(cantidad > 0) {
                            switch(productoSeleccionado) {
                                case 1: cantAlmuerzo += cantidad; break;
                                case 2: cantPupusas += cantidad; break;
                                case 3: cantPanes += cantidad; break;
                                case 4: cantBebida += cantidad; break;
                            }
                            cout << "¡Producto(s) agregado(s) con exito!" << endl;
                        } else {
                            cout << "Cantidad no valida. Intente de nuevo." << endl;
                        }
                    } else {
                        cout << "Opcion de producto no valida." << endl;
                    }
                    break;

                case 2: 
                    cout << "\n--- DETALLE DE TU PEDIDO ---" << endl;
                    if(cantAlmuerzo > 0) cout << "Almuerzos: " << cantAlmuerzo << " (Subtotal: $" << cantAlmuerzo*precioAlmuerzo << ")" << endl;
                    if(cantPupusas > 0)  cout << "Pupusas: " << cantPupusas << " (Subtotal: $" << cantPupusas*precioPupusas << ")" << endl;
                    if(cantPanes > 0)    cout << "Panes con Pollo: " << cantPanes << " (Subtotal: $" << cantPanes*precioPanes << ")" << endl;
                    if(cantBebida > 0)   cout << "Bebidas: " << cantBebida << " (Subtotal: $" << cantBebida*precioBebida << ")" << endl;
                    
                    subtotal = (cantAlmuerzo * precioAlmuerzo) + (cantPupusas * precioPupusas) + (cantPanes * precioPanes) + (cantBebida * precioBebida);
                    
                    if(subtotal == 0) {
                        cout << "Tu carrito esta vacio. ¡Agrega productos en la opcion 1!" << endl;
                    } else {
                        cout << "Subtotal actual: $" << subtotal << endl;
                    }
                    break;

                case 3: 
                    cantAlmuerzo = 0; cantPupusas = 0; cantPanes = 0; cantBebida = 0;
                    cout << "\n¡Pedido cancelado y carrito vaciado exitosamente!" << endl;
                    break;

                case 4: 
                    cout << "\nProcediendo al cierre de la cuenta..." << endl;
                    break;

                default:
                    cout << "Opcion no valida en el menu principal." << endl;
                    break;
            }
        }

        // calculo final fuera del menu del cliente
        subtotal = (cantAlmuerzo*precioAlmuerzo) + (cantPupusas*precioPupusas) + (cantPanes*precioPanes) + (cantBebida*precioBebida);

        if(subtotal == 0) {
            cout << "\nNo se realizo ninguna compra en esta sesion." << endl;
        } else {
            procesarFacturacion();
            // reseteo inmediato para el proximo cliente
            cantAlmuerzo = 0; cantPupusas = 0; cantPanes = 0; cantBebida = 0;
        }

        cout << "\n[ADMINISTRACION] ¿Desea registrar una nueva venta del dia?" << endl;
        cout << "1. Si (Abrir menu para otro cliente)\n2. No (Cerrar caja y ver reporte diario)" << endl;
        cout << "Seleccione una opcion: ";
        cin >> otraCompra;

    } while(otraCompra == 1); 

    mostrarReporte();
    return 0;
}

// gestion de cobro y aplicacion de descuento
void procesarFacturacion() {
    cout << "\n¿Eres estudiante activo de la universidad?" << endl;
    cout << "1. Si\n2. No" << endl;
    cout << "Seleccione una opcion: ";
    cin >> esEstudiante;

    // si el usuario escribe texto en vez de un numero, cin queda en error
    // esto limpia ese error y pide el dato de nuevo hasta que sea valido
    while(cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Entrada no valida. Por favor ingresa 1 o 2: ";
        cin >> esEstudiante;
    }

    switch(esEstudiante) {
        case 1:
            descuento = subtotal * 0.10;
            cout << "¡Se ha aplicado un 10% de descuento estudiantil!" << endl;
            break;
        default:
            descuento = 0.0;
            break;
    }

    totalPagar = subtotal - descuento;

    cout << "\n";
    for(int i=0; i<40; i++) cout << "*";
    cout << "\n        TICKET DE COMPRA UNIVERSITARIA" << endl;
    for(int i=0; i<40; i++) cout << "-";
    cout << "\n";

    if(cantAlmuerzo > 0) cout << "Almuerzos x" << cantAlmuerzo << " -------- $" << cantAlmuerzo*precioAlmuerzo << endl;
    if(cantPupusas > 0)  cout << "Pupusas x" << cantPupusas << " --------- $" << cantPupusas*precioPupusas << endl;
    if(cantPanes > 0)    cout << "Panes x" << cantPanes << " ----------- $" << cantPanes*precioPanes << endl;
    if(cantBebida > 0)   cout << "Bebidas x" << cantBebida << " ---------- $" << cantBebida*precioBebida << endl;

    cout << "\nSubtotal: ------------ $" << subtotal << endl;
    cout << "Descuento: ----------- $" << descuento << endl;
    cout << "TOTAL A PAGAR: ------- $" << totalPagar << endl;

    for(int i=0; i<40; i++) cout << "*";
    cout << "\n   ¡Gracias por tu compra! ¡Buen provecho!" << endl;

    guardarVenta();
}

// añade los montos al reporte general
void guardarVenta() {
    totalRecaudadoDia += totalPagar;
    totalAlmuerzosDia += cantAlmuerzo;
    totalPupusasDia += cantPupusas;
    totalPanesDia += cantPanes;
    totalBebidasDia += cantBebida;
    totalVentasRealizadas++;

    // guarda el total de esta venta en el historial (indice -1 porque ya se incremento arriba)
    if(totalVentasRealizadas <= MAX_VENTAS) {
        historialVentas[totalVentasRealizadas - 1] = totalPagar;
    }
}

// muestra el cierre final de caja
void mostrarReporte() {
    cout << "\n\n";
    for(int i=0; i<50; i++) cout << "=";
    cout << "\n          REPORTE DE VENTAS TOTALES DEL DIA" << endl;
    for(int i=0; i<50; i++) cout << "=";
    
    cout << "\nTotal de ordenes facturadas de forma exitosa: " << totalVentasRealizadas << endl;
    cout << "\n--- PRODUCTOS VENDIDOS EN EL DIA ---" << endl;
    cout << "Almuerzos Ejecutivos: " << totalAlmuerzosDia << endl;
    cout << "Pupusas totales:      " << totalPupusasDia << endl;
    cout << "Panes con Pollo:      " << totalPanesDia << endl;
    cout << "Bebidas / Refrescos:  " << totalBebidasDia << endl;
    for(int i=0; i<50; i++) cout << "-";
    
    cout << "\nTOTAL TOTAL RECAUDADO EN EL DIA: $" << totalRecaudadoDia << endl;
    for(int i=0; i<50; i++) cout << "=";
    cout << "\n             ¡Cierre de caja finalizado!" << endl;

    // estadisticas usando el arreglo historialVentas
    if(totalVentasRealizadas > 0) {
        double ventaMasAlta = historialVentas[0];
        double ventaMasBaja = historialVentas[0];
        double sumaTotal = 0.0;

        cout << "\n\n--- DETALLE DE CADA VENTA ---" << endl;
        for(int i = 0; i < totalVentasRealizadas; i++) {
            cout << "Venta #" << (i+1) << ": $" << historialVentas[i] << endl;
            sumaTotal += historialVentas[i];
            if(historialVentas[i] > ventaMasAlta) ventaMasAlta = historialVentas[i];
            if(historialVentas[i] < ventaMasBaja) ventaMasBaja = historialVentas[i];
        }

        cout << "\nVenta mas alta del dia: $" << ventaMasAlta << endl;
        cout << "Venta mas baja del dia: $" << ventaMasBaja << endl;
        cout << "Promedio por venta: $" << (sumaTotal / totalVentasRealizadas) << endl;
    }

    // busca el producto mas vendido recorriendo el arreglo de totales
    int totalesPorProducto[4] = {totalAlmuerzosDia, totalPupusasDia, totalPanesDia, totalBebidasDia};
    int indiceMax = 0;
    for(int i = 1; i < 4; i++) {
        if(totalesPorProducto[i] > totalesPorProducto[indiceMax]) {
            indiceMax = i;
        }
    }
    if(totalesPorProducto[indiceMax] > 0) {
        double ingresoProductoTop = totalesPorProducto[indiceMax] * preciosProductos[indiceMax];
        cout << "\nProducto mas vendido del dia: " << nombreProductos[indiceMax]
             << " (" << totalesPorProducto[indiceMax] << " unidades, $" << ingresoProductoTop << " generados)" << endl;
    }
}
