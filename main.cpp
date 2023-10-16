#include "enrutador.h"
#include "funciones.h"

#include <iostream>
#include <map>
#include <list>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;


int main(){
    int opcion=1, opcionred;
    char a;

    map <char,Enrutador> mR;              // ff             //Se define el mapa que contiene los routers mR
    map <char,Enrutador>::iterator iR;    //rf             // Se define el iterador sobre ese mapa IR

    opcionred= menuRED();

    if(opcionred==1)
        iniciarenrutador(mR);

    else if(opcionred==2)
        addRED(mR);

    else Redaleatoria(mR);


    while(opcion!=0){
        cout<<endl;
        opcion = menu();

        if(opcion==1)
            vertablaRed(mR);

        else if(opcion==2){
            cout << "Ingrese la letra del enrutador deseado: "; cin >> a;
            cout<<endl;

            iR = mR.find(a);

            if (!(iR==mR.end())) iR->second.verenrutador(a);
            else cout << "El enrutador ingresado no esta en la red " << endl;
        }

        else if(opcion==3)
            addE_R(mR);

        else if(opcion==4)
            editE_R(mR);

        else if(opcion==5)
            deleE_R(mR);

        else if(opcion==6)
            addR(mR);

        else if(opcion==7)
            deleR(mR);

        else if(opcion==8)
            mejorcamino(mR);

        else if(opcion==0)
            cout<<"El programa a finalizado."<<endl;

        else cout<<"Opcion incorrecta."<<endl;
    }



}










