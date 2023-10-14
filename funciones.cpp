#include "funciones.h"
#include <iostream>

using namespace std;


int menu(){
    int x;
    cout<<"------------ Menu de opciones ----------"<<endl;
    cout<<"1. Ver tabla General. "<<endl;
    cout<<"2. Ver tabla de un Enrutador. "<<endl;
    cout<<"0. Para finalizar."<<endl;

    cout<<"Ingrese la opcion deseada: "; cin>>x;
    cout<<endl;
    return x;
}

int menuRED(){
    int x;

    cout<<"---------- Menue de RED ----------"<<endl;
    cout << " 1. Cargar la red guardada en el archivo txt. " << endl;

    cout << " Escoga la opcion deseada: "; cin>>x;
    cout<<endl;

    return x;
}

void iniciarenrutador(map <char,Enrutador> &mR){
    char enlaces[2];
    char s;
    bool ban = false;
    string txt, co;
    long int costo;

    int l=1,j=0;
    Enrutador ru;

    // leer el archivo
    // Almacenar en el string txt toda la informacion contenida en red.txt
    fstream archivo("red.txt", ios::in);

    for(int i=0 ; !archivo.eof() ; i++){
        archivo.get(s);
        txt.push_back(s);
    }


    txt.pop_back(); // eliminar el ultimo caracter
    archivo.close();

    for (int i=0; i < txt.length() ; i++) if(txt[i]=='\n') l++; // contar las lineas del archivo

    map <char,Enrutador>::iterator rf;
    map <char,Enrutador>::iterator rs;

    for(int i=0 ; i<l ; i++){

        // leer la informacion del enlace y el costo
        // Extraer informacion de la linea i, entre dos enrutadores y el costo del enlace entre los dos enrutadores

        for( ; txt[j] != '\n' && j < txt.length() ; j++){
            if((int(txt[j]) >= 65 && int(txt[j]) <= 90)||(int(txt[j]) >= 97 && int(txt[j]) <= 122)){ // Es una letra
                enlaces[ban] = txt[j];  // guardar la informacion en el arreglo en
                ban=!ban;
            }
            else if(int(txt[j]) >= 48 && int(txt[j]) <= 57) co.push_back(txt[j]); // agregar el costo al string co
        }

        j++;
        costo = str2int(co);
        co = "";
        rf = mR.find(enlaces[0]);
        rs = mR.find(enlaces[1]);

        // verificar si el Enrutador enlaces[0] existe en mR
        if(rf == mR.end()){
            mR.insert(pair<char,Enrutador>(enlaces[0],ru));
            mR[enlaces[0]].addenlace(enlaces[0],0);
            mR[enlaces[0]].addenlace(enlaces[1],costo);
        }
        else mR[enlaces[0]].addenlace(enlaces[1],costo);

        // verificar si el Enrutador enlaces[1] existe en mR
        if(rs == mR.end()){
            mR.insert(pair<char,Enrutador>(enlaces[1],ru));
            mR[enlaces[1]].addenlace(enlaces[1],0);
            mR[enlaces[1]].addenlace(enlaces[0],costo);
        }
        else mR[enlaces[1]].addenlace(enlaces[0],costo);
    }

}

void vertablaRed(map <char,Enrutador> &mR){
    string list = "";
    int l = mR.size();

    map <char, int> fs;
    map <char,Enrutador>::iterator rf;
    map <char, int>::iterator rs;

    for(rf = mR.begin(); rf != mR.end(); rf++) list.push_back(rf->first);

    cout << endl << ' ' << "    ";

    for(rf=mR.begin();rf != mR.end(); rf++) cout<<' ' << rf->first << "  ";

    cout << endl;
    cout<<endl;

    for(rf = mR.begin(); rf != mR.end(); rf++){
        cout << "  " << rf->first << "| ";

        fs=rf->second.cos;
        rs=fs.begin();

        for(int j=0; j<l; j++){

            if(rs->first==list[j]){
                if((rs->second)<10) cout<<' '<<rs->second<<"  ";
                else if(((rs->second)/10)<10)  cout << ' ' << rs->second << " ";
                else if(((rs->second)/100)<10) cout << rs->second << " ";
                rs++;
            }
            else cout << " -  ";
        }
        cout << endl;
    }
}









int str2int(string a){
    int b,l,d=1,c=0;
    l=a.length();
    for(int i=l-1;i>=0;i--){
        b=a[i]-48;
        c+=b*d;
        d*=10;
    }
    return c;
}

string int2str(int a){
    int c=0,i=1;
    char e;
    string b;
    for(;(a/i);i=i*10)
        c++;
    for(int j=0;j<c;j++){
        i/=10;
        e=(a/i)+48;
        b.push_back(e);
        a-=(a/i)*i;
    }
    return b;
}







