#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
using namespace std;

//nota: Las siguientes declaraciones extern fueron implementadas 
//con ayuda de IA (Google Gemini) para enlazar las variables del archivo principal
const int MAX_VENTAS = 100;
//variables externas definidas en codigo.cpp
extern double totalRecaudadoDia;
extern int totalAlmuerzosDia;
extern int totalPupusasDia;
extern int totalPanesDia;
extern int totalBebidasDia;
extern int totalVentasRealizadas;
extern int otraCompra; 
extern int opcionPrincipal;
extern int productoSeleccionado;
extern int cantidad;
extern int cantAlmuerzo;
extern int cantPupusas;
extern int cantPanes;
extern int cantBebida;
extern double precioAlmuerzo;
extern double precioPupusas;
extern double precioPanes;
extern double precioBebida;
extern double subtotal;
extern double descuento;
extern double totalPagar;
extern int esEstudiante; 
extern double historialVentas[MAX_VENTAS];
extern string nombreProductos[4];
extern double preciosProductos[4];
//prototipos de las funciones del sistema
void procesarFacturacion();
void guardarVenta();
void mostrarReporte();

#endif