#include "enrutador.h"

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



