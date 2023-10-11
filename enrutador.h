#ifndef ENRUTADOR_H
#define ENRUTADOR_H

using namespace std;

#include <map>
#include <list>
#include <fstream>
#include <stdlib.h>
#include <time.h>

class Enrutador
{
private:
    map <char, int >::iterator r;

public:
    map <char,int > cos;
    bool addenlace(char enlace, int costo);
    bool editenlace(char enlace, int costo_nuevo);
};

#endif // ENRUTADOR_H
