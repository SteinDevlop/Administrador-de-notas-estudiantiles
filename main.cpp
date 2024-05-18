/*
Alejandro Pedro Steinman Cuesta - T00077151.
Andres Rubiano Marrugo - T00077084.
Administrador de Notas Estudiantiles version 1.1
"De este modo invocamos al Dios Maquina. De este modo reparamos lo que estaba roto."*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <limits>
#include <ctype.h>
#include <windows.h> 
using namespace std;

struct Estudiante {
    string codigo;
    string nombre;
    string carrera;
    float nota1;
    float nota2;
    float nota3;
    float nota_final;
    float calcular_notafinal(){return (nota1*0.3)+(nota2*0.35)+(nota3*0.35);}
};
class Administrador {
	public:
		Estudiante *db;
		int tam;
    	Administrador(int n) {
    		db = new Estudiante[n];
    		tam=n;
		}
		~Administrador(){
			delete[]db;
		}
    void importar() {
        string linea; int n = 0;
        ifstream leerArchivo("database.txt");
        while (getline(leerArchivo, linea)) {
            if (linea.size() != 0) {n++;}
        }
        leerArchivo.close(); leerArchivo.open("database.txt");
        delete[]db; tam = n;
        db = new Estudiante[tam];
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
            getline(leerArchivo, linea,'|');
            db[i].nota_final = atof(linea.c_str());
            getline(leerArchivo, linea);
        }
        leerArchivo.close();
    }
	void exportar( Estudiante base[], int tama, bool &pase){
    	ofstream escribirArchivo; escribirArchivo.open("database.txt",ios::trunc);
    	for (int i=0; i<tama; i++){escribirArchivo<<base[i].codigo<<"|"<<base[i].nombre<<"|"<<base[i].carrera<<"|"<<base[i].nota1<<"|"<<base[i].nota2<<"|"<<base[i].nota3<<"|"<<base[i].nota_final<<"|"<<endl;}
    	pase = true;
		escribirArchivo.close();
	}
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
		if(0<nota and nota<=5) return true;
		else return false;
	}
	bool comprobar(string cadena){
		int tam = cadena.size();
		if(tam==0 or isdigit(cadena[0]) or isblank(cadena[0])) return false;
		else{
			for (int i=1; i<tam;i++){if(isdigit(cadena[i])) {return false; break;}}
			return true;
		}	
	}
    void ordenar(Estudiante BASE[], int tam){
		for(int i=0; i<tam-1; i++){
				Estudiante aux;
			for(int j =i+1;j<tam;j++){
				if(BASE[i].codigo>BASE[j].codigo){
					aux = BASE[j];
					BASE[j]=BASE[i];
					BASE[i] = aux;
				}
			}
		}	
	}
	bool repet_cod(Estudiante BASE[], int tam, string cod) {
        for (int i = 0; i<tam; i++) {if (cod == BASE[i].codigo) {return true; break;}}
        return false;
    }
    bool verificador_cod(Estudiante BASE[], int tam, string codigo)
	{
		int tamano = codigo.size();
		if(tamano==8){
			for(int i =0 ; i<tamano; i++){
        		if ((isalpha(codigo[i])) or (isblank(codigo[i]))){cout<<"Error: Codigo incorrecto."<<endl;return false; break;}
			}
			if(repet_cod(BASE,tam, codigo)==true){cout<<"Error: Codigo existente"<<endl; return false;}
			else return true;
		}
		else if(tamano!=5){cout<<"Error: Formato de Codigo incorrecto."<<endl; return false;}
		else return true;	
	}
};
class MENU{
	public:
		void mostrar_menu(Administrador punt, Estudiante base[], int tam){//listo
			comandos cmd; bool c; string opcion="";
				do{
					system("cls");
					cmd.ordenar(base,tam);
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
					cout<<"Ingrese opcion (1-8): ";getline(cin,opcion);
					if(opcion.length()==1 and isdigit(opcion[0]) and (opcion >="1"and opcion<="8")){c=false; break;}
					else c = true;
				}while(c==true);
				char op = opcion[0];
					switch(op){	
					case '1':
						show_database(punt, base,tam); 
						break;
					case '2':
						agregar_est(punt,base,tam);
						break;
					case '3':
						buscar_est(punt, base,tam);
						break;
					case '4':
						borrar_est(punt, base,tam);
						break;
					case '5':
						modificar_est(punt, base,tam);
						break;
					case '6':
						introducir_notas(punt, base,tam);
						break;
					case '7':
						guardado(punt, base, tam); Sleep (500);
						break;
					case '8':
						cout<<"Cerrando";for(int i=0;i<3;i++){cout<<".";cout.flush();Sleep(250);};
						break;
				}
		}	
	private:
		void control(Administrador punt, Estudiante base[], int tam){//listo
			string ans=" "; cout<<endl;
			do{
				cout<<"\n Desea continuar en el programa? (S/N): ";getline(cin,ans);
				if(ans.length()<=2 and !(isdigit(ans[0])) and !(isblank(ans[0]))) {
					char op = ans[0];
					if(op=='S' or op=='s') {mostrar_menu(punt, base,tam); break;}
					else if (op =='N' or op =='n') {cout<<"Cerrando..."<<endl;break;}
				}
			}while(true);		
		}	
		void show_database(Administrador punt, Estudiante base[], int tam) {//listo
  			system("cls");
  			cout<<"___________________________________________________"<<endl;
  			cout<<"|            Informacion del Curso                |"<<endl;
  			cout<<"|_________________________________________________|"<<endl;
  			cout<<setw(9)<<"Codigo"<<setw(25)<<"Nombre Completo"<<setw(37)<<"Carrera"<<setw(10)<<"Corte 1"<<setw(8)<<"Corte 2"<<setw(8)<<"Corte 3"<<setw(11)<<"Nota Final"<<endl;
      		for(int i=0; i<tam;i++){cout<<setw(9)<<("T"+base[i].codigo)<<setw(25)<<base[i].nombre<<setw(37)<<base[i].carrera<<setw(10)<<base[i].nota1<<setw(8)<<base[i].nota2<<setw(8)<<base[i].nota3<<setw(8)<<base[i].nota_final<<endl;}	
			control(punt, base,tam);
		}
		void agregar_est(Administrador &punt, Estudiante *&base, int &tam) {//listo
			comandos cmd; string cod=" ", nombre=" ", carrera=" "; bool cont = false;
			do{
  				system("cls");
  				cout<<"___________________________________________________"<<endl;
  				cout<<"|         Agregar Estudiante al Sistema           |"<<endl;
  				cout<<"|_________________________________________________|"<<endl;
    			do {
        			cout << "\nIngrese 'T' seguido de los digitos del codigo estudiantil (Ingrese 'T000' para salir): ";cin.ignore();getline(cin,cod);
        			if (cod == "000") {mostrar_menu(punt, base,tam);break;}
        			else{cont = cmd.verificador_cod(base,tam, cod);}
    			}while (cont == false);
    			cout<<endl;
    			do {
        			cout << "Ingrese # seguido del nombre del Estudiante: "; cin.ignore();getline(cin, nombre); //
        			cont = cmd.comprobar(nombre);
        			if (!cont) {cout << "Error: Nombre no valido."<<endl;}
    			} while (!cont);
    			cout<<endl;
   				do {
        			cout << "Ingrese # seguido del carrera del Estudiante: ";cin.ignore();getline(cin, carrera); ///
        			cont = cmd.comprobar(carrera);
        			if (!cont) {cout << "Error: Carrera no valida."<<endl;}
    			} while (!cont);
    			Estudiante* temp = new Estudiante[tam+1];
    			for (int i = 0; i < tam; i++) {temp[i] = base[i];}
    			delete[] base;
            	base = temp;
  				base[tam].codigo=cod;
				base[tam].nombre=nombre;
				base[tam].carrera=carrera;
				base[tam].nota1=0;
				base[tam].nota2=0;
				base[tam].nota3=0;
				base[tam].nota_final=0;
				tam++;
				cout<<"Estudiante agregado correctamente." << endl;
				system("pause");
			}while(true);
			control(punt, base,tam);
		}
		void buscar_est(Administrador punt,Estudiante base[], int tam){//listo
			comandos cmd; int pos; string cod=""; bool cont;
			system("cls");
			cout<<"___________________________________________________"<<endl;
  			cout<<"|            Informacion del Estudiante           |"<<endl;
  			cout<<"|_________________________________________________|"<<endl;
        	cout << "\nIngrese 'T' seguido de los digitos del codigo estudiantil (Ingrese 'T000' para salir): ";cin.ignore();getline(cin,cod);
        	if (cod == "000") {mostrar_menu(punt, base,tam);}
        	else{cont = cmd.repet_cod(base,tam, cod);}
			if(cont == true){
				for(int i=0; i<tam;i++){if(base[i].codigo==cod) {pos = i; break;}}
				cout<<"_________________________________________________________________________________________________________________"<<endl;
				cout<<endl;
				cout<<"Informacion del Estudiante: "<<endl;
				cout<<"\t Codigo: "<<("T"+base[pos].codigo)<<endl;
				cout<<"\t Nombre: "<<base[pos].nombre<<endl;
				cout<<"\t Carrera: "<<base[pos].carrera<<endl;
				cout<<"\t Corte 1: "<<base[pos].nota1<<endl;
				cout<<"\t Corte 2: "<<base[pos].nota2<<endl;
				cout<<"\t Corte 3: "<<base[pos].nota3<<endl;
				cout<<"\t Nota Final: "<<base[pos].nota_final<<endl;
			}
			else {cout<<"No se ha encontrado informacion del Estudiante ingresado."<<endl;}
			control(punt, base,tam);
		}	
		void modificar_est(Administrador punt, Estudiante base[], int tam){//listo
			comandos cmd;int pos; string opcion=""; bool cont, c, ii, pase; string nombre="", carrera="", cod=""; float nota;
			do{
			system("cls");
			cout<<"___________________________________________________"<<endl;
  			cout<<"|      Modificar Informacion del Estudiante       |"<<endl;
  			cout<<"|_________________________________________________|"<<endl;
  			for(int i=0; i<tam;i++){base[i].nota_final = base[i].calcular_notafinal();}
  			
			cout<<setw(9)<<"Codigo"<<setw(25)<<"Nombre Completo"<<setw(37)<<"Carrera"<<setw(10)<<"Corte 1"<<setw(8)<<"Corte 2"<<setw(8)<<"Corte 3"<<setw(11)<<"Nota Final"<<endl;
      		for(int i=0; i<tam;i++){cout<<setw(9)<<("T"+base[i].codigo)<<setw(25)<<base[i].nombre<<setw(37)<<base[i].carrera<<setw(10)<<base[i].nota1<<setw(8)<<base[i].nota2<<setw(8)<<base[i].nota3<<setw(8)<<base[i].nota_final<<endl;}	
        	
			cout << "\nIngrese 'T' o 't', seguido de los digitos del codigo estudiantil (Ingrese 'T000' para salir): ";cin.ignore();getline(cin,cod);
			if(cod=="000"){mostrar_menu(punt, base,tam);}
        	else{cont = cmd.repet_cod(base,tam, cod);}
			if(cont == true){
				for(int i=0; i<tam;i++){if(base[i].codigo==cod) {pos = i; break;}}
				cout<<"El Estudiante se encuentra en el sistema"<<endl;
				do{
					cout<<"\n Que informacion desea modificar?: "<<endl;
					cout<<"\t 1) Nombre"<<endl;
					cout<<"\t 2) Carrera"<<endl;
					cout<<"\t 3) Nota Corte 1"<<endl;
					cout<<"\t 4) Nota Corte 2"<<endl;
					cout<<"\t 5) Nota Corte 3"<<endl;
					cout<<"Opcion (1-5): ";getline(cin, opcion);
					if(opcion.length()==1 and isdigit(opcion[0]) and (opcion>="1"and opcion<="5")){c=false; break;}	
					else c=true;				
				}while(c==true);
				char op = opcion[0];
				switch(op){
					case '1':
						do {
        					cout << "Ingrese # seguido del nombre del Estudiante: "; cin.ignore();getline(cin, nombre); //
        					cont = cmd.comprobar(nombre);
        					if (cont==false) {cout<<"Error: Nombre no valido."<<endl;}
    					} while (!cont);
    					base[pos].nombre = nombre;
    					cout<<"Informacion modificada correctamente. "<<endl;
    					break;
					case '2':
						do {
        					cout << "Ingrese # seguido del carrera del Estudiante: ";cin.ignore();getline(cin, carrera); ///
        					cont = cmd.comprobar(carrera);
        					if (!cont) {cout << "Error: Carrera no valida."<<endl;}
    					} while (!cont);
    					base[pos].carrera = carrera;
    					cout<<"Informacion modificada correctamente. "<<endl;
    					break;
					case '3':
						do{
							cout<<"Ingrese nueva nota del corte 1, correctamente: ";cin>>nota; 
							pase = cmd.comprobar(nota);
						} while(pase ==false); base[pos].nota1 = nota;
						cout<<"Informacion modificada correctamente. "<<endl;
						break;
					case '4':
						if(base[pos].nota1==0){cout<<"Debe ingresar la nota del corte 1 para editar este corte."<<endl;break;}
						if(base[pos].nota1!=0){
						do{
							cout<<"Ingrese nueva nota del corte 2, correctamente: ";cin>>nota; 
							pase = cmd.comprobar(nota);
						} while(pase ==false);base[pos].nota2 = nota;}
						cout<<"Informacion modificada correctamente. "<<endl;
						break;
					case '5':
						if(base[pos].nota1==0 or base[pos].nota2==0){cout<<"Debe ingresar la nota del corte 1 y/o 2 para editar este corte."<<endl;break;}
						if(base[pos].nota1!=0 or base[pos].nota2!=0){
						do{
							cout<<"Ingrese nueva nota del corte 3, correctamente: ";cin>>nota; 
							pase = cmd.comprobar(nota);
						} while(pase ==false);base[pos].nota3 = nota;}
						cout<<"Informacion modificada correctamente. "<<endl;
						break;
					}					
				do{
					string ans=" ";
					cout<<endl;
					cout<<"\n Desea agregando notas? (S/N): ";getline(cin,ans);
					if(ans.length()<=2 and !(isdigit(ans[0])) and !(isblank(ans[0]))) {
						char op = ans[0];
						if(op=='S' or op=='s') {ii=true; break;}
						else if (op =='N' or op =='n') {ii=false; break;}
					}
				}while(true);
			}
			else{cout<<"No se ha encontrado informacion del Estudiante"<<endl;system("pause");ii=true;}
		}while(ii==true);
		control(punt, base,tam);
	}
		void borrar_est(Administrador punt, Estudiante base[], int &tam){//listo
			comandos cmd; int ind =0, pos; string cod=""; bool cont;
			system("cls");
			cout<<"___________________________________________________"<<endl;
  			cout<<"|               Borrar Estudiante                 |"<<endl;
  			cout<<"|_________________________________________________|"<<endl;	
			cout<<endl;
			cout << "\nIngrese 'T' seguido de los digitos del codigo estudiantil (Ingrese 'T000' para salir): ";cin.ignore();getline(cin,cod);
			if(cod=="000"){mostrar_menu(punt, base,tam);}
        	else{cont = cmd.repet_cod(base,tam, cod);}
			if(cont == true){
				for(int i=0; i<tam;i++){if(base[i].codigo==cod) {pos = i;break;}}
				for(int i=0; i<tam;i++){if(base[i].codigo!=base[pos].codigo) {base[ind++]=base[i];}}
				tam = ind;
				cout<<"Estudiante eliminado correctamente."<<endl;
			}
			else{cout<<"No se ha encontrado informacion del Estudiante"<<endl;}
			control(punt, base,tam);
		}
		void introducir_notas(Administrador punt, Estudiante base[], int tam){//listo
			comandos cmd; int pos; char op; bool cont, ii, pase; string opcion="",cod="", nota=""; float note;
			do{
				system("cls");
				cout<<"___________________________________________________"<<endl;
  				cout<<"|  Notas de Estudiante -Informacion del Curso     |"<<endl;
  				cout<<"|_________________________________________________|"<<endl;
  				for(int i=0; i<tam;i++){base[i].nota_final = base[i].calcular_notafinal();}
  				cout<<setw(9)<<"Codigo"<<setw(25)<<"Nombre Completo"<<setw(37)<<"Carrera"<<setw(10)<<"Corte 1"<<setw(8)<<"Corte 2"<<setw(8)<<"Corte 3"<<setw(11)<<"Nota Final"<<endl;
      			for(int i=0; i<tam;i++){cout<<setw(9)<<("T"+base[i].codigo)<<setw(25)<<base[i].nombre<<setw(37)<<base[i].carrera<<setw(10)<<base[i].nota1<<setw(8)<<base[i].nota2<<setw(8)<<base[i].nota3<<setw(8)<<base[i].nota_final<<endl;}	
				do {
        			cout << "\nIngrese 'T' o 't' seguido de los digitos del codigo estudiantil correctamente (Ingrese 'T000' o 't000' para salir): ";cin.ignore();getline(cin,cod);
					if(cod=="000"){mostrar_menu(punt, base,tam);break;}
        			else{cont = cmd.repet_cod(base,tam,cod);}
    			}while (cont == false);
				if(cont == true){
					for(int i=0; i<tam;i++){if(base[i].codigo == cod) {pos = i; break;}}
					cout<<"El Estudiante se encuentra en el sistema."<<endl;
					cout<<"----------------------------"<<endl;
					cout<<"|Informacion de las notas: |"<<endl;
					cout<<"|Corte 1 -------------> 30%|"<<endl;
					cout<<"|Corte 2 -------------> 35%|"<<endl;
					cout<<"|Corte 3 -------------> 35%|"<<endl;
					cout<<"----------------------------"<<endl;
					do{
						cout<<"(Ingrese numero del corte) Nota a modificar. Opcion: (1-3) ";getline(cin,opcion);
						if(opcion.length()==1 and isdigit(opcion[0]) and (opcion>="1"and opcion<="3")){cont=false; break;}	
						else cont=true;			
					}while(cont==true);
					char op = opcion[0];
					switch (op){
						case '1':
							do{
								cout<<"Ingrese nueva nota del corte 1, correctamente: ";getline(cin,nota);
								if(isdigit(nota[0])){
									note = atof(nota.c_str());
									pase = cmd.comprobar(note);
								}
							} while(pase ==false); base[pos].nota1 = note;cout<<"Informacion modificada correctamente. "<<endl;
							break;
						case '2':
							if(base[pos].nota1==0){cout<<"Debe ingresar la nota del corte 1 para editar este corte."<<endl;break;}
							if(base[pos].nota1!=0){
							do{
								cout<<"Ingrese nueva nota del corte 2, correctamente: ";getline(cin,nota);
								if(isdigit(nota[0])){
									note = atof(nota.c_str());
									pase = cmd.comprobar(note);
								}
								pase = cmd.comprobar(note);
							} while(pase ==false);base[pos].nota2 = note;cout<<"Informacion modificada correctamente. "<<endl;}
							break;
						case '3':
							if(base[pos].nota1==0 or base[pos].nota2==0){cout<<"Debe ingresar la nota del corte 1 y/o 2 para editar este corte."<<endl;break;}
							if(base[pos].nota1!=0 or base[pos].nota2!=0){
							do{
								cout<<"Ingrese nueva nota del corte 3, correctamente: ";getline(cin,nota);
								if(isdigit(nota[0])){
									note = atof(nota.c_str());
									pase = cmd.comprobar(note);
								}
								pase = cmd.comprobar(note);
							} while(pase ==false);base[pos].nota3 = note;cout<<"Informacion modificada correctamente. "<<endl;}
							break;
					}
					
					do{
						string ans=" "; cout<<endl;
						cout<<"\n Desea agregando notas? (S/N): ";getline(cin,ans);
						if(ans.length()<=2 and !(isdigit(ans[0])) and !(isblank(ans[0]))) {
							char op = ans[0];
							if(op=='S' or op=='s') {ii=true; break;}
							else if (op =='N' or op =='n') {ii=false; break;}
						}
					}while(true);
				}
				else{cout<<"No se ha encontrado informacion del Estudiante"<<endl;ii=true;}
			}while(ii==true);
			control(punt, base,tam);
		}
		void guardado(Administrador punt, Estudiante base[], int tam){
			bool pase = false; punt.exportar(base, tam, pase);
			if (pase == true) cout<<"Los datos han sido guardados."<<endl;
			else if(pase == false) {cout<<"Datos no ha sido guardados correctamente."<<endl;}
			control(punt, base,tam);	
		}
};
/////
/////
int main(){
	comandos cmd; MENU menu; int opcion; bool c;int tam = cmd.num_db();
	Administrador puntero(tam); puntero.importar();
	cout<<"Importando informacion";for(int i=0;i<3;i++){cout<<".";cout.flush();Sleep(300);}cout<<endl;puntero.importar();
	cout<<"Informacion correctamente importada."<<endl; system("pause"); cout<<"Pulse cualquier tecla para continuar"<<endl;system("cls");
	menu.mostrar_menu(puntero, puntero.db,puntero.tam);
	puntero.~Administrador();
	return 0;
}
