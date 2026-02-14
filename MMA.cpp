#include <iostream>

using namespace std;

typedef char str50[50];

// Estructuras
struct sLuchador{
    int id_luchador;
    str50 nombre;
    str50 apodo;
    int peso;
    int victorias;
    int derrotas;
};
struct sNodoA{
    sLuchador luchador;
    sNodoA* siguiente;
};
typedef sLuchador top10[10];

//Funciones a Utilzar
void mostrarMenu();
void incripcionAtleta(sNodoA*& lstA, sLuchador nuevo, int &id_luchador);
void generarMainCard(sNodoA* lstA, int id_luchador);
void actualizarRecord(sNodoA* lstA);
void guardarGym(FILE* arcLuchadores, sNodoA* lstA);
void cargarGym(FILE* arcLuchadores, sNodoA*& lstA, int &id_luchador);
void vaciarLista(sNodoA*& lstA);
void insertarPorPeso(sNodoA*& lstA, sLuchador luchador);
sNodoA* buscarPorID(sNodoA* lstA, int id);
int calcularPuntaje(sLuchador luchador);
int cantidadLuchadores(FILE* arcLuchadores);
int cargarPrimeros10(top10 rankLuchador, sNodoA* listaA);
void ordenarTop10(top10 rankLuchador, int cantidad);
void evaluarLuchador(top10 rankLuchador, int cantidad, sLuchador luchador);

int main() {
    // Definion de variables a utilizarf
	short opc;
	int id_luchador = 0;
    top10 rankL = {0};
    sLuchador atleta;
    sNodoA *lst_atletas = 0;
    FILE* arcLuchadores;
    do{
    	mostrarMenu();
		cin>> opc;
    	switch(opc){
    		case 1:
    			incripcionAtleta(lst_atletas, atleta, id_luchador);
    			break;
			case 2:
				generarMainCard(lst_atletas,id_luchador);
				break;
			case 3:
				actualizarRecord(lst_atletas);
				break;
			case 4:
				guardarGym(arcLuchadores, lst_atletas);
				break;
			case 5:
				cargarGym(arcLuchadores, lst_atletas, id_luchador);
				break;
			case 0:
				vaciarLista(lst_atletas);
				break;
			default: 
				cout<< "Opcion invalida"<<endl;
				break;
		}
    	
	}while(opc!=0);
    
    return 0;
}

void mostrarMenu(){
    cout<< "               OCTAGON PRO - LIGA DE MMA"<<endl;
    cout<< "  1. Inscripcion Atleta"<<endl;
	cout<< "  2. Generar Main Card"<<endl;
    cout<< "  3. Actualizar record"<<endl;
    cout<< "  4. Guardar Gimnasio"<<endl;
    cout<< "  5. Cargar Gimnasio"<<endl;
    cout<< "  0. Salir"<<endl;
    cout<< ""<<endl;
    cout<< "opcion: "<<endl;
}

// Funciones Principales ---------------------------------------
void incripcionAtleta(sNodoA*& lstA, sLuchador nuevo, int &id_luchador){
	cout<< "                     INSCRIPCION ATLETA " << endl;
	id_luchador++;
	nuevo.id_luchador = id_luchador;
	cout<< "Ingrese nombre: ";
	cin>> nuevo.nombre;
	cout<< "Ingrese apodo: ";
	cin>> nuevo.apodo;
	cout<< "Ingrese peso: ";
	cin>> nuevo.peso;
	cout<< "Ingrese victorias: ";
	cin>> nuevo.victorias;
	cout<< "Ingrese derrotas: ";
	cin>> nuevo.derrotas;
	insertarPorPeso(lstA, nuevo);
}
void generarMainCard(sNodoA* lstA, int id_luchador){
	if(id_luchador < 10){
		cout<< "No hay suficientes luchadores" << endl;
		return;
	}
	sNodoA* aux = lstA;
	short cantP = 5;
	cout<< "                     MAIN CARD " << endl;
	cout<< "" << endl;
	for (int i = 0; i < cantP; i++){
		cout<< aux->luchador.nombre << "  vs " << aux->siguiente->luchador.nombre << endl;
		aux = aux->siguiente->siguiente;
	}
}
void actualizarRecord(sNodoA* lstA){
	int id;
	sNodoA* aux;
	cout<< "                     ACTUALIZAR RECORD " << endl;
	cout<< "Ingrese id del luchador: ";
	cin>> id;
	aux = buscarPorID(lstA, id);
	if(aux == NULL){
		cout<< "No se encontro el luchador"<<endl;
		return;
	}
	cout<< "Ingrese nuevas victorias: ";
	cin>> aux->luchador.victorias;
	cout<< "Ingrese nuevas derrotas: ";
	cin>> aux->luchador.derrotas;
}
void guardarGym(FILE* arcLuchadores, sNodoA* lstA){
	arcLuchadores = fopen("luchadores.dat", "wb");
	if(arcLuchadores == NULL){
		cout<< "Error al abrir el archivo"<<endl;
		return;
	}
	sNodoA* aux = lstA;
	while(aux != NULL){
		fwrite(&aux->luchador, sizeof(sLuchador), 1, arcLuchadores);
		aux = aux->siguiente;
	}
	fclose(arcLuchadores);	
}
void cargarGym(FILE* arcLuchadores, sNodoA*& lstA, int &id_luchador){
	arcLuchadores = fopen("luchadores.dat", "rb");
	if(arcLuchadores == NULL){
		cout<< "Error al abrir el archivo"<<endl;
		arcLuchadores = fopen("luchadores.dat", "wb");
		fclose(arcLuchadores);
		return;
	}
	id_luchador = cantidadLuchadores(arcLuchadores);
	sLuchador aux;
	while(!feof(arcLuchadores)){
		fread(&aux, sizeof(sLuchador), 1, arcLuchadores);
		insertarPorPeso(lstA, aux);
	}
	fclose(arcLuchadores);
}
// -------------------------------------------------------------


// Funciones necesarias ----------------------------------------
int cantidadLuchadores(FILE* arcLuchadores){
    int cant = 0;
	fseek(arcLuchadores, 0, SEEK_END);
	cant = ftell(arcLuchadores)/sizeof(sLuchador);
	fseek(arcLuchadores, 0, SEEK_SET);
    return cant;
}
void rankTop10(top10 rankLuchador, sNodoA* listaA){

    if(listaA == NULL) return;

    //cargamos los primeros 10
    int cantidad = cargarPrimeros10(rankLuchador, listaA);

    //ordenamos el vector
    ordenarTop10(rankLuchador, cantidad);

    //seguir recorriendo la lista
    sNodoA* aux = listaA; //uso una estructura auxiliar para almacenar la lista y no trabajar sobre la original
    int contador = 0;

    // saltamos los primeros 10 ya cargados
    while(aux != NULL && contador < cantidad){
        aux = aux->siguiente;
        contador++;
    }

    //compararo el resto de elementos de la lista
    while(aux != NULL){
        evaluarLuchador(rankLuchador, cantidad, aux->luchador);
        aux = aux->siguiente;
    }
}

void vaciarLista(sNodoA*& lstA){
    sNodoA* aux;
    while(lstA != NULL){
        aux = lstA;
        lstA = lstA->siguiente;
        delete aux;
    }
}
//--------------------------------------------------------------

// Funciones secundarias ---------------------------------------
void insertarPorPeso(sNodoA*& lstA, sLuchador luchador){
	sNodoA* nuevo = new sNodoA;
	nuevo->luchador = luchador;
	nuevo->siguiente = NULL;
	
	// Si la lista está vacía o el peso es menor al primero
    if(lstA == NULL || luchador.peso < lstA->luchador.peso){
        nuevo->siguiente = lstA;
        lstA = nuevo;
        return;
    }
	sNodoA* aux = lstA;
	while(aux->siguiente != NULL && aux->siguiente->luchador.peso < luchador.peso){
		aux = aux->siguiente;
	}
	nuevo->siguiente = aux->siguiente;
	aux->siguiente = nuevo;
}

//buesque secuencial del ID del Luchador
sNodoA* buscarPorID(sNodoA* lstA, int id){
	sNodoA* aux = lstA;
	while(aux != NULL && aux->luchador.id_luchador != id){
		aux = aux->siguiente;
	}
	return aux;
}
//--------------------------------------------------------------

int calcularPuntaje(sLuchador luchador){
    return luchador.victorias - luchador.derrotas;
}

int cargarPrimeros10(top10 rankLuchador, sNodoA* listaA){
	sNodoA* aux = listaA;
    int i = 0;
    while(aux != NULL && i < 10){
        rankLuchador[i] = aux->luchador;
        aux = aux->siguiente;
        i++;
    }
    return i; // devuelve cantidad cargada, por las dudas de si hay menos de 10
}

void ordenarTop10(top10 rankL, int cantidad){
    for(int i = 0; i < cantidad - 1; i++){
        for(int j = 0; j < cantidad - i - 1; j++){
            if(calcularPuntaje(rankL[j]) < calcularPuntaje(rankL[j+1])){
                sLuchador aux = rankL[j];
                rankL[j] = rankL[j+1];
                rankL[j+1] = aux;
            }
        }
    }
}

void evaluarLuchador(top10 rankLuchador, int cantidad, sLuchador candidato){
    int puntajeCandidato = calcularPuntaje(candidato);//calculo el de un candito de la lista
    int puntajeUltimo = calcularPuntaje(rankLuchador[cantidad - 1]); //comparo con el ultimo del array que ya esta ordenado

    if(puntajeCandidato > puntajeUltimo){
        rankLuchador[cantidad - 1] = candidato;
        ordenarTop10(rankLuchador, cantidad); //vuelvo a ordenar por si el que puse en ultimo lugar es mayor a alguno del array
    }
}

