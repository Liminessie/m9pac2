#include <iostream>
#include "./include/sqlite3.h"

using namespace std;

void printMenu(){
    cout << "Menu" << endl;
    cout << "1. Insert an animal and Name." << endl;
    cout << "2. Delete a register." << endl;
    cout << "3. Show databse." << endl;
    cout << "0 To exit" << endl;
    cout << endl;
}

sqlite3 *DB;

void insertAnimal(string& animal, string& name, string file){

    int openDB = sqlite3_open(file.c_str(), &DB);

    string insertion = "INSERT INTO Animals (Animal, Name) VALUES ('"+ animal +"', '"+ name +"');";

    char* errorMsg;

    int result  = sqlite3_exec(DB, insertion.c_str(),NULL, 0, &errorMsg);

    if (result != SQLITE_OK){
        cout << "Error al insertar datos: !" << endl;
        cout << "SQLite Error : " << errorMsg <<endl;
        sqlite3_free(errorMsg);
    }
    else{
        cout << "Inserción realizada!!" << endl;
    }


}


void deleteRegister(int id, string file){

    int openDB = sqlite3_open(file.c_str(), &DB);

    string sentence = "DELETE FROM Animals WHERE Animal_ID =" + to_string(id) + ";";

    char* errorMsg;

    int result  = sqlite3_exec(DB, sentence.c_str(),NULL, 0, &errorMsg);

    if (result != SQLITE_OK){
        cout << "Error al querer eliminar el registro!" << endl;
        cout << "SQLite Error : " << errorMsg <<endl;
        sqlite3_free(errorMsg);
    }
    else{
        cout << "Registro eliminado!!" << endl;
    }
}

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl; // Printing column name and value
    }
    cout << endl;
    return 0;
}

void printAnimals(string file) {
    sqlite3* DB;
    int openDB = sqlite3_open(file.c_str(), &DB);

    if (openDB != SQLITE_OK) {
        cout << "Error al abrir la base de datos!" << endl;
        return;
    }

    string query = "SELECT * FROM Animals;";
    char* errorMsg;

    // Execute SQL query
    int result = sqlite3_exec(DB, query.c_str(), callback, 0, &errorMsg);

    if (result != SQLITE_OK) {
        cout << "Error en la consulta SELECT: " << errorMsg << endl;
        sqlite3_free(errorMsg);
    }

    sqlite3_close(DB);
}


int main(){
    string file = "./base.db";

    int option = 10;
    string animal;
    string name;
    int id;

    int exist = sqlite3_open(file.c_str(), &DB);

    if (exist != SQLITE_OK){
        cout << "Error al abrir la base" << endl;
    }
    else cout << "Conexion correcta" << endl;



    bool menu = true;


    int openDB = sqlite3_open(file.c_str(), &DB);
    //Creating tale if doesn't exists!
    string dbCreation = R"(CREATE TABLE IF NOT EXISTS Animals(
                        Animal_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                        Animal TEXT NOT NULL,
                        Name TEXT);
    )";

    char* errorMsg;
    exist = sqlite3_exec(DB,dbCreation.c_str(),NULL, 0, &errorMsg);

    if (exist != SQLITE_OK){
        cout << "Error, No se ha podido crear la tabla!" << endl;
        cout << "SQLite Error : " << errorMsg <<endl;
        sqlite3_free(errorMsg);
    }
    else{
        cout << "Tabla creada!!" << endl;
    }


    sqlite3_close(DB);



    while (option != 0)
    {
        printMenu();
        cout << "Select an option: ";
        cin >> option; // Inputing option
        cout << endl;

        if (option == 1)
        {
            system("cls");
            cout << "Type the animal that you want to enter: ";
            cin >> animal;
            cout << "Enter the animal's name: ";
            cin >> name;
            insertAnimal(animal, name, file);
        }
        else if (option == 2)
        {
            system("cls");
            cout << "Type de Animal id that you want to delete: ";
            cin >> id;
            deleteRegister(id, file);

        }
        else if(option == 3) printAnimals(file);

        else if(option == 0){
            sqlite3_close(DB);
            cout << "See you! :) ";
        }


        else cout << "Wrong choice!!! 0, 1, 2 or 3 It's too easy!! :v" << endl;
    }

    sqlite3_close(DB);

    return 0;

}
