/*
Administrador de notas estudiantiles (nombre provisional)
Alejandro Pedro Steinman Cuesta - T00077151
Andres Rubiano Marrugo - T000
*/
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
// Main
int main(){
  return 0;
}
