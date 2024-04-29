/*
Administrador de notas estudiantiles (nombre provisional)
Alejandro Pedro Steinman Cuesta - T00077151
Andres Rubiano Marrugo - T00077084
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <ctype.h>
using namespace std;
//prototipos, clases, structs y demÃƒÂ¡s ...
struct Estudiante{
  int codigo;
  string nombre;
  string carrera;
  float nota1;
  float nota2;
  float nota3;
  float nota_final;
};
class comandos{
  public:
	int num_db(){
		string linea;
		int n=0;
    	ifstream leerArchivo;
    	leerArchivo.open("database.txt");
    	while(!leerArchivo.eof()){
    	getline(leerArchivo,linea);
    	if(linea.size()!=0){
    	n++;}}
    	leerArchivo.close();	
		return n;}
	bool comprobar(float nota){
		if( 0<=nota and nota<=5) return true;
		else return false;
	}
	bool comprobar(string cadena){
		int tam = cadena.size();
		for (int i =0; i<tam;i++){
			if(isalpha(cadena[i]) == false) return false; break;
		}
		return true;
	}
};
////
class data_base{
  public:
  	int tam;
	Estudiante *db;
  	data_base(int tam): db(new Estudiante [tam]){}
  	friend class MENU;
  	~data_base() { delete []db;}
  	
  	void importar(){
    	string linea;
    	int n=0; 
    	ifstream leerArchivo;
    	leerArchivo.open("D:\\Users\\Andres\\Downloads\\Administrador-de-notas-estudiantiles-main\\Administrador-de-notas-estudiantiles-main\\database.txt");
    	while(!leerArchivo.eof()){
    		getline(leerArchivo,linea);
    		if(linea.size()!=0){n++;}
		}
    	leerArchivo.close(); //cierre del flujo
    	leerArchivo.open("database.txt");
    	for (int i=0; i<n; i++){
    		getline(leerArchivo,linea,'|'); db[i].codigo=atoi(linea.c_str());
    		getline(leerArchivo,linea,'|'); db[i].nombre=linea;
    		getline(leerArchivo,linea,'|'); db[i].carrera=linea;
    		getline(leerArchivo,linea,'|'); db[i].nota1=atof(linea.c_str());
    		getline(leerArchivo,linea,'|'); db[i].nota2=atof(linea.c_str());
    		getline(leerArchivo,linea,'|'); db[i].nota3=atof(linea.c_str());
    		getline(leerArchivo,linea); db[i].nota_final=atof(linea.c_str());//falta un salto de linea 
		}leerArchivo.close();
  	}
  	void exportar(){
    	ofstream escribirArchivo;
    	escribirArchivo.open("D:\\Users\\Andres\\Downloads\\Administrador-de-notas-estudiantiles-main\\Administrador-de-notas-estudiantiles-main\\database.txt");
    	for (int i=0; i<tam; i++){
      		escribirArchivo<<db[i].codigo<<"|"<<db[i].nombre<<"|"<<db[i].carrera<<"|"<<db[i].nota1<<"|"<<db[i].nota2<<"|"<<db[i].nota3<<"|"<<db[i].nota_final<<endl;
    	}escribirArchivo.close();
	}
};
//////
class MENU {
  	public:
  		void show_database(data_base y){
      		for(int i=0; i<y.tam;i++){
      			cout<<y.db[i].codigo<<"\t"<<y.db[i].nombre<<"\t"<<y.db[i].carrera<<"\t"<<y.db[i].nota1<<"\t"<<y.db[i].nota2<<"\t"<<y.db[i].nota3<<"\t"<<y.db[i].nota_final<<endl;
	  		}	
  		}
  		void agregar_est(data_base y){
  			comandos cls;
  			int cant, i=1; int cod; string nombre; string carrera;
  			bool control; 
  			cout<<"Ingrese la cantidad de estudiantes que va a ingresar: ";cin>>cant;
  			do{
			  	cout<<"Ingrese codigo estudiantil: "; cin>>cod;
  				do {cout<<"Ingrese nombre del estudiante: ";getline(cin,nombre);cin.ignore(); control= cls.comprobar(nombre);}while(control==false);
  				do {cout<<"Ingrese carrera del estudiante: ";getline(cin,carrera);cin.ignore(); control = cls.comprobar(carrera);}while(control==false);
  				y.db[y.tam+i].codigo = cod;y.db[y.tam+i].nombre = nombre; y.db[y.tam+i].carrera = carrera;
  				i++;
			  }while();
		}
  			
};

//////
int main(){
	comandos cls; int tam = cls.num_db(); int opcion; bool cont;
	MENU menu; data_base DB(tam);
	//
	cout<<"-----Sistema de Administración Estudiantil-----"<<endl;
	cout<<"Importando informacion..."<<endl;DB.importar(); cout<<"Informacion correctamente importada."<<endl; system("pause");
	cout<<"Pulse cualquier tecla para continuar"<<endl;system("cls");
	do{
		cout<<"-----Sistema de Administración Estudiantil-----"<<endl;
			cout<<"1) Mostrar Estudiantes"<<endl;
			cout<<"2) Crear Estudiante"<<endl;
			cout<<"3) Buscar Estudiante"<<endl;
			cout<<"4) Borrar Estudiante"<<endl;
			cout<<"5) Modificar Estudiante"<<endl;
			cout<<"6) Introducir Notas"<<endl;
			cout<<"7) Salir"<<endl;
			cout<<"\t Ingrese opcion (1-7): ";cin>>opcion;
			switch(opcion){
				case 1:
					menu.show_database(DB);
					break;
				case 2:
					menu.agregar_est(DB);
					cont = false;
					break;
			/*	case 3:
					opcion3();
					break;
				case 4:
					cout<<"Saliendo del programa"<<endl;
					break;*/		
			}
	}while(cont ==false);
	return 0;
}
