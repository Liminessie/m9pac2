#include <iostream>
#include "./include/sqlite3.h"

using namespace std;

void printMenu(){
    cout << "menu";
}

sqlite3 *DB;



int main(){
    string file = "./base.db";

    int exist = sqlite3_open(file.c_str(), &DB);

    if (exist != SQLITE_OK){
        cout << "Error al abrir la base" << endl;
    }
    else cout << "Conexion correcta";

    sqlite3_close(DB);

    bool menu = true;


    int openDB = sqlite3_open(file.c_str(), &DB);



    return 0;
}
