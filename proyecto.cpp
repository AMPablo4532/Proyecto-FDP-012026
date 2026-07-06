#include <iostream>
#include <windows.h>

using namespace std;

// Variables para el control de las ventas del día (Acumuladores globales)
double totalRecaudadoDia = 0.0;
int totalAlmuerzosDia = 0;
int totalPupusasDia = 0;
int totalPanesDia = 0;
int totalBebidasDia = 0;
int totalVentasRealizadas = 0;
int otraCompra = 1; // Controla el ciclo de ventas del día (1 = Sí, 2 = No)

// 1. TIPOS DE DATOS (Variables para el menú y el control de la compra actual)
int opcionPrincipal = 0;
int productoSeleccionado = 0;
int cantidad = 0;

// Variables para acumular las cantidades de cada producto (por cliente)
int cantAlmuerzo = 0;
int cantPupusas = 0;
int cantPanes = 0;
int cantBebida = 0;

// Precios fijos de los productos
double precioAlmuerzo = 3.25;
double precioPupusas = 0.60;
double precioPanes = 2.00;
double precioBebida = 1.00;

// Variables de cálculo (por cliente)
double subtotal = 0.0;
double descuento = 0.0;
double totalPagar = 0.0;
int esEstudiante = 0; // Usaremos 1 para Sí y 2 para No

// ______________________________________________________________________________
// [ NUEVAS FUNCIONES] --> AnTonIo
// ______________________________________________________________________________
void procesarFacturacion();
void guardarVentasDia();
void mostrarReporteDia();
// ______________________________________________________________________________

int main() {

    SetConsoleOutputCP(CP_UTF8);

    // CICLO GLOBAL: Controla si se abre una nueva venta/cliente en el día
    do {
        cout << "\n=====================================================" << endl;
        cout << "=== BIENVENIDO AL SISTEMA DE COMIDA UNIVERSITARIA ===" << endl;
        cout << "=====================================================" << endl;

        // 2. CICLO WHILE (Controla el menú principal hasta que el usuario decida salir o pagar)
        while (opcionPrincipal != 4) {
            cout << "\n--- MENU PRINCIPAL ---" << endl;
            cout << "1. Ver Menu y Agregar Productos" << endl;
            cout << "2. Ver Detalle del Pedido Actual" << endl;
            cout << "3. Cancelar Compra (Vaciar Carrito)" << endl;
            cout << "4. Proceder al Pago y Facturar" << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcionPrincipal;

            // 3. ESTRUCTURA SWITCH (Para gestionar las opciones del menú principal)
            switch (opcionPrincipal) {
                
                case 1: // Ver menú y agregar productos
                    cout << "\n--- PRODUCTOS DISPONIBLES ---" << endl;
                    cout << "1. Almuerzo Ejecutivo ------- $" << precioAlmuerzo << endl;
                    cout << "2. Pupusa (unidad) ---------- $" << precioPupusas << endl;
                    cout << "3. Pan con Pollo ------------ $" << precioPanes << endl;
                    cout << "4. Bebida / Refresco -------- $" << precioBebida << endl;
                    cout << "Seleccione el numero de producto que desea: ";
                    cin >> productoSeleccionado;

                    // 4. CONDICIONAL IF (Validación de opción de producto válida)
                    if (productoSeleccionado >= 1 && productoSeleccionado <= 4) {
                        cout << "Ingrese la cantidad que desea llevar: ";
                        cin >> cantidad;

                        // Validar que la cantidad sea mayor a 0 usando operadores lógicos y condicionales
                        if (cantidad > 0) {
                            // Sumar al acumulador correspondiente según el producto elegido
                            if (productoSeleccionado == 1) {
                                cantAlmuerzo = cantAlmuerzo + cantidad;
                            } else if (productoSeleccionado == 2) {
                                cantPupusas += cantidad;
                            } else if (productoSeleccionado == 3) {
                                cantPanes += cantidad;
                            } else if (productoSeleccionado == 4) {
                                cantBebida += cantidad;
                            }
                            cout << "¡Producto(s) agregado(s) con exito!" << endl;
                        } else {
                            cout << "Cantidad no valida. Intente de nuevo." << endl;
                        }
                    } else {
                        cout << "Opcion de producto no valida." << endl;
                    }
                    break;

                case 2: // Ver detalle del pedido
                    cout << "\n--- DETALLE DE TU PEDIDO ---" << endl;
                
                    // Evaluamos de forma individual cada acumulador antes de imprimirlo
                    if (cantAlmuerzo > 0) {
                        cout << "Almuerzos: " << cantAlmuerzo << " (Subtotal: $" << cantAlmuerzo * precioAlmuerzo << ")" << endl;
                    }
                    if (cantPupusas > 0) {
                        cout << "Pupusas: " << cantPupusas << " (Subtotal: $" << cantPupusas * precioPupusas << ")" << endl;
                    }
                    if (cantPanes > 0) {
                        cout << "Panes con Pollo: " << cantPanes << " (Subtotal: $" << cantPanes * precioPanes << ")" << endl;
                    }
                    if (cantBebida > 0) {
                        cout << "Bebidas: " << cantBebida << " (Subtotal: $" << cantBebida * precioBebida << ")" << endl;
                    }
                    
                    // Cálculo del subtotal acumulado general
                    subtotal = (cantAlmuerzo * precioAlmuerzo) + (cantPupusas * precioPupusas) + 
                               (cantPanes * precioPanes) + (cantBebida * precioBebida);
                    
                    // Si el carrito está completamente vacío, le avisamos amigablemente al usuario
                    if (subtotal == 0) {
                        cout << "Tu carrito esta vacio. ¡Agrega productos en la opcion 1!" << endl;
                    } else {
                        cout << "Subtotal actual: $" << subtotal << endl;
                    }
                    break;

                case 3: // Cancelar compra
                    // Reiniciamos todas las variables de cantidad a 0
                    cantAlmuerzo = 0;
                    cantPupusas = 0;
                    cantPanes = 0;
                    cantBebida = 0;
                    cout << "\n¡Pedido cancelado y carrito vaciado exitosamente!" << endl;
                    break;

                case 4: // Salir del ciclo para proceder a pagar
                    cout << "\nProcediendo al cierre de la cuenta..." << endl;
                    break;

                default:
                    cout << "Opcion no valida en el menu principal." << endl;
                    break;
            }
        }
        // --- FASE DE FACTURACIÓN Y PAGO (Fuera del ciclo del menú del cliente) ---
        
        // ______________________________________________________________________________
        // [ FUNCION: FACTURACION]
        // ______________________________________________________________________________
        procesarFacturacion();
        // ______________________________________________________________________________

        // Preguntar al usuario (cajero/administrador) si desea procesar otra compra
        cout << "\n[ADMINISTRACION] ¿Desea registrar una nueva venta del dia?" << endl;
        cout << "1. Si (Abrir menu para otro cliente)\n2. No (Cerrar caja y ver reporte diario)" << endl;
        cout << "Seleccione una opcion: ";
        cin >> otraCompra;

        // Resetear variable de menú para el siguiente cliente si decide continuar
        if (otraCompra == 1) {
            opcionPrincipal = 0;
        }

    } while (otraCompra == 1); // Si elige 1, se repite todo para un nuevo cliente

    // ______________________________________________________________________________
    // [ FUNCION: REPORTE DEL DIA]
    // ______________________________________________________________________________
    mostrarReporteDia();
    // ______________________________________________________________________________

    return 0;
}

// ______________________________________________________________________________
// [ DEFINICIÓN DE LAS FUNCIONES]
// ______________________________________________________________________________

//____________________________________________________________________________________________________________________________________________________________
// [ FUNCION: FACTURACION] --> gestiona el cálculo del ticket, descuentos y la impresión del mismo
//____________________________________________________________________________________________________________________________________________________________
void procesarFacturacion() {
    // Calcular el subtotal final con operadores aritméticos
    subtotal = (cantAlmuerzo * precioAlmuerzo) + (cantPupusas * precioPupusas) + (cantPanes * precioPanes) + (cantBebida * precioBebida);

    // Si el carrito está vacío, no tiene sentido aplicar descuentos ni cobrar
    if (subtotal == 0) {
        cout << "\nNo se realizo ninguna compra en esta sesion." << endl;
    } else {
        // Preguntar si aplica a descuento de estudiante de la universidad
        cout << "\n¿Eres estudiante activo de la universidad?" << endl;
        cout << "1. Si\n2. No" << endl;
        cout << "Seleccione una opcion: ";
        cin >> esEstudiante;

        // Condicional para aplicar descuento (Operadores relacionales)
        if (esEstudiante == 1) {
            descuento = subtotal * 0.10; // 10% de descuento para la comunidad estudiantil
            cout << "¡Se ha aplicado un 10% de descuento estudiantil!" << endl;
        } else {
            descuento = 0.0;
        }

        totalPagar = subtotal - descuento;

        // 5. CICLO FOR (Simulación visual de la impresión de la factura/ticket)
        cout << "\n";
        for (int i = 0; i < 40; i++) {
            cout << "*";
        }
        
        cout << "\n        TICKET DE COMPRA UNIVERSITARIA" << endl;
        for (int i = 0; i < 40; i++) {
            cout << "-";
        }
        cout << "\n";

        // Mostrar el desglose final
        if (cantAlmuerzo > 0) cout << "Almuerzos x" << cantAlmuerzo << " -------- $" << cantAlmuerzo * precioAlmuerzo << endl;
        if (cantPupusas > 0)  cout << "Pupusas x" << cantPupusas << " --------- $" << cantPupusas * precioPupusas << endl;
        if (cantPanes > 0)    cout << "Panes x" << cantPanes << " ----------- $" << cantPanes * precioPanes << endl;
        if (cantBebida > 0)   cout << "Bebidas x" << cantBebida << " ---------- $" << cantBebida * precioBebida << endl;

        cout << "\nSubtotal: ------------ $" << subtotal << endl;
        cout << "Descuento: ----------- $" << descuento << endl;
        cout << "TOTAL A PAGAR: ------- $" << totalPagar << endl;

        for (int i = 0; i < 40; i++) {
            cout << "*";
        }
        cout << "\n   ¡Gracias por tu compra! ¡Buen provecho!" << endl;

        // ______________________________________________________________________________
        // [  FUNCION: PARA GUARDAR TOTALES]
        // ______________________________________________________________________________
        guardarVentasDia();
    }
}

//____________________________________________________________________________________________________________________________________________________________
// [  FUNCION: PARA GUARDAR TOTALES] --> encargada de sumar la venta actual al acumulador global del día
//____________________________________________________________________________________________________________________________________________________________
void guardarVentasDia() {
    // =======================================================
    // GUARDAR VENTAS DEL DÍA (Acumulación al reporte global)
    // =======================================================
    totalRecaudadoDia += totalPagar;
    totalAlmuerzosDia += cantAlmuerzo;
    totalPupusasDia += cantPupusas;
    totalPanesDia += cantPanes;
    totalBebidasDia += cantBebida;
    totalVentasRealizadas++;

    // Limpieza de variables del cliente actual para evitar basura en el próximo cliente
    cantAlmuerzo = 0;
    cantPupusas = 0;
    cantPanes = 0;
    cantBebida = 0;
}

//____________________________________________________________________________________________________________________________________________________________
// [ FUNCION: REPORTE DEL DIA] --> encargada de imprimir el consolidado total de ventas al cerrar la caja
//____________________________________________________________________________________________________________________________________________________________
void mostrarReporteDia() {
    // =======================================================
    // REPORTES GENERAL DE VENTAS DEL DÍA (Al terminar el ciclo do-while)
    // =======================================================
    cout << "\n\n";
    for (int i = 0; i < 50; i++) cout << "=";
    cout << "\n         REPORTE DE VENTAS TOTALES DEL DIA" << endl;
    for (int i = 0; i < 50; i++) cout << "=";
    
    cout << "\nTotal de ordenes facturadas de forma exitosa: " << totalVentasRealizadas << endl;
    cout << "\n--- PRODUCTOS VENDIDOS EN EL DIA ---" << endl;
    cout << "Almuerzos Ejecutivos: " << totalAlmuerzosDia << endl;
    cout << "Pupusas totales:      " << totalPupusasDia << endl;
    cout << "Panes con Pollo:      " << totalPanesDia << endl;
    cout << "Bebidas / Refrescos:  " << totalBebidasDia << endl;
    for (int i = 0; i < 50; i++) cout << "-";
    
    cout << "\nTOTAL TOTAL RECAUDADO EN EL DIA: $" << totalRecaudadoDia << endl;
    for (int i = 0; i < 50; i++) cout << "=";
    cout << "\n             ¡Cierre de caja finalizado!" << endl;
}