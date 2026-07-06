
PROTOTIPOS DE LAS FUNCIONES
 
void agregarProductos();
void mostrarDetallePedido();
void vaciarCarrito();

 DESARROLLO DE LAS FUNCIONES Gestión del pedido


void agregarProductos() {
    cout << "\n--- PRODUCTOS DISPONIBLES ---\n"
         << "1. Almuerzo Ejecutivo ------- $" << precioAlmuerzo << "\n"
         << "2. Pupusa (unidad) ---------- $" << precioPupusas << "\n"
         << "3. Pan con Pollo ------------ $" << precioPanes << "\n"
         << "4. Bebida / Refresco -------- $" << precioBebida << "\n"
         << "Seleccione el numero de producto que desea: ";
    cin >> productoSeleccionado;

    if (productoSeleccionado < 1 || productoSeleccionado > 4) {
        cout << "Opcion de producto no valida." << endl;
        return; 
    }

    cout << "Ingrese la cantidad que desea llevar: ";
    cin >> cantidad;

    if (cantidad <= 0) {
        cout << "Cantidad no valida. Intente de nuevo." << endl;
        return;
    }

   
    if (productoSeleccionado == 1) { cantAlmuerzo += cantidad; }
    else if (productoSeleccionado == 2) { cantPupusas += cantidad; }
    else if (productoSeleccionado == 3) { cantPanes += cantidad; }
    else if (productoSeleccionado == 4) { cantBebida += cantidad; }

    cout << "¡Producto(s) agregado(s) con exito!" << endl;
}

void mostrarDetallePedido() {
    cout << "\n--- DETALLE DE TU PEDIDO ---\n";

    // Impresiones directas sin bloques de llaves redundantes
    if (cantAlmuerzo > 0) cout << "Almuerzos: " << cantAlmuerzo << " (Subtotal: $" << (cantAlmuerzo * precioAlmuerzo) << ")\n";
    if (cantPupusas > 0)  cout << "Pupusas: " << cantPupusas << " (Subtotal: $" << (cantPupusas * precioPupusas) << ")\n";
    if (cantPanes > 0)    cout << "Panes con Pollo: " << cantPanes << " (Subtotal: $" << (cantPanes * precioPanes) << ")\n";
    if (cantBebida > 0)   cout << "Bebidas: " << cantBebida << " (Subtotal: $" << (cantBebida * precioBebida) << ")\n";
    
    
    subtotal = (cantAlmuerzo * precioAlmuerzo) + (cantPupusas * precioPupusas) + (cantPanes * precioPanes) + (cantBebida * precioBebida);
    
    if (subtotal == 0) {
        cout << "Tu carrito esta vacio. ¡Agrega productos en la opcion 1!" << endl;
    } else {
        cout << "Subtotal actual: $" << subtotal << endl;
    }
}

void vaciarCarrito() {
    // Reseteo agrupado en bloque horizontal
    cantAlmuerzo = 0; cantPupusas = 0; cantPanes = 0; cantBebida = 0;
    cout << "\n¡Pedido cancelado y carrito vaciado exitosamente!" << endl;
}