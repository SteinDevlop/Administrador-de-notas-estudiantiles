//quiero probar una cosa... dont touch
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
//prototipos, clases, structs y demás ...
struct estudiante{ //definición de struct "estudiante"
  int codigo;
  string nombre;
  string carrera;
  string materia;
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
    string linea; int n=0;
    ifstream leerArchivo; 
    leerArchivo.open("database.txt");
    while(!leerArchivo.eof()){
    getline(leerArchivo,linea);
    if(linea.size()!=0){n++;}} //Determina que el archivo ha terminado de leerse
    leerArchivo.close(); //cierre del flujo
    leerArchivo.open("database.txt");
    for (int i=0; i<n; i++){
      getline(leerArchivo,linea,'|'); p[i].codigo=atoi(linea.c_str());
      getline(leerArchivo,linea,'|'); p[i].nombre=linea;
      getline(leerArchivo,linea,'|'); p[i].carrera=linea;
      getline(leerArchivo,linea,'|'); p[i].nota1=atof(linea.c_str());
      getline(leerArchivo,linea,'|'); p[i].nota2=atof(linea.c_str());
      getline(leerArchivo,linea,'|'); p[i].nota3=atof(linea.c_str());
      getline(leerArchivo,linea,';'); p[i].nota_final=atof(linea.c_str());cout<<endl;
    }leerArchivo.close();
  }
  void exportar(Estudiante p[], int n){
    ofstream escribirArchivo;
    escribirArchivo.open("database.txt");
    for (int i=0; i<n; i++){
      escribirArchivo<<p[i].codigo<<"|"<<p[i].nombre<<"|"<<p[i].carrera<<"|"<<p[i].nota1<<"|"<<p[i].nota2<<"|"<<p[i].nota3<<"|"<<p[i].nota_final<<";"<<endl;
    }escribirArchivo.close();}
  };
class database: public comandos{
  private:
    int tam;
    estudiante *database;
  public:
    friend class menu;
    friend class comprobador;
    database(int cant): tam(cant){
      database = new estudiante [tam];
    }
    ~database(){
      delete[] database;
    }
};
class menu {
  private:
    bool estado;
  public:
    menu(bool est): estado(est){}

  void show_data_base(estudiante x, database y){
      for(int i =0; i<y.tam;i++){
        cout<<x[i].codigo<<"\t"<<x[i].nombre<<"\t"<<x[i].carrera<<"\t"x[i].
      }
  }

  //void agregar_est();
  //void show_estudiante();
  //void delete_estudiante();
  //void modificar_info_estudiante();
  //void agregar_notas();
};
