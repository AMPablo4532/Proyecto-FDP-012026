#include <iostream>
#include <windows.h>
#include <string>
#include "funciones.h" //enlace a las funciones externas

using namespace std;

//todas las variables que ocupa el sistema
double totalRecaudadoDia = 0.0;
int totalAlmuerzosDia = 0;
int totalPupusasDia = 0;
int totalPanesDia = 0;
int totalBebidasDia = 0;
int totalVentasRealizadas = 0;
int otraCompra = 1; 

int opcionPrincipal = 0;
int productoSeleccionado = 0;
int cantidad = 0;
int cantAlmuerzo = 0;
int cantPupusas = 0;
int cantPanes = 0;
int cantBebida = 0;

double precioAlmuerzo = 3.25;
double precioPupusas = 0.60;
double precioPanes = 2.00;
double precioBebida = 1.00;
double subtotal = 0.0;
double descuento = 0.0;
double totalPagar = 0.0;
int esEstudiante = 0; 

double historialVentas[MAX_VENTAS];

string nombreProductos[4] = {"Almuerzo Ejecutivo", "Pupusa", "Pan con Pollo", "Bebida/Refresco"};
double preciosProductos[4] = {precioAlmuerzo, precioPupusas, precioPanes, precioBebida};

int main() {
  SetConsoleOutputCP(CP_UTF8);

  do {
    opcionPrincipal = 0; 

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

    subtotal = (cantAlmuerzo*precioAlmuerzo) + (cantPupusas*precioPupusas) + (cantPanes*precioPanes) + (cantBebida*precioBebida);

    if(subtotal == 0) {
      cout << "\nNo se realizo ninguna compra en esta sesion." << endl;
    } else {
      procesarFacturacion();
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