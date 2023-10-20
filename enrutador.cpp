#include "enrutador.h"
#include <iostream>
using namespace std;

bool Enrutador::addenlace(char enlace,int costo){
    r = cos.find(enlace);                                                      // buscar si existe un enlance con la clave enlace
    if(r == cos.end()) cos.insert(pair<char,int >(enlace,costo));             // si no esta lo agrega
    return r == cos.end();                                                    // retorna buleano si lo encuentra o no

}

bool Enrutador::editenlace(char enlace, int costo_nuevo){
    r = cos.find(enlace);                                                     // buscar si existe un enlace con la clave enlace
    if(r != cos.end()){                                                       // si se encuentra el enlace
        r->second = costo_nuevo;                                              // editar su costo
        return true;
    }
    return false;
}

void Enrutador::verenrutador(char rut){

    cout <<"Enrutador "<<rut<<", tabla de enrutamiento.  "<<endl<< "  ";

    for(r=cos.begin();r!=cos.end();r++) cout<<' '<<r->first<<"  ";

    cout << endl << rut <<"|";

    for(r=cos.begin() ; r!=cos.end() ; r++){
        if((r->second)<10) cout << ' ' << r->second << "  ";
        else if(((r->second)/10)<10) cout<<' '<<r->second<< " ";
        else if(((r->second)/100)<10) cout<<r->second<<" ";
    }
    cout<<endl;
}
