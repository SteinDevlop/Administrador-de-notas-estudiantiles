/*Administrador de notas estudiantiles (nombre provisional)
Alejandro Pedro Steinman Cuesta - T00077151
Andres Rubiano Marrugo - T00077084 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <ctype.h>
#include <windows.h> 
using namespace std;
//prototipos, clases, structs y demas ...
struct estudiante{
  string codigo;
  string nombre;
  string carrera;
  float nota1;
  float nota2;
  float nota3;
  float nota_final;
  
  float calcular_notafinal(){return (nota1*0.3)+(nota2*0.35)+(nota3*0.35);} //metodo
};
//////
//////
class comandos{
  public:
  	void importar(estudiante db[], int &tam){
    	string linea;
    	int n=0; 
    	ifstream leerArchivo;
    	leerArchivo.open("database.txt");
    	while(getline(leerArchivo,linea)){
    		if(linea.size()!=0){n++;}
		}
    	leerArchivo.close(); //cierre del flujo		
    	leerArchivo.open("database.txt");
    	tam = n;
    	for (int i=0; i<n; i++){
    		getline(leerArchivo,linea,'|'); db[i].codigo=linea;
    		getline(leerArchivo,linea,'|'); db[i].nombre=linea;
    		getline(leerArchivo,linea,'|'); db[i].carrera=linea;
    		getline(leerArchivo,linea,'|'); db[i].nota1=atof(linea.c_str());
    		getline(leerArchivo,linea,'|'); db[i].nota2=atof(linea.c_str());
    		getline(leerArchivo,linea,'|'); db[i].nota3=atof(linea.c_str());
    		getline(leerArchivo,linea,'|'); db[i].nota_final = db[i].calcular_notafinal();
    		getline(leerArchivo,linea);
		}leerArchivo.close();
  	}
  	void exportar(estudiante db[], int tam, bool pase){
    	ofstream escribirArchivo;
    	escribirArchivo.open("database.txt",ios::trunc);
    	for (int i=0; i<tam; i++){escribirArchivo<<db[i].codigo<<"|"<<db[i].nombre<<"|"<<db[i].carrera<<"|"<<db[i].nota1<<"|"<<db[i].nota2<<"|"<<db[i].nota3<<"|"<<db[i].nota_final<<"|"<<endl;}
    	pase = true;
		escribirArchivo.close();
	}
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
		for (int i=0; i<tam;i++){
			if(!(isalpha(cadena[i])) and !(isblank(cadena[i]))) {return false; break;}
		}
		return true;
	}
	void guardado(estudiante db[], int tam){
		bool pase = false;
		exportar(db, tam, pase);
		if (pase == true) cout<<"Los datos no han sido guardados."<<endl;
		else if(pase == false) {cout<<"Datos guardados correctamente."<<endl;} 	
	}
	void ordenar(estudiante db[], int tam){
		for(int i=0; i<tam-1; i++){
				estudiante aux;
			for(int j =i+1;j<tam;j++){
				if(db[i].codigo>db[j].codigo){
					aux = db[j];
					db[j]=db[i];
					db[i] = aux;
				}
			}
		}	
	}
	bool control(){
		string ans;
		cout<<endl;
		cout<<"\n Desea continuar? (S/N): ";cin>>ans;cin.ignore();
		if(ans=="Si" or ans=="si" or ans=="S" or ans=="s") {return true;}
		else {return false;}	
	}
	bool verificar_cod(estudiante db[], int tam ,string cod){
		for (int i=0;i<tam;i++){if (cod == db[i].codigo) {return true; break;}}
		return false;
	}
};
////////
////////
class MENU {
	public:
		void mostrar_menu(estudiante db[], int tam){
			comandos cmd; int opcion; bool c;
			do{
			system("cls");
			cmd.ordenar(db,tam);
			cout<<"___________________________________________________"<<endl;
  			cout<<"|      Sistema de Administracion Estudiantil      |"<<endl;
  			cout<<"|_________________________________________________|"<<endl;
			cout<<"\t 1) Informacion Completa del Curso"<<endl;
			cout<<"\t 2) Crear Estudiante"<<endl;
			cout<<"\t 3) Informacion del Estudiante"<<endl;
			cout<<"\t 4) Borrar Estudiante"<<endl;
			cout<<"\t 5) Modificar Informacion del Estudiante"<<endl;
			cout<<"\t 6) Introducir Notas de Estudiante"<<endl;
			cout<<"\t 7) Guardar Cambios"<<endl;
			cout<<"\t 8) Salir"<<endl;
			cout<<"Ingrese opcion (1-8): ";cin>>opcion;cin.ignore();
			switch(opcion){
				case 1:
					show_database(db,tam);
					c = cmd.control();
					break;
				case 2:
					agregar_est(db, tam);
					c = cmd.control();
					break;
				case 3:
					buscar_est(db, tam);
					c = cmd.control();
					break;
				case 4:
					borrar_est(db, tam);
					c = cmd.control();
					break;
				case 5:
					modificar_est(db, tam);
					c = cmd.control();
					break;
				case 6:
					introducir_notas(db, tam);
					c = cmd.control();
					break;
				case 7:
					cmd.guardado(db, tam);
					c = cmd.control();
					break;
				default:
					c = false;
					break;
				}
			}while(c ==true);		
		}
  	private:
  		void show_database(estudiante db[], int tam){
  			system("cls");
  			cout<<"___________________________________________________"<<endl;
  			cout<<"|            Informacion del Curso                |"<<endl;
  			cout<<"|_________________________________________________|"<<endl;
  			cout<<setw(5)<<"Codigo"<<setw(25)<<"Nombre Completo"<<setw(37)<<"Carrera"<<setw(10)<<"Corte 1"<<setw(8)<<"Corte 2"<<setw(8)<<"Corte 3"<<setw(11)<<"Nota Final"<<endl;
      		for(int i=0; i<tam;i++){cout<<setw(5)<<db[i].codigo<<setw(25)<<db[i].nombre<<setw(37)<<db[i].carrera<<setw(10)<<db[i].nota1<<setw(8)<<db[i].nota2<<setw(8)<<db[i].nota3<<setw(8)<<db[i].nota_final<<endl;}	
  		}	
  		void agregar_est(estudiante *&db, int &tam){
  			comandos cls;
  			string nombre, cod, carrera, letra;
  			bool control, pase;
  			do{
  				system("cls");
  				cout<<"___________________________________________________"<<endl;
  				cout<<"|         Agregar Estudiante al Sistema           |"<<endl;
  				cout<<"|_________________________________________________|"<<endl;
			  	cout<<"\nIngrese codigo estudiantil (00 para regresar al menu principal): ";cin.ignore();cin>>cod; pase = cls.verificar_cod(db,tam,cod);
			  	if(pase == true or cod =="00") {cout<<"Error: Ingreso 00 o Estudiante existente."<<endl; mostrar_menu(db, tam);}
				else control = false;
				if (control == false){
					do {cout<<"Ingrese nombre del estudiante: ";cin.ignore();getline(cin,nombre); control= cls.comprobar(nombre);}while(control==false);
  					do {cout<<"Ingrese carrera del estudiante: ";cin.ignore();getline(cin,carrera); control = cls.comprobar(carrera);}while(control==false);
  					estudiante* temp = new estudiante[tam + 1];
  					for (int i = 0; i < tam; ++i) {temp[i] = db[i];}
            		delete[] db;
            		db = temp;
  					db[tam].codigo=cod;
					db[tam].nombre=nombre;
					db[tam].carrera=carrera;
					db[tam].nota1=0;
					db[tam].nota2=0;
					db[tam].nota3=0;
					db[tam].nota_final=0;
					tam++;
					cout <<"Estudiante agregado correctamente." << endl;
					system("pause");
				}
				if (control==false) {cout <<"Estudiante no agregado correctamente." << endl;system("pause"); break;}
			}while(true);
		}
	void buscar_est(estudiante db[], int tam){
			int pos; string cod; bool cont;
			system("cls");
			cout<<"___________________________________________________"<<endl;
  			cout<<"|            Informacion del Estudiante           |"<<endl;
  			cout<<"|_________________________________________________|"<<endl;
			cout<<"\n Ingrese codigo a buscar (00 para regresar al menu principal): ";cin>>cod;
			if(cod=="00"){mostrar_menu(db, tam);}
			else{
				for(int i=0; i<tam;i++){if(db[i].codigo==cod) {pos = i; cont = true; break;}}
				if(cont == true){
					cout<<"\n _________________________________________________________________________________________________________________"<<endl;
					cout<<endl;
					cout<<"Información del Estudiante: "<<endl;
					cout<<"\t Codigo: "<<db[pos].codigo<<endl;
					cout<<"\t Nombre: "<<db[pos].nombre<<endl;
					cout<<"\t Carrera: "<<db[pos].carrera<<endl;
					cout<<"\t Corte 1: "<<db[pos].nota1<<endl;
					cout<<"\t Corte 2: "<<db[pos].nota2<<endl;
					cout<<"\t Corte 3: "<<db[pos].nota3<<endl;
					cout<<"\t Nota Final: "<<db[pos].nota_final<<endl;
				}
			else {cout<<"No se ha encontrado informacion del estudiante"<<endl;}
			}
	}
	void modificar_est(estudiante db[], int tam){
		comandos cmd;
		int pos, op; bool cont, pase; string nombre, carrera, cod; float nota;
		system("cls");
		cout<<"___________________________________________________"<<endl;
  		cout<<"|      Modificar Informacion del Estudiante       |"<<endl;
  		cout<<"|_________________________________________________|"<<endl;
		show_database(db,tam);
		cout<<endl;
		cout<<"Ingrese codigo a buscar (00 para regresar al menu principal): ";cin>>cod;
		if(cod=="00"){mostrar_menu(db, tam);}
		else{
			for(int i=0; i<tam;i++){if(db[i].codigo==cod) {pos = i; cont = true; break;}}
			if(cont == true){
			cout<<"El estudiante se encuentra en el sistema"<<endl;
			do{
	  			cout<<"\n Que informacion desea modificar?: "<<endl;
				cout<<"\t 1) Nombre"<<endl;
				cout<<"\t 2) Carrera"<<endl;
				cout<<"\t 3) Corte 1"<<endl;
				cout<<"\t 4) Corte 2"<<endl;
				cout<<"\t 5) Corte 3"<<endl;
				cout<<"Opcion (1-5): ";cin>>op;cin.ignore();			
			}while(op>5 or op<1);cout<<endl;
			switch(op){
				case 1:
					do{
						cout<<"Ingrese nuevo nombre, correctamente: ";getline(cin, nombre);cin.ignore();
						if (cmd.comprobar(nombre)) {cout<<"Informacion modificada correctamente. ";system("pause");break;}
						else pase = false;
					} while(pase ==false);db[pos].nombre = nombre;
					break;
				case 2:
					do{
						cout<<"Ingrese nueva carrera, correctamente: ";getline(cin, carrera);cin.ignore();
						if (cmd.comprobar(carrera)){cout<<"Informacion modificada correctamente. ";system("pause");break;} 
						else pase = false;
					}while(pase ==false);db[pos].carrera = carrera;
					break;	
				case 3:
					do{
						cout<<"Ingrese nueva nota del corte 1, correctamente: ";cin>>nota;cin.ignore();
						if (cmd.comprobar(nota)) {cout<<"Informacion modificada correctamente. ";system("pause");break;}
						else pase = false;
					} while(pase ==false); db[pos].nota1 = nota;
					break;
				case 4:
					if (db[pos].nota1 ==0){cout<<"Debe ingresar la nota en el corte 1"<<endl;system("pause");break;}
					else{
						do{
							cout<<"Ingrese nueva nota del corte 2, correctamente: ";cin>>nota;cin.ignore();
						if (cmd.comprobar(nota)) {cout<<"Informacion modificada correctamente. ";system("pause");break;}
							else pase = false;
						}while(pase ==false);db[pos].nota2 = nota;
						break;				
					}
				case 5:
					if (db[pos].nota1 ==0 and db[pos].nota2==0){cout<<"Debe ingresar la nota en el corte 1 y corte 2"<<endl;system("pause");break;}
					else{
						do{
							cout<<"Ingrese nueva nota del corte 3, correctamente: ";cin>>nota;cin.ignore();
						if (cmd.comprobar(nota)) {cout<<"Informacion modificada correctamente. ";system("pause");break;}
							else pase = false;
						} while(pase ==false);db[pos].nota3 = nota;
						break;				
					}
				}					
			}
			else {cout<<"No se ha encontrado informacion del estudiante"<<endl;}
		}
	}
  	void borrar_est(estudiante db[], int &tam){
		int pos, op, ind =0; bool cont, pase; string nombre, carrera, cod; float nota;
		int a;
		system("cls");
		cout<<"___________________________________________________"<<endl;
  		cout<<"|               Borrar Estudiante                 |"<<endl;
  		cout<<"|_________________________________________________|"<<endl;		
		show_database(db,tam);
		cout<<endl;
		cout<<"Ingrese codigo del estudiante a eliminar (00 para regresar al menu principal): ";cin>>cod;
		if(cod=="00"){mostrar_menu(db, tam);}
		else{
			for(int i=0; i<tam;i++){if(db[i].codigo!=cod) {db[ind++]=db[i];}}
			tam = ind;
			cout<<"Estudiante eliminado correctamente."<<endl;
		}

	}
	void introducir_notas(estudiante db[], int tam){
		comandos cmd;
		int pos, op; bool cont, pase,a; float nota; string nombre, cod;
		do{
			system("cls");
			cout<<"___________________________________________________"<<endl;
  			cout<<"|  Notas de Estudiante -Informacion del Curso     |"<<endl;
  			cout<<"|_________________________________________________|"<<endl;
			for(int i=0; i<tam;i++){db[i].nota_final = db[i].calcular_notafinal();}
			show_database(db,tam);
      		cout<<"\nIngrese el codigo del estudiante (00 para regresar al menu principal): ";cin>>cod;cin.ignore();
      		if(cod=="00"){mostrar_menu(db, tam);}
      		else{
      			for(int i=0; i<tam;i++){if(db[i].codigo == cod) {pos = i; cont = true; break;}}
      			cout<<"El estudiante se encuentra en el sistema."<<endl;
      			cout<<endl;
      			cout<<"----------------------------"<<endl;
      			cout<<"|Informacion de las notas: |"<<endl;
      			cout<<"|Corte 1 -------------> 30%|"<<endl;
      			cout<<"|Corte 2 -------------> 35%|"<<endl;
      			cout<<"|Corte 3 -------------> 35%|"<<endl;
      			cout<<"----------------------------"<<endl;
      			do{cout<<"Ingrese el corte (1-3): "; cin>>op;}while(op<1 or op>3);
      			switch (op){
      			case 1:
					do{
						cout<<"Ingrese nueva nota del corte 1, correctamente: ";cin>>nota;cin.ignore();
						if (cmd.comprobar(nota)) {cout<<"Informacion modificada correctamente. ";system("pause");break;}
						else pase = false;
					} while(pase ==false); db[pos].nota1 = nota;
					break;
				case 2:
					if (db[pos].nota1 ==0){cout<<"Debe ingresar la nota en el corte 1"<<endl;system("pause");break;}
					else{
						do{
							cout<<"Ingrese nueva nota del corte 2, correctamente: ";cin>>nota;cin.ignore();
						if (cmd.comprobar(nota)) {cout<<"Informacion modificada correctamente. ";system("pause");break;}
							else pase = false;
						}while(pase ==false);db[pos].nota2 = nota;
						break;	
					}
				case 3:
					if (db[pos].nota1 ==0 and db[pos].nota2==0){cout<<"Debe ingresar la nota en el corte 1 y corte 2"<<endl;system("pause");break;}
					else{
						do{
							cout<<"Ingrese nueva nota del corte 3, correctamente: ";cin>>nota;cin.ignore();
						if (cmd.comprobar(nota)) {cout<<"Informacion modificada correctamente. "; system("pause");break;}
							else pase = false;
						} while(pase ==false);db[pos].nota3 = nota;
						break;				
					}
			  	}	
			  }
		}while(true);	
	}
};
//////
//////
//////
int main(){
	comandos cmd; int tam = cmd.num_db();
	estudiante *db; db = new estudiante[tam]; MENU menu;
	cout<<"Importando informacion";for(int i=0;i<3;i++){cout<<".";cout.flush();Sleep(300);}cout<<endl;cmd.importar(db, tam);
	cout<<"Informacion correctamente importada."<<endl; system("pause"); cout<<"Pulse cualquier tecla para continuar"<<endl;system("cls");
	menu.mostrar_menu(db,tam);
	delete []db; return 0;
}
