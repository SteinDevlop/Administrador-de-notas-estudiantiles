/*
Administrador de Notas Estudiantiles
Alejandro Pedro Steinman Cuesta - T00077151.
Andres Rubiano Marrugo - T00077084.
"De este modo invocamos al Dios Maquina. De este modo reparamos lo que estaba roto."

Falta: 
* Optimizar entorno visual
* Quitar o disminuir puntero control
* Seguir probando en busca de errores.
* Mejorar la actualizacion de pantalla para errores repetitivos
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <stdio.h>
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
    Estudiante(): codigo(""), nombre(""), carrera(""), nota1(0), nota2(0), nota3(0), nota_final(0) {}
};

class Administrador {
private:
    Estudiante *db = NULL;
    int tam;

public:
    Administrador() : db(NULL), tam(0) {}

    void importar() {
        string linea;
        int n = 0;
        ifstream leerArchivo("database.txt");
        while (getline(leerArchivo, linea)) {
            if (linea.size() != 0) {
                n++;
            }
        }
        leerArchivo.close();
        leerArchivo.open("database.txt");
        tam = n;
        db = new Estudiante[tam]; // Allocate memory
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
    }

    void exportar(bool &pase) {
        ofstream escribirArchivo("database.txt", ios::trunc);
        for (int i = 0; i < tam; i++) {
            escribirArchivo << db[i].codigo << "|" << db[i].nombre << "|" << db[i].carrera << "|" << db[i].nota1 << "|" << db[i].nota2 << "|" << db[i].nota3 << "|" << db[i].nota_final << "|" << endl;
        }
        pase = true;
        escribirArchivo.close();
    }

    int num_db() {
        string linea;
        int n = 0;
        ifstream leerArchivo("database.txt");
        while (getline(leerArchivo, linea)) {
            if (linea.size() != 0) {
                n++;
            }
        }
        leerArchivo.close();
        return n;
    }

    bool comprobar(float nota) {
        return (0 < nota && nota <= 5);
    }

    bool comprobar(string cadena) {
    int tam = cadena.size();
    for (int i = 0; i < tam; i++) {
        if (!isalpha(cadena[i]) && cadena[i] != ' ') {
            return false;
        }
    }
    return true;
}

    void guardado() {
        bool pase = false;
        exportar(pase);
        if (pase) {
            cout << "Datos guardados correctamente." << endl;
        } else {
            cout << "Los datos no han sido guardados." << endl;
        }
    }

    bool control() {
        string ans;
        cout << endl;
        cout << "Desea continuar? (S/N): ";
        cin >> ans;
        cin.ignore(); // Clear input buffer
        return (ans == "Si" || ans == "si" || ans == "S" || ans == "s");
    }

    void nota_final() {
        for (int i = 0; i < tam; i++) {
            db[i].nota_final = (db[i].nota1 * 0.3) + (db[i].nota2 * 0.35) + (db[i].nota3 * 0.35);
        }
    }

    bool repet_cod(string cod) {
        for (int i = 0; i < tam; i++) {
            if (cod == db[i].codigo) {
                return true;
            }
        }
        return false;
    }
    void show_database() {
        for (int i = 0; i < tam; i++) {
            cout << db[i].codigo << "\t" << db[i].nombre << "\t" << db[i].carrera << "\t" << db[i].nota1 << "\t" << db[i].nota2 << "\t" << db[i].nota3 << "\t" << db[i].nota_final << endl;
        }
    }
	bool verificador_cod(string codigo)
	{
		int tamano = codigo.size();

		for(int i =0 ; i<tamano; i++){
        	if (isalpha(codigo[i])){cout<<"Error: Codigo incorrecto."<<endl;return false;}}
		if (codigo.length() != 5) {cout << "Error: Formato de codigo incorrecto." << endl;return false;}
		if (repet_cod(codigo)) {cout << "Error: Estudiante existente." << endl;return false;}

	return true;
}
void agregar_est() {
    string cod, nombre, carrera;
    bool control = false;
    do {
        cout << "Ingrese codigo estudiantil (Los ultimos 5 digitos) (0 para salir)): ";
        cin >> cod;
        if (cod == "0") {return;}
    } while (!verificador_cod(cod));

    cin.ignore(); // Clear input buffer

    do {
        cout << "Ingrese nombre del Estudiante: ";
        getline(cin, nombre);
        control = comprobar(nombre);
        if (!control) {
            cout << "Nombre no valido." << endl;
        }
    } while (!control);

    do {
        cout << "Ingrese carrera del Estudiante: ";
        getline(cin, carrera);
        control = comprobar(carrera);
        if (!control) {
            cout << "Carrera no valida." << endl;
        }
    } while (!control);

    tam++;
    Estudiante* temp = new Estudiante[tam];
    for (int i = 0; i < tam - 1; i++) {
        temp[i] = db[i];
    }
    temp[tam - 1].codigo = cod;
    temp[tam - 1].nombre = nombre;
    temp[tam - 1].carrera = carrera;
    temp[tam - 1].nota1 = 0;
    temp[tam - 1].nota2 = 0;
    temp[tam - 1].nota3 = 0;
    temp[tam - 1].nota_final = 0;
    delete[] db;
    db = temp;
    cout << "Estudiante agregado correctamente." << endl;
}
	void buscar_est(){//revisar
			int pos; string cod; bool cont;
			cout<<"Ingrese codigo a buscar: ";cin>>cod; for(int i=0; i<tam;i++){if(db[i].codigo==cod) {pos = i; cont = true; break;}}
			if(cont == true){
				cout<<"_________________________________________________________________________________________________________________"<<endl;
				cout<<endl;
				cout<<"Informacion del Estudiante: "<<endl;
				cout<<"\t Codigo: "<<db[pos].codigo<<endl;
				cout<<"\t Nombre: "<<db[pos].nombre<<endl;
				cout<<"\t Carrera: "<<db[pos].carrera<<endl;
				cout<<"\t Corte 1: "<<db[pos].nota1<<endl;
				cout<<"\t Corte 2: "<<db[pos].nota2<<endl;
				cout<<"\t Corte 3: "<<db[pos].nota3<<endl;
				cout<<"\t Nota Final: "<<db[pos].nota_final<<endl;
			}
			else {cout<<"No se ha encontrado informacion del Estudiante ingresado."<<endl;}
	}
	void modificar_est(){
		int pos, op; bool cont, pase; string nombre="", carrera, cod; float nota;
		cout<<"__________________________________________________________________________________________________________________"<<endl;
		for(int i=0; i<tam;i++){cout<<db[i].codigo<<"\t"<<db[i].nombre<<"\t"<<db[i].carrera<<endl;}	
		cout<<"__________________________________________________________________________________________________________________"<<endl;
		cout<<"Ingrese codigo a buscar: ";cin>>cod;
		for(int i=0; i<tam;i++){if(db[i].codigo==cod) {pos = i; cont = true; break;}}
		if(cont == true){
			cout<<"El Estudiante se encuentra en el sistema"<<endl;
			do{
				cout<<"\n Que informacion desea modificar?: "<<endl;
				cout<<"\t 1) Nombre"<<endl;
				cout<<"\t 2) Carrera"<<endl;
				cout<<"\t 3) Nota Corte 1"<<endl;
				cout<<"\t 4) Nota Corte 2"<<endl;
				cout<<"\t 5) Nota Corte 3"<<endl;
				cout<<"Opcion (1-5): ";cin>>op;				
			}while(op>5 or op<1);
			switch(op){
				case 1:
					do{
						cin.ignore();
						cout<<"Ingrese nuevo nombre, correctamente: "; getline(cin, nombre);
						pase = comprobar(nombre);
					} while(pase ==false);db[pos].nombre = nombre;
					break;
				case 2:
					do{
						cin.ignore();
						cout<<"Ingrese nueva carrera, correctamente: "; getline(cin, carrera);
						pase = comprobar(carrera);
					}while(pase ==false);db[pos].carrera = carrera;
					break;	
				case 3:
					do{
						cout<<"Ingrese nueva nota del corte 1, correctamente: "; cin>>nota; cin.ignore();
						pase = comprobar(nota);
					} while(pase ==false); db[pos].nota1 = nota;
					break;
				case 4:
					if(db[pos].nota1==0){cout<<"Debe ingresar la nota del corte 1 para editar este corte."<<endl;}
					if(db[pos].nota1!=0){
					do{
						cout<<"Ingrese nueva nota del corte 2, correctamente: "; cin>>nota; cin.ignore();
						pase = comprobar(nota);
					} while(pase ==false);db[pos].nota2 = nota;}
					break;
				case 5:
					if(db[pos].nota1==0 or db[pos].nota2==0){cout<<"Debe ingresar la nota del corte 1 y/o 2 para editar este corte."<<endl;}
					if(db[pos].nota1!=0 or db[pos].nota2!=0){
					do{
						cout<<"Ingrese nueva nota del corte 3, correctamente: "; cin>>nota; cin.ignore();
						pase = comprobar(nota);
					} while(pase ==false);db[pos].nota3 = nota;}
					break;
			}					
		}
		else {cout<<"No se ha encontrado informacion del Estudiante"<<endl;}
	}
	void borrar_est()
	{
		int ind =0,pos;string nombre, carrera, cod;bool cont;
		for(int i=0; i<tam;i++){cout<<db[i].codigo<<"\t"<<db[i].nombre<<"\t"<<db[i].carrera<<endl;}
		cout<<endl;
		cout<<"Ingrese codigo del Estudiante a eliminar: ";cin>>cod;
		for(int i=0; i<tam;i++){if(db[i].codigo==cod) {pos = i; cont = true; break;}}
		if(cont == true)
		{
		for(int i=0; i<tam;i++){if(db[i].codigo!=cod) {db[ind++]=db[i];}}
		tam = ind;
		cout<<"Estudiante eliminado correctamente."<<endl;
		}
		else{cout<<"No se ha encontrado informacion del Estudiante"<<endl;}
	}
	void introducir_notas(){
		int pos, op; bool cont, pase; float nota; string nombre, cod;
		cout<<"Informacion del Curso"<<endl;
		for(int i=0; i<tam;i++){cout<<db[i].codigo<<"\t"<<db[i].nombre<<"\t"<<db[i].nota1<<"\t"<<db[i].nota2<<"\t"<<db[i].nota3<<"\t"<<db[i].nota_final<<endl;}
		cout<<"Ingrese el codigo del Estudiante: ";cin>>cod;
		for(int i=0; i<tam;i++){if(db[i].codigo == cod) {pos = i; cont = true; break;}}
		if(cont == true)
		{
		cout<<"El Estudiante se encuentra en el sistema."<<endl;
		cout<<"----------------------------"<<endl;
		cout<<"|Informacion de las notas: |"<<endl;
		cout<<"|Corte 1 -------------> 30%|"<<endl;
		cout<<"|Corte 2 -------------> 35%|"<<endl;
		cout<<"|Corte 3 -------------> 35%|"<<endl;
		cout<<"----------------------------"<<endl;
		do
		{
		cout<<"(Ingrese numero del corte) Nota a modificar. Opcion: (1-3) "; cin>>op;
		}while(op<1 or op>3);
			switch (op){
					case 1:
					cout<<"Ingrese nota a cambiar: "; cin>>nota; 
					pase=comprobar(nota); 
					if (pase == true){cont = true;db[pos].nota1=nota;}
					break;
				case 2:
					if (db[pos].nota1 !=0){
						cout<<"Ingrese nota a cambiar: "; cin>>nota; 
						pase=comprobar(nota); 
						if (pase == true){cont = true;db[pos].nota2=nota;}	
					}
					else {cont = false;}
					break;
				case 3:
					if ((db[pos].nota1 !=0) and (db[pos].nota2 !=0)){
						cout<<"Ingrese nota a cambiar: "; cin>>nota; 
						pase=comprobar(nota); 
						if (pase == true){cont = true;db[pos].nota3=nota;}	
					}
					break;}	
		cout<<"La nota cambiada exitosamente"<<endl;
	}
	else{cout<<"No se ha encontrado informacion del Estudiante"<<endl;}}
};
class MENU {
};
int main(){
	Administrador puntero;
	int opcion; bool c;
	puntero.importar();
	do{
		puntero.nota_final();
		system("cls");
		cout<<"-----Sistema de Administracion Estudiantil-----"<<endl;
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
					puntero.show_database();
					c = puntero.control();
					break;
				case 2:
					puntero.agregar_est();
					c = puntero.control();
					break;
				case 3:
					puntero.buscar_est();
					c = puntero.control();
					break;
				case 4:
					puntero.borrar_est();
					c = puntero.control();
					break;
				case 5:
					puntero.modificar_est();
					c = puntero.control();
					break;
				case 6:
					puntero.introducir_notas();
					c = puntero.control();
					break;
				case 7:
					puntero.guardado();
					c = puntero.control();
					break;
				case 8:
					c = false;
					break;
			}
	}while(c ==true);
	return 0;
}
