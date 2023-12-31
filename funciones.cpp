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
    cout<<"8. Mejor camino entre enrutadores. "<<endl;
    cout<<"0. Para finalizar."<<endl;

    cout<<"Ingrese la opcion deseada: "; cin>>x;
    return x;
}

int menuRED(){
    int x=0;

    cout<<"---------- Menue de RED ----------"<<endl;
    cout<<"1. Cargar la red guardada en el archivo txt. "<<endl;
    cout<<"2. Crear la red agregando todos los enrutadores. "<<endl;
    cout<<"3. Generar la red aleatoriamente. "<<endl;

    cout<<"Escoga la opcion deseada: "; cin>>x;

    while((x<1) || (x>3)){
        cout<<"La opcion no es correcta."<<endl;
        cout<<"Escoga una opcion correcta: "; cin>>x;
    }

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

void vertablaRed(map <char,Enrutador> &mR){  //Imprime toda la tabla de la red
    string list = "";
    int l = mR.size();

    map <char, int> fs;
    map <char,Enrutador>::iterator rf;
    map <char, int>::iterator rs;

    for(rf = mR.begin(); rf != mR.end(); rf++) list.push_back(rf->first);           //guarda los identificadores en la lista

    cout<<endl<<' '<<"    ";

    for(rf=mR.begin();rf != mR.end(); rf++) cout<<' '<<rf->first<<"  ";

    cout<<endl;
    cout<<endl;

    for(rf = mR.begin(); rf != mR.end(); rf++){                                    //Ciclo para recorrer el mapa
        cout<<"  "<<rf->first<< "| ";

        fs=rf->second.cos;                                                       //guarda el mapa cos en fs para compararlo
        rs=fs.begin();

        for(int j=0; j<l; j++){                                                  // Recorre las las columnas añadiendo costo

            if(rs->first==list[j]){                                            // Si el edintificador se encuentra, añade costo
                if((rs->second)<10) cout<<' '<<rs->second<<"  ";
                else if(((rs->second)/10)<10)  cout << ' ' << rs->second << " ";
                else if(((rs->second)/100)<10) cout << rs->second << " ";
                rs++;                                                          // aumenta el iterador del mapa fs para recorrelo
            }
            else cout << " -  ";
        }
        cout << endl;
    }
}

void addE_R(map <char,Enrutador> &mR){  //Añadir enlace
    char origen, destino;
    int x, costo=0;
    map <char,Enrutador>::iterator rf;

    cout<<"Ingrese el enrutador de origen: "; cin>>origen;
    cout<<"Ingrese el enrutador de destino: "; cin>>destino;

    x=verifiE_R(mR, origen, destino);                               // Verifica que los enrutadores se encuentren en la red

    if(x==1)    return;
    else if(x==2)   return;
    else if(x==3)   return;
    else cout<<endl;

    rf = mR.find(origen);
    auto r = rf->second.cos.find(destino);  // r se le lleva el valor de costo del mapa del destino si lo tiene.

    if (r != rf->second.cos.end())        // busca si r esta o no en el mapa, si no esta lo agregar.
        cout<<"El enlace "<<origen<<"-"<<destino<<" ya se encuentra establecido. "<<endl;

    else{
        cout<<"Ingrese el costo del nuevo enlace entre "<<origen<<"-"<<destino<<" : "; cin>>costo;
        (mR[origen].cos).insert(pair<char,int >(destino,costo)); //agrega un costo al nuevo enlace entre los 2 enrutadores
        (mR[destino].cos).insert(pair<char,int >(origen,costo));
        cout<<"El enlace "<<origen<<"-"<<destino<<" fue agregado co un costo de: "<<costo<<endl;
    }

}

void editE_R(map <char,Enrutador> &mR){ //Editar el costo de un enlace
    char origen, destino;
    int x, costo=0;
    map <char,Enrutador>::iterator rf;

    cout<<"Ingrese el enrutador de origen: "; cin>>origen;
    cout<<"Ingrese el enrutador de destino: "; cin>>destino;

    x=verifiE_R(mR, origen, destino);                                  //verifica que los enrutadores esten en la red

    if(x==1)    return;
    else if(x==2)   return;
    else if(x==3)   return;
    else cout<<endl;

    rf = mR.find(origen);
    auto r = rf->second.cos.find(destino);

    if (r != rf->second.cos.end()){   // valor del origuen es igual al de destino no esta el enlace
        cout<<"Ingrese el nuevo costo del enlace entre "<<origen<<"-"<<destino<<" : "; cin>>costo;
        mR[origen].editenlace(destino,costo);
        mR[destino].editenlace(origen,costo);
        cout<<endl<<"Se a modificado el costo del enlace "<<origen<<"-"<<destino<<endl;
    }
    else
        cout<<"El enlace "<<origen<<"-"<<destino<<" aun no ce encuentra agregado."<<endl;
}

void deleE_R(map <char,Enrutador> &mR){ //eliminar enlance
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
        (mR[origen].cos).erase(destino);                                          //elimina el enlace
        (mR[destino].cos).erase(origen);
    }
    else
        cout<<"El enlace "<<origen<<"-"<<destino<<" no es posible eliminarlo por que no a sido creado. "<<endl;
}

void addR(map <char,Enrutador> &mR){  //añade enrutador a la red
    char nuevo;
    cout<<endl<<"Ingrese el identificador del router a agregar: "; cin>>nuevo;

    Rou(mR, nuevo);
}

void deleR(map <char,Enrutador> &mR){  // elimina enrutador de la red
    char nombre;
    map <char,Enrutador>::iterator rf;
    map <char, int>::iterator rs;

    cout<<"Ingrese el identificador del enrutador a eliminar: "; cin>>nombre;

    rf = mR.find(nombre);
    if(rf == mR.end()) cout<<"El enrutador "<<nombre<<" no esta en la red.";   //busca si el enrutador no esta a la red

    else{                                                                   // si no llega al final, el enrutador si esta
        mR.erase(nombre);                                                   //elimina enrutador del mapa
        cout<<"El enrutador "<<nombre<<" fue eliminado de la red"<<endl;

        for(rf = mR.begin(); rf != mR.end(); rf++){                  // recorre el mapa para eliminar enlaces con el enrutador
            rs = (rf->second.cos).find(nombre);                      // rs tiene la tabla enrutamimiento del mapa y busca el enrutador

            if(rs != (rf->second.cos).end()) (rf->second.cos).erase(nombre);  // elimina
        }
    }
}

void addRED(map <char,Enrutador> &mR){  // crea red de routers
    int n;
    char nuevo;

    cout<<"Ingrese el numero de Enrutadores para crear la red: "; cin>>n;

    for(int i=1; i<=n; i++){
        cout<<endl<<"Ingrese el identificador del router "<<i<<" a agregar: "; cin>>nuevo;
        Rou(mR, nuevo);
    }
}

void Rou(map <char,Enrutador> &mR, char nuevo){  // verica exixtencia de router y añade a la red

    map <char,Enrutador>::iterator rf;
    Enrutador router;

    rf = mR.find(nuevo);
    if( !(rf == mR.end()) ){                     // si no llega al final, es que lo encontro
        cout<<"El router "<<nuevo<<" ya existe en la red " << endl;
        return;
    }
    else{                                                  // llego al final, no lo encuentra
        mR.insert(pair<char, Enrutador>(nuevo, router));   // añade nuevo objeto en mR con la clave nuevo y valor 'router'
        mR[nuevo].addenlace(nuevo,0);                      // crear enlace, con el mismo de 0

        cout<<"El router "<<nuevo<<" a sido ingresado a la red. "<<endl;
    }
}

int verifiE_R(map <char,Enrutador> &mR, char origen, char destino){  //verifica que los enrutadores existan
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

void Redaleatoria(map <char,Enrutador> &mR){
    map <char,Enrutador>::iterator rf;
    Enrutador ru;
    int nodos,conexiones,costo;
    char nodoEnlace;
    bool ban=1;
    string datos="";
    srand(time(NULL));
    nodos=3+rand()%(9-3);
    char *red= new char[nodos];

    for(int i=0; i < nodos;){                                    // crear cantidad nombres para enrutadores guarda en red
        ban=rand()%2;

        if(ban)nodoEnlace = char(65+rand()%(91-65));
        else nodoEnlace = char(97+rand()%(123-97));

        ban = 1;

        for(int j = 0;j<nodos;j++) if(red[j] == nodoEnlace) ban=0;

        if(ban){
            red[i]=nodoEnlace;
            i++;
        }
    }

    for(int i=0; i<nodos; i++){
        mR.insert(pair<char,Enrutador>(red[i],ru));
        mR[red[i]].addenlace(red[i],0);
    }

    for(rf = mR.begin(); rf != mR.end(); rf++){
        conexiones = 1 + rand()%(nodos-1);

        for(int i=0; i < conexiones; i++){
            nodoEnlace = red[rand()%nodos];
            costo = 1+rand()%(999);

            rf->second.addenlace(nodoEnlace,costo);
            mR[nodoEnlace].addenlace(rf->first,costo);
        }

    }
}

void mejorcamino(map <char,Enrutador> mR){
    map<char,Enrutador>::iterator rf;
    map<char, int>::iterator rs;
    int temp;

    int matriz_1[mR.size()][mR.size()];                             // matriz para costos entre los routers
    int matriz_cop[mR.size()][mR.size()];                           //matriz costos copia para encntrar ruta
    char emi, rec, nodo, matriz_2[mR.size()][mR.size()];           //matriz almacena nodos de la red

    for(int i=0; i<mR.size(); i++){
        rf = mR.begin();
        for(int j=0; j<mR.size(); j++){
            matriz_2[i][j] = rf->first;                           //se asigna el caracter del en la posición j del mapa
            rf++;
        }
    }

    rf = mR.begin();
    for(int i=0; i<mR.size(); i++){
        for(int j=0; j<mR.size(); j++){
            if( (rf->second.cos).find(matriz_2[i][j]) == (rf->second.cos).end() ){   // verifica si el nombre no se encontró
                matriz_1[i][j] =-1;
                matriz_cop[i][j] =-1;}
            else{                                                                // si el nombre se encotro, asigna el costo
                matriz_1[i][j] = (rf->second.cos)[matriz_2[i][j]];
                matriz_cop[i][j] = (rf->second.cos)[matriz_2[i][j]];}
        }
        rf++;
    }

    for(int k=0;k<mR.size();k++){                                    // algoritmo de Floyd-Warshall
        nodo = matriz_2[k][k];
        for(int i=0; i<mR.size(); i++){
            for(int j=0; j<mR.size(); j++){
                if(matriz_1[i][k] >= 0 && matriz_1[k][j] >= 0){
                    temp=matriz_1[i][k]+matriz_1[k][j];
                    if(temp<matriz_cop[i][j] || matriz_cop[i][j]==-1){
                        matriz_cop[i][j] = temp;
                        matriz_2[i][j] = nodo;
                    }
                }
            }
        }
    }

    map <char,int> enl;
    rf=mR.begin();
    for(int i=0;i<mR.size();i++,rf++)
        enl.insert(pair<char,int>(rf->first,i));

    cout<<"Router de origen: "; cin>>emi;
    cout<<"Router de destino: "; cin>>rec;

    if(enl.find(emi)==enl.end() || enl.find(rec)==enl.end()){
        cout<<"El router de origen o destino no existen";
        return;}

    cout<<"El camino optimo para ir de " << emi << " hasta " << rec << " es: ";
    cout << emi << "->";
    temp = enl[rec];
    while(matriz_2[temp][enl[emi]]!=rec && matriz_2[temp][enl[emi]]!=emi){
        cout<<matriz_2[temp][enl[emi]]<<"->";
        temp=enl[matriz_2[temp][enl[emi]]];
    }
    cout<<rec<<" tiene un costo de = "<<matriz_cop[(enl[emi])][(enl[rec])]<<endl;
}





int str2int(string a){
    int b,l,d=1,c=0;                         //Pasa de string a entero
    l=a.length();
    for(int i=l-1;i>=0;i--){
        b=a[i]-48;
        c+=b*d;
        d*=10;
    }
    return c;
}

string int2str(int a){
    int c=0,i=1;                          //convierte entero a string
    char e;
    string b;
    for(;(a/i);i=i*10)                   //ejecuta mientras a sea mayor que i, contar ciffras
        c++;
    for(int j=0;j<c;j++){               //convierte cada cifra a un string y lo agrega a b.
        i/=10;
        e=(a/i)+48;
        b.push_back(e);
        a-=(a/i)*i;
    }
    return b;
}







