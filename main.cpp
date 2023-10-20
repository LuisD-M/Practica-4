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

    map <char,Enrutador> mR;                                      //Se define el mapa que contiene los ENrutadores
    map <char,Enrutador>::iterator iR;                            // Se define el iterador sobre ese mapa

    opcionred= menuRED();

    if(opcionred==1)
        iniciarenrutador(mR);

    else if(opcionred==2)
        addRED(mR);                                                                   //ya

    else Redaleatoria(mR);


    while(opcion!=0){                                                                  //ya
        cout<<endl;
        opcion = menu();

        if(opcion==1)                                                                   //ya
            vertablaRed(mR);

        else if(opcion==2){
            cout << "Ingrese la letra del enrutador deseado: "; cin >> a;
            cout<<endl;

            iR = mR.find(a);

            if (!(iR==mR.end())) iR->second.verenrutador(a);                           //ya
            else cout << "El enrutador ingresado no esta en la red " << endl;
        }

        else if(opcion==3)                                                              //ya
            addE_R(mR);

        else if(opcion==4)                                                             //ya
            editE_R(mR);

        else if(opcion==5)
            deleE_R(mR);                                                               //ya

        else if(opcion==6)
            addR(mR);                                                                  //ya

        else if(opcion==7)
            deleR(mR);                                                                //ya

        else if(opcion==8)
            mejorcamino(mR);                                                        //ultimo

        else if(opcion==0)
            cout<<"El programa a finalizado."<<endl;

        else cout<<"Opcion incorrecta."<<endl;
    }



}










