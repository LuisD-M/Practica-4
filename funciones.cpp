#include "funciones.h"
#include <iostream>

using namespace std;


int menu(){
    int x;
    cout<<"------------ Menu de opciones ----------"<<endl;
    cout<<"1. Modelar una red."<<endl;
    cout<<"2. Agregar enlaces "<<endl;
    cout<<"0. Para finalizar."<<endl;

    cout<<"Ingrese la opcion deseada: "; cin>>x;
    cout<<endl;
    return x;
}
