#include "funciones.h"
#include <iostream>

using namespace std;


int menu(){
    int x;
    cout<<"------------ Menu de opciones ----------"<<endl;
    cout<<"1. Ver tabla general. "<<endl;
    cout<<"2. Ver tabla de un enrutador. "<<endl;
    cout<<"3. Insertar enlace entre enrutadores. "<<endl;
    cout<<"4. Editar enlace entre enrutadores. "<<endl;
    cout<<"5. Eliminar enlace entre enrutadores. "<<endl;
    cout<<"6. Agregar un enrutador a la red. "<<endl;
    cout<<"7. Eliminar un enrutador de la red. "<<endl;
    cout<<"0. Para finalizar."<<endl;

    cout<<"Ingrese la opcion deseada: "; cin>>x;
    return x;
}

int menuRED(){
    int x;

    cout<<"---------- Menue de RED ----------"<<endl;
    cout<<"1. Cargar la red guardada en el archivo txt. "<<endl;
    cout<<"2. Crear la red agregando todos los enrutadores. "<<endl;

    cout<<"Escoga la opcion deseada: "; cin>>x;

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

void addE_R(map <char,Enrutador> &mR){
    char origen, destino;
    int x, costo=0;
    map <char,Enrutador>::iterator rf;

    cout<<"Ingrese el enrutador de origen: "; cin>>origen;
    cout<<"Ingrese el enrutador de destino: "; cin>>destino;

    x=verifiE_R(mR, origen, destino);

    if(x==1)    return;
    else if(x==2)   return;
    else if(x==3)   return;
    else cout<<endl;

    rf = mR.find(origen);
    auto r = rf->second.cos.find(destino);

    if (r != rf->second.cos.end())
        cout<<"El enlace "<<origen<<"-"<<destino<<" ya se encuentra establecido. "<<endl;

    else{
        cout<<"Ingrese el costo del nuevo enlace entre "<<origen<<"-"<<destino<<" : "; cin>>costo;
        (mR[origen].cos).insert(pair<char,int >(destino,costo)); //agrega un costo al nuevo enlace entre los 2 enrutadores
        (mR[destino].cos).insert(pair<char,int >(origen,costo));
        cout<<"El enlace "<<origen<<"-"<<destino<<" fue agregado co un costo de: "<<costo<<endl;
    }

}

void editE_R(map <char,Enrutador> &mR){
    char origen, destino;
    int x, costo=0;
    map <char,Enrutador>::iterator rf;

    cout<<"Ingrese el enrutador de origen: "; cin>>origen;
    cout<<"Ingrese el enrutador de destino: "; cin>>destino;

    x=verifiE_R(mR, origen, destino);

    if(x==1)    return;
    else if(x==2)   return;
    else if(x==3)   return;
    else cout<<endl;

    rf = mR.find(origen);
    auto r = rf->second.cos.find(destino);

    if (r != rf->second.cos.end()){
        cout<<"Ingrese el nuevo costo del enlace entre "<<origen<<"-"<<destino<<" : "; cin>>costo;
        mR[origen].editenlace(destino,costo);
        mR[destino].editenlace(origen,costo);
        cout<<endl<<"Se a modificado el costo del enlace "<<origen<<"-"<<destino<<endl;
    }
    else
        cout<<"El enlace "<<origen<<"-"<<destino<<" aun no ce encuentra agregado."<<endl;
}

void deleE_R(map <char,Enrutador> &mR){
    char origen, destino;
    int x;
    map <char,Enrutador>::iterator rf;

    cout<<"Ingrese el enrutador de origen: "; cin>>origen;
    cout<<"Ingrese el enrutador de destino: "; cin>>destino;

    x=verifiE_R(mR, origen, destino);

    if(x==1)    return;
    else if(x==2)   return;
    else if(x==3)   return;
    else cout<<endl;

    rf = mR.find(origen);
    auto r = rf->second.cos.find(destino);

    if (r != rf->second.cos.end()){
        cout<<"El enlace "<<origen<<"-"<<destino<<" a sido eliminado. "<<endl;
        (mR[origen].cos).erase(destino);
        (mR[destino].cos).erase(origen);
    }
    else
        cout<<"El enlace "<<origen<<"-"<<destino<<" no es posible eliminarlo por que no a sido creado. "<<endl;
}

void addR(map <char,Enrutador> &mR){
    char nuevo;
    cout<<endl<<"Ingrese el identificador del router a agregar: "; cin>>nuevo;

    Rou(mR, nuevo);
}

void deleR(map <char,Enrutador> &mR){
    char nombre;
    map <char,Enrutador>::iterator rf;
    map <char, int>::iterator rs;

    cout<<"Ingrese el identificador del enrutador a eliminar: "; cin>>nombre;

    rf = mR.find(nombre);
    if(rf == mR.end()) cout<<"El enrutador "<<nombre<<" no esta en la red.";

    else{
        mR.erase(nombre);
        cout<<"El enrutador "<<nombre<<" fue eliminado de la red"<<endl;

        for(rf = mR.begin(); rf != mR.end(); rf++){        //  eliminar los enlaces con el enrutador eliminado
            rs = (rf->second.cos).find(nombre);                      // se busca la tabla de enrutamiento de router

            if(rs != (rf->second.cos).end()) (rf->second.cos).erase(nombre);
        }
    }
}

void addRED(map <char,Enrutador> &mR){
    int n;
    char nuevo;

    cout<<"Ingrese el numero de Enrutadores para crear la red: "; cin>>n;

    for(int i=1; i<=n; i++){
        cout<<endl<<"Ingrese el identificador del router "<<i<<" a agregar: "; cin>>nuevo;
        Rou(mR, nuevo);
    }
}

void Rou(map <char,Enrutador> &mR, char nuevo){

    map <char,Enrutador>::iterator rf;
    Enrutador router;

    rf = mR.find(nuevo);
    if( !(rf == mR.end()) ){
        cout<<"El router "<<nuevo<<" ya existe en la red " << endl;
        return;
    }
    else{
        mR.insert(pair<char, Enrutador>(nuevo, router));   // añade nuevo objeto en mR con la clave nuevo y valor 'router'
        mR[nuevo].addenlace(nuevo,0);                      // crear enlace de nuevo con nuevo de costo 0

        cout<<"El router "<<nuevo<<" a sido ingresado a la red. "<<endl;
    }
}

int verifiE_R(map <char,Enrutador> &mR, char origen, char destino){
    int x=0;
    map <char,Enrutador>::iterator rf;

    rf = mR.find(origen);
    if(rf == mR.end()){
        cout<<"El Enrutador "<<origen<<" no existe en la red."<< endl;
        x=1; }

    rf=mR.find(destino);
    if(rf==mR.end()){
        cout<<"El Enrutador "<<destino<<" no existe en la red."<<endl;
        x=2; }

    if(origen==destino){
        cout<<"El enlace "<<origen<<"-"<<destino<<" no es posible."<<endl;
        x=3; }

    return x;
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







