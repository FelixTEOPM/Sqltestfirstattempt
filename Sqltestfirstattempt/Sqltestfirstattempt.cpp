// Sqltestfirstattempt.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>

using namespace std;

int main() {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;

    // Allocate an environment handle
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    // Allocate a connection handle
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Connect to the database
    ret = SQLConnect(hDbc, (SQLWCHAR*)L"sqlexpress", SQL_NTS, (SQLWCHAR*)L"Username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS);

   if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        cout << "Connected to database successfully." << endl;
    
        // Example of executing a query
        SQLHSTMT hStmt;
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        // Example SELECT query
        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM Empleados", SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            SQLCHAR Nombre[60];
            SQLCHAR Apellido_paterno[60];
            SQLCHAR Apellido_materno[60];
            //int age;
            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 2, SQL_C_CHAR, Nombre, sizeof(Nombre), NULL);
                SQLGetData(hStmt, 3, SQL_C_CHAR, Apellido_paterno, sizeof(Apellido_paterno), NULL);
                SQLGetData(hStmt, 4, SQL_C_CHAR, Apellido_materno, sizeof(Apellido_materno), NULL);
                //SQLGetData(hStmt, 2, SQL_C_LONG, &age, 0, NULL);
                cout << "+--------------------+" << endl;
                cout << "|       Nombre       |" <<  endl;
                cout << "+--------------------+" << endl;
                cout << Nombre << " " << Apellido_paterno << " " << Apellido_materno << endl;
                cout << "+--------------------+" << endl;
                
            }
        }

        // Free statement handle
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }
    else {
        cout << "Failed to connect to database." << endl;
    }

    // Disconnect and free handles
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
