#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Enrutador{
    private:
        char nombre;                     // A,B,C,D
        vector<int> TablaEnruta;         // Vector para almacenar la tabla enrutamiento.

    public:
        Enrutador(char);
        ~Enrutador();

        char getmombre();
        void addenlace(char,int);
        void cutenlace(char);

        vector<int> getTablaEnruta();




};

Enrutador::Enrutador(char _nombre){
    nombre = _nombre;
    TablaEnruta = vector<int>(10,0);                //10 enrutadores A-J
    TablaEnruta[nombre-'A'] = 0;                    //Costo de llegar a la posicion misma del erutador es cero.
}
Enrutador::~Enrutador(){}

char Enrutador::getmombre(){
    return nombre;
}

void Enrutador::addenlace(char destino, int costo){

    int indice = destino - 'A';                                       // Proporciona la posicion en el vector segun la letra ingresada
    if (indice >= 0 && indice < TablaEnruta.size())                   // Condicion para analizar que el destino es valido entre los
            TablaEnruta[indice] = costo;                              // enrutadores.
    else cout<< "Error: "<<destino<<" no es valido."<<endl;
}

void Enrutador::cutenlace(char enlace){

    int indice = enlace - 'A';
    if (indice >= 0 && indice < TablaEnruta.size())
        TablaEnruta[indice] = 0;                                                 //Se lleva el valor a cero para simular que no hay enlace

    else cout<<"Error : "<<enlace<<" es un enlace no valido"<<endl;
}

vector<int> Enrutador::getTablaEnruta(){
    return TablaEnruta;
}


int main(){



    Enrutador enrutadorA('A');
    const vector<int> tablaini = enrutadorA.getTablaEnruta();

    cout<<"El enrutador "<<enrutadorA.getmombre()<<" a sido ingresado"<<endl;

    cout<<"La tabla inicial del enrutador A es: "<<endl;
    for(int i=0; i<tablaini.size(); i++)
        cout<<static_cast<char>('A'+i)<<":"<<tablaini[i]<<"  ";

    enrutadorA.addenlace('B',5);                                      // Actualiza la tabla de enrutamiento con el enlace B.
    const vector<int> tablaactua = enrutadorA.getTablaEnruta();

    cout<<endl;
    cout<<"La tabla actualizada del enrutador A es:"<<endl;
    for(int i=0; i<tablaactua.size(); i++)
        cout<<static_cast<char>('A'+i)<<":"<<tablaactua[i]<<"  ";

    enrutadorA.cutenlace('B');
    const vector<int> tablaactua1 = enrutadorA.getTablaEnruta();
    cout<<endl;
    cout<<"La tabla actualizada del enrutador A es:"<<endl;
    for(int i=0; i<tablaactua1.size(); i++)
        cout<<static_cast<char>('A'+i)<<":"<<tablaactua1[i]<<"  ";


}
