#include <iostream>
#include <string>

using namespace std;

int* ids = NULL;
double* pesos = NULL;
string* destinos = NULL;
int* prioridades = NULL;
char* estados = NULL;

int capacidad = 50;
int totalPaquetes = 0;
int frente = 0;

void mostrarMenu();
void agregarPaquete();
void despacharPaquete();
void inspeccionarFrente();
void reportePorDestino();
void liberarMemoria();
void duplicarCapacidad();

int main() {
    cout << "--- Sistema de Despacho Logistico MegaEnvio (Modo Punteros) ---" << endl << endl;
    cout << "Inicializando sistema con capacidad para " << capacidad << " paquetes..." << endl;

    ids = new int[capacidad];
    pesos = new double[capacidad];
    destinos = new string[capacidad];
    prioridades = new int[capacidad];
    estados = new char[capacidad];

    int opcion;

    do {
        cout << "Capacidad actual: " << capacidad << ". Paquetes en cola: " << (totalPaquetes - frente) << "." << endl;
        mostrarMenu();
        cout << "\nOpcion seleccionada: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                agregarPaquete();
                break;
            case 2:
                despacharPaquete();
                break;
            case 3:
                inspeccionarFrente();
                break;
            case 4:
                reportePorDestino();
                break;
            case 5:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
        cout << "------------------------------------------" << endl;
    } while (opcion != 5);

    liberarMemoria();
    return 0;
}

void mostrarMenu() {
    cout << "\nSeleccione una operacion:" << endl;
    cout << "1. Agregar Paquete (Encolar)" << endl;
    cout << "2. Despachar Paquete (Desencolar)" << endl;
    cout << "3. Inspeccionar Frente de Cola" << endl;
    cout << "4. Reporte por Destino" << endl;
    cout << "5. Salir (Liberar Memoria)" << endl;
}

void agregarPaquete() {
    if (totalPaquetes == capacidad) {
        cout << "¡Capacidad maxima alcanzada! Duplicando el almacenamiento..." << endl;
        duplicarCapacidad();
    }

    cout << "Ingrese ID: ";
    cin >> ids[totalPaquetes];

    cout << "Ingrese Peso (kg): ";
    cin >> pesos[totalPaquetes];

    cout << "Ingrese Destino: ";
    cin.ignore();
    getline(cin, destinos[totalPaquetes]);

    cout << "Ingrese Prioridad (1=Alta, 2=Media, 3=Baja): ";
    cin >> prioridades[totalPaquetes];

    estados[totalPaquetes] = 'E';

    cout << "Paquete " << ids[totalPaquetes] << " encolado. Capacidad utilizada: " << (totalPaquetes + 1) << "/" << capacidad << "." << endl;

    totalPaquetes++;
}

void duplicarCapacidad() {
    int nuevaCapacidad = capacidad * 2;

    int* nuevos_ids = new int[nuevaCapacidad];
    double* nuevos_pesos = new double[nuevaCapacidad];
    string* nuevos_destinos = new string[nuevaCapacidad];
    int* nuevas_prioridades = new int[nuevaCapacidad];
    char* nuevos_estados = new char[nuevaCapacidad];

    for (int i = 0; i < capacidad; ++i) {
        nuevos_ids[i] = ids[i];
        nuevos_pesos[i] = pesos[i];
        nuevos_destinos[i] = destinos[i];
        nuevas_prioridades[i] = prioridades[i];
        nuevos_estados[i] = estados[i];
    }

    delete[] ids;
    delete[] pesos;
    delete[] destinos;
    delete[] prioridades;
    delete[] estados;

    ids = nuevos_ids;
    pesos = nuevos_pesos;
    destinos = nuevos_destinos;
    prioridades = nuevas_prioridades;
    estados = nuevos_estados;

    capacidad = nuevaCapacidad;

    cout << "¡Memoria expandida! Nueva capacidad: " << capacidad << " paquetes." << endl;
}

void despacharPaquete() {
    if (frente >= totalPaquetes) {
        cout << "La cola de despacho esta vacia. No hay paquetes para despachar." << endl;
        return;
    }

    cout << "Despachando paquete..." << endl;
    estados[frente] = 'D';
    cout << "Paquete " << ids[frente] << " despachado con exito. Estado: '" << estados[frente] << "'." << endl;
    frente++;
}

void inspeccionarFrente() {
    if (frente >= totalPaquetes) {
        cout << "La cola de despacho esta vacia." << endl;
        return;
    }

    cout << "Frente de la cola:" << endl;
    cout << "  ID: " << ids[frente] << " | Peso: " << pesos[frente] << " kg | Destino: " << destinos[frente];
    
    cout << " | Prioridad: ";
    switch (prioridades[frente]) {
        case 1: cout << "Alta"; break;
        case 2: cout << "Media"; break;
        case 3: cout << "Baja"; break;
        default: cout << "Desconocida"; break;
    }
    cout << endl;
}

void reportePorDestino() {
    string destinoBuscado;
    cout << "Ingrese el destino para el reporte: ";
    getline(cin, destinoBuscado);

    int contador = 0;
    double sumaPesos = 0.0;

    for (int i = 0; i < totalPaquetes; ++i) {
        if (destinos[i] == destinoBuscado && estados[i] == 'E') {
            contador++;
            sumaPesos += pesos[i];
        }
    }

    cout << "Reporte para destino '" << destinoBuscado << "':" << endl;
    cout << "  Paquetes En Cola: " << contador << endl;
    
    if (contador > 0) {
        double pesoPromedio = sumaPesos / contador;
        cout << "  Peso Promedio: " << pesoPromedio << " kg" << endl;
    } else {
        cout << "  No hay paquetes en cola para este destino." << endl;
    }
}

void liberarMemoria() {
    cout << "Liberando " << capacidad << " bloques de memoria asignada..." << endl;

    delete[] ids;
    delete[] pesos;
    delete[] destinos;
    delete[] prioridades;
    delete[] estados;

    ids = NULL;
    pesos = NULL;
    destinos = NULL;
    prioridades = NULL;
    estados = NULL;

    cout << "Sistema cerrado. ¡Memoria libre!" << endl;
}
