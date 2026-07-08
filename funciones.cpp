#include <iostream>
#include <fstream> 
#include "funciones.h"

using namespace std;

void procesarFacturacion() {
  cout << "Eres estudiante activo de la universidad?" << endl;
  cout << "1. Si" << endl;
  cout << "2. No" << endl;
  cout << "Seleccione una opcion: ";
  cin >> esEstudiante;
    //nota: los metodos fail y clear fueron implementados con ayuda de IA 
    //para validar que el usuario ingrese un numero 1 o 2
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

    cout << endl;
    cout << "FACTURA" << endl;
    cout << "------------------------" << endl;

    if (cantAlmuerzo > 0) {
      cout << "Almuerzos: " << cantAlmuerzo << endl;
      cout << "Precio: $" << cantAlmuerzo * precioAlmuerzo << endl;
    }
    if (cantPupusas > 0) {
      cout << "Pupusas: " << cantPupusas << endl;
      cout << "Precio: $" << cantPupusas * precioPupusas << endl;
    }
    if (cantPanes > 0) {
      cout << "Panes: " << cantPanes << endl;
      cout << "Precio: $" << cantPanes * precioPanes << endl;
    }
    if (cantBebida > 0) {
      cout << "Bebidas: " << cantBebida << endl;
      cout << "Precio: $" << cantBebida * precioBebida << endl;
    }
    cout << "------------------------" << endl;
    cout << "Subtotal: $" << subtotal << endl;
    cout << "Descuento: $" << descuento << endl;
    cout << "Total: $" << totalPagar << endl;
    cout << "Gracias por su compra." << endl;

    // Manejo de archivos aspecto generado por IA
    ofstream archivo("factura.txt");
    if(archivo.is_open()) {
        archivo << "FACTURA CAFETERIA UNIVERSITARIA\n";
        archivo << "========================================\n\n";

        if(cantAlmuerzo > 0) archivo << "Almuerzos x" << cantAlmuerzo << " = $" << cantAlmuerzo*precioAlmuerzo << endl;
        if(cantPupusas > 0)  archivo << "Pupusas x" << cantPupusas << " = $" << cantPupusas*precioPupusas << endl;
        if(cantPanes > 0)    archivo << "Panes x" << cantPanes << " = $" << cantPanes*precioPanes << endl;
        if(cantBebida > 0)   archivo << "Bebidas x" << cantBebida << " = $" << cantBebida*precioBebida << endl;

        archivo << "\nSubtotal: $" << subtotal << endl;
        archivo << "Descuento (10%): $" << descuento << endl;
        archivo << "----------------------------------------" << endl;
        archivo << "TOTAL: $" << totalPagar << endl;
        
        archivo.close();
        cout << "\n[SISTEMA] Factura guardada exitosamente en 'factura.txt'\n";
    }
    guardarVenta();
}

void guardarVenta() {
  totalRecaudadoDia += totalPagar;
  totalAlmuerzosDia += cantAlmuerzo;
  totalPupusasDia += cantPupusas;
  totalPanesDia += cantPanes;
  totalBebidasDia += cantBebida;
  totalVentasRealizadas++;

  if(totalVentasRealizadas <= MAX_VENTAS) {
    historialVentas[totalVentasRealizadas - 1] = totalPagar;
  }
}

void mostrarReporte() {
    cout << "\n";
    cout << "REPORTE DE VENTAS" << endl;
    cout << "------------------------" << endl;
    cout << "Ventas realizadas: " << totalVentasRealizadas << endl;
    cout << "Almuerzos vendidos: " << totalAlmuerzosDia << endl;
    cout << "Pupusas vendidas: " << totalPupusasDia << endl;
    cout << "Panes vendidos: " << totalPanesDia << endl;
    cout << "Bebidas vendidas: " << totalBebidasDia << endl;
    cout << "Total recaudado: $" << totalRecaudadoDia << endl;

    if (totalVentasRealizadas > 0) {
        double ventaMasAlta = historialVentas[0];
        double ventaMasBaja = historialVentas[0];
        double sumaTotal = 0;

        cout << "\nDetalle de ventas:" << endl;

        for (int i = 0; i < totalVentasRealizadas; i++) {
          cout << "Venta " << i + 1 << ": $" << historialVentas[i] << endl;
          sumaTotal = sumaTotal + historialVentas[i];

          if (historialVentas[i] > ventaMasAlta) {
            ventaMasAlta = historialVentas[i];
          }

          if (historialVentas[i] < ventaMasBaja) {
            ventaMasBaja = historialVentas[i];
          }
        }
        cout << "\nVenta mas alta: $" << ventaMasAlta << endl;
        cout << "Venta mas baja: $" << ventaMasBaja << endl;
        cout << "Promedio: $" << sumaTotal / totalVentasRealizadas << endl;
    }

    int totalesPorProducto[4] = {
      totalAlmuerzosDia,
      totalPupusasDia,
      totalPanesDia,
      totalBebidasDia
    };
    int indiceMax = 0;

    for (int i = 1; i < 4; i++) {
      if (totalesPorProducto[i] > totalesPorProducto[indiceMax]) {
        indiceMax = i;
      }
    }
    if (totalesPorProducto[indiceMax] > 0) {
      cout << "\nProducto mas vendido: " << nombreProductos[indiceMax] << endl;
      cout << "Cantidad: " << totalesPorProducto[indiceMax] << endl;
    }
}