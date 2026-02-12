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
}
struct sNodoLiga{
    sLuchador luchador;
    sNodoLiga* siguiente;
}
typedef sLuchador top10[10];

//Funciones a Utilzar





int main() {
    // Definion de variables a utilizarf
	short opc;
    top10 rankL = {0};
    sLuchador atleta;
    sNodoA *lst_atletas = nullptr;
    file* arcLuchadores;
    cargarLista(arcLuchadores, lst_atletas);
    
    do{
    	mostrarMenu();
		cin>> opc;
    	switch(opc){
    		case 1:
    			incripcionAtleta(lst_atletas, atleta);
    			break;
			case 2:
				generarMainCard();
				break;
			case 3:
				actualizarRecord(lst_atletas);
				break;
			case 4:
				guardarGym();
				break;
			case 5:
				cargarGym();
				break;
			default: break;
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
void incripcionAtleta(sNodoA* lstA, sLuchador nuevo){
	cout<< "                     INSCRIPCION ATLETA " << endl;
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
void generarMainCard(){
	
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
void guardarGym(){

}
void cargarGym(){

}
// -------------------------------------------------------------
// Funciones necesarias ----------------------------------------

// vaciar lista
// calcular puntaje
// top 10
void rankTop10(top10 rankL, sNodoA* lstA){
	// llenar el top 10 con los primeros 10 luchadores de la lista

	// seguir recorriendo la lista y si encuentra un luchador
	// con mas puntaje que el ultimo del top 10, lo reemplaza
	
}
// ...

//--------------------------------------------------------------

// Funciones secundarias ---------------------------------------
void cargarLista(file* arcLuchadores, sNodoA* lstA){
	arcLuchadores = fopen("luchadores.dat", "rb");
	if(arcLuchadores == NULL){
		cout<< "Error al abrir el archivo"<<endl;
		return;
	}
	sLuchador aux;
	while(!feof(arcLuchadores)){
		fread(&aux, sizeof(sLuchador), 1, arcLuchadores);
		insertarPorPeso(lstA, aux);
	}
	fclose(arcLuchadores);
}

void insetarPorPeso(sNodoA* lstA, sLuchador luchador){
	sNodoA* nuevo = new sNodoA;
	sNodoA* aux = lstA;
	nuevo->luchador = luchador;
	if(lstA == NULL){
		lstA = nuevo;
		return;
	}
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





