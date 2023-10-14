#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "enrutador.h"

using namespace std;

int menu();                   //Meno de usuario

int menuRED();               // Menu de RED

void iniciarenrutador(map <char,Enrutador> &mR);

void vertablaRed(map <char,Enrutador> &mR);

int str2int(string a);                                     //convierte un string a un numero entero

string int2str(int a);                         //convierte un un numero entero a un string

#endif // FUNCIONES_H
