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
//notadelandres: Yo sugiero hacer un arreglo donde estén las tres notas y la nota final, es decir, float notas [4], se ahorra espacialidad y optimiza mejor;
  float nota1;
  float nota2;
  float nota3;
  float nota_final;
};
//pedazo que tengo que revisar
class comandos{
  public: 
    virtual void importar() const =0;
    virtual void exportar() const =0;
//
};
//proseguir
class data_base: public comandos{
  private:
    int tam;
    estudiante *database;
  public:
    data_base(int cant): tam(cant){
      database = new estudiante [tam];
    }
    ~data_base(){
      delete[] database;
    }
    friend class menu;
    friend class comprobador;
  /*void importar() const override{ }
  void exportar() const override{ }*/
//
};
class menu{
  public:
      //no necesita constructor??
  void agregar_est();
  void show_data_base();
  void show_estudiante();
  void delete_estudiante();
  void modificar_info_estudiante();
  void agregar_notas();
};
