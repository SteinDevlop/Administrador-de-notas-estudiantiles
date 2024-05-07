/*Solucion NO definitiva. Solo soluciona el correcto importe de los datos, los errores relacionados con agregar o quietes en la busqueda, o se han solucionado*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <ctype.h>
using namespace std;
//prototipos, clases, structs y demas ...
struct Estudiante{
  string codigo;
  string nombre;
  string carrera;
  float nota1;
  float nota2;
  float nota3;
  float nota_final;
};
////
////
class data_base{
  public:
  	int tam;
	Estudiante *db;
  	data_base(int tam): db(new Estudiante [tam]){}
  	friend class MENU;
  	~data_base() { delete []db;}
  	
  	void importar(){
    ifstream leerArchivo("database.txt");
    string linea;
    int n = 0;
    while (getline(leerArchivo, linea)) {
        if (linea.size() != 0) {
            n++;
        }
    }
    leerArchivo.clear(); // Limpiar el indicador de fin de archivo para poder leer nuevamente
    leerArchivo.seekg(0, ios::beg); // Volver al inicio del archivo
    tam = n;
    for (int i = 0; i < n; i++) {
        getline(leerArchivo, linea, '|');
        db[i].codigo = linea;
        getline(leerArchivo, linea, '|');
        db[i].nombre = linea;
        getline(leerArchivo, linea, '|');
        db[i].carrera = linea;
        getline(leerArchivo, linea, '|');
        db[i].nota1 = atof(linea.c_str());
        getline(leerArchivo, linea, '|');
        db[i].nota2 = atof(linea.c_str());
        getline(leerArchivo, linea, '|');
        db[i].nota3 = atof(linea.c_str());
        getline(leerArchivo, linea);
        db[i].nota_final = atof(linea.c_str());
    }
    leerArchivo.close();
    for (int i=0; i<tam; i++){
      		cout<<"|"<<db[i].codigo<<"|"<<db[i].nombre<<"|"<<db[i].carrera<<"|"<<db[i].nota1<<"|"<<db[i].nota2<<"|"<<db[i].nota3<<"|"<<db[i].nota_final<<"|"<<endl;
}}
  	void exportar(){
    	ofstream escribirArchivo;
    	escribirArchivo.open("database.txt");
    	for (int i=0; i<tam; i++){
      		escribirArchivo<<db[i].codigo<<"|"<<db[i].nombre<<"|"<<db[i].carrera<<"|"<<db[i].nota1<<"|"<<db[i].nota2<<"|"<<db[i].nota3<<"|"<<db[i].nota_final<<"|"<<endl;
    	}escribirArchivo.close();
	}
};
//////
//////
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
		if(0<nota and nota<=5) return true;
		else return false;
	}
	bool comprobar(string cadena){
		int tam = cadena.size();
		for (int i =0; i<tam;i++){
			if(isalpha(cadena[i]) == false) {return false; break;}
		}
		return true;
	}
	void guardado(data_base db){
		string ans;
		cout<<"Desea guardar los cambios? (S/N): ";cin>>ans;
		if(ans=="Si" or ans=="si" or ans=="S" or ans=="s" or ans=="SI"){
			db.exportar();
			cout<<"Datos guardados correctamente."<<endl;
		}
		else {cout<<"Los datos no han sido guardados."<<endl;}	
	}
	void control(bool &cont){
		string ans;
		cout<<endl;
		cout<<"Desea continuar? (S/N): ";cin>>ans;
		if(ans=="Si" or ans=="si" or ans=="S" or ans=="s") {
			cont = true;
		}
		else {cont = false;}	
	}
	void nota_final(data_base &y, int i){
		y.db[i].nota_final = (y.db[i].nota1*0.3) + (y.db[i].nota2 * 0.35) + (y.db[i].nota3 *0.35); 
	}
	bool verificar(data_base y, string cod){
		for (int i=0;i<y.tam;i++){
			if (cod ==y.db[i].codigo) {return true; break;}
		}
		return false;
	}
};
//////
//////
class MENU {
  	public:
  		void show_database(data_base y){
      		for(int i=0; i<y.tam;i++){cout<<y.db[i].codigo<<"\t"<<y.db[i].nombre<<"\t"<<y.db[i].carrera<<"\t"<<y.db[i].nota1<<"\t"<<y.db[i].nota2<<"\t"<<y.db[i].nota3<<"\t"<<y.db[i].nota_final<<endl;}	
  		}	
  		void agregar_est(data_base y){
  			comandos cls;
  			int cant= y.tam; int c=0, cont; string nombre, cod; string carrera;
  			bool control, pase;
  			while(true){
			  	do{
			  		cout<<"Ingrese codigo estudiantil (Los ultimos 5 digitos) (0 para salir)): "; cin>>cod; pase = cls.verificar(y,cod);
			  		if(cod=="0" or pase == true) {cout<<"Estudiante existente."<<endl; control= cls.comprobar(nombre);}}while(control==true);
  				do {cout<<"Ingrese nombre del estudiante: ";getline(cin,nombre);cin.ignore(); control= cls.comprobar(nombre);}while(!control);
  				do {cout<<"Ingrese carrera del estudiante: ";getline(cin,carrera);cin.ignore(); control = cls.comprobar(carrera);}while(!control);
				y.db[cant].codigo=cod;
				y.db[cant].nombre=nombre;
				y.db[cant].carrera=carrera;
				y.db[cant].nota1= 0;
				y.db[cant].nota2=0;
				y.db[cant].nota3=0;
				y.db[cant].nota_final=0;
				y.tam++;
				cout << "Estudiante agregado correctamente." << endl;
			}
		}	
	void buscar_est(data_base y){
			int pos; string cod; bool cont;
			cout<<"_________________________________________________________________________________________________________________"<<endl;
			for(int i=0; i<y.tam;i++){cout<<y.db[i].codigo<<"\t"<<y.db[i].nombre<<"\t"<<y.db[i].carrera<<"\t"<<y.db[i].nota1<<"\t"<<y.db[i].nota2<<"\t"<<y.db[i].nota3<<"\t"<<y.db[i].nota_final<<endl;}
			cout<<endl;
			cout<<"Ingrese codigo a buscar: ";cin>>cod; for(int i=0; i<y.tam;i++){if(y.db[i].codigo==cod) {pos = i; cont = true; break;}}
			if(cont == true){
				cout<<endl;
				cout<<"Información del Estudiante: "<<endl;
				cout<<"\t Codigo: "<<y.db[pos].codigo<<endl;
				cout<<"\t Nombre: "<<y.db[pos].nombre<<endl;
				cout<<"\t Carrera: "<<y.db[pos].carrera<<endl;
				cout<<"\t Corte 1: "<<y.db[pos].nota1<<endl;
				cout<<"\t Corte 2: "<<y.db[pos].nota2<<endl;
				cout<<"\t Corte 3: "<<y.db[pos].nota3<<endl;
				cout<<"\t Nota Final: "<<y.db[pos].nota_final<<endl;
			}
			else {cout<<"No se ha encontrado informacion del estudiante"<<endl;
			}
	}
	void modificar_est(data_base &y){//revisar
		comandos cmd;
		int pos, op; bool cont, pase; string nombre, carrera, cod; float nota;
		cout<<"__________________________________________________________________________________________________________________"<<endl;
		for(int i=0; i<y.tam;i++){cout<<y.db[i].codigo<<"\t"<<y.db[i].nombre<<"\t"<<y.db[i].carrera<<endl;}	
		cout<<endl;
		cout<<"Ingrese codigo a buscar: ";cin>>cod;
		for(int i=0; i<y.tam;i++){if(y.db[i].codigo==cod) {pos = i; cont = true; break;}}
		if(cont == true){
			cout<<endl;
			cout<<"Información del Estudiante: "<<endl;
			cout<<"\t Codigo: "<<y.db[pos].codigo<<endl;
			cout<<"\t Nombre: "<<y.db[pos].nombre<<endl;
			cout<<"\t Carrera: "<<y.db[pos].carrera<<endl;
			cout<<"\t Corte 1: "<<y.db[pos].nota1<<endl;
			cout<<"\t Corte 2: "<<y.db[pos].nota2<<endl;
			cout<<"\t Corte 3: "<<y.db[pos].nota3<<endl;
			cout<<"\t Nota Final: "<<y.db[pos].nota_final<<endl;
			cout<<"\n Que información desea modificar?: "<<endl;
			cout<<"\t 1) Nombre: "<<endl;
			cout<<"\t 2) Carrera: "<<endl;
			cout<<"\t 3) Nota Corte 1: "<<endl;
			cout<<"\t 4) Nota Corte 2: "<<endl;
			cout<<"\t 5) Nota Corte 3: "<<endl;
			cout<<"Opcion: ";cin>>op;
				do{
					switch(op){
						case 1:
							do{
								cout<<"Ingrese nuevo nombre, correctamente: "; getline(cin, nombre); cin.ignore();
								pase = cmd.comprobar(nombre);
							} while(pase ==false);
							y.db[pos].nombre = nombre;
							break;
						case 2:
							do{
								cout<<"Ingrese nueva carrera, correctamente: "; getline(cin, carrera); cin.ignore();
								pase = cmd.comprobar(carrera);
							} while(pase ==false);
							y.db[pos].carrera = carrera;
							break;	
						case 3:
							do{
								cout<<"Ingrese nueva nota del corte 1, correctamente: "; cin>>nota; 
								pase = cmd.comprobar(nota);
							} while(pase ==false);
							y.db[pos].nota1 = nota;
							break;
						case 4:
							do{
								cout<<"Ingrese nueva nota del corte 2, correctamente: "; cin>>nota; 
								pase = cmd.comprobar(nota);
							} while(pase ==false);
							y.db[pos].nota2 = nota;
							break;
						case 5:
							do{
								cout<<"Ingrese nueva nota del corte 3, correctamente: "; cin>>nota; 
								pase = cmd.comprobar(nota);
							} while(pase ==false);
							y.db[pos].nota3 = nota;
							break;
					}			
				}while(cont == false);
			}
			else {cout<<"No se ha encontrado informacion del estudiante"<<endl;
			}
	}
  	void borrar_est(data_base y){
		int pos, op, ind =0; bool cont, pase; string nombre, carrera, cod; float nota;
		int a;
		for(int i=0; i<y.tam;i++){cout<<y.db[i].codigo<<"\t"<<y.db[i].nombre<<"\t"<<y.db[i].carrera<<endl;}
		cout<<endl;
		cout<<"Ingrese codigo del estudiante a eliminar: ";cin>>cod;
		for(int i=0; i<y.tam;i++){if(y.db[i].codigo==cod) {y.db[ind++]=y.db[i];}}
		y.tam = ind;
		cout<<"Estudiante eliminado correctamente."<<endl;
	}
	void introducir_notas(data_base y){
		comandos cmd;
		int pos, op; bool cont, pase; float nota; string nombre, cod;
		int a;
		cout<<"Información del Curso"<<endl;
		for(int i=0; i<y.tam;i++){cout<<y.db[i].codigo<<"\t"<<y.db[i].nombre<<"\t"<<y.db[i].nota1<<"\t"<<y.db[i].nota2<<"\t"<<y.db[i].nota3<<"\t"<<y.db[i].nota_final<<endl;}
      	cout<<"Ingrese el codigo del estudiante: ";cin>>cod;
      	for(int i=0; i<y.tam;i++){if(y.db[i].codigo == cod) {pos = i; cont = true; break;}}
      	cout<<"El estudiante se encuentra en el sistema."<<endl;
      	cout<<"----------------------------"<<endl;
      	cout<<"|Informacion de las notas: |"<<endl;
      	cout<<"|Corte 1 -------------> 30%|"<<endl;
      	cout<<"|Corte 2 -------------> 35%|"<<endl;
      	cout<<"|Corte 3 -------------> 35%|"<<endl;
      	cout<<"----------------------------"<<endl;
      	do{
      		float nota;
      		cout<<"(Ingrese numero del corte) Nota a modificar. Corte: "; cin>>op;
      		switch (op){
      			case 1:
      				cout<<"Ingrese nota a cambiar: "; cin>>nota; 
					  pase=cmd.comprobar(nota); 
					  if (pase == true){cont = true;y.db[pos].nota1=nota;}
					  break;
				case 2:
					if (y.db[pos].nota1 !=0){
						cout<<"Ingrese nota a cambiar: "; cin>>nota; 
						pase=cmd.comprobar(nota); 
						if (pase == true){cont = true;y.db[pos].nota2=nota;}	
					}
					else {cont = false;}
					break;
				case 3:
					if ((y.db[pos].nota1 !=0) and (y.db[pos].nota2 !=0)){
						cout<<"Ingrese nota a cambiar: "; cin>>nota; 
						pase=cmd.comprobar(nota); 
						if (pase == true){cont = true;y.db[pos].nota3=nota;}	
					}
					else {cont = false;}
					break;
			  }		
		}while(cont==false);
		cout<<"La nota cambiada exitosamente"<<endl;
		cmd.nota_final(y,pos);
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
		system("cls");
		cout<<"-----Sistema de Administración Estudiantil-----"<<endl;
			cout<<"1) Mostrar Estudiantes"<<endl;
			cout<<"2) Crear Estudiante"<<endl;
			cout<<"3) Buscar Estudiante"<<endl;
			cout<<"4) Borrar Estudiante"<<endl;
			cout<<"5) Modificar Estudiante"<<endl;
			cout<<"6) Introducir Notas"<<endl;
			cout<<"7) Guardar Cambios"<<endl;
			cout<<"8) Salir"<<endl;
			cout<<"\t Ingrese opcion (1-8): ";cin>>opcion;
			switch(opcion){
				case 1:
					menu.show_database(DB);
					cls.control(cont);
					break;
				case 2:
					menu.agregar_est(DB);
					cls.control(cont);
					break;
				case 3:
					menu.buscar_est(DB);
					cls.control(cont);
					break;
				case 4:
					menu.borrar_est(DB);
					cls.control(cont);
					break;
				case 5:
					menu.modificar_est(DB);
					cls.control(cont);
					break;
				case 6:
					menu.introducir_notas(DB);
					cls.control(cont);
					break;
				case 7:
					DB.exportar();
					cls.control(cont);
					break;
				case 8:
					cont = false;
					break;
				default:
					cont = true;
					break;
			}
	}while(cont ==true);
	return 0;
}
