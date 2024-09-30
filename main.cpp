#include <iostream>
#include "./include/sqlite3.h"

sqlite3* DB;

using namespace std;

int main(){
    string file = "./base.db";

    int exist = sqlite3_open(file.c_str(), &DB);

    if (exist != SQLITE_OK){
        cout << "Error al abrir la base" << endl;
    }
    else cout << "Conexion correcta";

    sqlite3_close(DB);
    
    return 0;
}