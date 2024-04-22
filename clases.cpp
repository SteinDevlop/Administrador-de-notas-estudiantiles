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
class data_base{
  int tam;
  estudiante *database;
  public:
    data_base(int cant): tam(cant){
      database = new estudiante [tam];
    }
    ~data base{
      delete[] database;
    }
};
