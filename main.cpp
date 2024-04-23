/*
Administrador de notas estudiantiles (nombre provisional)
Alejandro Pedro Steinman Cuesta - T00077151
Andres Rubiano Marrugo - T000
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;
//prototipos, clases, structs y demÃ¡s ...
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
  void importar(Estudiante p[]){
    string linea;
    int n=0; //contar las lÃ­neas
    ifstream leerArchivo; //variable lÃ³gica de entrada
    leerArchivo.open("database.txt");
    while(!leerArchivo.eof()){
    getline(leerArchivo,linea);
    if(linea.size()!=0){ //Determina que el archivo ha terminado de leerse
    n++;}}
    leerArchivo.close(); //cierre del flujo
    leerArchivo.open("database.txt");
    
    for (int i=0; i<n; i++){
    getline(leerArchivo,linea,'|');
    p[i].codigo=atoi(linea.c_str());
    getline(leerArchivo,linea,'|');
    p[i].nombre=linea;
    getline(leerArchivo,linea,'|');
    p[i].carrera=linea;
    getline(leerArchivo,linea,'|');
    p[i].nota1=atoi(linea.c_str());
    getline(leerArchivo,linea,'|');
    p[i].nota2=atoi(linea.c_str());
    getline(leerArchivo,linea,'|');
    p[i].nota3=atoi(linea.c_str());
    getline(leerArchivo,linea);
    p[i].nota_final=atoi(linea.c_str());//falta un salto de linea
  }leerArchivo.close();
  }
  void exportar(Estudiante p[], int n){
    ofstream escribirArchivo;
    escribirArchivo.open("database.txt");
    for (int i=0; i<n; i++){
      escribirArchivo<<p[i].codigo<<"|"<<p[i].nombre<<"|"<<p[i].carrera<<"|"<<p[i].nota1<<"|"<<p[i].nota2<<"|"<<p[i].nota3<<"|"<<p[i].nota_final<<endl;
    }escribirArchivo.close();}
  };
class Data_base: public comandos{
  private:
  	int tam;
	Estudiante *database;
  public:
  	Data_base(int tam):database(new Estudiante [tam]){}
    ~Data_base(){delete[] database;}
	  };
int main(){
  comandos cls;
  int tam = cls.num_db();
  Estudiante *database = new Estudiante[tam];
  cls.importar(database);
  for(int i=0;i<cls.num_db();++i){
  cout<<database[i].nombre<<endl;
  }
  return 0;
}
